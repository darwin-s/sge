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
#include <GLFW/glfw3.h>

namespace {
sge::EventHandler defaultHandler;
}

namespace sge {
Window::Window(const ContextSettings contextSettings) : m_context(contextSettings), m_eventHandler(&defaultHandler) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowTitle(win, "SGE");
    glfwSetWindowSize(win, 100, 100);
    setCallbacks();
}

Window::Window(const std::string_view title, const ContextSettings contextSettings)
    : m_context(contextSettings), m_eventHandler(&defaultHandler) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowTitle(win, title.data());
    glfwSetWindowSize(win, 100, 100);
    setCallbacks();
}

Window::Window(const std::string_view title, const Vector2I size, const ContextSettings contextSettings)
    : m_context(contextSettings), m_eventHandler(&defaultHandler) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowTitle(win, title.data());
    glfwSetWindowSize(win, size.x, size.y);
    setCallbacks();
}

Window::Window(const std::string_view title, const Monitor::VideoMode videoMode, const Monitor& monitor,
               const ContextSettings contextSettings)
    : m_context(contextSettings), m_eventHandler(&defaultHandler) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowTitle(win, title.data());
    glfwSetWindowSize(win, videoMode.width, videoMode.height);
    glfwSetWindowMonitor(win, static_cast<GLFWmonitor*>(monitor.m_handle), 0, 0, videoMode.width, videoMode.height,
                         videoMode.refreshRate);
    setCallbacks();
}

Window::~Window() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    m_eventHandler = &defaultHandler;
    glfwSetWindowShouldClose(win, GLFW_TRUE);
}

void Window::show() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwShowWindow(win);
}

bool Window::isOpen() const {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    return glfwWindowShouldClose(win) == GLFW_FALSE;
}

const Context& Window::getContext() const {
    return m_context;
}

Context& Window::getContext() {
    return m_context;
}

void Window::setEventHandler(EventHandler& handler) {
    m_eventHandler = &handler;
}

void Window::setDefaultEventHandler() {
    m_eventHandler = &defaultHandler;
}

void Window::processEvents() {
    glfwPollEvents();
}

void Window::setTitle(const std::string_view title) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowTitle(win, title.data());
}

void Window::setPosition(const Vector2I pos) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowPos(win, pos.x, pos.y);
}

void Window::setSize(const Vector2I size) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowSize(win, size.x, size.y);
}

void Window::enableFullscreen(const Monitor::VideoMode videoMode, const Monitor& monitor) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);
    auto* active = Context::getCurrentContext();

    glfwSetWindowMonitor(win, static_cast<GLFWmonitor*>(monitor.m_handle), 0, 0, videoMode.width, videoMode.height,
                         videoMode.refreshRate);
    m_context.setCurrent(true);
    if (!m_context.getContextSettings().vsync) {
        glfwSwapInterval(0);
    } else {
        glfwSwapInterval(1);
    }
    m_context.setCurrent(false);
    if (active != nullptr) {
        active->setCurrent(true);
    }
}

void Window::disableFullscreen() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);
    auto* active = Context::getCurrentContext();

    glfwSetWindowMonitor(win, NULL, 50, 50, 100, 100, 0);
    glfwSetWindowAttrib(win, GLFW_DECORATED, GLFW_TRUE);
    m_context.setCurrent(true);
    if (!m_context.getContextSettings().vsync) {
        glfwSwapInterval(0);
    } else {
        glfwSwapInterval(1);
    }
    m_context.setCurrent(false);
    if (active != nullptr) {
        active->setCurrent(true);
    }
}

void Window::setSizeLimits(const Vector2I minSize, const Vector2I maxSize) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowSizeLimits(win, minSize.x, minSize.y, maxSize.x, maxSize.y);
}

void Window::setAspectRatio(const int numer, const int denom) {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowAspectRatio(win, numer, denom);
}

void Window::minimize() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwIconifyWindow(win);
}

void Window::maximize() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwMaximizeWindow(win);
}

void Window::restore() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwRestoreWindow(win);
}

void Window::requestAttention() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwRequestWindowAttention(win);
}

void Window::enableRawInput() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void Window::disableRawInput() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
}

void Window::disableCursor() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::hideCursor() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::enableCursor() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::swapBuffers() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSwapBuffers(win);
}

void Window::preventClosing() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowShouldClose(win, GLFW_FALSE);
}

void Window::close() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowShouldClose(win, GLFW_TRUE);
}

Vector2I Window::getPosition() const {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);
    Vector2I ret;

    glfwGetWindowPos(win, &ret.x, &ret.y);

    return ret;
}

Vector2I Window::getSize() const {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);
    Vector2I ret;

    glfwGetWindowSize(win, &ret.x, &ret.y);

    return ret;
}

Vector2I Window::getFramebufferSize() const {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);
    Vector2I ret;

    glfwGetFramebufferSize(win, &ret.x, &ret.y);

    return ret;
}

Vector2F Window::getContentScale() const {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);
    Vector2F ret;

    glfwGetWindowContentScale(win, &ret.x, &ret.y);

    return ret;
}

