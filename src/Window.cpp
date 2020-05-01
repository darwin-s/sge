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
Window::Window(ContextSettings contextSettings)
    : m_context(contextSettings), m_eventHandler(&defaultHandler) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowTitle(win, "SGE");
    glfwSetWindowSize(win, 100, 100);
    setCallbacks();
}

Window::Window(std::string_view title, ContextSettings contextSettings)
    : m_context(contextSettings), m_eventHandler(&defaultHandler) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowTitle(win, title.data());
    glfwSetWindowSize(win, 100, 100);
    setCallbacks();
}

Window::Window(std::string_view title, Vector2I size, ContextSettings contextSettings)
    : m_context(contextSettings), m_eventHandler(&defaultHandler) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowTitle(win, title.data());
    glfwSetWindowSize(win, size.x, size.y);
    setCallbacks();
}

Window::Window(std::string_view title, Monitor::VideoMode videoMode, const Monitor& monitor,
               ContextSettings contextSettings)
    : m_context(contextSettings), m_eventHandler(&defaultHandler) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowUserPointer(win, this);
    glfwSetWindowTitle(win, title.data());
    glfwSetWindowSize(win, videoMode.width, videoMode.height);
    glfwSetWindowMonitor(win, reinterpret_cast<GLFWmonitor*>(monitor.m_handle), 0, 0,
                         videoMode.width, videoMode.height, videoMode.refreshRate);
    setCallbacks();
}

Window::~Window() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    m_eventHandler = &defaultHandler;
    glfwSetWindowShouldClose(win, GLFW_TRUE);
}

void Window::show() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwShowWindow(win);
}

bool Window::isOpen() const {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

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

void Window::setTitle(std::string_view title) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowTitle(win, title.data());
}

void Window::setPosition(Vector2I pos) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowPos(win, pos.x, pos.y);
}

void Window::setSize(Vector2I size) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowSize(win, size.x, size.y);
}

void Window::enableFullscreen(Monitor::VideoMode videoMode, const Monitor& monitor) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowMonitor(win, reinterpret_cast<GLFWmonitor*>(monitor.m_handle), 0, 0,
                         videoMode.width, videoMode.height, videoMode.refreshRate);
}

void Window::disableFullscreen() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowMonitor(win, NULL, 50, 50, 100, 100, 0);
    glfwSetWindowAttrib(win, GLFW_DECORATED, GLFW_TRUE);
}

void Window::setSizeLimits(Vector2I minSize, Vector2I maxSize) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowSizeLimits(win, minSize.x, minSize.y, maxSize.x, maxSize.y);
}

void Window::setAspectRatio(int numer, int denom) {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowAspectRatio(win, numer, denom);
}

void Window::minimize() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwIconifyWindow(win);
}

void Window::maximize() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwMaximizeWindow(win);
}

void Window::restore() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwRestoreWindow(win);
}

void Window::requestAttention() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwRequestWindowAttention(win);
}

void Window::enableRawInput() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

void Window::disableRawInput() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
}

void Window::disableCursor() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::hideCursor() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::enableCursor() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::swapBuffers() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);
    Context* active = Context::getCurrentContext();

    m_context.setCurrent(true);
    if (!m_context.getContextSettings().vsync) {
        glfwSwapInterval(0);
    } else {
        glfwSwapInterval(1);
    }
    glfwSwapBuffers(win);
    m_context.setCurrent(false);
    if (active) {
        active->setCurrent(true);
    }
}

void Window::preventClosing() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowShouldClose(win, GLFW_FALSE);
}

void Window::close() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

    glfwSetWindowShouldClose(win, GLFW_TRUE);
}

Vector2I Window::getPosition() const {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);
    Vector2I ret;

    glfwGetWindowPos(win, &ret.x, &ret.y);

    return ret;
}

Vector2I Window::getSize() const {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);
    Vector2I ret;

    glfwGetWindowSize(win, &ret.x, &ret.y);

    return ret;
}

