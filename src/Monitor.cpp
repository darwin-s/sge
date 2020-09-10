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

std::size_t Monitor::getMonitorCount() {
    return SDL_GetNumVideoDisplays();
}

Monitor Monitor::getMonitor(int index) {
    return Monitor(index);
}

Monitor::VideoMode Monitor::getCurrentVideoMode() const {
    assert(m_handle < SDL_GetNumVideoDisplays());
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(m_handle, &mode);
    const VideoMode m{mode.w, mode.h, mode.refresh_rate};

    return m;
}

std::size_t Monitor::getVideoModeCount() const {
    assert(m_handle < SDL_GetNumVideoDisplays());
    return SDL_GetNumDisplayModes(m_handle);
}

Monitor::VideoMode Monitor::getVideoMode(int index) const {
    assert(m_handle < SDL_GetNumVideoDisplays());
    assert(index < SDL_GetNumDisplayModes(m_handle));

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(m_handle, index, &mode);
    VideoMode mod{mode.w, mode.h, mode.refresh_rate};

    return mod;
}

RectangleInt Monitor::getAvailableWorkArea() const {
    assert(m_handle < SDL_GetNumVideoDisplays());
    SDL_Rect r;
    SDL_GetDisplayUsableBounds(m_handle, &r);

    return RectangleInt(r.x, r.y, r.w, r.h);
}

const char* Monitor::getName() const {
    assert(m_handle < SDL_GetNumVideoDisplays());

    return SDL_GetDisplayName(m_handle);
}
}
