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

#include <SGE/RenderWindow.hpp>

namespace sge {
RenderWindow::RenderWindow(ContextSettings contextSettings) : Window(contextSettings) {
}

RenderWindow::RenderWindow(std::string_view title, ContextSettings contextSettings) : Window(title, contextSettings) {
}

RenderWindow::RenderWindow(std::string_view title, Vector2I size, ContextSettings contextSettings)
    : Window(title, size, contextSettings) {
}

RenderWindow::RenderWindow(std::string_view title, Monitor::VideoMode videoMode, const Monitor& monitor,
                           ContextSettings contextSettings)
    : Window(title, videoMode, monitor, contextSettings) {
}

Context& RenderWindow::getContext() {
    return Window::getContext();
}
}