Vector2I Window::getFramebufferSize() const {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);
    Vector2I ret;

    glfwGetFramebufferSize(win, &ret.x, &ret.y);

    return ret;
}

Vector2F Window::getContentScale() const {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);
    Vector2F ret;

    glfwGetWindowContentScale(win, &ret.x, &ret.y);

    return ret;
}

void Window::setCallbacks() {
    auto* win = reinterpret_cast<GLFWwindow*>(m_context.m_handle);

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
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowCloseEvent();
}

void Window::resizeCallback(void* window, int width, int height) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowResizeEvent(Vector2I(width, height));
}

void Window::framebufferResizeCallback(void* window, int width, int height) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowFramebufferResizeEvent(Vector2I(width, height));
}

void Window::contentScaleCallback(void* window, float xScale, float yScale) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowContentScaleEvent(Vector2F(xScale, yScale));
}

void Window::positionCallback(void* window, int xPos, int yPos) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowPositionEvent(Vector2I(xPos, yPos));
}

void Window::minimizeCallback(void* window, int minimized) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    if (minimized) {
        win->m_eventHandler->windowMinimizeEvent();
    } else {
        win->m_eventHandler->windowUnminimizeEvent();
    }
}

void Window::maximizeCallback(void* window, int maximized) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    if (maximized) {
        win->m_eventHandler->windowMaximizeEvent();
    } else {
        win->m_eventHandler->windowUnmaximizeEvent();
    }
}

void Window::focusCallback(void* window, int focused) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    if (focused) {
        win->m_eventHandler->windowGainedFocusEvent();
    } else {
        win->m_eventHandler->windowLostFocusEvent();
    }
}

void Window::refreshCallback(void* window) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->windowRefreshEvent();
}

void Window::keyboardCallback(void* window, int key, int scancode, int action, int mods) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
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
    kbe.ctrl = mods & GLFW_MOD_CONTROL;
    kbe.shift = mods & GLFW_MOD_SHIFT;
    kbe.alt = mods & GLFW_MOD_ALT;
    kbe.system = mods & GLFW_MOD_SUPER;
    kbe.capsLock = mods & GLFW_MOD_CAPS_LOCK;
    kbe.numLock = mods & GLFW_MOD_NUM_LOCK;

    win->m_eventHandler->keyboardEvent(kbe);
}

void Window::textInputCallback(void* window, unsigned int codePoint) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->textInputEvent(codePoint);
}

void Window::cursorPositionCallback(void* window, double xPos, double yPos) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->cursorPositionEvent(Vector2D(xPos, yPos));
}

void Window::cursorEnterCallback(void* window, int entered) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    if (entered) {
        win->m_eventHandler->cursorEnterEvent();
    } else {
        win->m_eventHandler->cursorLeaveEvent();
    }
}

void Window::mouseButtonCallback(void* window, int button, int action, int mods) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
    Mouse::MouseButtonEvent mbe{};

    mbe.button = Mouse::getButtonFromInternal(button);
    if (action == GLFW_PRESS) {
        mbe.state = Mouse::ButtonState::Pressed;
    } else {
        mbe.state = Mouse::ButtonState::Released;
    }
    mbe.ctrl = mods & GLFW_MOD_CONTROL;
    mbe.shift = mods & GLFW_MOD_SHIFT;
    mbe.alt = mods & GLFW_MOD_ALT;
    mbe.system = mods & GLFW_MOD_SUPER;
    mbe.capsLock = mods & GLFW_MOD_CAPS_LOCK;
    mbe.numLock = mods & GLFW_MOD_NUM_LOCK;

    win->m_eventHandler->mouseButtonEvent(mbe);
}

void Window::scrollCallback(void* window, double xOffset, double yOffset) {
    auto* handle = reinterpret_cast<GLFWwindow*>(window);
    auto* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));

    win->m_eventHandler->scrollEvent(Vector2D(xOffset, yOffset));
}
}

