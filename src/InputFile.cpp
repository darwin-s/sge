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

#include <SGE/InputFile.hpp>
#include <SGE/Application.hpp>
#include <SGE/Log.hpp>
#include <string>
#include <cassert>
#include <physfs.h>

namespace sge {
InputFile::InputFile() : m_handle(nullptr) {
    assert(PHYSFS_isInit());
}

InputFile::InputFile(const char* path, const std::size_t bufferSize)
    : m_handle(nullptr) {
    assert(PHYSFS_isInit());
    if (!open(path, bufferSize)) {
        Application::crashApplication("Failed to open file");
    }
}

InputFile::InputFile(InputFile&& other) noexcept : m_handle(other.m_handle) {
    assert(PHYSFS_isInit());
    other.m_handle = nullptr;
}

InputFile::~InputFile() {
    assert(PHYSFS_isInit());
    auto* file = static_cast<PHYSFS_File*>(m_handle);

    if (file != nullptr) {
        PHYSFS_close(file);
    }
}

InputFile& InputFile::operator=(InputFile&& other) noexcept {
    assert(PHYSFS_isInit());
    m_handle       = other.m_handle;
    other.m_handle = nullptr;

    return *this;
}

bool InputFile::open(const char* path, const std::size_t bufferSize) {
    assert(PHYSFS_isInit());

    if (isOpen()) {
        close();
    }

    m_handle = PHYSFS_openRead(path);
    if (m_handle == nullptr) {
        const auto ec = PHYSFS_getLastErrorCode();
        try {
            std::string msg = "File opening unsuccessful: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;
        } catch (...) {
            Application::crashApplication("Failed string manipulation");
        }

        return false;
    }

    if (PHYSFS_setBuffer(static_cast<PHYSFS_File*>(m_handle), bufferSize) ==
        0) {
        try {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "Buffer setting unsuccessful: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;

            PHYSFS_close(static_cast<PHYSFS_File*>(m_handle));
            m_handle = nullptr;
            return false;
        } catch (...) {
            sge::Application::crashApplication("Failed string manipulation");
        }
    }

    return true;
}

bool InputFile::isOpen() const {
    return m_handle != nullptr;
}

std::size_t InputFile::read(const std::size_t bytes, void* buffer) const {
    assert(PHYSFS_isInit());
    auto* file = static_cast<PHYSFS_File*>(m_handle);

    if (file == nullptr) {
        Log::general << Log::MessageType::Warning
                     << "File reading unsuccessful: file not opened"
                     << Log::Operation::Endl;

        Application::crashApplication("Failed to read file");
    }

    const auto read = PHYSFS_readBytes(file, buffer, bytes);
    if (read < 0) {
        try {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "File reading unsuccessful: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;

            Application::crashApplication("Failed to read file");
        } catch (...) {
            sge::Application::crashApplication("Failed string manipulation");
        }
    }

    if (read < bytes) {
        const auto ec = PHYSFS_getLastErrorCode();
        if (ec != PHYSFS_ERR_OK) {
            try {
                std::string msg = "File reading unsuccessful: ";
                msg += PHYSFS_getErrorByCode(ec);

                Log::general << Log::MessageType::Warning << msg.c_str()
                             << Log::Operation::Endl;

                Application::crashApplication("Failed to read file");
            } catch (...) {
                sge::Application::crashApplication(
                    "Failed string manipulation");
            }
        }
    }

    return read;
}

bool InputFile::eof() const {
    assert(PHYSFS_isInit());
    auto* file = static_cast<PHYSFS_File*>(m_handle);

    if (file == nullptr) {
        Log::general << Log::MessageType::Warning
                     << "Called eof() on unopened file" << Log::Operation::Endl;

        Application::crashApplication("Failed to get eof property of file");
    }

    return PHYSFS_eof(file) != 0;
}

std::size_t InputFile::tell() const {
    assert(PHYSFS_isInit());
    auto* file = static_cast<PHYSFS_File*>(m_handle);

    if (file == nullptr) {
        Log::general << Log::MessageType::Warning
                     << "Called tell() on unpened file" << Log::Operation::Endl;

        Application::crashApplication("Failed to tell on file");
    }

    const auto t = PHYSFS_tell(file);
    if (t < 0) {
        try {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "Position tell unsuccessful: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;

            Application::crashApplication("Failed to tell on file");
        } catch (...) {
            sge::Application::crashApplication("Failed string manipulation");
        }
    }

    return t;
}

void InputFile::seekg(const std::size_t seekPosition) {
    assert(PHYSFS_isInit());
    auto* file = static_cast<PHYSFS_File*>(m_handle);

    if (file == nullptr) {
        Log::general << Log::MessageType::Warning
                     << "Called seekg() on unopened file"
                     << Log::Operation::Endl;

        Application::crashApplication("Failed to seek in file");
    }

    if (PHYSFS_seek(file, seekPosition) == 0) {
        try {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "File seeking unsuccessful: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;

            Application::crashApplication("Failed to seek in file");
        } catch (...) {
            sge::Application::crashApplication("Failed string manipulation");
        }
    }
}

void InputFile::close() {
    assert(PHYSFS_isInit());
    auto* file = static_cast<PHYSFS_File*>(m_handle);

    if (file != nullptr && PHYSFS_close(file) == 0) {
        try {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "File closing unsuccessful: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;
        } catch (...) {
            sge::Application::crashApplication("Failed string manipulation");
        }
    }

    m_handle = nullptr;
}
}
