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
    float x;
    float y;
    std::uint8_t tintRed;
    std::uint8_t tintGreen;
    std::uint8_t tintBlue;
    float u;
    float v;
};
}

#endif//SGE_VERTEX_HPP
