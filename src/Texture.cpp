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

#include <SGE/Texture.hpp>
#include <SGE/Context.hpp>
#include <SGE/Filesystem.hpp>
#include <SGE/InputFile.hpp>
#include <glad.h>
#include <stb_image.h>
#include <stdexcept>
#include <cassert>
#include <cmath>

namespace sge {
Texture::Texture()
    : m_id(0), m_size(0, 0), m_wrapMode(WrapMode::ClampToBorder),
      m_filterMode(FilterMode::Nearest), m_hasMipmaps(false) {
}

Texture::Texture(const std::filesystem::path& file)
    : m_id(0), m_size(0, 0), m_wrapMode(WrapMode::ClampToBorder),
      m_filterMode(FilterMode::Nearest), m_hasMipmaps(false) {
    if (!loadFromFile(file)) {
        throw std::runtime_error("Failed to load texture");
    }
}

Texture::Texture(const std::size_t size, const void* data)
    : m_id(0), m_size(0, 0), m_wrapMode(WrapMode::ClampToBorder),
      m_filterMode(FilterMode::Nearest), m_hasMipmaps(false) {
    if (loadFromMemory(size, data)) {
        throw std::runtime_error("Failed to load texture");
    }
}

Texture::Texture(const Image& image)
    : m_id(0), m_size(0, 0), m_wrapMode(WrapMode::ClampToBorder),
      m_filterMode(FilterMode::Nearest), m_hasMipmaps(false) {
    if (loadFromImage(image)) {
        throw std::runtime_error("Failed to load texture");
    }
}

Texture::~Texture() {
    if (m_id != 0) {
        assert(Context::getCurrentContext() != nullptr);
        glDeleteTextures(1, &m_id);
    }
}

bool Texture::loadFromFile(const std::filesystem::path& path) {
    const auto imageSize = Filesystem::getFileSize(path);
    const InputFile image(path);
    auto imageData = image.read(imageSize);

    return loadFromMemory(imageSize, imageData.data());
}

bool Texture::loadFromMemory(const std::size_t size, const void* data) {
    assert(Context::getCurrentContext() != nullptr);

    if (m_id != 0) {
        glDeleteTextures(1, &m_id);
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    int w, h, c;
    auto* imageData = stbi_load_from_memory(static_cast<const stbi_uc*>(data),
                                            size,
                                            &w,
                                            &h,
                                            &c,
                                            STBI_rgb_alpha);
    if (imageData == nullptr || c < 4 || w == 0 || h == 0) {
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }

        return false;
    }

    m_size.x = static_cast<unsigned int>(w);
    m_size.y = static_cast<unsigned int>(h);

    const GLint texLevels = 1 + std::floor(std::log2(std::max(w, h)));

    glTextureStorage2D(m_id, texLevels, GL_RGBA8, m_size.x, m_size.y);
    glTextureSubImage2D(m_id,
                        0,
                        0,
                        0,
                        m_size.x,
                        m_size.y,
                        GL_RGBA,
                        GL_UNSIGNED_BYTE,
                        imageData);

    stbi_image_free(imageData);

    return true;
}

bool Texture::loadFromImage(const Image& image) {
    assert(Context::getCurrentContext() != nullptr);

    if (m_id != 0) {
        glDeleteTextures(1, &m_id);
    }

    if (image.getChannelNo() < 4) {
        return false;
    }

    if (image.getSize().x == 0 || image.getSize().y == 0) {
        return false;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    m_size = image.getSize();

    const GLint texLevels =
        1 + std::floor(std::log2(std::max(m_size.x, m_size.y)));
    glTextureStorage2D(m_id, texLevels, GL_RGBA8, m_size.x, m_size.y);
    glTextureSubImage2D(m_id,
                        0,
                        0,
                        0,
                        m_size.x,
                        m_size.y,
                        GL_RGBA,
                        GL_UNSIGNED_BYTE,
                        image.getPixelData());

    return true;
}

void Texture::setWrapMode(const WrapMode mode) {
    assert(Context::getCurrentContext() != nullptr);
    GLuint m;
    switch (mode) {
    case WrapMode::Repeat:
        m = GL_REPEAT;
        break;
    case WrapMode::MirroredRepeat:
        m = GL_MIRRORED_REPEAT;
        break;
    case WrapMode::ClampToEdge:
        m = GL_CLAMP_TO_EDGE;
        break;
    case WrapMode::ClampToBorder:
        m = GL_CLAMP_TO_BORDER;
        break;
    }

    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, m);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, m);

    m_wrapMode = mode;
}

void Texture::setFilterMode(const FilterMode mode) {
    assert(Context::getCurrentContext() != nullptr);
    GLuint m;
    switch (mode) {
    case FilterMode::Nearest:
        m = GL_NEAREST;
        break;
    case FilterMode::Linear:
        m = GL_LINEAR;
        break;
    case FilterMode::NearestMipmapNearest:
        m = GL_NEAREST_MIPMAP_NEAREST;
        break;
    case FilterMode::NearestMipmapLinear:
        m = GL_NEAREST_MIPMAP_LINEAR;
        break;
    case FilterMode::LinearMipmapNearest:
        m = GL_LINEAR_MIPMAP_NEAREST;
        break;
    case FilterMode::LinearMipmapLinear:
        m = GL_LINEAR_MIPMAP_LINEAR;
        break;
    }

    if (!m_hasMipmaps) {
        if (m == GL_NEAREST_MIPMAP_NEAREST || m == GL_LINEAR_MIPMAP_NEAREST) {
            m = GL_NEAREST;
        } else if (m == GL_NEAREST_MIPMAP_LINEAR
                   || m == GL_LINEAR_MIPMAP_LINEAR) {
            m = GL_LINEAR;
        }
    }
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, m);

    if (m == GL_LINEAR_MIPMAP_LINEAR || m == GL_NEAREST_MIPMAP_LINEAR) {
        m = GL_LINEAR;
    } else {
        m = GL_NEAREST;
    }

    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, m);

    m_filterMode = mode;
}

void Texture::generateMipmaps() {
    assert(Context::getCurrentContext() != nullptr);
    glGenerateTextureMipmap(m_id);
}

void Texture::bind(const int unit) {
    assert(Context::getCurrentContext() != nullptr);
    glBindTextureUnit(unit, m_id);
    m_hasMipmaps = true;
}

const glm::uvec2& Texture::getSize() const {
    return m_size;
}

Texture::WrapMode Texture::getWrapMode() const {
    return m_wrapMode;
}

Texture::FilterMode Texture::getFilterMode() const {
    return m_filterMode;
}

bool Texture::hasMipmaps() const {
    return m_hasMipmaps;
}

unsigned int Texture::getMaximumSize() {
    assert(Context::getCurrentContext() != nullptr);
    int r;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &r);

    return r;
}

unsigned int Texture::getMaximumImageUnits() {
    assert(Context::getCurrentContext() != nullptr);
    int r;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &r);

    return r;
}
}
