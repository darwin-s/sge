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

#include <SGE/RenderTarget.hpp>
#include <SGE/Drawable.hpp>
#include <SGE/VAO.hpp>
#include <cassert>
#include <glad.h>

namespace sge {
void RenderTarget::clear(const Color& clearColor) {
    auto* active = Context::getCurrentContext();

    getRenderingContext().setCurrent(true);
    glClearColor(static_cast<GLfloat>(clearColor.red) / 255, static_cast<GLfloat>(clearColor.green) / 255,
                 static_cast<GLfloat>(clearColor.blue) / 255, static_cast<GLfloat>(clearColor.alpha) / 255);
    glClear(GL_COLOR_BUFFER_BIT);

    if (active != nullptr) {
        active->setCurrent(true);
    }
}

void RenderTarget::draw(const Drawable& drawable, const RenderState& renderState) {
    drawable.draw(*this, renderState);
}

void RenderTarget::drawTriangles(const VAO& vao, const std::size_t firstVertex, const std::size_t vertexCount,
                                 const RenderState& renderState) {
    auto* active = Context::getCurrentContext();

    getRenderingContext().setCurrent(true);
    auto* sh = renderState.getShader();
    if (sh != nullptr) {
        sh->use();
    }
    vao.bind();
    glDrawArrays(GL_TRIANGLES, firstVertex, vertexCount);

    if (active != nullptr) {
        active->setCurrent(true);
    }
}

void RenderTarget::setViewportSize(const Vector2I size) {
    auto* active = Context::getCurrentContext();

    getRenderingContext().setCurrent(true);
    glViewport(0, 0, size.x, size.y);

    if (active != nullptr) {
        active->setCurrent(true);
    }
}
}