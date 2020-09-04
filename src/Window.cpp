// Copyright 2020 Dan Sirbu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <SGE/Window.hpp>
#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace {
sge::EventHandler defaultHandler;
}

namespace sge {
Window::Window()
    : m_handle(nullptr), m_eventHandler(&defaultHandler), m_open(false) {
    m_handle = SDL_CreateWindow("Untitled",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                100,
                                100,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN |
                                    SDL_WINDOW_RESIZABLE);
    SDL_SetWindowData(static_cast<SDL_Window*>(m_handle), "win", this);
}

Window::Window(const std::string_view title)
    : m_handle(nullptr), m_eventHandler(&defaultHandler), m_open(false) {
    m_handle = SDL_CreateWindow(title.data(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                100,
                                100,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN |
                                    SDL_WINDOW_RESIZABLE);
    SDL_SetWindowData(static_cast<SDL_Window*>(m_handle), "win", this);
}

Window::Window(const std::string_view title, const glm::ivec2& size)
    : m_handle(nullptr), m_eventHandler(&defaultHandler), m_open(false) {
    m_handle = SDL_CreateWindow(title.data(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                size.x,
                                size.y,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN |
                                    SDL_WINDOW_RESIZABLE);
    SDL_SetWindowData(static_cast<SDL_Window*>(m_handle), "win", this);
}

Window::Window(const std::string_view title,
               const Monitor::VideoMode& videoMode)
    : m_handle(nullptr), m_eventHandler(&defaultHandler), m_open(false) {
    m_handle = SDL_CreateWindow(title.data(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                100,
                                100,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN |
                                    SDL_WINDOW_RESIZABLE);
    SDL_SetWindowData(static_cast<SDL_Window*>(m_handle), "win", this);
    enableFullscreen(videoMode);
}

Window::~Window() {
    if (m_open) {
        m_eventHandler->windowCloseEvent();
    }

    m_eventHandler = &defaultHandler;
    SDL_DestroyWindow(static_cast<SDL_Window*>(m_handle));
}

void Window::show() {
    SDL_ShowWindow(static_cast<SDL_Window*>(m_handle));
    m_open = true;
}

bool Window::isOpen() const {
    return m_open;
}

void Window::setEventHandler(EventHandler& handler) {
    m_eventHandler = &handler;
}

void Window::setDefaultEventHandler() {
    m_eventHandler = &defaultHandler;
}

void Window::processEvents() {
    SDL_PumpEvents();
    SDL_FilterEvents(reinterpret_cast<SDL_EventFilter>(eventFilter), this);
}

void Window::setTitle(const std::string_view title) {
    SDL_SetWindowTitle(static_cast<SDL_Window*>(m_handle), title.data());
}

void Window::setPosition(const glm::ivec2& pos) {
    SDL_SetWindowPosition(static_cast<SDL_Window*>(m_handle), pos.x, pos.y);
}

void Window::setSize(const glm::ivec2& size) {
    SDL_SetWindowSize(static_cast<SDL_Window*>(m_handle), size.x, size.y);
}

void Window::enableFullscreen(const Monitor::VideoMode& videoMode) {
    SDL_DisplayMode mode;
    SDL_GetWindowDisplayMode(static_cast<SDL_Window*>(m_handle), &mode);
    mode.w            = videoMode.width;
    mode.h            = videoMode.height;
    mode.refresh_rate = videoMode.refreshRate;
    SDL_SetWindowDisplayMode(static_cast<SDL_Window*>(m_handle), &mode);
    SDL_SetWindowFullscreen(static_cast<SDL_Window*>(m_handle),
                            SDL_WINDOW_FULLSCREEN);
}

void Window::disableFullscreen() {
    SDL_SetWindowFullscreen(static_cast<SDL_Window*>(m_handle), 0);
}

void Window::minimize() {
    SDL_MinimizeWindow(static_cast<SDL_Window*>(m_handle));
}

void Window::maximize() {
    SDL_MaximizeWindow(static_cast<SDL_Window*>(m_handle));
}

void Window::restore() {
    SDL_RestoreWindow(static_cast<SDL_Window*>(m_handle));
}

void Window::close() {
    m_open = false;
}

glm::ivec2 Window::getPosition() const {
    glm::ivec2 ret;

    SDL_GetWindowPosition(static_cast<SDL_Window*>(m_handle), &ret.x, &ret.y);

    return ret;
}

glm::ivec2 Window::getSize() const {
    glm::ivec2 ret;

    SDL_GetWindowSize(static_cast<SDL_Window*>(m_handle), &ret.x, &ret.y);

    return ret;
}

void* Window::getHandle() const {
    return m_handle;
}

int Window::eventFilter(void* userdata, void* event) {
    auto* caller = static_cast<Window*>(userdata);
    auto* ev     = static_cast<SDL_Event*>(event);

    if (ev->type == SDL_WINDOWEVENT) {
        auto* win = SDL_GetWindowFromID(ev->window.windowID);
        auto* w   = static_cast<Window*>(SDL_GetWindowData(win, "win"));

        if (w == nullptr) {
            return 0;
        } else if (w != caller) {
            return 1;
        }

        switch (ev->window.event) {
        case SDL_WINDOWEVENT_EXPOSED:
            w->m_eventHandler->windowRefreshEvent();
            break;
        case SDL_WINDOWEVENT_MOVED:
            w->m_eventHandler->windowPositionEvent(
                {ev->window.data1, ev->window.data2});
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            w->m_eventHandler->windowResizeEvent(
                {ev->window.data1, ev->window.data2});
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            w->m_eventHandler->windowMinimizeEvent();
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            w->m_eventHandler->windowMaximizeEvent();
            break;
        case SDL_WINDOWEVENT_RESTORED:
            w->m_eventHandler->windowRestoredEvent();
            break;
        case SDL_WINDOWEVENT_ENTER:
            w->m_eventHandler->cursorEnterEvent();
            break;
        case SDL_WINDOWEVENT_LEAVE:
            w->m_eventHandler->cursorLeaveEvent();
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            w->m_eventHandler->windowGainedFocusEvent();
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            w->m_eventHandler->windowLostFocusEvent();
            break;
        case SDL_WINDOWEVENT_CLOSE:
            w->m_eventHandler->windowCloseEvent();
            break;
        }
    } else if (ev->type == SDL_KEYUP) {
        auto* win = SDL_GetWindowFromID(ev->key.windowID);
        auto* w   = static_cast<Window*>(SDL_GetWindowData(win, "win"));

        if (w == nullptr) {
            return 0;
        } else if (w != caller) {
            return 1;
        }

        Keyboard::KeyboardEvent e{};
        e.key      = Keyboard::getKeyFromInternal(ev->key.keysym.sym);
        e.state    = Keyboard::KeyState::Released;
        e.scancode = ev->key.keysym.scancode;
        e.ctrl     = (ev->key.keysym.mod & KMOD_CTRL) != 0;
        e.shift    = (ev->key.keysym.mod & KMOD_SHIFT) != 0;
        e.alt      = (ev->key.keysym.mod & KMOD_ALT) != 0;
        e.system   = (ev->key.keysym.mod & KMOD_GUI) != 0;
        e.capsLock = (ev->key.keysym.mod & KMOD_CAPS) != 0;
        e.numLock  = (ev->key.keysym.mod & KMOD_NUM) != 0;

        w->m_eventHandler->keyboardEvent(e);
    } else if (ev->type == SDL_KEYDOWN) {
        auto* win = SDL_GetWindowFromID(ev->key.windowID);
        auto* w   = static_cast<Window*>(SDL_GetWindowData(win, "win"));

        if (w == nullptr) {
            return 0;
        } else if (w != caller) {
            return 1;
        }

        Keyboard::KeyboardEvent e{};
        e.key = Keyboard::getKeyFromInternal(ev->key.keysym.sym);
        if (ev->key.repeat != 0) {
            e.state = Keyboard::KeyState::Repeating;
        } else {
            e.state = Keyboard::KeyState::Pressed;
        }
        e.scancode = ev->key.keysym.scancode;
        e.ctrl     = (ev->key.keysym.mod & KMOD_CTRL) != 0;
        e.shift    = (ev->key.keysym.mod & KMOD_SHIFT) != 0;
        e.alt      = (ev->key.keysym.mod & KMOD_ALT) != 0;
        e.system   = (ev->key.keysym.mod & KMOD_GUI) != 0;
        e.capsLock = (ev->key.keysym.mod & KMOD_CAPS) != 0;
        e.numLock  = (ev->key.keysym.mod & KMOD_NUM) != 0;

        w->m_eventHandler->keyboardEvent(e);
    } else if (ev->type == SDL_TEXTINPUT) {
        auto* win = SDL_GetWindowFromID(ev->text.windowID);
        auto* w   = static_cast<Window*>(SDL_GetWindowData(win, "win"));

        if (w == nullptr) {
            return 0;
        } else if (w != caller) {
            return 1;
        }

        w->m_eventHandler->textInputEvent(ev->text.text);
    } else if (ev->type == SDL_MOUSEMOTION) {
        auto* win = SDL_GetWindowFromID(ev->motion.windowID);
        auto* w   = static_cast<Window*>(SDL_GetWindowData(win, "win"));

        if (w == nullptr) {
            return 0;
        } else if (w != caller) {
            return 1;
        }

        if (!Mouse::isInRelativeMode()) {
            w->m_eventHandler->cursorPositionEvent(
                {ev->motion.x, ev->motion.y});
        } else {
            w->m_eventHandler->cursorPositionEvent(
                {ev->motion.xrel, ev->motion.yrel});
        }
    } else if (ev->type == SDL_MOUSEBUTTONUP) {
        auto* win = SDL_GetWindowFromID(ev->button.windowID);
        auto* w   = static_cast<Window*>(SDL_GetWindowData(win, "win"));

        if (w == nullptr) {
            return 0;
        } else if (w != caller) {
            return 1;
        }

        const auto mod = SDL_GetModState();

        Mouse::MouseButtonEvent e{};
        e.button   = Mouse::getButtonFromInternal(ev->button.button);
        e.state    = Mouse::ButtonState::Released;
        e.ctrl     = (mod & KMOD_CTRL) != 0;
        e.shift    = (mod & KMOD_SHIFT) != 0;
        e.alt      = (mod & KMOD_ALT) != 0;
        e.system   = (mod & KMOD_GUI) != 0;
        e.capsLock = (mod & KMOD_CAPS) != 0;
        e.numLock  = (mod & KMOD_NUM) != 0;

        w->m_eventHandler->mouseButtonEvent(e);
    } else if (ev->type == SDL_MOUSEBUTTONDOWN) {
        auto* win = SDL_GetWindowFromID(ev->button.windowID);
        auto* w   = static_cast<Window*>(SDL_GetWindowData(win, "win"));

        if (w == nullptr) {
            return 0;
        } else if (w != caller) {
            return 1;
        }

        const auto mod = SDL_GetModState();

        Mouse::MouseButtonEvent e{};
        e.button   = Mouse::getButtonFromInternal(ev->button.button);
        e.state    = Mouse::ButtonState::Pressed;
        e.ctrl     = (mod & KMOD_CTRL) != 0;
        e.shift    = (mod & KMOD_SHIFT) != 0;
        e.alt      = (mod & KMOD_ALT) != 0;
        e.system   = (mod & KMOD_GUI) != 0;
        e.capsLock = (mod & KMOD_CAPS) != 0;
        e.numLock  = (mod & KMOD_NUM) != 0;

        w->m_eventHandler->mouseButtonEvent(e);
    } else if (ev->type == SDL_MOUSEWHEEL) {
        auto* win = SDL_GetWindowFromID(ev->wheel.windowID);
        auto* w   = static_cast<Window*>(SDL_GetWindowData(win, "win"));

        if (w == nullptr) {
            return 0;
        } else if (w != caller) {
            return 1;
        }

        w->m_eventHandler->scrollEvent({ev->wheel.x, ev->wheel.y});
    }

    return 0;
}
}
