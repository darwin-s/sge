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
     * Creates a window, setting only the context settings for this window.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param contextSettings Settings for the underlying context
     */
    explicit Window(const ContextSettings& contextSettings = ContextSettings());

    /**
     * \brief Create window
     *
     *
     * Creates a window, setting it's title.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     * \param contextSettings Settings for the underlying context
     */
    explicit Window(std::string_view title, const ContextSettings& contextSettings = ContextSettings());

    /**
     * \brief Create window
     *
     *
     * Creates a window, setting it's title and size.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     * \param size Size of the window
     * \param contextSettings Settings for the underlying context
     */
    Window(std::string_view title, const Vector2I& size, const ContextSettings& contextSettings = ContextSettings());

    /**
     * \brief Create window
     *
     *
     * Creates a fullscreen window(not borderless window) on a monitor.
     * \note A created window is not yet shown on the screen. Use the "show" method to make it visible
     * \param title Title of the window
     * \param videoMode Video mode to be set
     * \param monitor Monitor on which to make the window fullscreen
     * \param contextSettings Settings for the underlying context
     */
    Window(std::string_view title, const Monitor::VideoMode& videoMode, const Monitor& monitor,
           const ContextSettings& contextSettings = ContextSettings());
    Window(const Window&) = delete;
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
     * \brief Get window context
     *
     *
     * Returns the underlying context of the window.
     * \return Reference to the context of the window
     */
    [[nodiscard]] const Context& getContext() const;

    /**
     * \brief Get window context
     *
     *
     * Returns the underlying context of the window.
     * \return Reference to the context of the window
     */
    [[nodiscard]] Context& getContext();

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
     * Processes events on all currently created windows and calls their event handlers.
     * \sa EventHandler
     */
    static void processEvents();

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
    void setPosition(const Vector2I& pos);

    /**
     * \brief Set window size
     *
     *
     * Sets the size of the window.
     * \param size New size of the window in virtual units.
     */
    void setSize(const Vector2I& size);

    /**
     * \brief Make the window fullscreen
     *
     *
     * Makes the window fullscreen on a monitor.
     * \param videoMode Video mode to be set
     * \param monitor Monitor on which the window will be fullscreen
     */
    void enableFullscreen(const Monitor::VideoMode& videoMode, const Monitor& monitor);

    /**
     * \brief Disable fullscreen window
     *
     * Returns the window back to windowed mode.
     */
    void disableFullscreen();

    /**
     * \brief Set window size limits
     *
     *
     * Sets a limit on the size of the window.
     * \param minSize Minimal window size in virtual units
     * \param maxSize Maximal window size in virtual units
     */
    void setSizeLimits(const Vector2I& minSize, const Vector2I& maxSize);

    /**
     * \brief Set window aspect ratio
     *
     *
     * Sets the aspect ratio to be maintained while resizing the window.
     * \param numer Numerator of the aspect ratio
     * \param denom Denominator of the aspect ratio
     */
    void setAspectRatio(int numer, int denom);

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
     * \brief Request attention
     *
     *
     * Requests attention from the user.
     */
    void requestAttention();

    /**
     * \brief Enable raw mouse input
     *
     *
     * Enables raw mouse input for the current window.
     * \note Raw input only works while the cursor is disabled
     */
    void enableRawInput();

    /**
     * \brief Disable raw mouse input
     *
     *
     * Disables raw mouse input for the current window.
     */
    void disableRawInput();

    /**
     * \brief Disable cursor
     *
     *
     * Disables the cursor for the current window
     */
    void disableCursor();

    /**
     * \brief Hide cursor
     *
     *
     * Hides the cursor for the current window.
     * \note A hidden cursor can still leave the window's area
     */
    void hideCursor();

    /**
     * \brief Enable cursor
     *
     *
     * Shows the cursor for the current window.
     */
    void enableCursor();

    /**
     * \brief Swap buffers
     *
     *
     * Swaps the front and back buffers for the current window.
     */
    void swapBuffers();

    /**
     * \brief Prevent window from closing
     *
     * Prevents the window from immediately closing (useful for event handlers).
     */
    void preventClosing();

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
    [[nodiscard]] Vector2I getPosition() const;

    /**
     * \brief Get window size
     *
     * Returns the current size of the window.
     * \return 2D vector with the size of the window in virtual units
     */
    [[nodiscard]] Vector2I getSize() const;

    /**
     * \brief Get window framebuffer size
     *
     *
     * Returns the current window framebuffer size.
     * \return 2D vector with the size of the framebuffer in pixels
     */
    [[nodiscard]] Vector2U getFramebufferSize() const;

    /**
     * \brief Get window DPI scale
     *
     *
     * Returns the current window DPI scale.
     * \return 2D vector with the window scaling factors
     */
    [[nodiscard]] Vector2F getContentScale() const;

private:
    SGE_PRIVATE void setCallbacks();
    static SGE_PRIVATE void closeCallback(void* window);
    static SGE_PRIVATE void resizeCallback(void* window, int width, int height);
    static SGE_PRIVATE void framebufferResizeCallback(void* window, int width, int height);
    static SGE_PRIVATE void contentScaleCallback(void* window, float xScale, float yScale);
    static SGE_PRIVATE void positionCallback(void* window, int xPos, int yPos);
    static SGE_PRIVATE void minimizeCallback(void* window, int minimized);
    static SGE_PRIVATE void maximizeCallback(void* window, int maximized);
    static SGE_PRIVATE void focusCallback(void* window, int focused);
    static SGE_PRIVATE void refreshCallback(void* window);
    static SGE_PRIVATE void keyboardCallback(void* window, int key, int scancode, int action, int mods);
    static SGE_PRIVATE void textInputCallback(void* window, unsigned int codePoint);
    static SGE_PRIVATE void cursorPositionCallback(void* window, double xPos, double yPos);
    static SGE_PRIVATE void cursorEnterCallback(void* window, int entered);
    static SGE_PRIVATE void mouseButtonCallback(void* window, int button, int action, int mods);
    static SGE_PRIVATE void scrollCallback(void* window, double xOffset, double yOffset);

    Context m_context;
    EventHandler* m_eventHandler;
};
}

#endif//SGE_WINDOW_HPP
