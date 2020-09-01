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

#include <SGE/Context.hpp>
#include <SGE/Window.hpp>
#include <SGE/Log.hpp>
#include <string>
#include <stdexcept>
#include <mutex>
#include <cassert>
#include <glad.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace {
constexpr int openGlVersionMajor = 4;
constexpr int openGlVersionMinor = 6;

thread_local sge::Context* active = nullptr;
sge::Context* shared              = nullptr;
int sharedCount                   = 0;
std::recursive_mutex sharedMutex;
bool loadedGL = false;
std::mutex loadedMutex;

void setHints(const sge::ContextSettings& settings) {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, settings.redBits);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, settings.greenBits);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, settings.blueBits);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, settings.alphaBits);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, settings.depthBits);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, settings.stencilBits);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    if (settings.samples > 0) {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, settings.samples);
    }
    SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
                        settings.srgbCapable ? 1 : 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, openGlVersionMajor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, openGlVersionMinor);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
                        settings.debugContext ? SDL_GL_CONTEXT_DEBUG_FLAG : 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
}

const char* sourceToString(const GLenum source) {
    switch (source) {
    case GL_DEBUG_SOURCE_API:
        return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        return "Window System";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        return "Shader Compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        return "Third Party";
    case GL_DEBUG_SOURCE_APPLICATION:
        return "Application";
    case GL_DEBUG_SOURCE_OTHER:
    default:
        return "Other";
    }
}

const char* typeToString(const GLenum type) {
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        return "Deprecated Behaviour";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        return "Undefined Behaviour";
    case GL_DEBUG_TYPE_PORTABILITY:
        return "Portability";
    case GL_DEBUG_TYPE_PERFORMANCE:
        return "Performance";
    case GL_DEBUG_TYPE_MARKER:
        return "Marker";
    case GL_DEBUG_TYPE_PUSH_GROUP:
        return "Push Group";
    case GL_DEBUG_TYPE_POP_GROUP:
        return "Pop Group";
    case GL_DEBUG_TYPE_OTHER:
    default:
        return "Other";
    }
}

const char* severityToString(const GLenum severity) {
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        return "High";
    case GL_DEBUG_SEVERITY_MEDIUM:
        return "Medium";
    case GL_DEBUG_SEVERITY_LOW:
        return "Low";
    case GL_DEBUG_SEVERITY_NOTIFICATION:
    default:
        return "Notification";
    }
}

void GLAPIENTRY messageCallback(const GLenum source,
                                const GLenum type,
                                const GLuint id,
                                const GLenum severity,
                                [[maybe_unused]] const GLsizei length,
                                const GLchar* message,
                                [[maybe_unused]] const void* userParam) {
    std::string msg = "OpenGL message: source - ";
    msg += sourceToString(source);
    msg += "; type - ";
    msg += typeToString(type);
    msg += "; id - ";
    msg += std::to_string(id);
    msg += "; severity - ";
    msg += severityToString(severity);
    msg += "; message - ";
    msg += message;
    {
        std::scoped_lock logLock(sge::Log::generalMutex);
        sge::Log::general << sge::Log::MessageType::Debug << msg
                          << sge::Log::Operation::Endl;
    }
    if (type == GL_DEBUG_TYPE_ERROR) {
        throw std::runtime_error(msg);
    }
}
}

namespace sge {
Context::Context(const ContextSettings& settings)
    : m_handle(nullptr), m_windowHandle(nullptr), m_sharedWindow(false) {
    create(nullptr, settings);
}

Context::Context(const Window& window, const ContextSettings& settings)
    : m_handle(nullptr), m_windowHandle(nullptr), m_sharedWindow(true) {
    create(window.m_handle, settings);
}

Context::~Context() {
    if (active == this) {
        setCurrent(false);
    }
    assert(active == nullptr);
    SDL_GL_DeleteContext(static_cast<SDL_GLContext>(m_handle));
    if (!m_sharedWindow) {
        SDL_DestroyWindow(static_cast<SDL_Window*>(m_windowHandle));
    }
    {
        std::scoped_lock sl(sharedMutex);
        if (sharedCount > 0) {
            sharedCount--;
        }
        if (this != shared && sharedCount == 0) {
            delete shared;
            shared = nullptr;
        }
    }
}

const ContextSettings& Context::getContextSettings() const {
    return m_settings;
}

void Context::setCurrent(const bool current) {
    if (current) {
        if (active == this) {
            return;
        }
        if (active != nullptr) {
            active->setCurrent(false);
        }
        if (SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_windowHandle),
                               static_cast<SDL_GLContext>(m_handle)) != 0) {
            std::scoped_lock logLock(sge::Log::generalMutex);
            sge::Log::general << sge::Log::MessageType::Error
                              << "SDL error: " << SDL_GetError()
                              << sge::Log::Operation::Endl;
            throw std::runtime_error("SDL error");
        }
        active = this;
    } else {
        if (active != this) {
            return;
        }
        if (SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_windowHandle),
                               NULL) != 0) {
            std::scoped_lock logLock(sge::Log::generalMutex);
            sge::Log::general << sge::Log::MessageType::Error
                              << "SDL error: " << SDL_GetError()
                              << sge::Log::Operation::Endl;
            throw std::runtime_error("SDL error");
        }
        active = nullptr;
    }
}

