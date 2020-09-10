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
#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace sge {
Keyboard::Key Keyboard::getKeyFromInternal(const int keyCode) {
    switch (keyCode) {
    case SDLK_SPACE:
        return Keyboard::Key::Space;
    case SDLK_QUOTE:
        return Keyboard::Key::Apostrophe;
    case SDLK_COMMA:
        return Keyboard::Key::Comma;
    case SDLK_MINUS:
        return Keyboard::Key::Minus;
    case SDLK_PERIOD:
        return Keyboard::Key::Period;
    case SDLK_SLASH:
        return Keyboard::Key::Slash;
    case SDLK_0:
        return Keyboard::Key::Num0;
    case SDLK_1:
        return Keyboard::Key::Num1;
    case SDLK_2:
        return Keyboard::Key::Num2;
    case SDLK_3:
        return Keyboard::Key::Num3;
    case SDLK_4:
        return Keyboard::Key::Num4;
    case SDLK_5:
        return Keyboard::Key::Num5;
    case SDLK_6:
        return Keyboard::Key::Num6;
    case SDLK_7:
        return Keyboard::Key::Num7;
    case SDLK_8:
        return Keyboard::Key::Num8;
    case SDLK_9:
        return Keyboard::Key::Num9;
    case SDLK_SEMICOLON:
        return Keyboard::Key::Semicolon;
    case SDLK_EQUALS:
        return Keyboard::Key::Equal;
    case SDLK_a:
        return Keyboard::Key::A;
    case SDLK_b:
        return Keyboard::Key::B;
    case SDLK_c:
        return Keyboard::Key::C;
    case SDLK_d:
        return Keyboard::Key::D;
    case SDLK_e:
        return Keyboard::Key::E;
    case SDLK_f:
        return Keyboard::Key::F;
    case SDLK_g:
        return Keyboard::Key::G;
    case SDLK_h:
        return Keyboard::Key::H;
    case SDLK_i:
        return Keyboard::Key::I;
    case SDLK_j:
        return Keyboard::Key::J;
    case SDLK_k:
        return Keyboard::Key::K;
    case SDLK_l:
        return Keyboard::Key::L;
    case SDLK_m:
        return Keyboard::Key::M;
    case SDLK_n:
        return Keyboard::Key::N;
    case SDLK_o:
        return Keyboard::Key::O;
    case SDLK_p:
        return Keyboard::Key::P;
    case SDLK_q:
        return Keyboard::Key::Q;
    case SDLK_r:
        return Keyboard::Key::R;
    case SDLK_s:
        return Keyboard::Key::S;
    case SDLK_t:
        return Keyboard::Key::T;
    case SDLK_u:
        return Keyboard::Key::U;
    case SDLK_v:
        return Keyboard::Key::V;
    case SDLK_w:
        return Keyboard::Key::W;
    case SDLK_x:
        return Keyboard::Key::X;
    case SDLK_y:
        return Keyboard::Key::Y;
    case SDLK_z:
        return Keyboard::Key::Z;
    case SDLK_LEFTBRACKET:
        return Keyboard::Key::LeftBracket;
    case SDLK_BACKSLASH:
        return Keyboard::Key::Backslash;
    case SDLK_RIGHTBRACKET:
        return Keyboard::Key::RightBracket;
    case SDLK_BACKQUOTE:
        return Keyboard::Key::Tilde;
    case SDLK_ESCAPE:
        return Keyboard::Key::Escape;
    case SDLK_RETURN:
        return Keyboard::Key::Enter;
    case SDLK_TAB:
        return Keyboard::Key::Tab;
    case SDLK_BACKSPACE:
        return Keyboard::Key::Backspace;
    case SDLK_INSERT:
        return Keyboard::Key::Insert;
    case SDLK_DELETE:
        return Keyboard::Key::Delete;
    case SDLK_RIGHT:
        return Keyboard::Key::ArrowRight;
    case SDLK_LEFT:
        return Keyboard::Key::ArrowLeft;
    case SDLK_DOWN:
        return Keyboard::Key::ArrowDown;
    case SDLK_UP:
        return Keyboard::Key::ArrowUp;
    case SDLK_PAGEUP:
        return Keyboard::Key::PageUp;
    case SDLK_PAGEDOWN:
        return Keyboard::Key::PageDown;
    case SDLK_HOME:
        return Keyboard::Key::Home;
    case SDLK_END:
        return Keyboard::Key::End;
    case SDLK_CAPSLOCK:
        return Keyboard::Key::CapsLock;
    case SDLK_SCROLLLOCK:
        return Keyboard::Key::ScrollLock;
    case SDLK_NUMLOCKCLEAR:
        return Keyboard::Key::NumLock;
    case SDLK_PRINTSCREEN:
        return Keyboard::Key::PrintScreen;
    case SDLK_PAUSE:
        return Keyboard::Key::Pause;
    case SDLK_F1:
        return Keyboard::Key::F1;
    case SDLK_F2:
        return Keyboard::Key::F2;
    case SDLK_F3:
        return Keyboard::Key::F3;
    case SDLK_F4:
        return Keyboard::Key::F4;
    case SDLK_F5:
        return Keyboard::Key::F5;
    case SDLK_F6:
        return Keyboard::Key::F6;
    case SDLK_F7:
        return Keyboard::Key::F7;
    case SDLK_F8:
        return Keyboard::Key::F8;
    case SDLK_F9:
        return Keyboard::Key::F9;
    case SDLK_F10:
        return Keyboard::Key::F10;
    case SDLK_F11:
        return Keyboard::Key::F11;
    case SDLK_F12:
        return Keyboard::Key::F12;
    case SDLK_KP_0:
        return Keyboard::Key::NumPad0;
    case SDLK_KP_1:
        return Keyboard::Key::NumPad1;
    case SDLK_KP_2:
        return Keyboard::Key::NumPad2;
    case SDLK_KP_3:
        return Keyboard::Key::NumPad3;
    case SDLK_KP_4:
        return Keyboard::Key::NumPad4;
    case SDLK_KP_5:
        return Keyboard::Key::NumPad5;
    case SDLK_KP_6:
        return Keyboard::Key::NumPad6;
    case SDLK_KP_7:
        return Keyboard::Key::NumPad7;
    case SDLK_KP_8:
        return Keyboard::Key::NumPad8;
    case SDLK_KP_9:
        return Keyboard::Key::NumPad9;
    case SDLK_KP_DECIMAL:
        return Keyboard::Key::NumPadDecimal;
    case SDLK_KP_DIVIDE:
        return Keyboard::Key::NumPadDivide;
    case SDLK_KP_MULTIPLY:
        return Keyboard::Key::NumPadMultiply;
    case SDLK_KP_MINUS:
        return Keyboard::Key::NumPadMinus;
    case SDLK_KP_PLUS:
        return Keyboard::Key::NumPadPlus;
    case SDLK_KP_ENTER:
        return Keyboard::Key::NumPadEnter;
    case SDLK_LSHIFT:
        return Keyboard::Key::LShift;
    case SDLK_LCTRL:
        return Keyboard::Key::LCtrl;
    case SDLK_LALT:
        return Keyboard::Key::LAlt;
    case SDLK_APPLICATION:
        return Keyboard::Key::System;
    case SDLK_RSHIFT:
        return Keyboard::Key::RShift;
    case SDLK_RCTRL:
        return Keyboard::Key::RCtrl;
    case SDLK_RALT:
        return Keyboard::Key::RAlt;
    case SDLK_MENU:
        return Keyboard::Key::Menu;
    default:
        return Keyboard::Key::Unknown;
    }
}

