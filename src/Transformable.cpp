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
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

namespace {
constexpr float PI = 3.14159265358979323846;
}

namespace sge {
Transformable::Transformable()
    : m_origin(0.0f, 0.0f, 0.0f), m_position(0.0f, 0.0f, 0.0f),
      m_scale(1.0f, 1.0f, 1.0f), m_rotation(0.0f), m_transform(1.0f),
      m_transformNeedsUpdate(true) {
}

void Transformable::setOrigin(const float x, const float y, const float z) {
    m_origin.x             = x;
    m_origin.y             = y;
    m_origin.z             = z;
    m_transformNeedsUpdate = true;
}

void Transformable::setOrigin(const glm::vec3& origin) {
    setOrigin(origin.x, origin.y, origin.z);
}

void Transformable::setPosition(const float x, const float y, const float z) {
    m_position.x           = x;
    m_position.y           = y;
    m_position.z           = z;
    m_transformNeedsUpdate = true;
}

void Transformable::setPosition(const glm::vec3& position) {
    setPosition(position.x, position.y, position.z);
}

void Transformable::setScale(const float xFactor,
                             const float yFactor,
                             float zFactor) {
    m_scale.x              = xFactor;
    m_scale.y              = yFactor;
    m_scale.z              = zFactor;
    m_transformNeedsUpdate = true;
}

void Transformable::setScale(const glm::vec3& factor) {
    setScale(factor.x, factor.y, factor.z);
}

void Transformable::setRotation(const float xDeg,
                                const float yDeg,
                                const float zDeg) {
    m_rotation.x = std::fmod(xDeg, 360.0f);
    m_rotation.y = std::fmod(yDeg, 360.0f);
    m_rotation.z = std::fmod(zDeg, 360.0f);

    if (m_rotation.x < 0.0f) {
        m_rotation.x += 360.0f;
    }
    if (m_rotation.y < 0.0f) {
        m_rotation.y += 360.0f;
    }
    if (m_rotation.z < 0.0f) {
        m_rotation.z += 360.0f;
    }

    m_transformNeedsUpdate = true;
}

void Transformable::setRotation(const glm::vec3& degrees) {
    setRotation(degrees.x, degrees.y, degrees.z);
}

void Transformable::move(const float x, const float y, const float z) {
    setPosition(m_position.x + x, m_position.y + y, m_position.z + z);
}

void Transformable::move(const glm::vec3& offset) {
    move(offset.x, offset.y, offset.z);
}

void Transformable::scale(const float xFactor,
                          const float yFactor,
                          const float zFactor) {
    setScale(m_scale.x * xFactor, m_scale.y * yFactor, m_scale.z * zFactor);
}

void Transformable::scale(const glm::vec3& factor) {
    scale(factor.x, factor.y, factor.z);
}

void Transformable::rotate(const float xDeg,
                           const float yDeg,
                           const float zDeg) {
    setRotation(m_rotation.x + xDeg, m_rotation.y + yDeg, m_rotation.z + zDeg);
}

void Transformable::rotate(const glm::vec3& degrees) {
    rotate(degrees.x, degrees.y, degrees.z);
}

const glm::vec3& Transformable::getOrigin() const {
    return m_origin;
}

const glm::vec3& Transformable::getPosition() const {
    return m_position;
}

const glm::vec3& Transformable::getScale() const {
    return m_scale;
}

glm::vec3 Transformable::getRotation() const {
    return m_rotation;
}

const glm::mat4& Transformable::getTransform() const {
    if (m_transformNeedsUpdate) {
        m_transform            = glm::mat4(1.0f);
        m_transform            = glm::translate(m_transform, m_position);
        m_transform            = glm::translate(m_transform, m_origin);
        m_transform            = glm::rotate(m_transform,
                                  glm::radians(m_rotation.x),
                                  glm::vec3(1.0f, 0.0f, 0.0f));
        m_transform            = glm::rotate(m_transform,
                                  glm::radians(m_rotation.y),
                                  glm::vec3(0.0f, 1.0f, 0.0f));
        m_transform            = glm::rotate(m_transform,
                                  glm::radians(m_rotation.z),
                                  glm::vec3(0.0f, 0.0f, 1.0f));
        m_transform            = glm::translate(m_transform, -m_origin);
        m_transform            = glm::scale(m_transform, m_scale);
        m_transformNeedsUpdate = false;
    }

    return m_transform;
}
}
