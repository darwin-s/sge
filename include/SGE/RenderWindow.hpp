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

#ifndef SGE_RENDERWINDOW_HPP
#define SGE_RENDERWINDOW_HPP

#include <SGE/Export.hpp>
#include <SGE/Window.hpp>
#include <SGE/RenderTarget.hpp>
#include <string_view>

namespace sge {

/**
 * \brief Render window object
 *
 *
 * Object representing a window, which is a render target.
 */
class SGE_API RenderWindow : public Window, public RenderTarget {
public:
    /**
     * \brief Create render window
     *
     *
     * Creates a window, setting only the context settings for this window.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param contextSettings Settings for the underlying context
     */
    explicit RenderWindow(ContextSettings contextSettings = ContextSettings());

    /**
     * \brief Create render window
     *
     *
     * Creates a window, setting it's title.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     * \param contextSettings Settings for the underlying context
     */
    explicit RenderWindow(std::string_view title, ContextSettings contextSettings = ContextSettings());

    /**
     * \brief Create render window
     *
     *
     * Creates a window, setting it's title and size.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     * \param size Size of the window
     * \param contextSettings Settings for the underlying context
     */
    RenderWindow(std::string_view title, Vector2I size, ContextSettings contextSettings = ContextSettings());

    /**
     * \brief Create render window
     *
     *
     * Creates a fullscreen window(not borderless window) on a monitor.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     * \param videoMode Video mode to be set
     * \param monitor Monitor on which to make the window fullscreen
     * \param contextSettings Settings for the underlying context
     */
    RenderWindow(std::string_view title, Monitor::VideoMode videoMode, const Monitor& monitor,
        ContextSettings contextSettings = ContextSettings());

    Context& getRenderingContext() override;

    Vector2U getPhysicalSize() const override;
};
}

#endif//SGE_RENDERWINDOW_HPP
