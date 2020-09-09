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
#include <memory>

namespace sge {
class VAO;

/**
 * \brief Vertex Buffer Object
 * 
 * 
 * Object representing a vertex buffer. It is used to hold vertex data.
 * Vertex buffers have access flags, which restrict their use. If a buffer
 * is initialized with read access only, then mapping it for writing will
 * give an error.
 */
class SGE_API VBO {
public:
    /**
     * \brief Buffer access flags
     *
     *
     * Represents the access intention when mapping the buffer, or
     * the access restriction when creating it.
     */
    enum AccessFlags {
        NoAccess    = 0,     ///< Buffer may not be accessed after creation
        ReadAccess  = 1 << 0,///< Buffer may be accessed for reading
        WriteAccess = 1 << 1 ///< Buffer may be accessed for writing
    };

    /**
     * \brief Create vertex buffer
     *
     *
     * Creates a vertex buffer with 0 size, and no data
     */
    VBO();

    /**
     * \brief Create vertex buffer
     *
     *
     * Creates a vertex buffer of a certain size, and access restrictions,
     * optionally initializing it's contents, with some data.
     * \param size Size of the vertex buffer in bytes
     * \param flags Access flags for the vertex buffer
     * \param data Optional data to fill the buffer
     */
    VBO(std::size_t size, AccessFlags flags, void* data = nullptr);

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
     * \brief Allocate buffer
     *
     *
     * Allocates buffer storage and optionally initializes it with some data.
     * \note If the buffer is already allocated, then calling this function will give an error
     * \param size Size of the buffer
     * \param flags Access flags for the buffer
     * \param data Optional data to initialize the buffer
     */
    void allocate(std::size_t size, AccessFlags flags, void* data = nullptr);

    /**
     * \brief Is buffer allocated
     *
     *
     * Returns whether the buffer storage was allocated.
     * \return true if buffer was allocated, false otherwise
     */
    [[nodiscard]] bool isAllocated() const;

    /**
     * \brief Get buffer size
     *
     *
     * Returns the storage size of the buffer
     * \return Storage size
     */
    [[nodiscard]] std::size_t getSize() const;

    /**
     * \brief Map buffer
     *
     *
     * Maps a range of the buffer into CPU memory, to read or write to it.
     * This mapping is persistent, so it
     * \note Currently you cannot map a buffer for both reading and writing.
     * \param offset Offset inside the buffer where the map is going to start
     * \param length Length of the map
     * \param flags Access flags for the map
     * \param invalidateRange Invalidate the previous contents of the buffer in the specified range
     * \return Pointer to the memory map
     */
    [[nodiscard]] void* mapBuffer(std::size_t offset,
                                  std::size_t length,
                                  AccessFlags flags,
                                  bool invalidateRange = false);

    /**
     * \brief Unmap buffer
     */
    void unmapBuffer();

    /**
     * \brief Flush changes
     *
     *
     * Flushes the changes made to a buffer mapping.
     * \param offset Offset of the sub-region to be flushed.
     * \param length Length of the sub-region to be flushed.
     */
    void flushChanges(std::size_t offset, std::size_t length);

    /**
     * \brief Bind as element array
     *
     *
     * Binds the current array as a element index target.
     */
    void bindElementArray();

private:
    unsigned int m_id;
    bool m_allocated;
    std::size_t m_size;
    bool m_mapped;
    std::size_t m_mapLength;

    friend class VAO;
};
}

#endif//SGE_VBO_HPP
