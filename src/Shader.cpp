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

#include <SGE/Shader.hpp>
#include <SGE/Application.hpp>
#include <SGE/Context.hpp>
#include <SGE/Filesystem.hpp>
#include <SGE/InputFile.hpp>
#include <SGE/Log.hpp>
#include <unordered_map>
#include <cassert>
#include <glad.h>

namespace sge {
Shader::Shader() : m_uniforms(nullptr) {
    assert(Context::getCurrentContext());
    try {
        m_uniforms = new std::unordered_map<std::string, int>;
    } catch (...) {
        Application::crashApplication("Bad alloc");
    }
    m_id = glCreateProgram();
}

Shader::Shader(Shader&& other) noexcept : m_id(other.m_id) {
    other.m_id = 0;
}

Shader::~Shader() {
    assert(Context::getCurrentContext());
    glDeleteProgram(m_id);

    auto* uf =
        reinterpret_cast<std::unordered_map<std::string, int>*>(m_uniforms);
    delete uf;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    m_id       = other.m_id;
    other.m_id = 0;

    return *this;
}

bool Shader::load(const char* file, const Type type) const {
    assert(Context::getCurrentContext());
    const auto shaderSize = Filesystem::getFileSize(file);
    const InputFile shader(file);
    auto* buffer = new unsigned char[shaderSize];
    shader.read(shaderSize, buffer);

    bool r = load(shaderSize, buffer, type);

    delete[] buffer;

    return r;
}

bool Shader::load(const std::size_t size,
                  const void* data,
                  const Type type) const {
    assert(Context::getCurrentContext());
    GLuint shader;
    GLint success;
    if (type == Vertex) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderSource(shader,
                   1,
                   reinterpret_cast<const char* const*>(&data),
                   reinterpret_cast<const GLint*>(&size));
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> log(logLength);
        glGetShaderInfoLog(shader, logLength, &logLength, log.data());

        glDeleteShader(shader);

        Log::general << Log::MessageType::Error
                     << "Shader compilation error: " << log.data()
                     << Log::Operation::Endl;

        return false;
    }

    glAttachShader(m_id, shader);

    return true;
}

bool Shader::link() {
    assert(Context::getCurrentContext());
    GLint success;
    GLint uniforms;
    char* nameBuffer = nullptr;
    GLsizei nbSize   = 0;
    auto* uf =
        reinterpret_cast<std::unordered_map<std::string, int>*>(m_uniforms);

    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logLength;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> log(logLength);
        glGetProgramInfoLog(m_id, logLength, &logLength, log.data());

        glDeleteProgram(m_id);

        Log::general << Log::MessageType::Error
                     << "Shader compilation error: " << log.data()
                     << Log::Operation::Endl;

        return false;
    }

    glGetProgramInterfaceiv(m_id, GL_UNIFORM, GL_ACTIVE_RESOURCES, &uniforms);
    if (uniforms > 0) {
        glGetProgramInterfaceiv(m_id, GL_UNIFORM, GL_MAX_NAME_LENGTH, &nbSize);
        nameBuffer = new char[nbSize];
        for (auto i = 0; i < uniforms; i++) {
            const GLenum prop = GL_ARRAY_SIZE;
            GLint arraySize   = 0;
            glGetProgramResourceName(m_id,
                                     GL_UNIFORM,
                                     i,
                                     nbSize,
                                     NULL,
                                     nameBuffer);
            auto loc =
                glGetProgramResourceLocation(m_id, GL_UNIFORM, nameBuffer);
            try {
                uf->insert(std::make_pair(nameBuffer, loc));
            } catch (...) {
                Application::crashApplication(
                    "Could not insert into unordered map");
            }

            glGetProgramResourceiv(m_id,
                                   GL_UNIFORM,
                                   i,
                                   1,
                                   &prop,
                                   1,
                                   NULL,
                                   &arraySize);

            for (auto j = 1; j < arraySize; j++) {
                try {
                    std::string n(nameBuffer);
                    n.resize(n.size() - 2);
                    n += std::to_string(j) + "]";
                    auto loc2 = glGetProgramResourceLocation(m_id,
                                                             GL_UNIFORM,
                                                             n.c_str());
                    try {
                        uf->insert(std::make_pair(n, loc2));
                    } catch (...) {
                        Application::crashApplication(
                            "Could not insert into unordered map");
                    }
                } catch (...) {
                    Application::crashApplication("Failed string manipulation");
                }
            }
        }
        delete[] nameBuffer;
    }

    return true;
}

void Shader::use() const {
    glUseProgram(m_id);
}

bool Shader::hasUniform(const char* name) {
    auto* uf =
        reinterpret_cast<std::unordered_map<std::string, int>*>(m_uniforms);

    if (uf->find(name) != uf->end()) {
        return true;
    }

    return false;
}

void Shader::setUniform(const char* name, const glm::mat4& mat) {
    auto* uf =
        reinterpret_cast<std::unordered_map<std::string, int>*>(m_uniforms);
    if (auto l = uf->find(name); l != uf->end()) {
        glProgramUniformMatrix4fv(m_id, l->second, 1, GL_FALSE, &mat[0][0]);
    } else {
        Application::crashApplication("Uniform does not exist");
    }
}

void Shader::setUniform(const char* name, const unsigned int uint) {
    auto* uf =
        reinterpret_cast<std::unordered_map<std::string, int>*>(m_uniforms);
    if (auto l = uf->find(name); l != uf->end()) {
        glProgramUniform1ui(m_id, l->second, uint);
    } else {
        Application::crashApplication("Uniform does not exist");
    }
}

void Shader::setUniform(const char* name, const signed int sint) {
    auto* uf =
        reinterpret_cast<std::unordered_map<std::string, int>*>(m_uniforms);
    if (auto l = uf->find(name); l != uf->end()) {
        glProgramUniform1i(m_id, l->second, sint);
    } else {
        Application::crashApplication("Uniform does not exist");
    }
}
}
