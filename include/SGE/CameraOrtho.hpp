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

#ifndef SGE_CAMERAORTHO_HPP
#define SGE_CAMERAORTHO_HPP

#include <SGE/Export.hpp>
#include <SGE/Camera.hpp>
#include <glm/vec2.hpp>

namespace sge {
/**
 * \brief Camera with orthogonal projection
 * 
 * 
 * This object represents a camera with an orthogonal projection 
 * transform. When using orthogonal projection, the vertices don't get smaller 
 * when further from the camera. This type of camera is used mostly in 2D games or 
 * when drawing GUI overlays.
 */
class SGE_API CameraOrtho final : public sge::Camera {
public:
    /**
     * \brief Create camera
     *
     *
     * Creates a default camera, that displays the world from (-1, -1) to (1, 1).
     */
    CameraOrtho();

    /**
     * \brief Create camera
     *
     *
     * Creates a camera that display a rectangular area of the world.
     * \param rect Rectangle defining the camera's view
     */
    explicit CameraOrtho(const RectangleFloat& rect);

    /**
     * \brief Create camera
     *
     *
     * Creates a camera that is centered on a point and has a certain size.
     * \param center Center coordinates of the camera
     * \param size Size of the camera's rectangle
     */
    CameraOrtho(const glm::vec2& center, const glm::vec2& size);

    /**
     * \brief Set camera size
     * \param width Width of camera's view rectangle
     * \param height Height of camera's view rectangle
     */
    void setSize(float width, float height);

    /**
     * \brief Set camera size
     * \param size Size of the camera
     */
    void setSize(const glm::vec2& size);

    /**
     * \brief Set camera view rectangle
     * \param rect Rectangle representing the camera's view
     */
    void setRectangle(const RectangleFloat& rect);

    /**
     * \brief Get camera size
     * \return Size of camera's view rectangle
     */
    [[nodiscard]] const glm::vec2& getSize() const;

    /**
     * \brief Get camera view rectangle
     * \return Camera's view rectangle
     */
    [[nodiscard]] RectangleFloat getRectangle() const;

    [[nodiscard]] const glm::mat4& getPerspectiveTransform() const override;

private:
    glm::vec2 m_center;
    glm::vec2 m_size;
    mutable glm::mat4 m_transform;
    mutable bool m_transformNeedsUpdate;
};
}

#endif//SGE_CAMERAORTHO_HPP
