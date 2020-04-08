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

#include <sge/hash.hpp>

namespace
{
    constexpr uint64_t fnv_prime  = 0x00000100000001B3;
    constexpr uint64_t fnv_offset = 0xcbf29ce484222325;

    uint64_t fnv(const std::uint8_t* data, const std::size_t size)
    {
        uint64_t hash = fnv_offset;

        for(std::size_t i = 0; i < size; i++)
            hash = (hash ^ data[i]) * fnv_prime;

        return hash;
    }
}

namespace sge
{
    Hash::Hash()
        : mHash(0)
    {

    }

    Hash::Hash(const Hash& other)
        : mHash(other.mHash)
    {

    }

    Hash::Hash(Hash&& other)
        : mHash(other.mHash)
    {
        other.mHash = 0;
    }

    Hash::Hash(const std::uint64_t hash)
        : mHash(hash)
    {

    }

    Hash::Hash(const std::uint8_t* data, const std::size_t size)
        : mHash(fnv(data, size))
    {

    }

    Hash::Hash(const std::string& s)
        : mHash(fnv(reinterpret_cast<const std::uint8_t*>(s.c_str()), s.length()))
    {

    }

    Hash& Hash::operator=(const Hash& other)
    {
        mHash = other.mHash;

        return *this;
    }

    Hash& Hash::operator=(Hash&& other)
    {
        mHash = other.mHash;
        other.mHash = 0;

        return *this;
    }

    Hash& Hash::operator=(const std::uint64_t hash)
    {
        mHash = hash;

        return *this;
    }

    Hash& Hash::operator=(const std::string& s)
    {
        mHash = fnv(reinterpret_cast<const std::uint8_t*>(s.c_str()), s.length());

        return *this;
    }

    bool Hash::operator==(const Hash& other) const
    {
        return mHash == other.mHash;
    }

    bool Hash::operator!=(const Hash& other) const
    {
        return mHash != other.mHash;
    }

    bool Hash::operator==(const std::uint64_t hash) const
    {
        return mHash == hash;
    }

    bool Hash::operator!=(const std::uint64_t hash) const
    {
        return mHash != hash;
    }

    Hash::operator std::uint64_t() const
    {
        return mHash;
    }

    void Hash::Set(const std::uint8_t* data, const std::size_t size)
    {
        mHash = fnv(data, size);
    }

    std::uint64_t Hash::Get() const
    {
        return mHash;
    }
}