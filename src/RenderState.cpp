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

#include <SGE/RenderState.hpp>

namespace sge {
RenderState RenderState::defaultState = RenderState(nullptr);

RenderState::RenderState(Shader* shader) : m_shader(shader) {
}

Shader* RenderState::getShader() const {
    return m_shader;
}

void RenderState::setShader(Shader* shader) {
    m_shader = shader;
}
}