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

#ifndef SGE_COLOR_HPP
#define SGE_COLOR_HPP

#include <SGE/Export.hpp>
#include <SGE/Types.hpp>

namespace sge {
/**
 * \brief Color object
 *
 *
 * Object representing colors using 8bpp RGBA representation.
 */
class SGE_API Color {
public:
    /**
     * \brief Create color object
     * \param red Red value (0-255)
     * \param green Green value (0-255)
     * \param blue Blue value (0-255)
     * \param alpha Alpha value (0-255)
     */
    explicit Color(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 255);

    std::uint8_t red; ///< Red value
    std::uint8_t green; ///< Green value
    std::uint8_t blue; ///< Blue value
    std::uint8_t alpha; ///< Alpha value
};
}

#endif//SGE_COLOR_HPP