void Window::setCallbacks() {
    auto* win = static_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowCloseCallback(win, reinterpret_cast<GLFWwindowclosefun>(closeCallback));
    glfwSetWindowSizeCallback(win, reinterpret_cast<GLFWwindowsizefun>(resizeCallback));
    glfwSetFramebufferSizeCallback(win, reinterpret_cast<GLFWframebuffersizefun>(framebufferResizeCallback));
    glfwSetWindowContentScaleCallback(win, reinterpret_cast<GLFWwindowcontentscalefun>(contentScaleCallback));
    glfwSetWindowPosCallback(win, reinterpret_cast<GLFWwindowposfun>(positionCallback));
    glfwSetWindowIconifyCallback(win, reinterpret_cast<GLFWwindowiconifyfun>(minimizeCallback));
    glfwSetWindowMaximizeCallback(win, reinterpret_cast<GLFWwindowmaximizefun>(maximizeCallback));
    glfwSetWindowFocusCallback(win, reinterpret_cast<GLFWwindowfocusfun>(focusCallback));
    glfwSetWindowRefreshCallback(win, reinterpret_cast<GLFWwindowrefreshfun>(refreshCallback));
    glfwSetKeyCallback(win, reinterpret_cast<GLFWkeyfun>(keyboardCallback));
    glfwSetCharCallback(win, reinterpret_cast<GLFWcharfun>(textInputCallback));
    glfwSetCursorPosCallback(win, reinterpret_cast<GLFWcursorposfun>(cursorPositionCallback));
    glfwSetCursorEnterCallback(win, reinterpret_cast<GLFWcursorenterfun>(cursorEnterCallback));
    glfwSetMouseButtonCallback(win, reinterpret_cast<GLFWmousebuttonfun>(mouseButtonCallback));
    glfwSetScrollCallback(win, reinterpret_cast<GLFWscrollfun>(scrollCallback));
}

void Window::closeCallback(void* window) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowCloseEvent();
}

void Window::resizeCallback(void* window, const int width, const int height) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowResizeEvent(Vector2I(width, height));
}

void Window::framebufferResizeCallback(void* window, const int width, const int height) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowFramebufferResizeEvent(Vector2I(width, height));
}

void Window::contentScaleCallback(void* window, const float xScale, const float yScale) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowContentScaleEvent(Vector2F(xScale, yScale));
}

void Window::positionCallback(void* window, const int xPos, const int yPos) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowPositionEvent(Vector2I(xPos, yPos));
}

void Window::minimizeCallback(void* window, const int minimized) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    if (minimized != 0) {
        win->m_eventHandler->windowMinimizeEvent();
    } else {
        win->m_eventHandler->windowUnminimizeEvent();
    }
}

void Window::maximizeCallback(void* window, const int maximized) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    if (maximized != 0) {
        win->m_eventHandler->windowMaximizeEvent();
    } else {
        win->m_eventHandler->windowUnmaximizeEvent();
    }
}

void Window::focusCallback(void* window, const int focused) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    if (focused != 0) {
        win->m_eventHandler->windowGainedFocusEvent();
    } else {
        win->m_eventHandler->windowLostFocusEvent();
    }
}

void Window::refreshCallback(void* window) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowRefreshEvent();
}

void Window::keyboardCallback(void* window, const int key, const int scancode, const int action, const int mods) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));
    Keyboard::KeyboardEvent kbe{};

    kbe.key = Keyboard::getKeyFromInternal(key);
    if (action == GLFW_PRESS) {
        kbe.state = Keyboard::KeyState::Pressed;
    } else if (action == GLFW_REPEAT) {
        kbe.state = Keyboard::KeyState::Repeating;
    } else {
        kbe.state = Keyboard::KeyState::Released;
    }
    kbe.scancode = scancode;
    kbe.ctrl = (mods & GLFW_MOD_CONTROL) != 0;
    kbe.shift = (mods & GLFW_MOD_SHIFT) != 0;
    kbe.alt = (mods & GLFW_MOD_ALT) != 0;
    kbe.system = (mods & GLFW_MOD_SUPER) != 0;
    kbe.capsLock = (mods & GLFW_MOD_CAPS_LOCK) != 0;
    kbe.numLock = (mods & GLFW_MOD_NUM_LOCK) != 0;

    win->m_eventHandler->keyboardEvent(kbe);
}

void Window::textInputCallback(void* window, const unsigned int codePoint) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->textInputEvent(codePoint);
}

void Window::cursorPositionCallback(void* window, const double xPos, const double yPos) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->cursorPositionEvent(Vector2D(xPos, yPos));
}

void Window::cursorEnterCallback(void* window, const int entered) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    if (entered != 0) {
        win->m_eventHandler->cursorEnterEvent();
    } else {
        win->m_eventHandler->cursorLeaveEvent();
    }
}

void Window::mouseButtonCallback(void* window, const int button, const int action, const int mods) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));
    Mouse::MouseButtonEvent mbe{};

    mbe.button = Mouse::getButtonFromInternal(button);
    if (action == GLFW_PRESS) {
        mbe.state = Mouse::ButtonState::Pressed;
    } else {
        mbe.state = Mouse::ButtonState::Released;
    }

    mbe.ctrl = (mods & GLFW_MOD_CONTROL) != 0;
    mbe.shift = (mods & GLFW_MOD_SHIFT) != 0;
    mbe.alt = (mods & GLFW_MOD_ALT) != 0;
    mbe.system = (mods & GLFW_MOD_SUPER) != 0;
    mbe.capsLock = (mods & GLFW_MOD_CAPS_LOCK) != 0;
    mbe.numLock = (mods & GLFW_MOD_NUM_LOCK) != 0;

    win->m_eventHandler->mouseButtonEvent(mbe);
}

void Window::scrollCallback(void* window, const double xOffset, const double yOffset) {
    auto* handle = static_cast<GLFWwindow*>(window);
    auto* win = static_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->scrollEvent(Vector2D(xOffset, yOffset));
}
}
