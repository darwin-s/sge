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

#include <SGE/Image.hpp>
#include <SGE/Application.hpp>
#include <SGE/Filesystem.hpp>
#include <SGE/InputFile.hpp>
#include <stb_image.h>

namespace sge {
Image::Image() : m_data(nullptr), m_size(0, 0) {
}

Image::Image(const char* file) : m_data(nullptr), m_size(0, 0) {
    if (!loadFromFile(file)) {
        Application::crashApplication("Failed to load image");
    }
}

Image::Image(const std::size_t size, const void* data)
    : m_data(nullptr), m_size(0, 0) {
    if (!loadFromMemory(size, data)) {
        Application::crashApplication("Failed to load image");
    }
}

Image::Image(Image&& other) noexcept
    : m_data(other.m_data), m_size(other.m_size) {
    other.m_data = nullptr;
    other.m_size = glm::uvec2(0, 0);
}

Image::~Image() {
    if (m_data != nullptr) {
        stbi_image_free(m_data);
    }
}

Image& Image::operator=(Image&& other) noexcept {
    m_data = other.m_data;
    m_size = other.m_size;

    other.m_data = nullptr;
    other.m_size = glm::uvec2(0, 0);

    return *this;
}

bool Image::loadFromFile(const char* path) {
    const auto fileSize = Filesystem::getFileSize(path);
    const InputFile file(path);
    unsigned char* buff = new unsigned char[fileSize];
    file.read(fileSize, buff);

    bool r = loadFromMemory(fileSize, buff);

    delete[] buff;

    return r;
}

bool Image::loadFromMemory(const std::size_t size, const void* data) {
    if (m_data != nullptr) {
        stbi_image_free(m_data);
    }

    int x, y;
    m_data = stbi_load_from_memory(static_cast<const stbi_uc*>(data),
                                   size,
                                   &x,
                                   &y,
                                   NULL,
                                   STBI_rgb_alpha);

    if (x < 0 || y < 0) {
        return false;
    }

    m_size.x = static_cast<unsigned int>(x);
    m_size.y = static_cast<unsigned int>(y);

    return m_data != nullptr;
}

unsigned char* Image::getPixelData() const {
    return m_data;
}

const glm::uvec2& Image::getSize() const {
    return m_size;
}
}
