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

#include <SGE/CameraPersp.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sge {
CameraPersp::CameraPersp()
    : m_fov(-75.0f), m_aspectRatio(1.0f), m_nearPlane(0.1f),
      m_farPlane(1000.0f), m_transform(1.0f), m_transformNeedsUpdate(true) {
}

CameraPersp::CameraPersp(float fov, float aspectRatio, float near, float far)
    : m_fov(-fov), m_aspectRatio(aspectRatio), m_nearPlane(near),
      m_farPlane(far), m_transform(1.0f), m_transformNeedsUpdate(true) {
}
void CameraPersp::setFov(float fov) {
    m_fov = -fov;

    m_transformNeedsUpdate = true;
}

void CameraPersp::setAspectRatio(float aspectRatio) {
    m_aspectRatio = aspectRatio;

    m_transformNeedsUpdate = true;
}

void CameraPersp::setNearPlane(float near) {
    m_nearPlane = near;

    m_transformNeedsUpdate = true;
}

void CameraPersp::setFarPlane(float far) {
    m_farPlane = far;

    m_transformNeedsUpdate = true;
}

float CameraPersp::getFov() const {
    return m_fov;
}

float CameraPersp::getAspectRatio() const {
    return m_aspectRatio;
}

float CameraPersp::getNearPlane() const {
    return m_nearPlane;
}

float CameraPersp::getFarPlane() const {
    return m_farPlane;
}

const glm::mat4& CameraPersp::getPerspectiveTransform() const {
    if (m_transformNeedsUpdate) {
        m_transform = glm::perspective(glm::radians(75.0f), 1.0f, 0.1f, 10.0f);

        m_transformNeedsUpdate = false;
    }

    return m_transform;
}
}