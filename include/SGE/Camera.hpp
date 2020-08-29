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
#include <SGE/Matrix.hpp>
#include <SGE/Rectangle.hpp>
#include <SGE/Vector2.hpp>

namespace sge {
/**
 * \brief 2D Camera object
 *
 *
 * This object represents a 2D camera with the ability to set the viewport.
 * Setting the viewport allows to define where on the screen the camera's contents
 * will be drawn. The camera can be moved, rotated and zoomed.
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
     * Creates a default camera, that displays the world from (-1, -1) to (1, 1).
     */
    Camera();

    /**
     * \brief Create camera
     *
     *
     * Creates a camera that display a rectangular area of the world.
     * \param rect Rectangle defining the camera's view
     */
    explicit Camera(const RectangleFloat& rect);

    /**
     * \brief Create camera
     *
     *
     * Creates a camera that is centered on a point and has a certain size.
     * \param center Center coordinates of the camera
     * \param size Size of the camera's rectangle
     */
    Camera(const Vector2F& center, const Vector2F& size);

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
     * \brief Set camera center
     * \param x Center's x coordinate
     * \param y Center's y coordinate
     */
    void setCenter(float x, float y);

    /**
     * \brief Set camera center
     * \param center Position of the center
     */
    void setCenter(const Vector2F& center);

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
    void setSize(const Vector2F& size);

    /**
     * \brief Set camera view rectangle
     * \param rect Rectangle representing the camera's view
     */
    void setRectangle(const RectangleFloat& rect);

    /**
     * \brief Set camera rotation
     * \param degrees Camera rotation in degrees
     */
    void setRotation(float degrees);

    /**
     * \brief Move camera
     * \param x X offset
     * \param y Y offset
     */
    void move(float x, float y);

    /**
     * \brief Move camera
     * \param offset Position offset
     */
    void move(const Vector2F& offset);

    /**
     * \brief Zoom camera
     *
     *
     * Zooms the camera by a certain factor. A factor value of X makes the objects look X times bigger.
     * \param factor Zoom factor
     */
    void zoom(float factor);

    /**
     * \brief Rotate camera
     * \param degrees Rotation in degrees
     */
    void rotate(float degrees);

    /**
     * \brief Get viewport
     *
     * Returns the viewport size as a fraction of the rendering target's framebuffer
     * \return Viewport rectangle
     */
    [[nodiscard]] const RectangleFloat& getViewport() const;

    /**
     * \brief Get camera center
     * \return Camera center position
     */
    [[nodiscard]] const Vector2F& getCenter() const;

    /**
     * \brief Get camera size
     * \return Size of camera's view rectangle
     */
    [[nodiscard]] const Vector2F& getSize() const;

    /**
     * \brief Get camera view rectangle
     * \return Camera's view rectangle
     */
    [[nodiscard]] RectangleFloat getRectangle() const;

    /**
     * \brief Get camera rotation
     * \return Camera's rotation in degrees
     */
    [[nodiscard]] float getRoatation() const;

    /**
     * \brief Get camera's transform matrix
     * \return Transform to world coordinates
     */
    [[nodiscard]] const Matrix& getTransform() const;

    /**
     * \brief Get inverse of camera's transform matrix
     * \return Inverse of transform matrix
     */
    [[nodiscard]] const Matrix& getInverseTransform() const;

private:
    Vector2F m_center;
    Vector2F m_size;
    float m_rotation;
    RectangleFloat m_viewport;
    mutable Matrix m_transform;
    mutable bool m_transformNeedsUpdate;
    mutable Matrix m_inverseTransform;
    mutable bool m_inverseTransformNeedsUpdate;
};
}

#endif//SGE_CAMERA_HPP
