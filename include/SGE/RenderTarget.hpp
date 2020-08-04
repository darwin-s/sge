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

    /**
     * \brief Get rendering context
     * \return Reference to the rendering context
     */
    virtual Context& getContext() = 0;

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
     */
    void drawTriangles(const VAO& vao, std::size_t firstVertex, std::size_t vertexCount,
                       const RenderState& renderState = RenderState::defaultState);

    /**
     * \brief Set viewport size
     *
     *
     * Sets the size of the OpenGL viewport
     * \param size Size of viewport
     */
    void setViewportSize(Vector2I size);
};
}

#endif//SGE_RENDERTARGET_HPP
