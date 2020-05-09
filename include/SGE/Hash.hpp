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

#ifndef SGE_HASH_HPP
#define SGE_HASH_HPP

#include <SGE/Types.hpp>
#include <SGE/Export.hpp>
#include <string_view>
#include <cstddef>//std::size_t

namespace sge {
/**
 * \brief An object that stores 64-bit hashes
 *
 *
 * sge::Hash holds a 64-bit fnv1-a hash.
 * It can be created from a string,
 * a vector of arbitrary data, or from another Hash object.
 *
 * An uninitialized hash has a value of 0.
 * Usage example:
 * \code
 * sge::Hash h1("Hello, world!");
 * sge::Hash h2(h1);
 *
 * if (h1 == h2) {
 *     //...
 * }
 * \endcode
 */
class SGE_API Hash {
public:
    /**
     * \brief Default constructor
     *
     *
     * Construct a hash object and assigns 0 to it.
     */
    Hash();

    /**
     * \brief Construct a hash from a raw value
     *
     *
     * Constructs a hash object and assigns it's value
     * to the raw value provided.
     * \param hash The raw value of the hash
     */
    explicit Hash(std::uint64_t hash);

    /**
     * \brief Construct a hash using a vector of data
     *
     *
     * Constructs a hash object by applying the algorithm
     * to the data provided and assigning the value to the object.
     * \param data vector with the raw data
     */
    explicit Hash(const ByteData& data);

    /**
     * \brief Construct a hash from a string
     *
     *
     * Constructs a hash object by applying the algorithm
     * to a string and assigning the value to the object.
     * \param s String to be hashed
     */
    explicit Hash(std::string_view s);

    /**
     * \brief Assign the hash value using a raw value
     *
     *
     * Assign the value of a hash object by copying the raw
     * value to it.
     * \param hash Raw hash value
     * \return *this
     */
    Hash& operator=(std::uint64_t hash);

    /**
     * \brief Assign the hash value using a string
     *
     *
     * Assigns the value of a hash object by applying the hashing
     * algorithm to a string and using that value.
     * \param s The string to be hashed
     * \return *this
     */
    Hash& operator=(std::string_view s);

    /**
     * \brief Assign the hash value using raw data
     *
     *
     * Assigns the value of a hash object by applying the hashing
     * algorithm to raw data and using that value.
     * \param data data vector with raw bytes
     * \return *this
     */
    Hash& operator=(const ByteData& data);

    /**
     * \brief Compare hashes
     *
     *
     * Compares the internal value of two hashes
     * and returns an appropriate boolean value.
     * \param other The hash object to compare to
     * \return true if the internal values are equal, false otherwise
     */
    bool operator==(const Hash& other) const;

    /**
     * \brief Compare hashes
     *
     *
     * Compares the internal value of two hashes
     * and returns an appropriate boolean value.
     * \param other The hash object to compare to
     * \return true if the internal values are <b>not</b> equal, false otherwise
     */
    bool operator!=(const Hash& other) const;

    /**
     * \brief Compare hashes
     *
     * Compares the internal value of a hash
     * with a raw value and returns the appropriate
     * boolean value.
     * \param hash The raw hash value to compare to
     * \return true if the values are equal, false otherwise
     */
    bool operator==(std::uint64_t hash) const;

    /**
     * \brief Compare hashes
     *
     * Compares the internal value of a hash
     * with a raw value and returns the appropriate
     * boolean value.
     * \param hash The raw hash value to compare to
     * \return true if the values are <b>not</b> equal, false otherwise
     */
    bool operator!=(std::uint64_t hash) const;

    /**
     * \brief Cast the hash object to std::uint64_t
     *
     *
     * Explicitly casts the hash object to a 64-bit
     * unsigned integer.
     * \return The internal value of the hash object
     */
    explicit operator std::uint64_t() const;

    /**
     * \brief Get the internal value
     *
     *
     * Returns the 64-bit unsigned internal value
     * of the hash object.
     * \return The internal hash value
     */
    [[nodiscard]] std::uint64_t get() const;

private:
    std::uint64_t m_hash;
};
}

#endif// SGE_HASH_HPP