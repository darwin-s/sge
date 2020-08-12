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

#include <SGE/Resource.hpp>
#include <SGE/Log.hpp>

namespace sge {
Resource::Resource() : m_id(0), m_ready(false), m_failed(false) {

}

std::uint64_t Resource::getId() const {
    std::scoped_lock s(m_idMutex);
    return m_id;
}

bool Resource::isReady() const {
    std::scoped_lock s(m_readyMutex);
    return m_ready;
}

bool Resource::isFailed() const {
    return m_failed;
}

void Resource::fail(const std::string_view reason) {
    std::string msg = "Resource loading failed: ";
    msg += reason;
    std::scoped_lock sl(Log::generalMutex);
    Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
    m_failed = true;
}

void Resource::setReady(const bool ready) {
    std::scoped_lock s(m_readyMutex);
    m_ready = ready;
}
}
