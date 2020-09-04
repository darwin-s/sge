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

#ifndef SGE_WINDOW_HPP
#define SGE_WINDOW_HPP

#include <SGE/Export.hpp>
#include <SGE/Monitor.hpp>
#include <SGE/EventHandler.hpp>
#include <SGE/ContextSettings.hpp>
#include <SGE/Context.hpp>
#include <string_view>

namespace sge {
/**
 * \brief Object representing a window
 *
 * This object is used to represent a window on the user's screen.
 * It allows manipulation of the window and making it fullscreen on any monitor.
 * \note Windows should be created adn their events should be processed only on the main thread
 *
 * Usage example:
 * \code
 * sge::window w("title");
 * w.show();
 * while (w.isOpen()) {
 *     //...
 * }
 * \endcode
 */
class SGE_API Window {
public:
    /**
     * \brief Create window
     *
     *
     * Creates a window
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     */
    explicit Window();

    /**
     * \brief Create window
     *
     *
     * Creates a window, setting it's title.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     */
    explicit Window(std::string_view title);

    /**
     * \brief Create window
     *
     *
     * Creates a window, setting it's title and size.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     * \param size Size of the window
     */
    Window(std::string_view title,
           const glm::ivec2& size);

    /**
     * \brief Create window
     *
     *
     * Creates a fullscreen window.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     * \param videoMode Video mode to be set
     */
    Window(std::string_view title,
           const Monitor::VideoMode& videoMode);
    Window(const Window&)     = delete;
    Window(Window&&) noexcept = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) noexcept = delete;

    /**
     * \brief Destroy a window
     *
     *
     * Closes a window definitively.
     */
    virtual ~Window();

    /**
     * \brief Show window
     *
     *
     * Makes the window visible on screen.
     */
    void show();

    /**
     * \brief Get window open state
     *
     *
     * Returns a boolean telling whether the window is still opened or not.
     * \return true if the window is still opened, false otherwise
     */
    [[nodiscard]] bool isOpen() const;

    /**
     * \brief Set the window event handler
     *
     *
     * Sets the event handler for this window.
     * \param handler Reference to an event handler object
     * \sa EventHandler
     */
    void setEventHandler(EventHandler& handler);

    /**
     * \brief Set the window event handler to default one
     *
     *
     * Sets the window's event handler to point to the default one (one that does not do anything).
     */
    void setDefaultEventHandler();

    /**
     * \brief Process events
     *
     *
     * Processes events on this window and calls it's event handler.
     * \sa EventHandler
     */
    void processEvents();

    /**
     * \brief Set window title
     *
     *
     * Sets the title of the window.
     * \param title UTF-8 encoded string to be set as title
     */
    void setTitle(std::string_view title);

    /**
     * \brief Set window position
     *
     *
     * Sets a new position for the window.
     * \param pos New position of the window in virtual units
     */
    void setPosition(const glm::ivec2& pos);

    /**
     * \brief Set window size
     *
     *
     * Sets the size of the window.
     * \param size New size of the window in virtual units.
     */
    void setSize(const glm::ivec2& size);

    /**
     * \brief Make the window fullscreen
     *
     *
     * Makes the window fullscreen.
     * \param videoMode Video mode to be set
     */
    void enableFullscreen(const Monitor::VideoMode& videoMode);

    /**
     * \brief Disable fullscreen window
     *
     * Returns the window back to windowed mode.
     */
    void disableFullscreen();

    /**
     * \brief Minimize window
     *
     *
     * Minimizes the window.
     */
    void minimize();

    /**
     * \brief Maximize window
     *
     *
     * Maximizes the window.
     */
    void maximize();

    /**
     * \brief Restore window
     *
     *
     * Restores the window from either a maximized or a minimized state.
     */
    void restore();

    /**
     * \brief Close window
     *
     *
     * Closes the window.
     */
    void close();

    /**
     * \brief Get window position
     *
     *
     * Returns the current position of the window.
     * \return 2D vector with the position of the window in virtual units
     */
    [[nodiscard]] glm::ivec2 getPosition() const;

    /**
     * \brief Get window size
     *
     * Returns the current size of the window.
     * \return 2D vector with the size of the window in virtual units
     */
    [[nodiscard]] glm::ivec2 getSize() const;

    /**
     * \brief Get window handle
     *
     *
     * Returns the internal handle of the window.
     * \return Internal window handle
     */
    [[nodiscard]] void* getHandle() const;

private:
    friend class Context;

    static int eventFilter(void* userdata, void* event);

    void* m_handle;
    EventHandler* m_eventHandler;
    bool m_open;
};
}

#endif//SGE_WINDOW_HPP
