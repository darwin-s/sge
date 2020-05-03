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

#include <SGE/Filesystem.hpp>
#include <SGE/Log.hpp>
#include <string>
#include <cassert>
#include <physfs.h>

namespace sge {
bool Filesystem::exists(const std::filesystem::path& path) {
    assert(PHYSFS_isInit());
    return PHYSFS_exists(path.generic_u8string().c_str()) != 0;
}

std::size_t Filesystem::getFileSize(const std::filesystem::path& path) {
    assert(PHYSFS_isInit());
    PHYSFS_Stat st;

    if (!PHYSFS_stat(path.generic_u8string().c_str(), &st)) {
        return 0;
    }

    return st.filesize;
}

bool Filesystem::isFileReadOnly(const std::filesystem::path& path) {
    assert(PHYSFS_isInit());
    PHYSFS_Stat st;

    if (!PHYSFS_stat(path.generic_u8string().c_str(), &st)) {
        return true;
    }

    return st.readonly != 0;
}

Filesystem::FileType Filesystem::getFileType(const std::filesystem::path& path) {
    assert(PHYSFS_isInit());
    PHYSFS_Stat st;

    if (!PHYSFS_stat(path.generic_u8string().c_str(), &st)) {
        return FileType::Other;
    }

    switch (st.filetype) {
    case PHYSFS_FILETYPE_REGULAR:
        return FileType::Regular;
    case PHYSFS_FILETYPE_DIRECTORY:
        return FileType::Directory;
    case PHYSFS_FILETYPE_OTHER:
    default:
        return FileType::Other;
    }
}

bool Filesystem::mount(const std::filesystem::path& archive, const std::filesystem::path& mountPoint) {
    assert(PHYSFS_isInit());

#ifndef SGE_DEBUG
    if (std::filesystem::is_directory(archive)) {
        return false;
    }
#endif

    std::filesystem::path realname = archive;

    if (!std::filesystem::exists(realname)) {
        realname.replace_extension(".zip");
        if (!std::filesystem::exists(realname)) {
            realname.replace_extension(".7z");
            if (!std::filesystem::exists(realname)) {
                {
                    std::scoped_lock sl(Log::generalMutex);
                    Log::general << Log::MessageType::Warning << "File mounting unsuccessful: non-existent archive" <<
                                 Log::Operation::Endl;
                }
                return false;
            }
        }
    }

    if (!PHYSFS_mount(realname.u8string().c_str(), mountPoint.generic_u8string().c_str(), 0)) {
        PHYSFS_ErrorCode ec = PHYSFS_getLastErrorCode();
        std::string msg = "File mounting unsuccessful: ";
        msg += PHYSFS_getErrorByCode(ec);
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
        }
        return false;
    }

    return true;
}

void Filesystem::unmount(const std::filesystem::path& archive) {
    assert(PHYSFS_isInit());

#ifndef SGE_DEBUG
    if (std::filesystem::is_directory(archive)) {
        return;
    }
#endif

    std::filesystem::path realname = archive;

    if (!std::filesystem::exists(realname)) {
        realname.replace_extension(".zip");
        if (!std::filesystem::exists(realname)) {
            realname.replace_extension(".7z");
            if (!std::filesystem::exists(realname)) {
                {
                    std::scoped_lock sl(Log::generalMutex);
                    Log::general << Log::MessageType::Warning << "File unmounting unsuccessful: non-existent archive" <<
                                 Log::Operation::Endl;
                }
                return;
            }
        }
    }

    if (!PHYSFS_unmount(realname.u8string().c_str())) {
        PHYSFS_ErrorCode ec = PHYSFS_getLastErrorCode();
        std::string msg = "File unmounting unsuccessful: ";
        msg += PHYSFS_getErrorByCode(ec);
        {
            std::scoped_lock sl(Log::generalMutex);
            Log::general << Log::MessageType::Warning << msg << Log::Operation::Endl;
        }
    }
}
}

