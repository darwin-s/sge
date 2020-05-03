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

#ifndef SGE_FILESYSTEM_HPP
#define SGE_FILESYSTEM_HPP

#include <SGE/Export.hpp>
#include <filesystem>

namespace sge {
class SGE_API Filesystem {
public:
    enum class FileType {
        Regular,
        Directory,
        Other
    };

    [[nodiscard]] static bool exists(const std::filesystem::path& path);
    [[nodiscard]] static std::size_t getFileSize(const std::filesystem::path& path);
    [[nodiscard]] static bool isFileReadOnly(const std::filesystem::path& path);
    [[nodiscard]] static FileType getFileType(const std::filesystem::path& path);
    static bool mount(const std::filesystem::path& archive, const std::filesystem::path& mountPoint);
    static void unmount(const std::filesystem::path& archive);
};
}

#endif //SGE_FILESYSTEM_HPP
