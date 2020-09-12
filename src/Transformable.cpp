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

#include <SGE/Transformable.hpp>
#include <cmath>

namespace {
constexpr float PI = 3.14159265358979323846;
}

namespace sge {
Transformable::Transformable()
    : m_origin(0.0f, 0.0f), m_position(0.0f, 0.0f), m_scale(1.0f, 1.0f),
      m_rotation(0.0f), m_transform(1.0f), m_transformNeedsUpdate(true) {
}

void Transformable::setOrigin(const float x, const float y) {
    m_origin.x             = x;
    m_origin.y             = y;
    m_transformNeedsUpdate = true;
}

void Transformable::setOrigin(const glm::vec2& origin) {
    setOrigin(origin.x, origin.y);
}

void Transformable::setPosition(const float x, const float y) {
    m_position.x           = x;
    m_position.y           = y;
    m_transformNeedsUpdate = true;
}

void Transformable::setPosition(const glm::vec2& position) {
    setPosition(position.x, position.y);
}

void Transformable::setScale(const float xFactor, const float yFactor) {
    m_scale.x              = xFactor;
    m_scale.y              = yFactor;
    m_transformNeedsUpdate = true;
}

void Transformable::setScale(const glm::vec2& factor) {
    setScale(factor.x, factor.y);
}

void Transformable::setRotation(const float degrees) {
    m_rotation = std::fmod(degrees, 360.0f);
    if (m_rotation < 0.0f) {
        m_rotation += 360.0f;
    }

    m_transformNeedsUpdate = true;
}

void Transformable::move(const float x, const float y) {
    setPosition(m_position.x + x, m_position.y + y);
}

void Transformable::move(const glm::vec2& offset) {
    move(offset.x, offset.y);
}

void Transformable::scale(const float xFactor, const float yFactor) {
    setScale(m_scale.x * xFactor, m_scale.y * yFactor);
}

void Transformable::scale(const glm::vec2& factor) {
    scale(factor.x, factor.y);
}

void Transformable::rotate(const float degrees) {
    setRotation(m_rotation + degrees);
}

const glm::vec2& Transformable::getOrigin() const {
    return m_origin;
}

const glm::vec2& Transformable::getPosition() const {
    return m_position;
}

const glm::vec2& Transformable::getScale() const {
    return m_scale;
}

float Transformable::getRotation() const {
    return m_rotation;
}

const glm::mat4& Transformable::getTransform() const {
    if (m_transformNeedsUpdate) {
        const auto radians = -m_rotation * PI / 180.0f;//Radians = angle*pi/180
        const auto cos     = std::cos(radians);
        const auto sin     = std::sin(radians);
        const auto scaleXCos = m_scale.x * cos;
        const auto scaleYCos = m_scale.y * cos;
        const auto scaleXSin = m_scale.x * sin;
        const auto scaleYSin = m_scale.y * sin;
        //This codes transforms the origin and then adds the position to it
        const auto translateX =
            -m_origin.x * scaleXCos - m_origin.y * scaleYSin + m_position.x;
        const auto translateY =
            m_origin.x * scaleXSin - m_origin.y * scaleYCos + m_position.y;

        m_transform = glm::mat4(scaleXCos,
                                -scaleXSin,
                                0.0f,
                                0.0f,
                                scaleYSin,
                                scaleYCos,
                                0.0f,
                                0.0f,
                                0.0f,
                                0.0f,
                                1.0f,
                                0.0f,
                                translateX,
                                translateY,
                                0.0f,
                                1.0f);

        m_transformNeedsUpdate = false;
    }

    return m_transform;
}
}