int Keyboard::getCodeFromKey(const Key key) {
    switch (key) {
    case Keyboard::Key::Space:
        return SDLK_SPACE;
    case Keyboard::Key::Apostrophe:
        return SDLK_QUOTE;
    case Keyboard::Key::Comma:
        return SDLK_COMMA;
    case Keyboard::Key::Minus:
        return SDLK_MINUS;
    case Keyboard::Key::Period:
        return SDLK_PERIOD;
    case Keyboard::Key::Slash:
        return SDLK_SLASH;
    case Keyboard::Key::Num0:
        return SDLK_1;
    case Keyboard::Key::Num1:
        return SDLK_2;
    case Keyboard::Key::Num2:
        return SDLK_2;
    case Keyboard::Key::Num3:
        return SDLK_3;
    case Keyboard::Key::Num4:
        return SDLK_4;
    case Keyboard::Key::Num5:
        return SDLK_5;
    case Keyboard::Key::Num6:
        return SDLK_6;
    case Keyboard::Key::Num7:
        return SDLK_7;
    case Keyboard::Key::Num8:
        return SDLK_8;
    case Keyboard::Key::Num9:
        return SDLK_9;
    case Keyboard::Key::Semicolon:
        return SDLK_SEMICOLON;
    case Keyboard::Key::Equal:
        return SDLK_EQUALS;
    case Keyboard::Key::A:
        return SDLK_a;
    case Keyboard::Key::B:
        return SDLK_b;
    case Keyboard::Key::C:
        return SDLK_c;
    case Keyboard::Key::D:
        return SDLK_d;
    case Keyboard::Key::E:
        return SDLK_e;
    case Keyboard::Key::F:
        return SDLK_f;
    case Keyboard::Key::G:
        return SDLK_g;
    case Keyboard::Key::H:
        return SDLK_h;
    case Keyboard::Key::I:
        return SDLK_i;
    case Keyboard::Key::J:
        return SDLK_j;
    case Keyboard::Key::K:
        return SDLK_k;
    case Keyboard::Key::L:
        return SDLK_l;
    case Keyboard::Key::M:
        return SDLK_m;
    case Keyboard::Key::N:
        return SDLK_n;
    case Keyboard::Key::O:
        return SDLK_o;
    case Keyboard::Key::P:
        return SDLK_p;
    case Keyboard::Key::Q:
        return SDLK_q;
    case Keyboard::Key::R:
        return SDLK_r;
    case Keyboard::Key::S:
        return SDLK_s;
    case Keyboard::Key::T:
        return SDLK_t;
    case Keyboard::Key::U:
        return SDLK_u;
    case Keyboard::Key::V:
        return SDLK_v;
    case Keyboard::Key::W:
        return SDLK_w;
    case Keyboard::Key::X:
        return SDLK_x;
    case Keyboard::Key::Y:
        return SDLK_y;
    case Keyboard::Key::Z:
        return SDLK_z;
    case Keyboard::Key::LeftBracket:
        return SDLK_LEFTBRACKET;
    case Keyboard::Key::Backslash:
        return SDLK_BACKSLASH;
    case Keyboard::Key::RightBracket:
        return SDLK_RIGHTBRACKET;
    case Keyboard::Key::Tilde:
        return SDLK_BACKQUOTE;
    case Keyboard::Key::Escape:
        return SDLK_ESCAPE;
    case Keyboard::Key::Enter:
        return SDLK_RETURN;
    case Keyboard::Key::Tab:
        return SDLK_TAB;
    case Keyboard::Key::Backspace:
        return SDLK_BACKSPACE;
    case Keyboard::Key::Insert:
        return SDLK_INSERT;
    case Keyboard::Key::Delete:
        return SDLK_DELETE;
    case Keyboard::Key::ArrowRight:
        return SDLK_RIGHT;
    case Keyboard::Key::ArrowLeft:
        return SDLK_LEFT;
    case Keyboard::Key::ArrowDown:
        return SDLK_DOWN;
    case Keyboard::Key::ArrowUp:
        return SDLK_UP;
    case Keyboard::Key::PageUp:
        return SDLK_PAGEUP;
    case Keyboard::Key::PageDown:
        return SDLK_PAGEDOWN;
    case Keyboard::Key::Home:
        return SDLK_HOME;
    case Keyboard::Key::End:
        return SDLK_END;
    case Keyboard::Key::CapsLock:
        return SDLK_CAPSLOCK;
    case Keyboard::Key::ScrollLock:
        return SDLK_SCROLLLOCK;
    case Keyboard::Key::NumLock:
        return SDLK_NUMLOCKCLEAR;
    case Keyboard::Key::PrintScreen:
        return SDLK_PRINTSCREEN;
    case Keyboard::Key::Pause:
        return SDLK_PAUSE;
    case Keyboard::Key::F1:
        return SDLK_F1;
    case Keyboard::Key::F2:
        return SDLK_F2;
    case Keyboard::Key::F3:
        return SDLK_F3;
    case Keyboard::Key::F4:
        return SDLK_F4;
    case Keyboard::Key::F5:
        return SDLK_F5;
    case Keyboard::Key::F6:
        return SDLK_F6;
    case Keyboard::Key::F7:
        return SDLK_F7;
    case Keyboard::Key::F8:
        return SDLK_F8;
    case Keyboard::Key::F9:
        return SDLK_F9;
    case Keyboard::Key::F10:
        return SDLK_F10;
    case Keyboard::Key::F11:
        return SDLK_F11;
    case Keyboard::Key::F12:
        return SDLK_F12;
    case Keyboard::Key::NumPad0:
        return SDLK_KP_0;
    case Keyboard::Key::NumPad1:
        return SDLK_KP_1;
    case Keyboard::Key::NumPad2:
        return SDLK_KP_2;
    case Keyboard::Key::NumPad3:
        return SDLK_KP_3;
    case Keyboard::Key::NumPad4:
        return SDLK_KP_4;
    case Keyboard::Key::NumPad5:
        return SDLK_KP_5;
    case Keyboard::Key::NumPad6:
        return SDLK_KP_6;
    case Keyboard::Key::NumPad7:
        return SDLK_KP_7;
    case Keyboard::Key::NumPad8:
        return SDLK_KP_8;
    case Keyboard::Key::NumPad9:
        return SDLK_KP_9;
    case Keyboard::Key::NumPadDecimal:
        return SDLK_KP_DECIMAL;
    case Keyboard::Key::NumPadDivide:
        return SDLK_KP_DIVIDE;
    case Keyboard::Key::NumPadMultiply:
        return SDLK_KP_MULTIPLY;
    case Keyboard::Key::NumPadMinus:
        return SDLK_KP_MINUS;
    case Keyboard::Key::NumPadPlus:
        return SDLK_KP_PLUS;
    case Keyboard::Key::NumPadEnter:
        return SDLK_KP_ENTER;
    case Keyboard::Key::LShift:
        return SDLK_LSHIFT;
    case Keyboard::Key::LCtrl:
        return SDLK_LCTRL;
    case Keyboard::Key::LAlt:
        return SDLK_LALT;
    case Keyboard::Key::System:
        return SDLK_APPLICATION;
    case Keyboard::Key::RShift:
        return SDLK_RSHIFT;
    case Keyboard::Key::RCtrl:
        return SDLK_RCTRL;
    case Keyboard::Key::RAlt:
        return SDLK_RALT;
    case Keyboard::Key::Menu:
        return SDLK_MENU;
    default:
        return SDLK_UNKNOWN;
    }
}

int Keyboard::getKeyScancode(const Key key) {
    return SDL_GetScancodeFromKey(getCodeFromKey(key));
}

const char* Keyboard::getKeyName(const Key key) {
    return SDL_GetKeyName(getCodeFromKey(key));
}

const char* Keyboard::getKeyName(const int scancode) {
    return SDL_GetKeyName(
        SDL_GetKeyFromScancode(static_cast<SDL_Scancode>(scancode)));
}

Keyboard::KeyState Keyboard::getKeyState(const Key key) {
    const auto* state = SDL_GetKeyboardState(NULL);

    if (state[getKeyScancode(key)] == 1) {
        return KeyState::Pressed;
    }

    return KeyState::Released;
}

void Keyboard::setTextInput(bool input) {
    if (input) {
        SDL_StartTextInput();
    } else {
        SDL_StopTextInput();
    }
}

bool Keyboard::isTextureInputEnabled() {
    return SDL_IsTextInputActive() == SDL_TRUE;
}
}
