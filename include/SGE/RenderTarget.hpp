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
#include <SGE/CameraOrtho.hpp>
#include <SGE/VBO.hpp>
#include <SGE/VAO.hpp>
#include <SGE/Vertex.hpp>
#include <SGE/Shader.hpp>
#include <glm/vec2.hpp>

namespace sge {
class Drawable;
class Window;

/**
 * \brief Base for render targets
 *
 *
 * This objects serves as a base for all rendering targets, such as windows, textures, etc.
 */
class SGE_API RenderTarget {
public:
    /**
     * \brief Create rendering context
     *
     *
     * Creates a rendering context with an OpenGL context,
     * \param contextSettings Settings for the OpenGL context
     */
    explicit RenderTarget(
        const ContextSettings& contextSettings = ContextSettings());

    /**
     * \brief Create rendering context
     *
     *
     * Creates a rendering context for a window with an OpenGL context.
     * \param win Window to use for context
     * \param contextSettings Settings for the OpenGL context
     */
    explicit RenderTarget(
        const Window& win,
        const ContextSettings& contextSettings = ContextSettings());

    virtual ~RenderTarget();

    /**
     * \brief Get physical size
     *
     *
     * Get the physical size in pixels of the rendering target.
     * \return 
     */
    [[nodiscard]] virtual glm::ivec2 getPhysicalSize() const = 0;

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
    [[nodiscard]] const Camera* getCamera() const;

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
    glm::vec2 pixelToCoordinates(const glm::ivec2& pixel,
                                 const Camera& cam) const;

    /**
     * \brief Map world coordinates to pixel
     *
     *
     * Maps a world coordinate to the respective pixel position on screen.
     * \param coordinate World coordinates
     * \param cam Camera used to reference the view
     * \return Pixel coordinates
     */
    glm::ivec2 coordinatesToPixel(const glm::vec2& coordinate,
                                  const Camera& cam) const;

    Context& getContext();

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
    void draw(const Drawable& drawable,
              const RenderState& renderState = RenderState::defaultState);

    /**
     * \brief Draw Triangles
     * \param vertices Pointer to a vertex array with 3 vertices
     * \param renderState Rendering state
     */
    void
    drawTriangle(const Vertex* vertices,
                 const RenderState& renderState = RenderState::defaultState);

    /**
     * \brief Draw Quad
     * \param vertices Pointer to a vertex array with 4 vertices
     * \param renderState Rendering states
     */
    void drawQuad(const Vertex* vertices,
                  const RenderState& renderState = RenderState::defaultState);

    /**
     * \brief Flush rendering queue
     * 
     * 
     * Flushes all pending drawing operations.
     */
    void flushRenderQueue();

    static const CameraOrtho
        defaultCamera;///< Default camera for render targets

private:
    void setBuffers();

    const Camera* m_camera;
    Context m_context;
    VAO m_defaultVAO;
    VBO m_defaultVBO;
    VBO m_defaultEBO;
    std::size_t m_vertexCount;
    std::size_t m_indicesCount;
    unsigned int* m_indices;
    Vertex* m_verticesBatch;
    Shader* m_currentShader;
    void* m_sync;
    void* m_usedTextures;
    unsigned int m_usedTextureUnits;
};
}

#endif//SGE_RENDERTARGET_HPP
