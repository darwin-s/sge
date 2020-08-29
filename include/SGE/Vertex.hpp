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

#ifndef SGE_VERTEX_HPP
#define SGE_VERTEX_HPP

#include <SGE/Export.hpp>
#include <SGE/Types.hpp>
#include <SGE/Vector2.hpp>

namespace sge {
/**
 * \brief Vertex Object
 *
 *
 * Object representing a single vertex, used for drawing.
 */
struct SGE_API Vertex {
    float x;               ///< X position
    float y;               ///< Y position
    std::uint8_t tintRed;  ///< Red tint
    std::uint8_t tintGreen;///< Green tint
    std::uint8_t tintBlue; ///< Blue tind
    float u;               ///< U texture position
    float v;               ///< V texture position
};
}

#endif//SGE_VERTEX_HPP
