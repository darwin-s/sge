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

#ifndef SGE_INPUTFILE_HPP
#define SGE_INPUTFILE_HPP

#include <SGE/Export.hpp>
#include <SGE/Types.hpp>

namespace sge {
/**
 * \brief Object representing a virtual file
 *
 *
 * This object is used to operated with virtual files in the virtual filesystem. It is used for
 * streaming data from a virtual file.
 * Usage example:
 * \code
 * sge::InputFile f("file.txt");
 * sge::ByteData dt = f.read(34);
 * // process data...
 * \endcode
 */
class SGE_API InputFile {
public:
    static constexpr std::size_t defaultBufferSize =
        65536;///< Default internal buffer size

    /**
     * \brief Create file
     *
     *
     * Creates a file that is not yet in an opened state.
     */
    explicit InputFile();

    /**
     * \brief Create file
     *
     *
     * Creates a file and immediately opens it.
     * \param path Path to the virtual file
     * \param bufferSize Internal buffer size
     */
    explicit InputFile(const char* path,
                       std::size_t bufferSize = defaultBufferSize);

    /**
     * \brief Move file
     *
     *
     * Move-constructs the file object.
     * \param other The other file
     */
    InputFile(InputFile&& other) noexcept;
    InputFile(const InputFile&) = delete;

    /**
     * \brief Destroy file
     *
     *
     * Closes the file and then destroys the object.
     */
    ~InputFile();

    /**
     * \brief Move file
     *
     *
     * Move-assigns the file
     * \param other The other file
     * \return *this
     */
    InputFile& operator=(InputFile&& other) noexcept;
    InputFile& operator=(const InputFile&) = delete;

    /**
     * \brief Open file
     *
     *
     * Tries to open the virtual file.
     * \param path Path to the virtual file
     * \param bufferSize Size of the internal buffer
     * \return true on success, false otherwise
     */
    bool open(const char* path, std::size_t bufferSize = defaultBufferSize);

    /**
     * \brief Is File Open
     *
     *
     * Returns whether the file was opened.
     * \return true if file is open, false otherwise
     */
    [[nodiscard]] bool isOpen() const;

    /**
     * \brief Read File Data
     *
     *
     * Reads a number of bytes from the file and writes it into a buffer.
     * \param bytes Number of bytes to read
     * \param buffer Buffer to read into
     * \return Number of bytes read (may be less than std::size_t bytes if file reached EOF)
     */
    std::size_t read(std::size_t bytes, void* buffer) const;

    /**
     * \brief End of File
     *
     *
     * Returns whether the end of file was reached.
     * \return true if EOF was reached, false otherwise.
     */
    [[nodiscard]] bool eof() const;

    /**
     * \brief Get position
     *
     *
     * Returns the current position in the file, relative to it's beginning.
     * \return The byte number at which this handle is set
     */
    [[nodiscard]] std::size_t tell() const;

    /**
     * \brief Seek file
     *
     *
     * Seeks to a certain position in the file, relative to the beginning.
     * \param seekPosition Position to seek to.
     */
    void seekg(std::size_t seekPosition);

    /**
     * \brief Close file
     *
     *
     * Closes the file handle.
     */
    void close();

private:
    void* m_handle;
};
}

#endif//SGE_INPUTFILE_HPP
