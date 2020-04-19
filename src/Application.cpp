// Copyright 2020 Sirbu Dan
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

namespace {
sge::Application* current = nullptr;
}

namespace sge {
Application::Application() {
    assert(!current);

    sge::Log::general.open("log.txt");

    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW!");

    current = this;
}

Application::Application(int argc, char** argv) {
    assert(!current);

    for (int i = 0; i < argc; i++) {
        m_args.emplace_back(argv[i]);
    }

    sge::Log::general.open("log.txt");

    glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_FALSE);
    if (!glfwInit())
        throw std::runtime_error("Could not initialize GLFW!");

    current = this;
}

Application::~Application() {
    assert(current == this);

    sge::Log::general.close();

    glfwTerminate();

    current = nullptr;
}

Application::ReturnCode Application::run() {
    assert(current == this);

    if (onInit() != ReturnOk)
        return ReturnError;
    if (onRun() != ReturnOk)
        return ReturnError;
    return ReturnError;
}

std::list<std::string> Application::getArgs() const {
    assert(current == this);

    return m_args;
}
}

