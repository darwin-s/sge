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

#include <SGE/VAO.hpp>
#include <SGE/Context.hpp>
#include <cassert>
#include <glad.h>

namespace sge {
VAO::VAO() : m_id(0) {
    assert(Context::getCurrentContext());
    glCreateVertexArrays(1, &m_id);
}

VAO::VAO(VAO &&other) noexcept : m_id(other.m_id) {
    other.m_id = 0;
}

VAO::~VAO() {
    assert(Context::getCurrentContext());
    glDeleteVertexArrays(1, &m_id);
}

VAO& VAO::operator=(VAO&& other) noexcept {
    m_id = other.m_id;
    other.m_id = 0;

    return *this;
}

void VAO::bindVBO(const VBO& vbo, const unsigned int bindingIndex, const std::int64_t offset, 
                  const std::size_t stride) const {
    assert(Context::getCurrentContext());
    glVertexArrayVertexBuffer(m_id, bindingIndex, vbo.m_id, offset, stride);
}

void VAO::enableAttribute(const unsigned int index) const {
    assert(Context::getCurrentContext());
    glEnableVertexArrayAttrib(m_id, index);
}

void VAO::setAttributeFormat(const unsigned int index, const int size, const Data type, const bool normalized, 
                             const unsigned int relativeOffset) const {
    assert(Context::getCurrentContext());
    GLuint dataType = 0;
    switch (type) {
    case Data::Byte:
        dataType = GL_BYTE;
        break;
    case Data::Short:
        dataType = GL_SHORT;
        break;
    case Data::Int:
        dataType = GL_INT;
        break;
    case Data::Fixed:
        dataType = GL_FIXED;
        break;
    case Data::Float:
        dataType = GL_FLOAT;
        break;
    case Data::HalfFloat:
        dataType = GL_HALF_FLOAT;
        break;
    case Data::Double:
        dataType = GL_DOUBLE;
        break;
    case Data::UnsignedByte:
        dataType = GL_UNSIGNED_BYTE;
        break;
    case Data::UnsignedShort:
        dataType = GL_UNSIGNED_SHORT;
        break;
    case Data::UnsignedInt:
        dataType = GL_UNSIGNED_INT;
        break;
    }
    glVertexArrayAttribFormat(m_id, index, size, dataType, normalized ? GL_TRUE : GL_FALSE, relativeOffset);
}

void VAO::setAttributeBinding(const unsigned int index, const unsigned int bindingIndex) const {
    assert(Context::getCurrentContext());
    glVertexArrayAttribBinding(m_id, index, bindingIndex);
}

void VAO::bind() const {
    assert(Context::getCurrentContext());
    glBindVertexArray(m_id);
}
}