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
VBO::VBO() : m_id(0) {
    assert(Context::getCurrentContext());
    glCreateBuffers(1, &m_id);
}

VBO::VBO(VBO&& other) noexcept : m_id(other.m_id) {
    other.m_id = 0;
}

VBO::~VBO() {
    assert(Context::getCurrentContext());
    glDeleteBuffers(1, &m_id);
}

VBO& VBO::operator=(VBO&& other) noexcept {
    m_id = other.m_id;
    other.m_id = 0;

    return *this;
}

void VBO::setData(const std::size_t size, const void* data) const {
    assert(Context::getCurrentContext());
    glNamedBufferData(m_id, size, data, GL_STATIC_DRAW);
}
}