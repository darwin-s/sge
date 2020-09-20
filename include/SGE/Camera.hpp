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

#ifndef SGE_CAMERA_HPP
#define SGE_CAMERA_HPP

#include <SGE/Export.hpp>
#include <SGE/Rectangle.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

namespace sge {
/**
 * \brief Camera object
 *
 *
 * This object represents a camera with the ability to set the viewport.
 * Setting the viewport allows to define where on the screen the camera's contents
 * will be drawn. The camera can be moved, rotated and zoomed. This is a base class for cameras 
 * with different perspective transforms.
 * Usage example:
 * \code
 * sge::Camera map(sge::RectangleFloat(0.0f, 0.0f, 10.0f, 10.0f)); // Camera that shows the world from (0, 0) to (10, 10)
 * map.setViewPort(sge::RectangleFloat(0.75f, 0.0f, 0.25f, 0.25f)); // Camera will display in the top left corner;
 * renderTarget.setCamera(map);
 * renderTarget.draw(world);
 * renderTarget.setCamera(sge::RenderTarget::defaultCamera); // Set back the default camera
 * renderTarget.draw(overlay); // Draw something on top of the screen
 * \endcode
 */
class SGE_API Camera {
public:
    /**
     * \brief Create camera
     *
     *
     * Creates a default camera at (0, 0, 1) looking towards negative Z with no rotation
     */
    Camera();

    /**
     * \brief Set camera viewport
     *
     *
     * Sets the camera's viewport to a fraction of the rendering target's one.
     * A viewport ratio of (0, 0, 1, 1) will fill the whole screen.
     * \param viewportRatio Ratio of position and size of the viewport
     */
    void setViewPort(const RectangleFloat& viewportRatio);

    /**
     * \brief Look at position
     * \param x X position
     * \param y Y position
     * \param z Z position
     */
    void lookAt(float x, float y, float z = 0.0f);

    /**
     * \brief Look at position
     * \param position Position to look towards
     */
    void lookAt(const glm::vec3& position);

    /**
     * \brief Set the camera's direction vector
     * 
     * 
     * \note The direction values must be normalized
     * \param x X direction
     * \param y Y direction
     * \param z Z direction
     */
    void setDirection(float x, float y, float z = -1.0f);

    /**
     * \brief Set the camera's direction vector
     * 
     * 
     * \note The direction vector must be normalized
     * \param direction Direction vector
     */
    void setDirection(const glm::vec3& direction);

    /**
     * \brief Set camera position
     * \param x X position
     * \param y Y position
     * \param z Z position
     */
    void setPosition(float x, float y, float z = 1.0f);

    /**
     * \brief Set camera position
     * \param position Position of the camera
     */
    void setPosition(const glm::vec3& position);

    /**
     * \brief Set camera rotation
     * \param yaw Yaw rotation in degrees
     * \param pitch Piych rotation in degrees
     */
    void setRotation(float yaw, float pitch);

    /**
     * \brief Set camera rotation
     * 
     * 
     * Sets camera rotation (X - yaw, Y - pitch)
     * \param degrees Camera rotation vector in degrees
     */
    void setRotation(const glm::vec2& degrees);

    /**
     * \brief Move camera
     * \param x X offset
     * \param y Y offset
     * \param z Z offset
     */
    void move(float x, float y, float z = 0.0f);

    /**
     * \brief Move camera
     * \param offset Position offset
     */
    void move(const glm::vec3& offset);

    /**
     * \brief Rotate camera
     * \param yaw Yaw rotation in degrees
     * \param pitch Piych rotation in degrees
     */
    void rotate(float yaw, float pitch);

    /**
     * \brief Rotate camera
     * 
     * 
     * Rotate camera (X - yaw, Y - pitch)
     * \param degrees Rotation vector in degrees
     */
    void rotate(const glm::vec2& degrees);

    /**
     * \brief Get viewport
     *
     * Returns the viewport size as a fraction of the rendering target's framebuffer
     * \return Viewport rectangle
     */
    [[nodiscard]] const RectangleFloat& getViewport() const;

    /**
     * \brief Get camera postion
     * \return Camera position
     */
    [[nodiscard]] const glm::vec3& getPosition() const;

    /**
     * \brief Get normalized direction vector
     * \return Direction vector of the camera
     */
    [[nodiscard]] const glm::vec3& getDirection() const;

    /**
     * \brief Get camera rotation
     * 
     * 
     * Get camera's rotation vector (X - yaw, Y - pitch)
     * \return Camera's rotation in degrees
     */
    [[nodiscard]] const glm::vec2& getRotation() const;

    /**
     * \brief Get camera transform
     * \return Camera perspective and view transform
     */
    [[nodiscard]] glm::mat4 getTransform() const;

    /**
     * \brief Get camera's perspective transform matrix
     * \return Perspective transform
     */
    [[nodiscard]] virtual const glm::mat4& getPerspectiveTransform() const = 0;

    /**
     * \brief Get inverse of camera's transform matrix
     * \return Inverse of transform matrix
     */
    [[nodiscard]] glm::mat4 getInverseTransform() const;

private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    glm::vec2 m_rotation;
    RectangleFloat m_viewport;
    mutable glm::mat4 m_transform;
    mutable bool m_transformNeedsUpdate;
};
}

#endif//SGE_CAMERA_HPP
