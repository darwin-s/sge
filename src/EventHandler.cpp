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

#include <SGE/EventHandler.hpp>

namespace sge {
void EventHandler::windowCloseEvent() {
}

void EventHandler::windowResizeEvent(const Vector2I& size) {
}

void EventHandler::windowFramebufferResizeEvent(const Vector2U& size) {
}

void EventHandler::windowContentScaleEvent(const Vector2F& scale) {
}

void EventHandler::windowPositionEvent(const Vector2I& pos) {
}

void EventHandler::windowMinimizeEvent() {
}

void EventHandler::windowUnminimizeEvent() {
}

void EventHandler::windowMaximizeEvent() {
}

void EventHandler::windowUnmaximizeEvent() {
}

void EventHandler::windowGainedFocusEvent() {
}

void EventHandler::windowLostFocusEvent() {
}

void EventHandler::windowRefreshEvent() {
}

void EventHandler::keyboardEvent(Keyboard::KeyboardEvent event) {
}

void EventHandler::textInputEvent(unsigned int codePoint) {
}

void EventHandler::cursorPositionEvent(const Vector2D& pos) {
}

void EventHandler::cursorEnterEvent() {
}

void EventHandler::cursorLeaveEvent() {
}

void EventHandler::mouseButtonEvent(Mouse::MouseButtonEvent event) {
}

void EventHandler::scrollEvent(const Vector2D& scroll) {
}

}
