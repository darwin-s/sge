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
RenderState RenderState::defaultState = RenderState(glm::mat4(1.0f));

RenderState::RenderState(std::shared_ptr<Shader> shader)
    : shader(std::move(shader)), transform(1.0f), texture(nullptr) {
}

RenderState::RenderState(const glm::mat4& transform)
    : shader(nullptr), transform(transform), texture(nullptr) {
}

RenderState::RenderState(std::shared_ptr<Texture> texture)
    : shader(nullptr), transform(1.0f), texture(std::move(texture)) {
}
}
