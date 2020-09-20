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
#include <glm/gtc/matrix_transform.hpp>

namespace {
constexpr float PI = 3.14159265358979323846;
}

namespace sge {
Camera::Camera()
    : m_position(0.0f, 0.0f, 1.0f), m_direction(0.0f, 0.0f, -1.0f),
      m_rotation(0.0f, 0.0f), m_viewport(0.0f, 0.0f, 1.0f, 1.0f),
      m_transform(1.0f), m_transformNeedsUpdate(true) {
}

void Camera::setViewPort(const RectangleFloat& viewportRatio) {
    m_viewport = viewportRatio;
}

void Camera::lookAt(float x, float y, float z) {
    m_direction = glm::normalize(m_position - glm::vec3(x, y, z));

    m_transformNeedsUpdate = true;
}

void Camera::lookAt(const glm::vec3& position) {
    lookAt(position.x, position.y, position.z);
}

void Camera::setDirection(float x, float y, float z) {
    m_direction = glm::vec3(x, y, z);

    m_transformNeedsUpdate = true;
}

void Camera::setDirection(const glm::vec3& direction) {
    setDirection(direction.x, direction.y, direction.z);
}

void Camera::setPosition(float x, float y, float z) {
    m_position = glm::vec3(x, y, z);

    m_transformNeedsUpdate = true;
}

void Camera::setPosition(const glm::vec3& position) {
    setPosition(position.x, position.y, position.z);
}

void Camera::setRotation(float yaw, float pitch) {
    m_rotation = glm::vec2(yaw, pitch);
    m_direction.x =
        cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
    m_direction.y = sin(glm::radians(m_rotation.y));
    m_direction.z =
        sin(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
    m_direction = glm::normalize(m_direction);

    m_transformNeedsUpdate = true;
}

void Camera::setRotation(const glm::vec2& degrees) {
    setRotation(degrees.x, degrees.y);
}

void Camera::move(float x, float y, float z) {
    //glm::vec3 mv = glm::vec3(x, y, z);
    //mv *= m_direction;
    //setPosition(m_position.x + mv.x, m_position.y + mv.y, m_position.z + mv.z);
    m_position += z * m_direction;
    m_position += x *
        glm::normalize(glm::cross(m_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_position.y += y;

    m_transformNeedsUpdate = true;
}

void Camera::move(const glm::vec3& offset) {
    move(offset.x, offset.y, offset.z);
}

void Camera::rotate(float yaw, float pitch) {
    m_rotation.x += yaw;
    m_rotation.y -= pitch;

    m_direction.x +=
        cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
    m_direction.y += sin(glm::radians(m_rotation.y));
    m_direction.z +=
        sin(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
    m_direction = glm::normalize(m_direction);

    m_transformNeedsUpdate = true;
}

void Camera::rotate(const glm::vec2& degrees) {
    rotate(degrees.x, degrees.y);
}

const RectangleFloat& Camera::getViewport() const {
    return m_viewport;
}

const glm::vec3& Camera::getPosition() const {
    return m_position;
}

const glm::vec3& Camera::getDirection() const {
    return m_direction;
}

const glm::vec2& Camera::getRotation() const {
    return m_rotation;
}

glm::mat4 Camera::getTransform() const {
    if (m_transformNeedsUpdate) {
        glm::vec3 dir = m_direction;
        /*if (m_rotation.x != 0 && m_rotation.y != 0) {
            dir.x = cos(glm::radians(m_rotation.x)) *
                cos(glm::radians(m_rotation.y));
            dir.y = sin(glm::radians(m_rotation.y));
            dir.z = sin(glm::radians(m_rotation.x)) *
                cos(glm::radians(m_rotation.y));
            dir = glm::normalize(dir);
        }*/

        m_transform = glm::lookAt(m_position,
                                  m_position + dir,
                                  glm::vec3(0.0f, 1.0f, 0.0f));

        m_transformNeedsUpdate = false;
    }

    return getPerspectiveTransform() * m_transform;
}

glm::mat4 Camera::getInverseTransform() const {
    return glm::inverse(getTransform());
}
}