bool Context::isExtensionAvailable(const std::string_view extensionName) const {
    if (SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_windowHandle),
                           static_cast<SDL_GLContext>(m_handle)) != 0) {
        std::scoped_lock logLock(sge::Log::generalMutex);
        sge::Log::general << sge::Log::MessageType::Error
                          << "SDL error: " << SDL_GetError()
                          << sge::Log::Operation::Endl;
        throw std::runtime_error("SDL error");
    }
    const auto supported =
        SDL_GL_ExtensionSupported(extensionName.data()) == SDL_TRUE;
    if (active != nullptr) {
        if (SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_windowHandle),
                               static_cast<SDL_GLContext>(active->m_handle)) !=
            0) {
            std::scoped_lock logLock(sge::Log::generalMutex);
            sge::Log::general << sge::Log::MessageType::Error
                              << "SDL error: " << SDL_GetError()
                              << sge::Log::Operation::Endl;
            throw std::runtime_error("SDL error");
        }
    } else {
        if (SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_windowHandle),
                               NULL) != 0) {
            std::scoped_lock logLock(sge::Log::generalMutex);
            sge::Log::general << sge::Log::MessageType::Error
                              << "SDL error: " << SDL_GetError()
                              << sge::Log::Operation::Endl;
            throw std::runtime_error("SDL error");
        }
    }
    return supported;
}

Context* Context::getCurrentContext() {
    return active;
}

void Context::create(void* winHandle, const ContextSettings& settings) {
    {
        std::scoped_lock sl(sharedMutex);
        if (sharedCount == 0) {
#ifdef SGE_DEBUG
            const ContextSettings s(false, 0, true, false);
#else
            const ContextSettings s(false, 0, false, false);
#endif
            sharedCount--;
            shared = new Context(s);
        }
        sharedCount++;
        setHints(settings);
        if (sharedCount == 0) {
            SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
            m_windowHandle =
                SDL_CreateWindow("hidden",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 1,
                                 1,
                                 SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
            m_handle =
                SDL_GL_CreateContext(static_cast<SDL_Window*>(m_windowHandle));
        } else {
            if (SDL_GL_MakeCurrent(
                    static_cast<SDL_Window*>(shared->m_windowHandle),
                    static_cast<SDL_GLContext>(shared->m_handle)) != 0) {
                std::scoped_lock logLock(sge::Log::generalMutex);
                sge::Log::general << sge::Log::MessageType::Error
                                  << "SDL error: " << SDL_GetError()
                                  << sge::Log::Operation::Endl;
                throw std::runtime_error("SDL error");
            }
            SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
            if (winHandle == nullptr) {
                m_windowHandle =
                    SDL_CreateWindow("hidden",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     1,
                                     1,
                                     SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN);
                m_handle = SDL_GL_CreateContext(
                    static_cast<SDL_Window*>(m_windowHandle));
            } else {
                m_windowHandle = winHandle;
                m_handle =
                    SDL_GL_CreateContext(static_cast<SDL_Window*>(winHandle));
            }
        }
    }

    {
        std::scoped_lock sl(loadedMutex);
        if (!loadedGL) {
            if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(
                    SDL_GL_GetProcAddress)) == 0) {
                throw std::runtime_error(
                    "Could not load OpenGL function pointers");
            }
            loadedGL = true;
        }
    }
    if (!settings.vsync) {
        SDL_GL_SetSwapInterval(0);
    } else {
        SDL_GL_SetSwapInterval(1);
    }

    if (settings.debugContext) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(messageCallback, nullptr);
    }

    m_settings.vsync        = settings.vsync;
    m_settings.debugContext = settings.debugContext;
    m_settings.srgbCapable  = settings.srgbCapable;
    glGetIntegerv(GL_SAMPLES, &m_settings.samples);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
                                          GL_FRONT_LEFT,
                                          GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE,
                                          &m_settings.redBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
                                          GL_FRONT_LEFT,
                                          GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE,
                                          &m_settings.greenBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
                                          GL_FRONT_LEFT,
                                          GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE,
                                          &m_settings.blueBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
                                          GL_FRONT_LEFT,
                                          GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE,
                                          &m_settings.alphaBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER,
                                          GL_DEPTH,
                                          GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE,
                                          &m_settings.depthBits);
    glGetFramebufferAttachmentParameteriv(
        GL_DRAW_FRAMEBUFFER,
        GL_STENCIL,
        GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE,
        &m_settings.stencilBits);

    if (active != nullptr) {
        if (SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_windowHandle),
                               static_cast<SDL_GLContext>(active->m_handle)) !=
            0) {
            std::scoped_lock logLock(sge::Log::generalMutex);
            sge::Log::general << sge::Log::MessageType::Error
                              << "SDL error: " << SDL_GetError()
                              << sge::Log::Operation::Endl;
            throw std::runtime_error("SDL error");
        }
    } else {
        if (SDL_GL_MakeCurrent(static_cast<SDL_Window*>(m_windowHandle),
                               NULL) != 0) {
            std::scoped_lock logLock(sge::Log::generalMutex);
            sge::Log::general << sge::Log::MessageType::Error
                              << "SDL error: " << SDL_GetError()
                              << sge::Log::Operation::Endl;
            throw std::runtime_error("SDL error");
        }
    }
}
}
