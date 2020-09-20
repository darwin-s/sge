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

#include <SGE/CameraOrtho.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sge {
CameraOrtho::CameraOrtho()
    : m_center(0.0f, 0.0f), m_size(2.0f, 2.0f), m_transform(1.0f),
      m_transformNeedsUpdate(true) {
}

CameraOrtho::CameraOrtho(const RectangleFloat& rect)
    : m_center(rect.left + rect.width / 2.0f, rect.top - rect.height / 2.0f),
      m_size(rect.width, rect.height), m_transform(1.0f),
      m_transformNeedsUpdate(true) {
}

CameraOrtho::CameraOrtho(const glm::vec2& center, const glm::vec2& size)
    : m_center(center), m_size(size), m_transform(1.0f),
      m_transformNeedsUpdate(true) {
}

/*void CameraOrtho::setCenter(const float x, const float y) {
    m_center.x = x;
    m_center.y = y;

    m_transformNeedsUpdate = true;
}

void CameraOrtho::setCenter(const glm::vec2& center) {
    setCenter(center.x, center.y);
}*/

void CameraOrtho::setSize(const float width, const float height) {
    m_size.x = width;
    m_size.y = height;

    m_transformNeedsUpdate = true;
}

void CameraOrtho::setSize(const glm::vec2& size) {
    setSize(size.x, size.y);
}

void CameraOrtho::setRectangle(const RectangleFloat& rect) {
    m_center.x = rect.left + rect.width / 2.0f;
    m_center.y = rect.top - rect.height / 2.0f;
    m_size.x   = rect.width;
    m_size.y   = rect.height;
}

/*void CameraOrtho::move(const float x, const float y) {
    setCenter(m_center.x + x, m_center.y + y);
}

void CameraOrtho::move(const glm::vec2& offset) {
    move(offset.x, offset.y);
}*/

/*const glm::vec2& CameraOrtho::getCenter() const {
    return m_center;
}*/

const glm::vec2& CameraOrtho::getSize() const {
    return m_size;
}

RectangleFloat CameraOrtho::getRectangle() const {
    const RectangleFloat rect{m_center.x - m_size.x / 2.0f,
                              m_center.y + m_size.y / 2.0f,
                              m_size.x,
                              m_size.y};
    return rect;
}

const glm::mat4& CameraOrtho::getPerspectiveTransform() const {
    if (m_transformNeedsUpdate) {
        RectangleFloat r = getRectangle();
        m_transform =
            glm::ortho(r.left, r.left + r.width, r.top - r.height, r.top);

        m_transformNeedsUpdate = false;
    }

    return m_transform;
}
}