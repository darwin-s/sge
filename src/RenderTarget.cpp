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
#include <SGE/Shader.hpp>
#include <cmath>
#include <glad.h>

namespace sge {
const Camera RenderTarget::defaultCamera = Camera();

RenderTarget::RenderTarget() : m_cameraChanged(true) {
}

void RenderTarget::setCamera(const Camera& camera) {
    m_camera        = camera;
    m_cameraChanged = true;
}

const Camera& RenderTarget::getCamera() const {
    return m_camera;
}

RectangleInt RenderTarget::getViewport(const Camera& cam) const {
    const auto width  = static_cast<float>(getPhysicalSize().x);
    const auto height = static_cast<float>(getPhysicalSize().y);
    const auto& rect  = cam.getViewport();

    return RectangleInt(static_cast<int>(std::round(width * rect.left)),
                        static_cast<int>(std::round(height * rect.top)),
                        static_cast<int>(std::round(width * rect.width)),
                        static_cast<int>(std::round(height * rect.height)));
}

glm::vec2 RenderTarget::pixelToCoordinates(const glm::ivec2& pixel,
                                           const Camera& cam) const {
    const auto viewport = getViewport(cam);
    const glm::vec4 normalized(
        -1.0f + 2.0f * (pixel.x - viewport.left) / viewport.width,
        1.0f - 2.0f * (pixel.y - viewport.top) / viewport.height,
        0.0f,
        1.0f);

    return cam.getInverseTransform() * normalized;
}

glm::ivec2 RenderTarget::coordinatesToPixel(const glm::vec2& coordinate,
                                            const Camera& cam) const {
    const glm::vec2 normalized =
        cam.getTransform() * glm::vec4(coordinate.x, coordinate.y, 0.0f, 1.0f);
    const auto viewport = getViewport(cam);

    return glm::ivec2(
        static_cast<int>((normalized.x + 1.0f) / 2.0f * viewport.width +
                         viewport.left),
        static_cast<int>((normalized.y + 1.0f) / 2.0f * viewport.height +
                         viewport.top));
}

void RenderTarget::clear(const Color& clearColor) {
    auto* active = Context::getCurrentContext();

    getRenderingContext().setCurrent(true);
    glClearColor(static_cast<GLfloat>(clearColor.red) / 255,
                 static_cast<GLfloat>(clearColor.green) / 255,
                 static_cast<GLfloat>(clearColor.blue) / 255,
                 static_cast<GLfloat>(clearColor.alpha) / 255);
    glClear(GL_COLOR_BUFFER_BIT);

    if (active != nullptr) {
        active->setCurrent(true);
    }
}

void RenderTarget::draw(const Drawable& drawable,
                        const RenderState& renderState) {
    drawable.draw(*this, renderState);
}

void RenderTarget::drawTriangles(const VAO& vao,
                                 const std::size_t firstVertex,
                                 const std::size_t vertexCount,
                                 const RenderState& renderState) {
    auto* active = Context::getCurrentContext();

    getRenderingContext().setCurrent(true);

    if (m_cameraChanged) {
        const auto view = getViewport(getCamera());
        const auto top  = getPhysicalSize().y - (view.top + view.height);

        glViewport(view.left, top, view.width, view.height);
    }

    if (renderState.shader != nullptr) {
        renderState.shader->use();
        if (renderState.shader->hasUniform("transform")) {
            renderState.shader->setUniform("transform",
                                           renderState.transform *
                                               getCamera().getTransform());
        }
    }

    vao.bind();
    glDrawArrays(GL_TRIANGLES, firstVertex, vertexCount);

    if (active != nullptr) {
        active->setCurrent(true);
    }
}
}
