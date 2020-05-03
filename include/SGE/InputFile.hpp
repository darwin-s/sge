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
#include <filesystem>

namespace sge {
class SGE_API InputFile {
public:
    static constexpr std::size_t defaultBufferSize = 65536;
    explicit InputFile();
    explicit InputFile(const std::filesystem::path& path, std::size_t bufferSize = defaultBufferSize);
    InputFile(InputFile&& other) noexcept;
    InputFile(const InputFile&) = delete;
    ~InputFile();
    InputFile& operator=(InputFile&& other) noexcept;
    InputFile& operator=(const InputFile&) = delete;
    bool open(const std::filesystem::path& path, std::size_t bufferSize = defaultBufferSize);
    [[nodiscard]] bool isOpen() const;
    ByteData read(std::size_t bytes);
    [[nodiscard]] bool eof() const;
    [[nodiscard]] std::size_t tell() const;
    [[nodiscard]] bool seekg(std::size_t seekPosition);
    void close();
private:
    void* m_handle;
};
}

#endif //SGE_INPUTFILE_HPP
