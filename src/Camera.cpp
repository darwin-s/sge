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

#include <SGE/Camera.hpp>
#include <cmath>

namespace {
constexpr float PI = 3.14159265358979323846;
}

namespace sge {
Camera::Camera()
    : m_center(0.0f, 0.0f), m_size(2.0f, 2.0f), m_rotation(0.0f),
      m_viewport(0.0f, 0.0f, 1.0f, 1.0f), m_transform(1.0f),
      m_transformNeedsUpdate(true), m_inverseTransform(1.0f),
      m_inverseTransformNeedsUpdate(true) {
}

Camera::Camera(const RectangleFloat& rect)
    : m_center(rect.left + rect.width / 2.0f, rect.top - rect.height / 2.0f),
      m_size(rect.width, rect.height), m_rotation(0.0f),
      m_viewport(0.0f, 0.0f, 1.0f, 1.0f), m_transform(1.0f),
      m_transformNeedsUpdate(true), m_inverseTransform(1.0f),
      m_inverseTransformNeedsUpdate(true) {
}

Camera::Camera(const glm::vec2& center, const glm::vec2& size)
    : m_center(center), m_size(size), m_rotation(0.0f),
      m_viewport(0.0f, 0.0f, 1.0f, 1.0f), m_transform(1.0f),
      m_transformNeedsUpdate(true), m_inverseTransform(1.0f),
      m_inverseTransformNeedsUpdate(true) {
}

void Camera::setViewPort(const RectangleFloat& viewportRatio) {
    m_viewport = viewportRatio;
}

void Camera::setCenter(const float x, const float y) {
    m_center.x = x;
    m_center.y = y;

    m_transformNeedsUpdate        = true;
    m_inverseTransformNeedsUpdate = true;
}

void Camera::setCenter(const glm::vec2& center) {
    setCenter(center.x, center.y);
}

void Camera::setSize(const float width, const float height) {
    m_size.x = width;
    m_size.y = height;

    m_transformNeedsUpdate        = true;
    m_inverseTransformNeedsUpdate = true;
}

void Camera::setSize(const glm::vec2& size) {
    setSize(size.x, size.y);
}

void Camera::setRectangle(const RectangleFloat& rect) {
    m_center.x = rect.left + rect.width / 2.0f;
    m_center.y = rect.top - rect.height / 2.0f;
    m_size.x   = rect.width;
    m_size.y   = rect.height;
}

void Camera::setRotation(const float degrees) {
    m_rotation = std::fmod(degrees, 360.0f);
    if (m_rotation < 0.0f) {
        m_rotation += 360.0f;
    }

    m_transformNeedsUpdate        = true;
    m_inverseTransformNeedsUpdate = true;
}

void Camera::move(const float x, const float y) {
    setCenter(m_center.x + x, m_center.y + y);
}

void Camera::move(const glm::vec2& offset) {
    move(offset.x, offset.y);
}

void Camera::zoom(const float factor) {
    const auto zoom = 1.0f /
        factor;//For example a 2x zoom would mean shrinking the view size twice

    setSize(m_size.x * zoom, m_size.y * zoom);
}

void Camera::rotate(const float degrees) {
    setRotation(m_rotation + degrees);
}

const RectangleFloat& Camera::getViewport() const {
    return m_viewport;
}

const glm::vec2& Camera::getCenter() const {
    return m_center;
}

const glm::vec2& Camera::getSize() const {
    return m_size;
}

RectangleFloat Camera::getRectangle() const {
    const RectangleFloat rect{m_center.x - m_size.x / 2.0f,
                              m_center.y + m_size.y / 2.0f,
                              m_size.x,
                              m_size.y};
    return rect;
}

float Camera::getRotation() const {
    return m_rotation;
}

const glm::mat4& Camera::getTransform() const {
    if (m_transformNeedsUpdate) {
        const auto radians = m_rotation * PI / 180.0f;//Radians = angle*pi/180
        const auto cos     = std::cos(radians);
        const auto sin     = std::sin(radians);
        const auto translateX =
            -m_center.x * cos - m_center.y * sin + m_center.x;
        const auto translateY =
            m_center.x * sin - m_center.y * cos + m_center.y;

        const auto a = 2.0f / m_size.x;
        const auto b = 2.0f / m_size.y;
        const auto c = -a * m_center.x;
        const auto d = -b * m_center.y;

        m_transform = glm::mat4(a * cos,
                                -b * sin,
                                0.0f,
                                0.0f,
                                a * sin,
                                b * cos,
                                0.0f,
                                0.0f,
                                0.0f,
                                0.0f,
                                1.0f,
                                0.0f,
                                a * translateX + c,
                                b * translateY + d,
                                0.0f,
                                1.0f);

        m_transformNeedsUpdate = false;
    }

    return m_transform;
}

const glm::mat4& Camera::getInverseTransform() const {
    if (m_inverseTransformNeedsUpdate) {
        m_inverseTransform            = glm::inverse(getTransform());
        m_inverseTransformNeedsUpdate = false;
    }

    return m_inverseTransform;
}
}
