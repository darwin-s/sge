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

#include <SGE/Hash.hpp>

namespace {
constexpr uint64_t fnvPrime = 0x00000100000001B3;
constexpr uint64_t fnvOffset = 0xcbf29ce484222325;

std::uint64_t fnv(const std::uint8_t* data, const std::size_t size) {
    uint64_t hash = fnvOffset;

    for (std::size_t i = 0; i < size; i++)
        hash = (hash ^ data[i]) * fnvPrime;

    return hash;
}
}

namespace sge {
Hash::Hash()
    : m_hash(0) {

}

Hash::Hash(const std::uint64_t hash)
    : m_hash(hash) {

}

Hash::Hash(const std::uint8_t* data, const std::size_t size)
    : m_hash(fnv(data, size)) {

}

Hash::Hash(std::string_view s)
    : m_hash(fnv(reinterpret_cast<const std::uint8_t*>(s.data()), s.length())) {

}

Hash& Hash::operator=(const std::uint64_t hash) {
    m_hash = hash;

    return *this;
}

Hash& Hash::operator=(std::string_view s) {
    m_hash = fnv(reinterpret_cast<const std::uint8_t*>(s.data()), s.length());

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

void Hash::set(const std::uint8_t* data, size_t size) {
    m_hash = fnv(data, size);
}

std::uint64_t Hash::get() const {
    return m_hash;
}
}