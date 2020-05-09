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
#include <SGE/Log.hpp>
#include <cassert>
#include <physfs.h>

namespace sge {
InputFile::InputFile() : m_handle(nullptr) {
    assert(PHYSFS_isInit());
}

InputFile::InputFile(const std::filesystem::path& path, std::size_t bufferSize) : m_handle(nullptr) {
    assert(PHYSFS_isInit());
    open(path, bufferSize);
}

InputFile::InputFile(InputFile&& other) noexcept : m_handle(other.m_handle) {
    assert(PHYSFS_isInit());
    other.m_handle = nullptr;
}

InputFile::~InputFile() {
    assert(PHYSFS_isInit());
    close();
}

InputFile& InputFile::operator=(InputFile&& other) noexcept {
    assert(PHYSFS_isInit());
    m_handle = other.m_handle;
    other.m_handle = nullptr;

    return *this;
}

bool InputFile::open(const std::filesystem::path& path, std::size_t bufferSize) {
    assert(PHYSFS_isInit());

    if (isOpen()) {
        close();
    }

    m_handle = PHYSFS_openRead(path.generic_u8string().c_str());
    if (!m_handle) {
        PHYSFS_ErrorCode ec = PHYSFS_getLastErrorCode();
        std::string msg = "File opening unsuccessful: ";
        msg += PHYSFS_getErrorByCode(ec);
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
        }
        return false;
    }

    if (!PHYSFS_setBuffer(reinterpret_cast<PHYSFS_File*>(m_handle), bufferSize)) {
        PHYSFS_ErrorCode ec = PHYSFS_getLastErrorCode();
        std::string msg = "Buffer setting unsuccessful: ";
        msg += PHYSFS_getErrorByCode(ec);
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
        }
        PHYSFS_close(reinterpret_cast<PHYSFS_File*>(m_handle));
        m_handle = nullptr;
        return false;
    }

    return true;
}

bool InputFile::isOpen() const {
    return m_handle != nullptr;
}

ByteData InputFile::read(std::size_t bytes) {
    assert(PHYSFS_isInit());
    ByteData ret(bytes);
    auto* file = reinterpret_cast<PHYSFS_File*>(m_handle);

    if (!file) {
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << "File reading unsuccessful: file not opened"
                         << Log::Operation::Endl;
        }
        return ByteData();
    }

    std::int64_t read = PHYSFS_readBytes(file, ret.data(), bytes);
    if (read < 0) {
        PHYSFS_ErrorCode ec = PHYSFS_getLastErrorCode();
        std::string msg = "File reading unsuccessful: ";
        msg += PHYSFS_getErrorByCode(ec);
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
        }
        return ByteData();
    }
    ret.resize(read);

    return ret;
}

bool InputFile::eof() const {
    assert(PHYSFS_isInit());
    auto* file = reinterpret_cast<PHYSFS_File*>(m_handle);

    if (!file) {
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << "Called eof() on unopened file" << Log::Operation::Endl;
        }
        return true;
    }

    return PHYSFS_eof(file) != 0;
}

std::size_t InputFile::tell() const {
    assert(PHYSFS_isInit());
    auto* file = reinterpret_cast<PHYSFS_File*>(m_handle);

    if (file) {
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << "Called tell() on unpened file" << Log::Operation::Endl;
        }
        return 0;
    }

    std::int64_t t = PHYSFS_tell(file);
    if (t < 0) {
        PHYSFS_ErrorCode ec = PHYSFS_getLastErrorCode();
        std::string msg = "Position tell unsuccessful: ";
        msg += PHYSFS_getErrorByCode(ec);
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
        }

        return 0;
    }

    return t;
}

bool InputFile::seekg(std::size_t seekPosition) {
    assert(PHYSFS_isInit());
    auto* file = reinterpret_cast<PHYSFS_File*>(m_handle);

    if (!file) {
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << "Called seekg() on unopened file" << Log::Operation::Endl;
        }
        return false;
    }

    if (!PHYSFS_seek(file, seekPosition)) {
        PHYSFS_ErrorCode ec = PHYSFS_getLastErrorCode();
        std::string msg = "File seeking unsuccessful: ";
        msg += PHYSFS_getErrorByCode(ec);
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
        }
        return false;
    }

    return true;
}

void InputFile::close() {
    assert(PHYSFS_isInit());
    auto* file = reinterpret_cast<PHYSFS_File*>(m_handle);

    if (file && !PHYSFS_close(file)) {
        PHYSFS_ErrorCode ec = PHYSFS_getLastErrorCode();
        std::string msg = "File seeking unsuccessful: ";
        msg += PHYSFS_getErrorByCode(ec);
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
        }
    }

    m_handle = nullptr;
}
}
