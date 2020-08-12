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
#include <SGE/Log.hpp>
#include <string>
#include <stdexcept>
#include <mutex>
#include <cassert>
#include <glad.h>
#include <GLFW/glfw3.h>

namespace {
constexpr int openGlVersionMajor = 4;
constexpr int openGlVersionMinor = 6;

thread_local sge::Context* active = nullptr;
sge::Context* shared = nullptr;
int sharedCount = 0;
std::recursive_mutex sharedMutex;
bool loadedGL = false;
std::mutex loadedMutex;

void setHints(const int refreshRate, const sge::ContextSettings& settings) {
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RED_BITS, settings.redBits);
    glfwWindowHint(GLFW_GREEN_BITS, settings.greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, settings.blueBits);
    glfwWindowHint(GLFW_ALPHA_BITS, settings.alphaBits);
    glfwWindowHint(GLFW_DEPTH_BITS, settings.depthBits);
    glfwWindowHint(GLFW_STENCIL_BITS, settings.stencilBits);
    glfwWindowHint(GLFW_SAMPLES, settings.samples);
    glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
    glfwWindowHint(GLFW_SRGB_CAPABLE, settings.srgbCapable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openGlVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openGlVersionMinor);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, settings.debugContext ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

void GLAPIENTRY messageCallback(const GLenum source, const GLenum type, const GLuint id, const GLenum severity, 
                                [[maybe_unused]] const GLsizei length, const GLchar* message, 
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
        sge::Log::general << sge::Log::MessageType::Debug << msg << sge::Log::Operation::Endl;
    }
    if (type == GL_DEBUG_TYPE_ERROR) {
        throw std::runtime_error(msg);
    }
}
}

namespace sge {
Context::Context(const ContextSettings settings) : m_handle(nullptr) {
    create(GLFW_DONT_CARE, settings);
}

Context::~Context() {
    if (active == this) {
        setCurrent(false);
    }
    assert(active == nullptr);
    glfwDestroyWindow(static_cast<GLFWwindow*>(m_handle));
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
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_handle));
        active = this;
    } else {
        if (active != this) {
            return;
        }
        glfwMakeContextCurrent(NULL);
        active = nullptr;
    }
}

bool Context::isExtensionAvailable(const std::string_view extensionName) const {
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_handle));
    const auto supported = glfwExtensionSupported(extensionName.data()) == GLFW_TRUE;
    if (active != nullptr) {
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(active->m_handle));
    } else {
        glfwMakeContextCurrent(NULL);
    }
    return supported;
}

Context* Context::getCurrentContext() {
    return active;
}

void Context::create(const int refreshRate, const ContextSettings& settings) {
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
        setHints(refreshRate, settings);
        if (sharedCount == 0) {
            m_handle = glfwCreateWindow(1, 1, "hidden", NULL, NULL);
        } else {
            m_handle = glfwCreateWindow(1, 1, "hidden", NULL, static_cast<GLFWwindow*>(shared->m_handle));
        }
    }
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_handle));
    {
        std::scoped_lock sl(loadedMutex);
        if (!loadedGL) {
            if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) == 0) {
                throw std::runtime_error("Could not load OpenGL function pointers");
            }
            loadedGL = true;
        }
    }
    if (!settings.vsync) {
        glfwSwapInterval(0);
    } else {
        glfwSwapInterval(1);
    }

    if (settings.debugContext) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(messageCallback, nullptr);
    }

    m_settings.vsync = settings.vsync;
    m_settings.debugContext = settings.debugContext;
    m_settings.srgbCapable = settings.srgbCapable;
    glGetIntegerv(GL_SAMPLES, &m_settings.samples);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE,
                                          &m_settings.redBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE,
                                          &m_settings.greenBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE,
                                          &m_settings.blueBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_FRONT_LEFT, GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE,
                                          &m_settings.alphaBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_DEPTH, GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE,
                                          &m_settings.depthBits);
    glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_STENCIL, GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE,
                                          &m_settings.stencilBits);

    if (active != nullptr) {
        glfwMakeContextCurrent(static_cast<GLFWwindow*>(active->m_handle));
    } else {
        glfwMakeContextCurrent(NULL);
    }
}
}
