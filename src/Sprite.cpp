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

#include <SGE/Sprite.hpp>
#include <SGE/RenderTarget.hpp>

namespace sge {
Sprite::Sprite(Texture* texture,
               const RectangleFloat& textureRect,
               const glm::vec2& size)
    : m_tex(texture) {
    m_vertices[0].pos.x = 0.0f;
    m_vertices[0].pos.y = 0.0f;
    m_vertices[1].pos.y = 0.0f;
    m_vertices[2].pos.x = 0.0f;
    setTextureRectangle(textureRect);
    setModelSize(size);
    setTint(Color(255, 255, 255, 255));
}

void Sprite::setTexture(Texture* texture) {
    m_tex = texture;
}

void Sprite::setTextureRectangle(const RectangleFloat& textureRect) {
    m_textureRect          = textureRect;
    m_vertices[0].texPos.x = textureRect.left;
    m_vertices[0].texPos.y = textureRect.top;
    m_vertices[1].texPos.x = textureRect.left + textureRect.width;
    m_vertices[1].texPos.y = textureRect.top;
    m_vertices[2].texPos.x = textureRect.left;
    m_vertices[2].texPos.y = textureRect.top + textureRect.height;
    m_vertices[3].texPos.x = textureRect.left + textureRect.width;
    m_vertices[3].texPos.y = textureRect.top + textureRect.height;
}

void Sprite::setTint(const Color& tintColor) {
    m_vertices[0].tint = tintColor;
    m_vertices[1].tint = tintColor;
    m_vertices[2].tint = tintColor;
    m_vertices[3].tint = tintColor;
}

void Sprite::setModelSize(const float w, const float h) {
    m_vertices[1].pos.x = w;
    m_vertices[2].pos.y = -h;
    m_vertices[3].pos.x = w;
    m_vertices[3].pos.y = -h;
}

void Sprite::setModelSize(const glm::vec2& size) {
    setModelSize(size.x, size.y);
}

Texture* Sprite::getTexture() const {
    return m_tex;
}

const RectangleFloat& Sprite::getTextureRectangle() const {
    return m_textureRect;
}

const Color& Sprite::getTint() const {
    return m_vertices[0].tint;
}

RectangleFloat Sprite::getModelBounds() const {
    return RectangleFloat(0.0f,
                          0.0f,
                          m_vertices[1].pos.x,
                          -m_vertices[2].pos.y);
}

RectangleFloat Sprite::getWorldBounds() const {
    const glm::vec4 points[] = {
        getTransform() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        getTransform() * glm::vec4(m_vertices[1].pos.x, 0.0f, 0.0f, 1.0f),
        getTransform() * glm::vec4(0.0f, m_vertices[2].pos.y, 0.0f, 1.0f),
        getTransform() *
            glm::vec4(m_vertices[1].pos.x, m_vertices[2].pos.y, 0.0f, 1.0f)};

    const auto minX =
        std::min({points[0].x, points[1].x, points[2].x, points[3].x});// Left
    const auto maxX =
        std::max({points[0].x, points[1].x, points[2].x, points[3].x});// Right
    const auto minY =
        std::min({points[0].y, points[1].y, points[2].y, points[3].y});// Bottom
    const auto maxY =
        std::max({points[0].y, points[1].y, points[2].y, points[3].y});// Top

    return RectangleFloat(minX, maxY, maxX - minX, maxY - minY);
}

void Sprite::draw(RenderTarget& target, RenderState renderState) const {
    renderState.transform *= getTransform();
    renderState.texture = m_tex;

    target.drawQuad(m_vertices, renderState);
}
}
