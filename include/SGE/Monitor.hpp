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

#ifndef SGE_MONITOR_HPP
#define SGE_MONITOR_HPP

#include <SGE/Export.hpp>
#include <SGE/Vector2.hpp>
#include <SGE/Rectangle.hpp>
#include <vector>
#include <string>

namespace sge {
class Window;

/**
 * \brief Object used to represent monitors
 *
 *
 * This class is used to represent monitors on the currently running setup.
 * It may be used to get properties of one or more monitors such as their size,
 * content scaling (dpi scaling factor), resolution, gamma and virtual position.
 * \note Monitor handling must happen only in the main thread
 *
 * \note A monitor object is valid until the monitor configuration changes.
 * \note After that the monitor object must be re-created.
 *
 * \note Virtual units are used for positions and sizes. These may not equal to pixels on the target platform.
 *
 * Usage example:
 * \code
 * sge::Monitor mon = sge::Monitor::getPrimaryMonitor();
 * // use monitor's properties...
 * \endcode
 */
class SGE_API Monitor {
public:
    /**
     * \brief Video mode
     *
     *
     * Represents a video mode for a monitor.
     */
    struct VideoMode {
        int width;      ///< Width in virtual units
        int height;     ///< Height in virtual units
        int refreshRate;///< Refresh rate of the monitor
    };

    /**
     * \brief Create monitor from a handle
     *
     *
     * Creates a monitor object from an internal handle pointer.
     * \note This constructor is used only internally in the library. It should not be used by users
     * \param handle Internal handle of the monitor
     */
    SGE_PRIVATE explicit Monitor(int handle);

    /**
     * \brief Get primary monitor
     *
     *
     * Returns the primary monitor on the current system. The primary monitor is usually the one
     * on which windows are created by default.
     * \return The primary monitor
     */
    static Monitor getPrimaryMonitor();

    /**
     * \brief Get all monitors
     *
     * Returns a vector with all the monitors currently connected.
     * \return Vector containing all currently connected monitors
     */
    static std::vector<Monitor> getMonitors();

    /**
     * \brief Get current video mode
     *
     *
     * Returns the current video mode set on the monitor.
     * \return Current video mode
     * \sa Monitor::VideoMode
     */
    [[nodiscard]] VideoMode getCurrentVideoMode() const;

    /**
     * \brief Get supported video modes
     *
     *
     * Returns all the video modes supported by this monitor.
     * \return Vector containing all supported video modes
     * \sa Monitor::VideoMode
     */
    [[nodiscard]] std::vector<VideoMode> getSupportedVideoModes() const;

    /**
     * \brief Get available work area
     *
     *
     * Returns the freely available area of the screen on this monitor.
     * \return WorkArea structure describing the free area
     * \sa Monitor::WorkArea
     */
    [[nodiscard]] RectangleInt getAvailableWorkArea() const;

    /**
     * \brief Get monitor name
     *
     *
     * Returns the human-readable name of the monitor formatted in UTF-8.
     * \return String containing the monitor name
     */
    [[nodiscard]] std::string getName() const;

private:
    friend class Window;
    int m_handle;
};
}

#endif//SGE_MONITOR_HPP
