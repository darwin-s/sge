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
#include <SGE/Context.hpp>
#include <SGE/Filesystem.hpp>
#include <SGE/InputFile.hpp>
#include <SGE/Log.hpp>
#include <cassert>
#include <glad.h>

namespace sge {
Shader::Shader() {
    assert(Context::getCurrentContext());
    m_id = glCreateProgram();
}

Shader::Shader(Shader&& other) noexcept : m_id(other.m_id) {
    other.m_id = 0;
}

Shader::~Shader() {
    assert(Context::getCurrentContext());
    glDeleteProgram(m_id);
}

Shader& Shader::operator=(Shader&& other) noexcept {
    m_id = other.m_id;
    other.m_id = 0;

    return *this;
}

bool Shader::load(const std::filesystem::path& file, Type type) const {
    assert(Context::getCurrentContext());
    std::size_t shaderSize = Filesystem::getFileSize(file);
    InputFile shader(file);
    ByteData shaderData = shader.read(shaderSize);

    return load(shaderSize, shaderData.data(), type);
}

bool Shader::load(std::size_t size, const void* data, Type type) const {
    assert(Context::getCurrentContext());
    GLuint shader;
    GLint success;
    if (type == Vertex) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, data, size);
    glSpecializeShader(shader, "main", 0, nullptr, nullptr);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> log(logLength);
        glGetShaderInfoLog(shader, logLength, &logLength, log.data());

        glDeleteShader(shader);

        std::scoped_lock l(Log::generalMutex);
        Log::general << Log::MessageType::Error << "Shader compilation error: " << log.data() << Log::Operation::Endl;

        return false;
    }

    glAttachShader(m_id, shader);

    return true;
}

bool Shader::link() const {
    assert(Context::getCurrentContext());
    GLint success;

    glLinkProgram(m_id);

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        GLint logLength;
        glGetProgramiv(m_id, GL_LINK_STATUS, &logLength);

        std::vector<GLchar> log(logLength);
        glGetProgramInfoLog(m_id, logLength, &logLength, log.data());

        glDeleteProgram(m_id);

        std::scoped_lock l(Log::generalMutex);
        Log::general << Log::MessageType::Error << "Shader compilation error: " << log.data() << Log::Operation::Endl;

        return false;
    }

    return true;
}

void Shader::use() const {
    glUseProgram(m_id);
}
}