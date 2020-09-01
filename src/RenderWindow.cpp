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
#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace sge {
RenderWindow::RenderWindow(const ContextSettings contextSettings)
    : Window(), m_context(*this, contextSettings) {
}

RenderWindow::RenderWindow(const std::string_view title,
                           const ContextSettings contextSettings)
    : Window(title), m_context(*this, contextSettings) {
}

RenderWindow::RenderWindow(const std::string_view title,
                           const Vector2I size,
                           const ContextSettings contextSettings)
    : Window(title, size), m_context(*this, contextSettings) {
}

RenderWindow::RenderWindow(const std::string_view title,
                           const Monitor::VideoMode videoMode,
                           const ContextSettings contextSettings)
    : Window(title, videoMode), m_context(*this, contextSettings) {
}

Context& RenderWindow::getRenderingContext() {
    return m_context;
}

Vector2I RenderWindow::getPhysicalSize() const {
    auto* w = static_cast<SDL_Window*>(getHandle());
    Vector2I r;

    SDL_GL_GetDrawableSize(w, &r.x, &r.y);

    return r;
}

void RenderWindow::swapBuffers() {
    auto* w = static_cast<SDL_Window*>(getHandle());

    SDL_GL_SwapWindow(w);
}
}
