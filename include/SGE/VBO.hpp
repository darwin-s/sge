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

#ifndef SGE_VBO_HPP
#define SGE_VBO_HPP

#include <SGE/Export.hpp>
#include <SGE/Types.hpp>

namespace sge {
class VAO;

/**
 * \brief Vertex Buffer Object
 * 
 * 
 * Object representing a vertex buffer
 */
class SGE_API VBO {
public:
    /**
     * \brief Construct a new VBO object
     * 
     * 
     * Construct a vertex buffer with no data
     */
    VBO();

    /**
     * \brief Construct a new VBO object
     * 
     * \param other The other VBO to move data from
     */
    VBO(VBO&& other) noexcept;

    /**
     * \brief Destroy the VBO object
     * 
     */
    ~VBO();

    /**
     * \brief Move VBO
     * 
     * \param other The other VBO to move data from
     * \return VBO& *this
     */
    VBO& operator=(VBO&& other) noexcept;

    VBO(const VBO&) = delete;
    VBO& operator=(const VBO&) = delete;

    /**
     * \brief Set the buffer data
     * 
     * 
     * Sets the data that the VBO will hold
     * \param size Size of the data
     * \param data Pointer to the data
     */
    void setData(std::size_t size, const void* data) const;

private:
    unsigned int m_id;

    friend class VAO;
};
}

#endif//SGE_VBO_HPP