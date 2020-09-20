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

#ifndef SGE_CAMERAPERSP_HPP
#define SGE_CAMERAPERSP_HPP

#include <SGE/Export.hpp>
#include <SGE/Camera.hpp>

namespace sge {
/**
 * \brief Camera with perspective projection
 * 
 * 
 * This object represents a camera with perspective projection 
 * transform. This type of projection is used in 3D games. The vertices 
 * get smaller, the further they are from the camera.
 */
class SGE_API CameraPersp final : public sge::Camera {
public:
    /**
     * \brief Create perspective camera
     * 
     * 
     * Creates a perspective camera fiv 75 degree FOV, a 1:1 aspect ratio, a 0.1 near plane 
     * and 1000 far plane distance.
     */
    CameraPersp();

    /**
     * \brief Create perspective camera
     * 
     * 
     * Creates a perspective camera with the specified parameters.
     * \param fov Field of view value in degrees
     * \param aspectRatio Aspect ratio of the perspective
     * \param near Near plane of the perspective
     * \param far Far plane of the perspective
     */
    CameraPersp(float fov,
                float aspectRatio,
                float near = 0.1f,
                float far  = 1000.0f);

    /**
     * \brief Set camera fov
     * \param fov Field of View in degrees 
     */
    void setFov(float fov);

    /**
     * \brief Set camera aspect ratio
     * \param aspectRatio New aspect ratio 
     */
    void setAspectRatio(float aspectRatio);

    /**
     * \brief Set camera near plane distance
     * \param near Near plane distance
     */
    void setNearPlane(float near);

    /**
     * \brief Set camera far plane distance
     * \param far Far plane distance
     */
    void setFarPlane(float far);

    /**
     * \brief Get camera fov
     * \return Field of View of the camera in degrees 
     */
    [[nodiscard]] float getFov() const;

    /**
     * \brief Get aspect ratio
     * \return Aspect ratio of the camera
     */
    [[nodiscard]] float getAspectRatio() const;

    /**
     * \brief Get the near plane
     * \return Near plane of the camera
     */
    [[nodiscard]] float getNearPlane() const;

    /**
     * \brief Get the far plane
     * \return Far plane of the camera
     */
    [[nodiscard]] float getFarPlane() const;

    [[nodiscard]] virtual const glm::mat4&
    getPerspectiveTransform() const override;

private:
    float m_fov;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
    mutable glm::mat4 m_transform;
    mutable bool m_transformNeedsUpdate;
};
}

#endif//SGE_CAMERAPERSP_HPP
