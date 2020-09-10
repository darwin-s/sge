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
RenderWindow::RenderWindow(const ContextSettings& contextSettings)
    : Window(), RenderTarget(*this, contextSettings) {
}

RenderWindow::RenderWindow(const char* title,
                           const ContextSettings& contextSettings)
    : Window(title), RenderTarget(*this, contextSettings) {
}

RenderWindow::RenderWindow(const char* title,
                           const glm::ivec2 size,
                           const ContextSettings& contextSettings)
    : Window(title, size), RenderTarget(*this, contextSettings) {
}

RenderWindow::RenderWindow(const char* title,
                           const Monitor::VideoMode videoMode,
                           const ContextSettings& contextSettings)
    : Window(title, videoMode), RenderTarget(*this, contextSettings) {
}

glm::ivec2 RenderWindow::getPhysicalSize() const {
    auto* w = static_cast<SDL_Window*>(getHandle());
    glm::ivec2 r;

    SDL_GL_GetDrawableSize(w, &r.x, &r.y);

    return r;
}

void RenderWindow::swapBuffers() {
    auto* w = static_cast<SDL_Window*>(getHandle());

    flushRenderQueue();
    SDL_GL_SwapWindow(w);
}
}
