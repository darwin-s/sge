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

#ifndef SGE_CONTEXTSETTINGS_HPP
#define SGE_CONTEXTSETTINGS_HPP

#include <SGE/Export.hpp>

namespace sge {
/**
 * \brief Object representing the settings for an OpenGL context
 *
 *
 * This classed is used to hold settings for the creation of an OpenGL
 * context. It holds only data, except for it's constructor.
 * \note All contexts in debug builds of the library are debug builds
 * \note All contexts are OpenGL 4.6 core contexts without forward compatibility
 */
struct SGE_API ContextSettings {
    /**
     * \brief Construct a settings object
     *
     *
     * Creates a settings object with the set parameters.
     * \param vsync Enable VSync for the context
     * \param samples Number of samples for MSAA (0 to disable)
     * \param debugContext OpenGL debug context
     * \param srgbCapable SRGB capable context
     * \param depthBits Number of bits for the depth buffer
     * \param stencilBits Number of bits for the stencil buffer
     * \param redBits Number of red bits
     * \param greenBits Number of green bits
     * \param blueBits Number of blue bits
     * \param alphaBits Number of alpha bits
     */
    explicit ContextSettings(bool vsync        = false,
                             int samples       = 0,
                             bool debugContext = false,
                             bool srgbCapable  = false,
                             int depthBits     = 24,
                             int stencilBits   = 8,
                             int redBits       = 8,
                             int greenBits     = 8,
                             int blueBits      = 8,
                             int alphaBits     = 8);

    bool vsync;       ///< VSync enabled
    int samples;      ///< MSAA samples
    bool debugContext;///< OpenGL debug context
    bool srgbCapable; ///< SRGB capable context
    int depthBits;    ///< Number of bits for the depth buffer
    int stencilBits;  ///< Number of bits for the stencil buffer
    int redBits;      ///< Number of red bits
    int greenBits;    ///< Number of green bits
    int blueBits;     ///< Number of blue bits
    int alphaBits;    ///< Number of alpha bits
};
}

#endif//SGE_CONTEXTSETTINGS_HPP
