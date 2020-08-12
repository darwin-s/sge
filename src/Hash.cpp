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

#include <SGE/Hash.hpp>

namespace {
constexpr uint64_t fnvPrime = 0x00000100000001B3;
constexpr uint64_t fnvOffset = 0xcbf29ce484222325;

std::uint64_t fnv(const sge::ByteData& data) {
    auto hash = fnvOffset;

    for (const auto& b : data) {
        hash = (hash ^ b) * fnvPrime;
    }

    return hash;
}

std::uint64_t fnv(const std::string_view s) {
    auto hash = fnvOffset;

    for (const auto& b : s) {
        hash = (hash ^ static_cast<const std::uint8_t>(b)) * fnvPrime;
    }

    return hash;
}
}

namespace sge {
Hash::Hash() : m_hash(0) {
}

Hash::Hash(const std::uint64_t hash) : m_hash(hash) {
}

Hash::Hash(const ByteData& data) : m_hash(fnv(data)) {
}

Hash::Hash(const std::string_view s) : m_hash(fnv(s)) {
}

Hash& Hash::operator=(const std::uint64_t hash) {
    m_hash = hash;

    return *this;
}

Hash& Hash::operator=(const std::string_view s) {
    m_hash = fnv(s);

    return *this;
}

Hash& Hash::operator=(const ByteData& data) {
    m_hash = fnv(data);

    return *this;
}

bool Hash::operator==(const Hash& other) const {
    return m_hash == other.m_hash;
}

bool Hash::operator!=(const Hash& other) const {
    return m_hash != other.m_hash;
}

bool Hash::operator==(const std::uint64_t hash) const {
    return m_hash == hash;
}

bool Hash::operator!=(const std::uint64_t hash) const {
    return m_hash != hash;
}

Hash::operator std::uint64_t() const {
    return m_hash;
}

std::uint64_t Hash::get() const {
    return m_hash;
}
}