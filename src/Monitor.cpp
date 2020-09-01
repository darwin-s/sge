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

#include <SGE/Monitor.hpp>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <cassert>

namespace sge {
Monitor::Monitor(int handle) : m_handle(handle) {
    assert(handle < SDL_GetNumVideoDisplays());
}

Monitor Monitor::getPrimaryMonitor() {
    return Monitor(0);
}

std::vector<Monitor> Monitor::getMonitors() {
    auto monCount = SDL_GetNumVideoDisplays();
    std::vector<Monitor> monitors;

    monitors.reserve(monCount);
    for (auto i = 0; i < monCount; i++) {
        monitors.emplace_back(i);
    }

    return monitors;
}

Monitor::VideoMode Monitor::getCurrentVideoMode() const {
    assert(m_handle < SDL_GetNumVideoDisplays());
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(m_handle, &mode);
    const VideoMode m{mode.w, mode.h, mode.refresh_rate};

    return m;
}

std::vector<Monitor::VideoMode> Monitor::getSupportedVideoModes() const {
    assert(m_handle < SDL_GetNumVideoDisplays());
    auto modeCount = SDL_GetNumDisplayModes(m_handle);
    std::vector<VideoMode> m(modeCount);

    for (auto i = 0; i < modeCount; i++) {
        SDL_DisplayMode mode;
        SDL_GetDisplayMode(m_handle, i, &mode);
        VideoMode mod{mode.w, mode.h, mode.refresh_rate};
        m.emplace_back(mod);
    }

    return m;
}

RectangleInt Monitor::getAvailableWorkArea() const {
    assert(m_handle < SDL_GetNumVideoDisplays());
    SDL_Rect r;
    SDL_GetDisplayUsableBounds(m_handle, &r);

    return RectangleInt(r.x, r.y, r.w, r.h);
}

std::string Monitor::getName() const {
    assert(m_handle < SDL_GetNumVideoDisplays());
    const auto* name = SDL_GetDisplayName(m_handle);

    return std::string(name);
}
}
