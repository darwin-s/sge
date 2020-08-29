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

#ifndef SGE_VAO_HPP
#define SGE_VAO_HPP

#include <SGE/Export.hpp>
#include <SGE/VBO.hpp>
#include <SGE/Types.hpp>

namespace sge {
/**
 * \brief Vertex Array Object
 *
 *
 * Class representing an OpenGL VAO. It is used to hold vertex attributes
 * for rendering.
 */
class SGE_API VAO {
public:
    /**
     * \brief Vertex Attribute data type
     *
     *
     * Represents the data type of the vertex attribute
     */
    enum class Data {
        Byte,         ///< Byte size integer
        Short,        ///< Short (16-bit) integer
        Int,          ///< Integer (32-bit)
        Fixed,        ///< Fixed precision number
        Float,        ///< Floating point number
        HalfFloat,    ///< Half precision floating point number
        Double,       ///< Double precision floating point number
        UnsignedByte, ///< Unsigned byte size integer
        UnsignedShort,///< Unsigned short (16-bit) integer
        UnsignedInt   ///< Unsigned integer (32-bit)
    };

    /**
     * \brief Create VAO object
     */
    VAO();

    /**
     * \brief Create VAO object
     * \param other Other VAO object to move from
     */
    VAO(VAO&& other) noexcept;

    /**
     * \brief Destruct VAO Object
     */
    ~VAO();

    /**
     * \brief Move assign VAO object
     * \param other Other VAO object to move from
     * \return *this
     */
    VAO& operator=(VAO&& other) noexcept;

    VAO(const VAO&) = delete;
    VAO& operator=(const VAO&) = delete;

    /**
     * \brief Bind VBO
     *
     *
     * Binds a VBO to this array object.
     * \param vbo VBO to bind
     * \param bindingIndex Index to bind to
     * \param offset Offset of the first element in the VBO
     * \param stride Size to get to the next element in the VBO
     */
    void bindVBO(const VBO& vbo,
                 unsigned int bindingIndex,
                 std::int64_t offset,
                 std::size_t stride) const;

    /**
     * \brief Enable vertex attribute
     *
     *
     * Enables an attribute for the current VAO
     * \param index Attribute index
     */
    void enableAttribute(unsigned int index) const;

    /**
     * \brief Set Attribute Format
     *
     *
     * Sets the format of an attribute
     * \param index Index of the attribute
     * \param size Size of attribute
     * \param type Type of data for the vertex attribute
     * \param normalized Whether the data is normalized (between 0 and 1)
     * \param relativeOffset Relative offset of the element
     */
    void setAttributeFormat(unsigned int index,
                            int size,
                            Data type,
                            bool normalized,
                            unsigned int relativeOffset) const;

    /**
     * \brief Bind Attribute to VBO binding
     * \param index Attribute index
     * \param bindingIndex VBO binding index
     */
    void setAttributeBinding(unsigned int index,
                             unsigned int bindingIndex) const;

    /**
     * \brief Bind this VAO
     */
    void bind() const;

private:
    unsigned int m_id;
};
}

#endif//SGE_VAO_HPP
