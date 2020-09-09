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

#include <SGE/VBO.hpp>
#include <SGE/Context.hpp>
#include <cassert>
#include <glad.h>

namespace sge {
VBO::VBO()
    : m_id(0), m_allocated(false), m_size(0), m_mapped(false), m_mapLength(0) {
    assert(Context::getCurrentContext());
    glCreateBuffers(1, &m_id);
}

VBO::VBO(std::size_t size, AccessFlags flags, void* data)
    : m_id(0), m_allocated(true), m_size(size), m_mapped(false),
      m_mapLength(0) {
    assert(Context::getCurrentContext());
    glCreateBuffers(1, &m_id);
    GLbitfield f = 0;

    if (flags != NoAccess) {
        f |= GL_MAP_PERSISTENT_BIT;
    }

    if ((flags & ReadAccess) != 0) {
        f |= GL_MAP_READ_BIT;
    }
    if ((flags & WriteAccess) != 0) {
        f |= GL_MAP_WRITE_BIT;
    }
    glNamedBufferStorage(m_id, size, data, f);
}

VBO::VBO(VBO&& other) noexcept
    : m_id(other.m_id), m_allocated(other.m_allocated), m_size(other.m_size),
      m_mapped(other.m_mapped), m_mapLength(other.m_mapLength) {
    other.m_id        = 0;
    other.m_allocated = false;
    other.m_size      = 0;
    other.m_mapped    = false;
    other.m_mapLength = 0;
}

VBO::~VBO() {
    assert(Context::getCurrentContext());
    unmapBuffer();
    glDeleteBuffers(1, &m_id);
}

VBO& VBO::operator=(VBO&& other) noexcept {
    m_id              = other.m_id;
    m_allocated       = other.m_allocated;
    m_size            = other.m_size;
    m_mapped          = other.m_mapped;
    m_mapLength       = other.m_mapLength;
    other.m_id        = 0;
    other.m_allocated = false;
    other.m_size      = 0;
    other.m_mapped    = false;
    other.m_mapLength = 0;

    return *this;
}

void VBO::allocate(std::size_t size, AccessFlags flags, void* data) {
    assert(!m_allocated && Context::getCurrentContext());

    GLbitfield f = 0;

    if (flags != NoAccess) {
        f |= GL_MAP_PERSISTENT_BIT;
    }

    if ((flags & ReadAccess) != 0) {
        f |= GL_MAP_READ_BIT;
    }
    if ((flags & WriteAccess) != 0) {
        f |= GL_MAP_WRITE_BIT;
    }
    glNamedBufferStorage(m_id, size, data, f);

    m_allocated = true;
    m_size      = size;
}

bool VBO::isAllocated() const {
    return m_allocated;
}

std::size_t VBO::getSize() const {
    return m_size;
}

void* VBO::mapBuffer(std::size_t offset,
                     std::size_t length,
                     AccessFlags flags,
                     bool invalidateRange) {
    assert(m_allocated && Context::getCurrentContext());
    m_mapped    = true;
    m_mapLength = length;

    GLbitfield f = GL_MAP_PERSISTENT_BIT | GL_MAP_FLUSH_EXPLICIT_BIT;

    if ((flags & ReadAccess) != 0) {
        f |= GL_MAP_READ_BIT;
    } else if ((flags & WriteAccess) != 0) {
        f |= GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT;
    }

    if (invalidateRange && (flags & ReadAccess) == 0) {
        f |= GL_MAP_INVALIDATE_RANGE_BIT;
    }

    return glMapNamedBufferRange(m_id, offset, length, f);
}

void VBO::unmapBuffer() {
    assert(Context::getCurrentContext());
    if (m_mapped) {
        glFlushMappedNamedBufferRange(m_id, 0, m_mapLength);
        glUnmapNamedBuffer(m_id);
    }
}

void VBO::flushChanges(std::size_t offset, std::size_t length) {
    assert(m_mapped && Context::getCurrentContext());
    glFlushMappedNamedBufferRange(m_id, offset, length);
}

void VBO::bindElementArray() {
    assert(Context::getCurrentContext());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}
}
