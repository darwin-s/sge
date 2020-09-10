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

#ifndef SGE_TEXTURE_HPP
#define SGE_TEXTURE_HPP

#include <SGE/Export.hpp>
#include <SGE/Resource.hpp>
#include <SGE/Image.hpp>
#include <glm/vec2.hpp>

namespace sge {
/**
 * \brief Texture object
 *
 *
 * Object representing a texture, which is used for rendering objects.
 * The texture does not hold it's image data. It only holds a handle
 * to the OpenGL texture, which most likely will be held in VRAM.
 * Usage example:
 * \code
 * sge::Texture t("/texture.png");
 * renderTarget.draw(drawableObject, RenderState(&t));
 * \endcode
 */
class SGE_API Texture final : public Resource {
public:
    /**
     * \brief Texture wrapping mode
     *
     *
     * Represents the wrapping mode for when the texture coordinates are outside the
     * area of the texture.
     */
    enum class WrapMode {
        Repeat,        ///< Repeat the texture
        MirroredRepeat,///< Repeat the texture mirrored
        ClampToEdge,   ///< Clamp to the edge of the texture
        ClampToBorder  ///< Clamp to the border of the texture
    };

    /**
     * \brief Texture filtering mode
     *
     * Represents the filtering mode for the texture.
     */
    enum class FilterMode {
        Nearest,             ///< Nearest filtering
        Linear,              ///< Linear filtering
        NearestMipmapNearest,///< Nearest mipmap, nearest pixel filtering
        NearestMipmapLinear, ///< Nearest mipmap, linear pixel filtering
        LinearMipmapNearest, ///< Linear mipmap, nearest pixel filtering
        LinearMipmapLinear   ///< Linear mipmap, linear pixel filtering
    };

    /**
     * \brief Create texture
     *
     *
     * Creates an empty texture
     */
    Texture();

    /**
     * \brief Create texture
     *
     *
     * Creates a texture by loading an image from a virtual file.
     * \param file File to load texture from
     */
    explicit Texture(const char* file);

    /**
     * \brief Create texture
     *
     *
     * Creates a texture by loading an image from memory.
     * \param size Memory buffer size
     * \param data Pointer to memory buffer
     */
    Texture(std::size_t size, const void* data);

    /**
     * \brief Create texture
     *
     *
     * Creates a texture by taking pixel data from a loaded image.
     * \param image Image to load data from
     */
    explicit Texture(const Image& image);

    /**
     * \brief Destroy texture
     */
    virtual ~Texture();

    Texture(const Texture&) = delete;
    Texture(Texture&&)      = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;

    /**
     * \brief Load texture
     *
     *
     * Load a texture from a virtual file.
     * \param path Path to file
     * \return true on success, false otherwise
     */
    bool loadFromFile(const char* path) override;

    /**
     * \brief Load texture
     *
     *
     * Load a texture from a memory buffer.
     * \param size Size of memory buffer
     * \param data Pointer to memory buffer
     * \return true on success, false otherwise
     */
    bool loadFromMemory(std::size_t size, const void* data) override;

    /**
     * \brief Load texture
     *
     *
     * Load a texture from an already loaded image.
     * \param image Image to load from
     * \return true on success, false otherwise
     */
    bool loadFromImage(const Image& image);

    /**
     * \brief Set texture wrapping mode
     * \param mode Wrapping mode
     */
    void setWrapMode(WrapMode mode);

    /**
     * \brief Set texture filtering mode
     * \param mode Filtering mode
     */
    void setFilterMode(FilterMode mode);

    /**
     * \brief Generate texture mipmaps
     */
    void generateMipmaps();

    /**
     * \brief Bind texture
     *
     *
     * Binds the texture to a OpenGL texture unit.
     * \param unit Texture unit to be bound
     */
    void bind(int unit);

    /**
     * \brief Get texture size
     * \return Texture size
     */
    const glm::uvec2& getSize() const;

    /**
     * \brief Get texture wrapping mode
     * \return Texture wrapping mode
     */
    WrapMode getWrapMode() const;

    /**
     * \brief Get texture filtering mode
     * \return Texture filtering mode
     */
    FilterMode getFilterMode() const;

    /**
     * \brief Texture has mipmaps
     * \return true if texture has mipmaps, false otherwise
     */
    bool hasMipmaps() const;

    /**
     * \brief Get maximum texture size
     *
     *
     * Returns the maximum size of a texture. The size represents the maximum height and width of a texture.
     * For example a size of 4096 means that the maximum texture size is 4096*4096.
     * \return Maximum texture size
     */
    static unsigned int getMaximumSize();

    /**
     * \brief Get maximum image units
     *
     *
     * Returns the maximum number of samplers bound in a fragment shader
     * at a time.
     * \return Maximum number of image units
     */
    static unsigned int getMaximumImageUnits();

private:
    unsigned int m_id;
    glm::uvec2 m_size;
    WrapMode m_wrapMode;
    FilterMode m_filterMode;
    bool m_hasMipmaps;
};
}

#endif//SGE_TEXTURE_HPP
