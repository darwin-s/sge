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
#include <SGE/Application.hpp>
#include <SGE/Log.hpp>
#include <filesystem>
#include <cassert>
#include <physfs.h>

namespace sge {
bool Filesystem::exists(const char* path) {
    assert(PHYSFS_isInit());
    return PHYSFS_exists(path) != 0;
}

std::size_t Filesystem::getFileSize(const char* path) {
    assert(PHYSFS_isInit());
    PHYSFS_Stat st;

    if (PHYSFS_stat(path, &st) == 0) {
        try {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "Could not get file size: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;
        } catch (...) {
            Application::crashApplication("Failed string manipulation");
        }

        Application::crashApplication("Failed to get file size");
    }

    return st.filesize;
}

bool Filesystem::isFileReadOnly(const char* path) {
    assert(PHYSFS_isInit());
    PHYSFS_Stat st;

    if (PHYSFS_stat(path, &st) == 0) {
        try {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "Could not find if file is read-only: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;
        } catch (...) {
            Application::crashApplication("Failed string manipulation");
        }

        Application::crashApplication("Failed to get file read-only property");
    }

    return st.readonly != 0;
}

Filesystem::FileType Filesystem::getFileType(const char* path) {
    assert(PHYSFS_isInit());
    PHYSFS_Stat st;

    if (PHYSFS_stat(path, &st) == 0) {
        try {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "Could not get file type: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;
        } catch (...) {
            Application::crashApplication("Failed string manipulation");
        }

        Application::crashApplication("Failed to get file type");
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

bool Filesystem::mount(const char* archive, const char* mountPoint) {
    assert(PHYSFS_isInit());

#ifndef SGE_DEBUG
    if (std::filesystem::is_directory(archive)) {
        return false;
    }
#endif
    try {
        std::filesystem::path realName = archive;

        if (!std::filesystem::exists(realName)) {
            realName.replace_extension(".zip");
            if (!std::filesystem::exists(realName)) {
                realName.replace_extension(".7z");
                if (!std::filesystem::exists(realName)) {
                    Log::general
                        << Log::MessageType::Warning
                        << "File mounting unsuccessful: non-existent archive"
                        << Log::Operation::Endl;
                    return false;
                }
            }
        }

        if (PHYSFS_mount(realName.u8string().c_str(), mountPoint, 0) == 0) {
            try {
                const auto ec   = PHYSFS_getLastErrorCode();
                std::string msg = "File mounting unsuccessful: ";
                msg += PHYSFS_getErrorByCode(ec);

                Log::general << Log::MessageType::Warning << msg.c_str()
                             << Log::Operation::Endl;
            } catch (...) {
                Application::crashApplication("Failed string manipulation");
            }

            return false;
        }
    } catch (...) {
        Application::crashApplication("Failed string manipulation");
    }

    return true;
}

void Filesystem::unmount(const char* archive) {
    assert(PHYSFS_isInit());

#ifndef SGE_DEBUG
    if (std::filesystem::is_directory(archive)) {
        return;
    }
#endif
    try {
        std::filesystem::path realName = archive;

        if (!std::filesystem::exists(realName)) {
            realName.replace_extension(".zip");
            if (!std::filesystem::exists(realName)) {
                realName.replace_extension(".7z");
                if (!std::filesystem::exists(realName)) {
                    Log::general
                        << Log::MessageType::Warning
                        << "File unmounting unsuccessful: non-existent archive"
                        << Log::Operation::Endl;
                    Application::crashApplication("Failed to unmount archive");
                }
            }
        }

        if (PHYSFS_unmount(realName.u8string().c_str()) == 0) {
            const auto ec   = PHYSFS_getLastErrorCode();
            std::string msg = "File unmounting unsuccessful: ";
            msg += PHYSFS_getErrorByCode(ec);

            Log::general << Log::MessageType::Warning << msg.c_str()
                         << Log::Operation::Endl;

            Application::crashApplication("Failed to unmount archive");
        }
    } catch (...) {
        Application::crashApplication("Failed string manipulation");
    }
}
}
