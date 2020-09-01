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
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <physfs.h>

namespace {
sge::Application* current = nullptr;
}

namespace sge {
Application::Application() {
    if (current != nullptr) {
        throw std::logic_error("More than one application is current");
    }

    Log::general.open("log.txt");

    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC |
                 SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Could not initialize SDL!");
    }

    if (PHYSFS_init(NULL) == 0) {
        const auto code = PHYSFS_getLastErrorCode();
        std::string msg = "Failed to initialize PhysFS: ";
        if (code != PHYSFS_ERR_OK) {
            msg += PHYSFS_getErrorByCode(code);
        }
        throw std::runtime_error(msg);
    }

    assert(PHYSFS_getLastErrorCode() == PHYSFS_ERR_OK);

    current = this;
}

Application::Application(const int argc, char** argv) {
    if (current != nullptr) {
        throw std::logic_error("More than one application is current");
    }

    for (auto i = 0; i < argc; i++) {
        m_args.emplace_back(argv[i]);
    }

    Log::general.open("log.txt");

    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC |
                 SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Could not initialize SDL!");
    }

    if (PHYSFS_init(argv[0]) == 0) {
        const auto code = PHYSFS_getLastErrorCode();
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

    Log::general.close();

    PHYSFS_deinit();
    SDL_Quit();

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
