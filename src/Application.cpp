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

#include <SGE/Application.hpp>
#include <SGE/Log.hpp>
#include <cassert>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <physfs.h>

namespace {
sge::Application* current = nullptr;

void errorCallback(int code, const char* message) {
    std::string msg = "GLFW error(";
    switch (code) {
    case GLFW_NOT_INITIALIZED:
        msg += "NOT_INITIALIZED): ";
        break;
    case GLFW_NO_CURRENT_CONTEXT:
        msg += "NO_CURRENT_CONTEXT): ";
        break;
    case GLFW_INVALID_ENUM:
        msg += "INVALID_ENUM): ";
        break;
    case GLFW_INVALID_VALUE:
        msg += "INVALID_VALUE): ";
        break;
    case GLFW_OUT_OF_MEMORY:
        msg += "OUT_OF_MEMORY): ";
        break;
    case GLFW_API_UNAVAILABLE:
        msg += "API_UNAVAILABLE): ";
        break;
    case GLFW_VERSION_UNAVAILABLE:
        msg += "VERSION_UNAVAILABLE): ";
        break;
    case GLFW_PLATFORM_ERROR:
        msg += "PLATFORM_ERROR): ";
        break;
    case GLFW_FORMAT_UNAVAILABLE:
        msg += "FORMAT_UNAVAILABLE): ";
        break;
    case GLFW_NO_WINDOW_CONTEXT:
        msg += "NO_WINDOW_CONTEXT): ";
        break;
    default:
        msg += "UNK): ";
        break;
    }

    msg += message;

    {
        std::scoped_lock l(sge::Log::generalMutex);
        sge::Log::general << sge::Log::MessageType::Error << msg << sge::Log::Operation::Endl;
    }

    throw std::runtime_error(msg);
}

void monitorCallback(GLFWmonitor* monitor, int event) {
    std::string msg = "Monitor \"";
    msg += glfwGetMonitorName(monitor);
    msg += "\" ";
    if (event == GLFW_CONNECTED) {
        msg += "connected";
    } else if (event == GLFW_DISCONNECTED) {
        msg += "disconnected";
    }

    {
        std::scoped_lock l(sge::Log::generalMutex);
        sge::Log::general << sge::Log::MessageType::Info << msg << sge::Log::Operation::Endl;
    }
}
}

namespace sge {
Application::Application() {
    if (current) {
        throw std::logic_error("More than one application is current");
    }

    sge::Log::general.open("log.txt");

    glfwSetErrorCallback(errorCallback);

    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    glfwSetMonitorCallback(monitorCallback);

    if (!PHYSFS_init(NULL)) {
        PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();
        std::string msg = "Failed to initialize PhysFS: ";
        if (code != PHYSFS_ERR_OK) {
            msg += PHYSFS_getErrorByCode(code);
        }
        throw std::runtime_error(msg);
    }

    assert(PHYSFS_getLastErrorCode() == PHYSFS_ERR_OK);

    current = this;
}

Application::Application(int argc, char** argv) {
    if (current) {
        throw std::logic_error("More than one application is current");
    }

    for (int i = 0; i < argc; i++) {
        m_args.emplace_back(argv[i]);
    }

    sge::Log::general.open("log.txt");

    glfwSetErrorCallback(errorCallback);

    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
    if (!glfwInit()) {
        throw std::runtime_error("Could not initialize GLFW!");
    }

    glfwSetMonitorCallback(monitorCallback);

    if (!PHYSFS_init(argv[0])) {
        PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();
        std::string msg = "Failed to initialize PhysFS: ";
        if (code != PHYSFS_ERR_OK) {
            msg += PHYSFS_getErrorByCode(code);
        }
        throw std::runtime_error(msg);
    }

    assert(PHYSFS_getLastErrorCode() == PHYSFS_ERR_OK);

    current = this;
}

Application::~Application() {
    assert(current == this);

    sge::Log::general.close();

    PHYSFS_deinit();
    glfwTerminate();

    current = nullptr;
}

Application::ReturnCode Application::run() {
    assert(current == this);

    if (onInit() != ReturnOk) {
        return ReturnError;
    }
    if (onRun() != ReturnOk) {
        return ReturnError;
    }

    return ReturnOk;
}

std::vector<std::string> Application::getArgs() const {
    assert(current == this);

    return m_args;
}
}
