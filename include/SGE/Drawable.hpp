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

#ifndef SGE_DRAWABLE_HPP
#define SGE_DRAWABLE_HPP

#include <SGE/Export.hpp>
#include <SGE/RenderState.hpp>

namespace sge {
class RenderTarget;

/**
 * \brief Drawable base object
 *
 *
 * Base for all objects that can be drawn on the screen
 */
class SGE_API Drawable {
protected:
    friend class RenderTarget;

    /**
     * \brief Draw object
     *
     * Override this function to draw your object onto a render target
     * \param target Render target to draw to
     * \param renderState Rendering state given by the render target
     */
    virtual void draw(RenderTarget& target, RenderState renderState) const = 0;
};
}

#endif//SGE_DRAWABLE_HPP
