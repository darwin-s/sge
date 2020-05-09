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
#include <GLFW/glfw3.h>
#include <cassert>

namespace sge {
Monitor::Monitor(void* handle) : m_handle(handle) {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (handle == monitorHandles[i])
            mon = monitorHandles[i];
    }

    assert(mon != nullptr);
#endif
}

Monitor Monitor::getPrimaryMonitor() {
    return Monitor(glfwGetPrimaryMonitor());
}

std::vector<Monitor> Monitor::getMonitors() {
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    std::vector<Monitor> monitors;

    monitors.reserve(monCount);
    for (int i = 0; i < monCount; i++) {
        monitors.emplace_back(monitorHandles[i]);
    }

    return monitors;
}

Monitor::VideoMode Monitor::getCurrentVideoMode() const {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    const GLFWvidmode* mode = glfwGetVideoMode(mon);
    VideoMode m{mode->width, mode->height, mode->redBits, mode->greenBits, mode->blueBits, mode->refreshRate};

    return m;
}

std::vector<Monitor::VideoMode> Monitor::getSupportedVideoModes() const {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    int modeCount = 0;
    const GLFWvidmode* modes = glfwGetVideoModes(mon, &modeCount);
    std::vector<Monitor::VideoMode> m(modeCount);

    for (int i = 0; i < modeCount; i++) {
        VideoMode mod{modes[i].width,     modes[i].height,   modes[i].redBits,
                      modes[i].greenBits, modes[i].blueBits, modes[i].refreshRate};
        m.emplace_back(mod);
    }

    return m;
}

Vector2I Monitor::getPhysicalSizeMm() const {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    int widthMm = 0;
    int heightMm = 0;

    glfwGetMonitorPhysicalSize(mon, &widthMm, &heightMm);

    return Vector2I(widthMm, heightMm);
}

Vector2F Monitor::getContentScale() const {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    float xScale = 0.0f;
    float yScale = 0.0f;

    glfwGetMonitorContentScale(mon, &xScale, &yScale);

    return Vector2F(xScale, yScale);
}

Vector2I Monitor::getVirtualPosition() const {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    int xPos = 0;
    int yPos = 0;

    glfwGetMonitorPos(mon, &xPos, &yPos);

    return Vector2I(xPos, yPos);
}

Monitor::WorkArea Monitor::getAvailableWorkArea() const {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    int xPos = 0;
    int yPos = 0;
    int width = 0;
    int height = 0;

    glfwGetMonitorWorkarea(mon, &xPos, &yPos, &width, &height);

    return WorkArea{{xPos, yPos}, width, height};
}

std::string Monitor::getName() const {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    const char* name = glfwGetMonitorName(mon);

    return std::string(name);
}

Monitor::GammaRamp Monitor::getCurrentGammaRamp() const {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    const GLFWgammaramp* rmp = glfwGetGammaRamp(mon);
    GammaRamp ramp;
    ramp.size = rmp->size;
    ramp.red.resize(ramp.size);
    ramp.green.resize(ramp.size);
    ramp.blue.resize(ramp.size);

    for (std::size_t i = 0; i < ramp.size; i++) {
        ramp.red[i] = rmp->red[i];
    }
    for (std::size_t i = 0; i < ramp.size; i++) {
        ramp.green[i] = rmp->green[i];
    }
    for (std::size_t i = 0; i < ramp.size; i++) {
        ramp.blue[i] = rmp->blue[i];
    }

    return ramp;
}

void Monitor::setGammaRamp(const GammaRamp& ramp) {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);
    GLFWgammaramp rmp{};
    rmp.size = ramp.size;
    rmp.red = new unsigned short[rmp.size];
    rmp.green = new unsigned short[rmp.size];
    rmp.blue = new unsigned short[rmp.size];

    for (std::size_t i = 0; i < ramp.size; i++) {
        rmp.red[i] = ramp.red[i];
    }
    for (std::size_t i = 0; i < ramp.size; i++) {
        rmp.green[i] = ramp.green[i];
    }
    for (std::size_t i = 0; i < ramp.size; i++) {
        rmp.blue[i] = ramp.blue[i];
    }

    glfwSetGammaRamp(mon, &rmp);
    delete[] rmp.red;
    delete[] rmp.green;
    delete[] rmp.blue;
}

void Monitor::setGamma(float gamma) {
#ifdef SGE_DEBUG
    int monCount = 0;
    GLFWmonitor** monitorHandles = glfwGetMonitors(&monCount);
    GLFWmonitor* glfw_mon = nullptr;

    for (int i = 0; i < monCount; i++) {
        if (m_handle == monitorHandles[i])
            glfw_mon = monitorHandles[i];
    }

    assert(glfw_mon != nullptr);
#endif
    auto* mon = reinterpret_cast<GLFWmonitor*>(m_handle);

    glfwSetGamma(mon, gamma);
}
}
