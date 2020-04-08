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

#ifndef __SGE_HASH_HPP__
#define __SGE_HASH_HPP__

#include <sge/export.hpp>
#include <cstdint>
#include <cstddef> //std::size_t
#include <string>

namespace sge
{
    class SGE_API Hash
    {
    public:

        Hash();

        Hash(const Hash& other);

        Hash(Hash&& other);

        explicit Hash(std::uint64_t hash);

        Hash(const std::uint8_t* data, std::size_t size);

        Hash(const std::string& s);

        Hash& operator=(const Hash& other);

        Hash& operator=(Hash&& other);

        Hash& operator=(std::uint64_t hash);

        Hash& operator=(const std::string& s);

        bool operator==(const Hash& other) const;

        bool operator!=(const Hash& other) const;

        bool operator==(std::uint64_t hash) const;

        bool operator!=(std::uint64_t hash) const;

        operator std::uint64_t() const;

        void Set(const std::uint8_t* data, std::size_t size);

        std::uint64_t Get() const;

    private:

        std::uint64_t mHash;

    };
}

#endif //!__SGE_HASH_HPP__