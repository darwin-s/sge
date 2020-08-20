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

#ifndef SGE_RENDERTARGET_HPP
#define SGE_RENDERTARGET_HPP

#include <SGE/Export.hpp>
#include <SGE/Context.hpp>
#include <SGE/RenderState.hpp>
#include <SGE/Color.hpp>
#include <SGE/Types.hpp>
#include <SGE/Vector2.hpp>
#include <SGE/Camera.hpp>

namespace sge {
class Drawable;
class VAO;

/**
 * \brief Base for render targets
 *
 *
 * This objects serves as a base for all rendering targets, such as windows, textures, etc.
 */
class SGE_API RenderTarget {
public:
    RenderTarget();

    virtual ~RenderTarget() = default;

    /**
     * \brief Get rendering context
     * \return Reference to the rendering context
     */
    [[nodiscard]] virtual Context& getRenderingContext() = 0;

    /**
     * \brief Get physical size
     *
     *
     * Get the physical size in pixels of the rendering target.
     * \return 
     */
    [[nodiscard]] virtual Vector2U getPhysicalSize() const = 0;

    /**
     * \brief Set camera
     *
     *
     * Sets the camera to be used with the current render target
     * \param camera Camera to be used with this target
     */
    void setCamera(const Camera& camera);

    /**
     * \brief Get camera
     * \return Currently used camera for this target
     */
    [[nodiscard]] const Camera& getCamera() const;

    /**
     * \brief Get viewport dimensions
     *
     *
     * Get the dimensions in pixels of a camera's viewport
     * \param cam Camera
     * \return Viewport rectangle
     */
    RectangleInt getViewport(const Camera& cam) const;

    /**
     * \brief Map pixel position to world coordinates
     *
     *
     * Maps a pixel on screen to the corresponding world coordinate.
     * \param pixel Pixel position
     * \param cam Camera used to reference the view
     * \return World coordinates
     */
    Vector2F pixelToCoordinates(const Vector2I& pixel, const Camera& cam) const;

    /**
     * \brief Map world coordinates to pixel
     *
     *
     * Maps a world coordinate to the respective pixel position on screen.
     * \param coordinate World coordinates
     * \param cam Camera used to reference the view
     * \return Pixel coordinates
     */
    Vector2I coordinatesToPixel(const Vector2F& coordinate, const Camera& cam) const;

    /**
     * \brief Clear the framebuffer
     * \param clearColor Color to fill with
     */
    void clear(const Color& clearColor = Color(0, 0, 0, 255));

    /**
     * \brief Draw a drawable object
     * \param drawable Reference to drawable object
     * \param renderState Rendering state
     */
    void draw(const Drawable& drawable, const RenderState& renderState = RenderState::defaultState);

    /**
     * \brief Draw triangles
     * \param vao VAO for drawing
     * \param firstVertex Index of first vertex
     * \param vertexCount Number of vertices
     * \param renderState Current rendering state
     */
    void drawTriangles(const VAO& vao, std::size_t firstVertex, std::size_t vertexCount,
                       const RenderState& renderState = RenderState::defaultState);

    static const Camera defaultCamera; ///< Default camera for render targets

private:
    bool m_cameraChanged;
    Camera m_camera;
};
}

#endif//SGE_RENDERTARGET_HPP
