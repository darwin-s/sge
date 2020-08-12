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

#include <SGE/Mouse.hpp>
#include <SGE/Window.hpp>
#include <GLFW/glfw3.h>

namespace sge {
Mouse::Button Mouse::getButtonFromInternal(int button) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_1:
        return Button::Left;
    case GLFW_MOUSE_BUTTON_2:
        return Button::Right;
    case GLFW_MOUSE_BUTTON_3:
        return Button::Middle;
    case GLFW_MOUSE_BUTTON_4:
        return Button::Mb4;
    case GLFW_MOUSE_BUTTON_5:
        return Button::Mb5;
    case GLFW_MOUSE_BUTTON_6:
        return Button::Mb6;
    case GLFW_MOUSE_BUTTON_7:
        return Button::Mb7;
    case GLFW_MOUSE_BUTTON_8:
        return Button::Mb8;
    default:
        return Button::Left;
    }
}

int Mouse::getCodeFromButton(const Button button) {
    switch (button) {
    case Button::Left:
        return GLFW_MOUSE_BUTTON_1;
    case Button::Right:
        return GLFW_MOUSE_BUTTON_2;
    case Button::Middle:
        return GLFW_MOUSE_BUTTON_3;
    case Button::Mb4:
        return GLFW_MOUSE_BUTTON_4;
    case Button::Mb5:
        return GLFW_MOUSE_BUTTON_5;
    case Button::Mb6:
        return GLFW_MOUSE_BUTTON_6;
    case Button::Mb7:
        return GLFW_MOUSE_BUTTON_7;
    case Button::Mb8:
        return GLFW_MOUSE_BUTTON_8;
    default:
        return -1;
    }
}

std::string Mouse::getButtonName(const Button button) {
    switch (button) {
    case Button::Left:
        return "LMB";
    case Button::Right:
        return "RMB";
    case Button::Middle:
        return "Mouse3";
    case Button::Mb4:
        return "Mouse4";
    case Button::Mb5:
        return "Mouse5";
    case Button::Mb6:
        return "Mouse6";
    case Button::Mb7:
        return "Mouse7";
    case Button::Mb8:
        return "Mouse8";
    default:
        return "LMB";
    }
}

Mouse::ButtonState Mouse::getButtonState(const Window& window, const Button button) {
    auto* win = static_cast<GLFWwindow*>(window.getContext().m_handle);
    const auto state = glfwGetMouseButton(win, getCodeFromButton(button));

    switch (state) {
    case GLFW_PRESS:
        return ButtonState::Pressed;
    case GLFW_RELEASE:
    default:
        return ButtonState::Released;
    }
}

bool Mouse::isRawInputSupported() {
    return glfwRawMouseMotionSupported() == GLFW_TRUE;
}
}
