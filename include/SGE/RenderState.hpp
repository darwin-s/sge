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

#ifndef SGE_RENDERSTATE_HPP
#define SGE_RENDERSTATE_HPP

#include <SGE/Export.hpp>
#include <SGE/Matrix.hpp>

namespace sge {
class Shader;
class Texture;

/**
 * \brief Render state
 *
 *
 * Object that represents the current state of rendering, such as
 * the currently used shader, texture, etc.
 */
class SGE_API RenderState {
public:
    /**
     * \brief Construct render state
     * \param shader Shader program to be used for rendering
     */
    explicit RenderState(Shader* shader);

    /**
     * \brief Construct render state
     * \param transform Transform to be passed to shader program
     */
    explicit RenderState(const Matrix& transform);

    /**
     * \brief Construct render state
     * \param texture Texture to be used for rendering
     */
    explicit RenderState(Texture* texture);

    static RenderState defaultState;///< Default rendering state

    Shader* shader;
    Matrix transform;
    Texture* texture;
};
}

#endif//SGE_RENDERSTATE_HPP
