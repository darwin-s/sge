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
#include <SGE/Version.hpp>
#include <SGE/Context.hpp>
#include <SGE/Log.hpp>
#include <cassert>
#include <exception>
#include <string>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <glad.h>
#include <physfs.h>

namespace {
sge::Application* current = nullptr;
}

namespace sge {
Application::Application() : m_args(nullptr), m_argc(0) {
    if (current != nullptr) {
        crashApplication("More than one active progra");
    }

    Log::general.open("log.txt");
    Log::general << Log::MessageType::Info << "Started SGE v" << SGE_VER_MAJOR
                 << "." << SGE_VER_MINOR << "." << SGE_VER_PATCH << "."
                 << SGE_VER_TWEAK << Log::Operation::Endl;

    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC |
                 SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) != 0) {
        crashApplication("Could not initialize SDL!");
    }

    if (PHYSFS_init(NULL) == 0) {
        const auto code = PHYSFS_getLastErrorCode();
        try {
            std::string msg = "Failed to initialize PhysFS: ";
            if (code != PHYSFS_ERR_OK) {
                msg += PHYSFS_getErrorByCode(code);
            }
            crashApplication(msg.c_str());
        } catch (...) {
            crashApplication("Failed string manipulation");
        }
    }

    assert(PHYSFS_getLastErrorCode() == PHYSFS_ERR_OK);

    Context temp;
    Log::general << Log::MessageType::Info << "OpenGL Vendor: "
                 << reinterpret_cast<const char*>(glGetString(GL_VENDOR))
                 << Log::Operation::Endl;
    Log::general << Log::MessageType::Info << "OpenGL Renderer: "
                 << reinterpret_cast<const char*>(glGetString(GL_RENDERER))
                 << Log::Operation::Endl;
    Log::general << Log::MessageType::Info << "OpenGL Version: "
                 << reinterpret_cast<const char*>(glGetString(GL_VERSION))
                 << Log::Operation::Endl;

    current = this;
}

Application::Application(const int argc, char** argv)
    : m_args(nullptr), m_argc(0) {
    if (current != nullptr) {
        crashApplication("More than one application is current");
    }

    m_args = argv;
    m_argc = argc;

    Log::general.open("log.txt");
    Log::general.open("log.txt");
    Log::general << Log::MessageType::Info << "Started SGE v" << SGE_VER_MAJOR
                 << "." << SGE_VER_MINOR << "." << SGE_VER_PATCH << "."
                 << SGE_VER_TWEAK << Log::Operation::Endl;

    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC |
                 SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) != 0) {
        crashApplication("Could not initialize SDL!");
    }

    if (PHYSFS_init(argv[0]) == 0) {
        try {
            const auto code = PHYSFS_getLastErrorCode();
            std::string msg = "Failed to initialize PhysFS: ";
            if (code != PHYSFS_ERR_OK) {
                msg += PHYSFS_getErrorByCode(code);
            }
            crashApplication(msg.c_str());
        } catch (...) {
            crashApplication("Failed string manipulation");
        }
    }

    assert(PHYSFS_getLastErrorCode() == PHYSFS_ERR_OK);

    Context temp;
    Log::general << Log::MessageType::Info << "OpenGL Vendor: "
                 << reinterpret_cast<const char*>(glGetString(GL_VENDOR))
                 << Log::Operation::Endl;
    Log::general << Log::MessageType::Info << "OpenGL Renderer: "
                 << reinterpret_cast<const char*>(glGetString(GL_RENDERER))
                 << Log::Operation::Endl;
    Log::general << Log::MessageType::Info << "OpenGL Version: "
                 << reinterpret_cast<const char*>(glGetString(GL_VERSION))
                 << Log::Operation::Endl;

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

const char* const* Application::getArgs() const {
    assert(current == this);

    return m_args;
}

int Application::getArgCount() const {
    assert(current == this);

    return m_argc;
}

void Application::crashApplication(const char* reason) {
    try {
        std::string message =
            "SGE has crashed!\nFor more information consult the "
            "log file.\nReason: ";
        message += reason;
        Log::general << Log::MessageType::Error
                     << "Application crash: " << reason << Log::Operation::Endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "SGE Crash",
                                 message.c_str(),
                                 NULL);
    } catch (...) {
        std::terminate();
    }

    std::terminate();
}
}
