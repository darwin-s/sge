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
#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace sge {
Mouse::Button Mouse::getButtonFromInternal(const int button) {
    switch (button) {
    case SDL_BUTTON_LEFT:
        return Button::Left;
    case SDL_BUTTON_RIGHT:
        return Button::Right;
    case SDL_BUTTON_MIDDLE:
        return Button::Middle;
    case SDL_BUTTON_X1:
        return Button::Mb4;
    case SDL_BUTTON_X2:
        return Button::Mb5;
    default:
        return Button::Unknown;
    }
}

int Mouse::getCodeFromButton(const Button button) {
    switch (button) {
    case Button::Left:
        return SDL_BUTTON_LEFT;
    case Button::Right:
        return SDL_BUTTON_RIGHT;
    case Button::Middle:
        return SDL_BUTTON_MIDDLE;
    case Button::Mb4:
        return SDL_BUTTON_X1;
    case Button::Mb5:
        return SDL_BUTTON_X2;
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
    default:
        return "Unknows";
    }
}

Mouse::ButtonState Mouse::getButtonState(const Button button) {
    const auto state = SDL_GetMouseState(NULL, NULL);

    if ((state & SDL_BUTTON(getCodeFromButton(button))) != 0) {
        return ButtonState::Pressed;
    }

    return ButtonState::Released;
}

Vector2I Mouse::getMousePosition() {
    Vector2I pos;
    if (isInRelativeMode()) {
        SDL_GetRelativeMouseState(&pos.x, &pos.y);
    } else {
        SDL_GetMouseState(&pos.x, &pos.y);
    }

    return pos;
}

void Mouse::setRelativeMode(bool active) {
    SDL_SetRelativeMouseMode(active ? SDL_TRUE : SDL_FALSE);
}

bool Mouse::isInRelativeMode() {
    return SDL_GetRelativeMouseMode() == SDL_TRUE;
}

void Mouse::setCursorVisibility(bool visible) {
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

bool Mouse::isCursorVisible() {
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
}
}
