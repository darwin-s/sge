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

#include <SGE/Keyboard.hpp>
#include <SGE/Window.hpp>
#include <GLFW/glfw3.h>

namespace sge {
Keyboard::Key Keyboard::getKeyFromInternal(const int keyCode) {
    switch (keyCode) {
    case GLFW_KEY_SPACE:
        return Keyboard::Key::Space;
    case GLFW_KEY_APOSTROPHE:
        return Keyboard::Key::Apostrophe;
    case GLFW_KEY_COMMA:
        return Keyboard::Key::Comma;
    case GLFW_KEY_MINUS:
        return Keyboard::Key::Minus;
    case GLFW_KEY_PERIOD:
        return Keyboard::Key::Period;
    case GLFW_KEY_SLASH:
        return Keyboard::Key::Slash;
    case GLFW_KEY_0:
        return Keyboard::Key::Num0;
    case GLFW_KEY_1:
        return Keyboard::Key::Num1;
    case GLFW_KEY_2:
        return Keyboard::Key::Num2;
    case GLFW_KEY_3:
        return Keyboard::Key::Num3;
    case GLFW_KEY_4:
        return Keyboard::Key::Num4;
    case GLFW_KEY_5:
        return Keyboard::Key::Num5;
    case GLFW_KEY_6:
        return Keyboard::Key::Num6;
    case GLFW_KEY_7:
        return Keyboard::Key::Num7;
    case GLFW_KEY_8:
        return Keyboard::Key::Num8;
    case GLFW_KEY_9:
        return Keyboard::Key::Num9;
    case GLFW_KEY_SEMICOLON:
        return Keyboard::Key::Semicolon;
    case GLFW_KEY_EQUAL:
        return Keyboard::Key::Equal;
    case GLFW_KEY_A:
        return Keyboard::Key::A;
    case GLFW_KEY_B:
        return Keyboard::Key::B;
    case GLFW_KEY_C:
        return Keyboard::Key::C;
    case GLFW_KEY_D:
        return Keyboard::Key::D;
    case GLFW_KEY_E:
        return Keyboard::Key::E;
    case GLFW_KEY_F:
        return Keyboard::Key::F;
    case GLFW_KEY_G:
        return Keyboard::Key::G;
    case GLFW_KEY_H:
        return Keyboard::Key::H;
    case GLFW_KEY_I:
        return Keyboard::Key::I;
    case GLFW_KEY_J:
        return Keyboard::Key::J;
    case GLFW_KEY_K:
        return Keyboard::Key::K;
    case GLFW_KEY_L:
        return Keyboard::Key::L;
    case GLFW_KEY_M:
        return Keyboard::Key::M;
    case GLFW_KEY_N:
        return Keyboard::Key::N;
    case GLFW_KEY_O:
        return Keyboard::Key::O;
    case GLFW_KEY_P:
        return Keyboard::Key::P;
    case GLFW_KEY_Q:
        return Keyboard::Key::Q;
    case GLFW_KEY_R:
        return Keyboard::Key::R;
    case GLFW_KEY_S:
        return Keyboard::Key::S;
    case GLFW_KEY_T:
        return Keyboard::Key::T;
    case GLFW_KEY_U:
        return Keyboard::Key::U;
    case GLFW_KEY_V:
        return Keyboard::Key::V;
    case GLFW_KEY_W:
        return Keyboard::Key::W;
    case GLFW_KEY_X:
        return Keyboard::Key::X;
    case GLFW_KEY_Y:
        return Keyboard::Key::Y;
    case GLFW_KEY_Z:
        return Keyboard::Key::Z;
    case GLFW_KEY_LEFT_BRACKET:
        return Keyboard::Key::LeftBracket;
    case GLFW_KEY_BACKSLASH:
        return Keyboard::Key::Backslash;
    case GLFW_KEY_RIGHT_BRACKET:
        return Keyboard::Key::RightBracket;
    case GLFW_KEY_GRAVE_ACCENT:
        return Keyboard::Key::Tilde;
    case GLFW_KEY_ESCAPE:
        return Keyboard::Key::Escape;
    case GLFW_KEY_ENTER:
        return Keyboard::Key::Enter;
    case GLFW_KEY_TAB:
        return Keyboard::Key::Tab;
    case GLFW_KEY_BACKSPACE:
        return Keyboard::Key::Backspace;
    case GLFW_KEY_INSERT:
        return Keyboard::Key::Insert;
    case GLFW_KEY_DELETE:
        return Keyboard::Key::Delete;
    case GLFW_KEY_RIGHT:
        return Keyboard::Key::ArrowRight;
    case GLFW_KEY_LEFT:
        return Keyboard::Key::ArrowLeft;
    case GLFW_KEY_DOWN:
        return Keyboard::Key::ArrowDown;
    case GLFW_KEY_UP:
        return Keyboard::Key::ArrowUp;
    case GLFW_KEY_PAGE_UP:
        return Keyboard::Key::PageUp;
    case GLFW_KEY_PAGE_DOWN:
        return Keyboard::Key::PageDown;
    case GLFW_KEY_HOME:
        return Keyboard::Key::Home;
    case GLFW_KEY_END:
        return Keyboard::Key::End;
    case GLFW_KEY_CAPS_LOCK:
        return Keyboard::Key::CapsLock;
    case GLFW_KEY_SCROLL_LOCK:
        return Keyboard::Key::ScrollLock;
    case GLFW_KEY_NUM_LOCK:
        return Keyboard::Key::NumLock;
    case GLFW_KEY_PRINT_SCREEN:
        return Keyboard::Key::PrintScreen;
    case GLFW_KEY_PAUSE:
        return Keyboard::Key::Pause;
    case GLFW_KEY_F1:
        return Keyboard::Key::F1;
    case GLFW_KEY_F2:
        return Keyboard::Key::F2;
    case GLFW_KEY_F3:
        return Keyboard::Key::F3;
    case GLFW_KEY_F4:
        return Keyboard::Key::F4;
    case GLFW_KEY_F5:
        return Keyboard::Key::F5;
    case GLFW_KEY_F6:
        return Keyboard::Key::F6;
    case GLFW_KEY_F7:
        return Keyboard::Key::F7;
    case GLFW_KEY_F8:
        return Keyboard::Key::F8;
    case GLFW_KEY_F9:
        return Keyboard::Key::F9;
    case GLFW_KEY_F10:
        return Keyboard::Key::F10;
    case GLFW_KEY_F11:
        return Keyboard::Key::F11;
    case GLFW_KEY_F12:
        return Keyboard::Key::F12;
    case GLFW_KEY_KP_0:
        return Keyboard::Key::NumPad0;
    case GLFW_KEY_KP_1:
        return Keyboard::Key::NumPad1;
    case GLFW_KEY_KP_2:
        return Keyboard::Key::NumPad2;
    case GLFW_KEY_KP_3:
        return Keyboard::Key::NumPad3;
    case GLFW_KEY_KP_4:
        return Keyboard::Key::NumPad4;
    case GLFW_KEY_KP_5:
        return Keyboard::Key::NumPad5;
    case GLFW_KEY_KP_6:
        return Keyboard::Key::NumPad6;
    case GLFW_KEY_KP_7:
        return Keyboard::Key::NumPad7;
    case GLFW_KEY_KP_8:
        return Keyboard::Key::NumPad8;
    case GLFW_KEY_KP_9:
        return Keyboard::Key::NumPad9;
    case GLFW_KEY_KP_DECIMAL:
        return Keyboard::Key::NumPadDecimal;
    case GLFW_KEY_KP_DIVIDE:
        return Keyboard::Key::NumPadDivide;
    case GLFW_KEY_KP_MULTIPLY:
        return Keyboard::Key::NumPadMultiply;
    case GLFW_KEY_KP_SUBTRACT:
        return Keyboard::Key::NumPadMinus;
    case GLFW_KEY_KP_ADD:
        return Keyboard::Key::NumPadPlus;
    case GLFW_KEY_KP_ENTER:
        return Keyboard::Key::NumPadEnter;
    case GLFW_KEY_LEFT_SHIFT:
        return Keyboard::Key::LShift;
    case GLFW_KEY_LEFT_CONTROL:
        return Keyboard::Key::LCtrl;
    case GLFW_KEY_LEFT_ALT:
        return Keyboard::Key::LAlt;
    case GLFW_KEY_LEFT_SUPER:
        return Keyboard::Key::LSystem;
    case GLFW_KEY_RIGHT_SHIFT:
        return Keyboard::Key::RShift;
    case GLFW_KEY_RIGHT_CONTROL:
        return Keyboard::Key::RCtrl;
    case GLFW_KEY_RIGHT_ALT:
        return Keyboard::Key::RAlt;
    case GLFW_KEY_RIGHT_SUPER:
        return Keyboard::Key::RSystem;
    case GLFW_KEY_MENU:
        return Keyboard::Key::Menu;
    default:
        return Keyboard::Key::Unknown;
    }
}

int Keyboard::getCodeFromKey(const Key key) {
    switch (key) {
    case Keyboard::Key::Space:
        return GLFW_KEY_SPACE;
    case Keyboard::Key::Apostrophe:
        return GLFW_KEY_APOSTROPHE;
    case Keyboard::Key::Comma:
        return GLFW_KEY_COMMA;
    case Keyboard::Key::Minus:
        return GLFW_KEY_MINUS;
    case Keyboard::Key::Period:
        return GLFW_KEY_PERIOD;
    case Keyboard::Key::Slash:
        return GLFW_KEY_SLASH;
    case Keyboard::Key::Num0:
        return GLFW_KEY_0;
    case Keyboard::Key::Num1:
        return GLFW_KEY_1;
    case Keyboard::Key::Num2:
        return GLFW_KEY_2;
    case Keyboard::Key::Num3:
        return GLFW_KEY_3;
    case Keyboard::Key::Num4:
        return GLFW_KEY_4;
    case Keyboard::Key::Num5:
        return GLFW_KEY_5;
    case Keyboard::Key::Num6:
        return GLFW_KEY_6;
    case Keyboard::Key::Num7:
        return GLFW_KEY_7;
    case Keyboard::Key::Num8:
        return GLFW_KEY_8;
    case Keyboard::Key::Num9:
        return GLFW_KEY_9;
    case Keyboard::Key::Semicolon:
        return GLFW_KEY_SEMICOLON;
    case Keyboard::Key::Equal:
        return GLFW_KEY_EQUAL;
    case Keyboard::Key::A:
        return GLFW_KEY_A;
    case Keyboard::Key::B:
        return GLFW_KEY_B;
    case Keyboard::Key::C:
        return GLFW_KEY_C;
    case Keyboard::Key::D:
        return GLFW_KEY_D;
    case Keyboard::Key::E:
        return GLFW_KEY_E;
    case Keyboard::Key::F:
        return GLFW_KEY_F;
    case Keyboard::Key::G:
        return GLFW_KEY_G;
    case Keyboard::Key::H:
        return GLFW_KEY_H;
    case Keyboard::Key::I:
        return GLFW_KEY_I;
    case Keyboard::Key::J:
        return GLFW_KEY_J;
    case Keyboard::Key::K:
        return GLFW_KEY_K;
    case Keyboard::Key::L:
        return GLFW_KEY_L;
    case Keyboard::Key::M:
        return GLFW_KEY_M;
    case Keyboard::Key::N:
        return GLFW_KEY_N;
    case Keyboard::Key::O:
        return GLFW_KEY_O;
    case Keyboard::Key::P:
        return GLFW_KEY_P;
    case Keyboard::Key::Q:
        return GLFW_KEY_Q;
    case Keyboard::Key::R:
        return GLFW_KEY_R;
    case Keyboard::Key::S:
        return GLFW_KEY_S;
    case Keyboard::Key::T:
        return GLFW_KEY_T;
    case Keyboard::Key::U:
        return GLFW_KEY_U;
    case Keyboard::Key::V:
        return GLFW_KEY_V;
    case Keyboard::Key::W:
        return GLFW_KEY_W;
    case Keyboard::Key::X:
        return GLFW_KEY_X;
    case Keyboard::Key::Y:
        return GLFW_KEY_Y;
    case Keyboard::Key::Z:
        return GLFW_KEY_Z;
    case Keyboard::Key::LeftBracket:
        return GLFW_KEY_LEFT_BRACKET;
    case Keyboard::Key::Backslash:
        return GLFW_KEY_BACKSLASH;
    case Keyboard::Key::RightBracket:
        return GLFW_KEY_RIGHT_BRACKET;
    case Keyboard::Key::Tilde:
        return GLFW_KEY_GRAVE_ACCENT;
    case Keyboard::Key::Escape:
        return GLFW_KEY_ESCAPE;
    case Keyboard::Key::Enter:
        return GLFW_KEY_ENTER;
    case Keyboard::Key::Tab:
        return GLFW_KEY_TAB;
    case Keyboard::Key::Backspace:
        return GLFW_KEY_BACKSPACE;
    case Keyboard::Key::Insert:
        return GLFW_KEY_INSERT;
    case Keyboard::Key::Delete:
        return GLFW_KEY_DELETE;
    case Keyboard::Key::ArrowRight:
        return GLFW_KEY_RIGHT;
    case Keyboard::Key::ArrowLeft:
        return GLFW_KEY_LEFT;
    case Keyboard::Key::ArrowDown:
        return GLFW_KEY_DOWN;
    case Keyboard::Key::ArrowUp:
        return GLFW_KEY_UP;
    case Keyboard::Key::PageUp:
        return GLFW_KEY_PAGE_UP;
    case Keyboard::Key::PageDown:
        return GLFW_KEY_PAGE_DOWN;
    case Keyboard::Key::Home:
        return GLFW_KEY_HOME;
    case Keyboard::Key::End:
        return GLFW_KEY_END;
    case Keyboard::Key::CapsLock:
        return GLFW_KEY_CAPS_LOCK;
    case Keyboard::Key::ScrollLock:
        return GLFW_KEY_SCROLL_LOCK;
    case Keyboard::Key::NumLock:
        return GLFW_KEY_NUM_LOCK;
    case Keyboard::Key::PrintScreen:
        return GLFW_KEY_PRINT_SCREEN;
    case Keyboard::Key::Pause:
        return GLFW_KEY_PAUSE;
    case Keyboard::Key::F1:
        return GLFW_KEY_F1;
    case Keyboard::Key::F2:
        return GLFW_KEY_F2;
    case Keyboard::Key::F3:
        return GLFW_KEY_F3;
    case Keyboard::Key::F4:
        return GLFW_KEY_F4;
    case Keyboard::Key::F5:
        return GLFW_KEY_F5;
    case Keyboard::Key::F6:
        return GLFW_KEY_F6;
    case Keyboard::Key::F7:
        return GLFW_KEY_F7;
    case Keyboard::Key::F8:
        return GLFW_KEY_F8;
    case Keyboard::Key::F9:
        return GLFW_KEY_F9;
    case Keyboard::Key::F10:
        return GLFW_KEY_F10;
    case Keyboard::Key::F11:
        return GLFW_KEY_F11;
    case Keyboard::Key::F12:
        return GLFW_KEY_F12;
    case Keyboard::Key::NumPad0:
        return GLFW_KEY_KP_0;
    case Keyboard::Key::NumPad1:
        return GLFW_KEY_KP_1;
    case Keyboard::Key::NumPad2:
        return GLFW_KEY_KP_2;
    case Keyboard::Key::NumPad3:
        return GLFW_KEY_KP_3;
    case Keyboard::Key::NumPad4:
        return GLFW_KEY_KP_4;
    case Keyboard::Key::NumPad5:
        return GLFW_KEY_KP_5;
    case Keyboard::Key::NumPad6:
        return GLFW_KEY_KP_6;
    case Keyboard::Key::NumPad7:
        return GLFW_KEY_KP_7;
    case Keyboard::Key::NumPad8:
        return GLFW_KEY_KP_8;
    case Keyboard::Key::NumPad9:
        return GLFW_KEY_KP_9;
    case Keyboard::Key::NumPadDecimal:
        return GLFW_KEY_KP_DECIMAL;
    case Keyboard::Key::NumPadDivide:
        return GLFW_KEY_KP_DIVIDE;
    case Keyboard::Key::NumPadMultiply:
        return GLFW_KEY_KP_MULTIPLY;
    case Keyboard::Key::NumPadMinus:
        return GLFW_KEY_KP_SUBTRACT;
    case Keyboard::Key::NumPadPlus:
        return GLFW_KEY_KP_ADD;
    case Keyboard::Key::NumPadEnter:
        return GLFW_KEY_KP_ENTER;
    case Keyboard::Key::LShift:
        return GLFW_KEY_LEFT_SHIFT;
    case Keyboard::Key::LCtrl:
        return GLFW_KEY_LEFT_CONTROL;
    case Keyboard::Key::LAlt:
        return GLFW_KEY_LEFT_ALT;
    case Keyboard::Key::LSystem:
        return GLFW_KEY_LEFT_SUPER;
    case Keyboard::Key::RShift:
        return GLFW_KEY_RIGHT_SHIFT;
    case Keyboard::Key::RCtrl:
        return GLFW_KEY_RIGHT_CONTROL;
    case Keyboard::Key::RAlt:
        return GLFW_KEY_RIGHT_ALT;
    case Keyboard::Key::RSystem:
        return GLFW_KEY_RIGHT_SUPER;
    case Keyboard::Key::Menu:
        return GLFW_KEY_MENU;
    default:
        return GLFW_KEY_UNKNOWN;
    }
}

int Keyboard::getKeyScancode(const Key key) {
    return glfwGetKeyScancode(getCodeFromKey(key));
}

std::string Keyboard::getKeyName(const Key key) {
    const char* name = glfwGetKeyName(getCodeFromKey(key), GLFW_KEY_UNKNOWN);
    return name ? std::string(name) : "unknown";
}

std::string Keyboard::getKeyName(const int scancode) {
    const char* name = glfwGetKeyName(GLFW_KEY_UNKNOWN, scancode);
    return name ? std::string(name) : "unknown";
}

Keyboard::KeyState Keyboard::getKeyState(const Window& window, const Key key) {
    auto* win = reinterpret_cast<GLFWwindow*>(window.getContext().m_handle);
    int state = glfwGetKey(win, getCodeFromKey(key));

    switch (state) {
    case GLFW_PRESS:
        return KeyState::Pressed;
    case GLFW_REPEAT:
        return KeyState::Repeating;
    case GLFW_RELEASE:
    default:
        return KeyState::Released;
    }
}
}

