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

#ifndef SGE_IMAGE_HPP
#define SGE_IMAGE_HPP

#include <SGE/Export.hpp>
#include <SGE/Resource.hpp>
#include <SGE/Vector2.hpp>

namespace sge {
/**
 * \brief Object representing a raw image
 *
 *
 * This object is used to represent a raw image. The image pixels are flipped vertically for use with OpenGL.
 * The object holds raw pixel data and does not yet hold any OpenGL texture objects.
 * The following formats are supported:
 * - JPEG (baseline and progressive without 12 bpc/arithmetic)
 * - PNG (1/2/4/8/16 bits per channel)
 * - TGA
 * - BMP (non-1bpp and non-RLE)
 * - PSD (composed view 8/16 bits per channel)
 * - GIF
 * - HDR
 * - PIC
 * - PNM (PPM and PGM binary only)
 * Usage example:
 * \code
 * sge::Image img("image.png");
 * unsigned char* pixelData = img.getPixelData();
 * // Use pixel data...
 * \endcode
 */
class SGE_API Image final : public Resource {
public:
    /**
     * \brief Create image
     *
     *
     * Constructs an empty image object.
     */
    Image();

    /**
     * \brief Create image
     *
     *
     * Creates and loads an image from a virtual file.
     * \throws std::runtime_error
     * \param file Path to the virtual file
     */
    explicit Image(const std::filesystem::path& file);

    /**
     * \brief Create image
     *
     *
     * Creates and loads an image from memory.
     * \throws std::runtime_error
     * \param size Size of provided data in bytes
     * \param data Pointer to the data buffer
     */
    Image(std::size_t size, const void* data);

    /**
     * \brief Move-construct an image object
     *
     *
     * Moves data from another image object.
     * \param other The other image object
     */
    Image(Image&& other) noexcept;

    /**
     * \brief Destroy image
     *
     *
     * Deconstructs the image object
     */
    virtual ~Image();

    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

    /**
     * \brief Move-assign image object
     *
     *
     * Moves data from another image object.
     * \param other the other image object
     * \returns *this
     */
    Image& operator=(Image&& other) noexcept;

    /**
     * \brief Load image from a virtual file
     *
     *
     * Loads an image from a virtual file.
     * \param path Path to the virtual file
     * \returns true on success, false otherwise
     */
    bool loadFromFile(const std::filesystem::path& path) override;

    /**
     * \brief Load image from memory
     *
     *
     * Loads an image from memory.
     * \param size Size of provided data in bytes
     * \param data Pointer to the data buffer
     * \returns true on success, false otherwise
     */
    bool loadFromMemory(std::size_t size, const void* data) override;

    /**
     * \brief Get image pixel data
     *
     *
     * Returns a pointer to the raw pixel data of the image.
     * \returns Pointer to pixel data
     */
    unsigned char* getPixelData() const;

    /**
     * \brief Get image size
     *
     *
     * Returns the size in pixels of the image.
     * \returns Vector containing the image's size
     */
    const Vector2U& getSize() const;

    /**
     * \brief Get number of channels
     *
     *
     * Returns the number of color channels in this image.
     * \returns Number of color channels
     */
    int getChannelNo() const;

private:
    unsigned char* m_data;
    Vector2U m_size;
    int m_channels;
};
}

#endif// SGE_IMAGE_HPP
