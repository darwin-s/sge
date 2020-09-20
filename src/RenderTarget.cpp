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
#include <SGE/Texture.hpp>
#include <SGE/Application.hpp>
#include <cmath>
#include <glad.h>

namespace {
constexpr std::size_t batchVerticesNum = 1000;
unsigned int maxTextures               = 0;
}

namespace sge {
const CameraOrtho RenderTarget::defaultCamera = CameraOrtho();

RenderTarget::RenderTarget(const ContextSettings& contextSettings)
    : m_camera(&defaultCamera), m_context(contextSettings), m_vertexCount(0),
      m_indicesCount(0), m_indices(nullptr), m_verticesBatch(nullptr),
      m_currentShader(nullptr), m_sync(nullptr), m_usedTextures(nullptr),
      m_usedTextureUnits(0) {
    glEnable(GL_DEPTH_TEST);
    setBuffers();
    try {
        m_usedTextures = new std::vector<Texture*>;
    } catch (...) {
        Application::crashApplication("Bad alloc");
    }
    auto* ut = reinterpret_cast<std::vector<Texture*>*>(m_usedTextures);
    ut->reserve(maxTextures);
}

RenderTarget::RenderTarget(const Window& win,
                           const ContextSettings& contextSettings)
    : m_camera(&defaultCamera), m_context(win, contextSettings),
      m_vertexCount(0), m_indicesCount(0), m_indices(nullptr),
      m_verticesBatch(nullptr), m_currentShader(nullptr), m_sync(nullptr),
      m_usedTextures(nullptr), m_usedTextureUnits(0) {
    glEnable(GL_DEPTH_TEST);
    setBuffers();
    try {
        m_usedTextures = new std::vector<Texture*>;
    } catch (...) {
        Application::crashApplication("Bad alloc");
    }
    auto* ut = reinterpret_cast<std::vector<Texture*>*>(m_usedTextures);
    ut->reserve(maxTextures);
}

RenderTarget::~RenderTarget() {
    auto* ut = reinterpret_cast<std::vector<Texture*>*>(m_usedTextures);
    delete ut;
}

void RenderTarget::setCamera(const Camera& camera) {
    flushRenderQueue();

    m_camera = &camera;
}

const Camera* RenderTarget::getCamera() const {
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

Context& RenderTarget::getContext() {
    return m_context;
}

void RenderTarget::clear(const Color& clearColor) {
    auto* active = Context::getCurrentContext();

    m_context.setCurrent(true);
    glClearColor(static_cast<GLfloat>(clearColor.red) / 255,
                 static_cast<GLfloat>(clearColor.green) / 255,
                 static_cast<GLfloat>(clearColor.blue) / 255,
                 static_cast<GLfloat>(clearColor.alpha) / 255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (active != nullptr) {
        active->setCurrent(true);
    }
}

void RenderTarget::draw(const Drawable& drawable,
                        const RenderState& renderState) {
    drawable.draw(*this, renderState);
}

void RenderTarget::drawTriangle(const Vertex* vertices,
                                const RenderState& renderState) {
    m_context.setCurrent(true);
    auto* ut = reinterpret_cast<std::vector<Texture*>*>(m_usedTextures);

    if (m_currentShader == nullptr) {
        m_currentShader = renderState.shader;
    }

    if (m_vertexCount + 2 >= batchVerticesNum) {
        flushRenderQueue();
    }

    if (m_indicesCount + 2 >= batchVerticesNum) {
        flushRenderQueue();
    }

    unsigned int textureUnit = 0;
    bool newTexture          = true;
    for (unsigned int i = 0; i < ut->size(); i++) {
        try {
            if (ut->at(i) == renderState.texture || ut->at(i) == nullptr) {
                newTexture  = false;
                textureUnit = i;
                break;
            }
        } catch (...) {
            Application::crashApplication("Failed to access vector");
        }
    }

    if (newTexture && m_usedTextureUnits + 1 >= maxTextures) {
        flushRenderQueue();
    }

    if (renderState.shader != m_currentShader) {
        flushRenderQueue();
        m_currentShader = renderState.shader;
    }

    if (newTexture) {
        try {
            ut->push_back(renderState.texture);
        } catch (...) {
            Application::crashApplication("Cannot push back to vector");
        }
        textureUnit = m_usedTextureUnits;
        m_usedTextureUnits++;
    }

    if (m_sync != nullptr) {
        GLenum waitReturn = GL_UNSIGNALED;
        while (waitReturn != GL_ALREADY_SIGNALED &&
               waitReturn != GL_CONDITION_SATISFIED) {
            waitReturn = glClientWaitSync(static_cast<GLsync>(m_sync),
                                          GL_SYNC_FLUSH_COMMANDS_BIT,
                                          1);
        }
        glDeleteSync(static_cast<GLsync>(m_sync));
        m_sync = nullptr;
    }

    m_verticesBatch[m_vertexCount].pos =
        renderState.transform * glm::vec4(vertices[0].pos, 1.0f);
    m_verticesBatch[m_vertexCount].tint    = vertices[0].tint;
    m_verticesBatch[m_vertexCount].texPos  = vertices[0].texPos;
    m_verticesBatch[m_vertexCount].texUnit = textureUnit;
    m_verticesBatch[m_vertexCount + 1].pos =
        renderState.transform * glm::vec4(vertices[1].pos, 1.0f);
    m_verticesBatch[m_vertexCount + 1].tint    = vertices[1].tint;
    m_verticesBatch[m_vertexCount + 1].texPos  = vertices[1].texPos;
    m_verticesBatch[m_vertexCount + 1].texUnit = textureUnit;
    m_verticesBatch[m_vertexCount + 2].pos =
        renderState.transform * glm::vec4(vertices[2].pos, 1.0f);
    m_verticesBatch[m_vertexCount + 2].tint    = vertices[2].tint;
    m_verticesBatch[m_vertexCount + 2].texPos  = vertices[2].texPos;
    m_verticesBatch[m_vertexCount + 2].texUnit = textureUnit;
    m_indices[m_indicesCount]                  = m_vertexCount;
    m_indices[m_indicesCount + 1]              = m_vertexCount + 1;
    m_indices[m_indicesCount + 2]              = m_vertexCount + 2;

    m_defaultVBO.flushChanges(sizeof(Vertex) * m_vertexCount,
                              sizeof(Vertex) * 3);

    m_defaultEBO.flushChanges(sizeof(unsigned int) * m_vertexCount,
                              sizeof(unsigned int) * 3);

    m_vertexCount += 3;
    m_indicesCount += 3;
}

void RenderTarget::drawQuad(const Vertex* vertices,
                            const RenderState& renderState) {
    m_context.setCurrent(true);
    auto* ut = reinterpret_cast<std::vector<Texture*>*>(m_usedTextures);

    if (m_currentShader == nullptr) {
        m_currentShader = renderState.shader;
    }

    if (m_vertexCount + 3 >= batchVerticesNum) {
        flushRenderQueue();
    }

    if (m_indicesCount + 5 >= batchVerticesNum) {
        flushRenderQueue();
    }

    unsigned int textureUnit = 0;
    bool newTexture          = true;
    for (unsigned int i = 0; i < ut->size(); i++) {
        try {
            if (ut->at(i) == renderState.texture || ut->at(i) == nullptr) {
                newTexture  = false;
                textureUnit = i;
                break;
            }
        } catch (...) {
            Application::crashApplication("Failed to access vector");
        }
    }

    if (newTexture && m_usedTextureUnits + 1 >= maxTextures) {
        flushRenderQueue();
    }

    if (renderState.shader != m_currentShader) {
        flushRenderQueue();
        m_currentShader = renderState.shader;
    }

    if (newTexture) {
        try {
            ut->push_back(renderState.texture);
        } catch (...) {
            Application::crashApplication("Cannot push back to vector");
        }
        textureUnit = m_usedTextureUnits;
        m_usedTextureUnits++;
    }

    if (m_sync != nullptr) {
        GLenum waitReturn = GL_UNSIGNALED;
        while (waitReturn != GL_ALREADY_SIGNALED &&
               waitReturn != GL_CONDITION_SATISFIED) {
            waitReturn = glClientWaitSync(static_cast<GLsync>(m_sync),
                                          GL_SYNC_FLUSH_COMMANDS_BIT,
                                          1);
        }
        glDeleteSync(static_cast<GLsync>(m_sync));
        m_sync = nullptr;
    }

    m_verticesBatch[m_vertexCount].pos =
        renderState.transform * glm::vec4(vertices[0].pos, 1.0f);
    m_verticesBatch[m_vertexCount].tint    = vertices[0].tint;
    m_verticesBatch[m_vertexCount].texPos  = vertices[0].texPos;
    m_verticesBatch[m_vertexCount].texUnit = textureUnit;
    m_verticesBatch[m_vertexCount + 1].pos =
        renderState.transform * glm::vec4(vertices[1].pos, 1.0f);
    m_verticesBatch[m_vertexCount + 1].tint    = vertices[1].tint;
    m_verticesBatch[m_vertexCount + 1].texPos  = vertices[1].texPos;
    m_verticesBatch[m_vertexCount + 1].texUnit = textureUnit;
    m_verticesBatch[m_vertexCount + 2].pos =
        renderState.transform * glm::vec4(vertices[2].pos, 1.0f);
    m_verticesBatch[m_vertexCount + 2].tint    = vertices[2].tint;
    m_verticesBatch[m_vertexCount + 2].texPos  = vertices[2].texPos;
    m_verticesBatch[m_vertexCount + 2].texUnit = textureUnit;
    m_verticesBatch[m_vertexCount + 3].pos =
        renderState.transform * glm::vec4(vertices[3].pos, 1.0f);
    m_verticesBatch[m_vertexCount + 3].tint    = vertices[3].tint;
    m_verticesBatch[m_vertexCount + 3].texPos  = vertices[3].texPos;
    m_verticesBatch[m_vertexCount + 3].texUnit = textureUnit;
    m_indices[m_indicesCount]                  = m_vertexCount;
    m_indices[m_indicesCount + 1]              = m_vertexCount + 1;
    m_indices[m_indicesCount + 2]              = m_vertexCount + 2;
    m_indices[m_indicesCount + 3]              = m_vertexCount + 2;
    m_indices[m_indicesCount + 4]              = m_vertexCount + 1;
    m_indices[m_indicesCount + 5]              = m_vertexCount + 3;

    m_defaultVBO.flushChanges(sizeof(Vertex) * m_vertexCount,
                              sizeof(Vertex) * 4);

    m_defaultEBO.flushChanges(sizeof(unsigned int) * m_vertexCount,
                              sizeof(unsigned int) * 6);

    m_vertexCount += 4;
    m_indicesCount += 6;
}

void RenderTarget::flushRenderQueue() {
    if (m_vertexCount == 0) {
        return;
    }

    auto* ut = reinterpret_cast<std::vector<Texture*>*>(m_usedTextures);

    const auto view = getViewport(*getCamera());
    const auto top  = getPhysicalSize().y - (view.top + view.height);

    glViewport(view.left, top, view.width, view.height);

    if (m_currentShader != nullptr) {
        m_currentShader->use();
        if (m_currentShader->hasUniform("transform")) {
            m_currentShader->setUniform("transform",
                                        getCamera()->getTransform());
        }

        if (m_currentShader->hasUniform("tex[0]")) {
            for (int i = 0; i < m_usedTextureUnits; i++) {
                try {
                    std::string u = "tex[" + std::to_string(i) + "]";
                    m_currentShader->setUniform(u.c_str(), i);
                    ut->at(i)->bind(i);
                } catch (...) {
                    Application::crashApplication("Failed string manipulation");
                }
            }
        }
    }

    glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);

    if (m_sync != nullptr) {
        glDeleteSync(static_cast<GLsync>(m_sync));
    }

    m_sync = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

    m_vertexCount      = 0;
    m_indicesCount     = 0;
    m_usedTextureUnits = 0;
    ut->clear();
    m_currentShader = nullptr;
}

void RenderTarget::setBuffers() {
    m_defaultVBO.allocate(sizeof(Vertex) * batchVerticesNum, VBO::WriteAccess);
    m_defaultEBO.allocate(sizeof(unsigned int) * batchVerticesNum,
                          VBO::WriteAccess);
    m_defaultVAO.bindVBO(m_defaultVBO, 0, 0, sizeof(Vertex));
    m_defaultVAO.enableAttribute(0);
    m_defaultVAO.enableAttribute(1);
    m_defaultVAO.enableAttribute(2);
    m_defaultVAO.enableAttribute(3);
    m_defaultVAO.setAttributeFormat(0,
                                    3,
                                    VAO::Data::Float,
                                    true,
                                    offsetof(Vertex, pos));
    m_defaultVAO.setAttributeFormat(1,
                                    3,
                                    VAO::Data::UnsignedByte,
                                    true,
                                    offsetof(Vertex, tint));
    m_defaultVAO.setAttributeFormat(2,
                                    2,
                                    VAO::Data::Float,
                                    true,
                                    offsetof(Vertex, texPos));
    m_defaultVAO.setAttributeFormat(3,
                                    1,
                                    VAO::Data::Float,
                                    false,
                                    offsetof(Vertex, texUnit));
    m_defaultVAO.setAttributeBinding(0, 0);
    m_defaultVAO.setAttributeBinding(1, 0);
    m_defaultVAO.setAttributeBinding(2, 0);
    m_defaultVAO.setAttributeBinding(3, 0);

    m_verticesBatch =
        static_cast<Vertex*>(m_defaultVBO.mapBuffer(0,
                                                    m_defaultVBO.getSize(),
                                                    VBO::WriteAccess,
                                                    true));
    m_indices = static_cast<unsigned int*>(
        m_defaultEBO.mapBuffer(0,
                               m_defaultEBO.getSize(),
                               VBO::WriteAccess,
                               true));

    m_defaultVAO.bind();
    m_defaultEBO.bindElementArray();

    if (maxTextures == 0) {
        maxTextures = Texture::getMaximumImageUnits();
        if (maxTextures > 32) {
            maxTextures = 32;
        }
    }
}
}
