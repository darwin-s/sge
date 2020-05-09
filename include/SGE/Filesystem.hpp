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
/**
 * \brief Object representing the virtual filesystem
 *
 *
 * This class is used to access the virtual filesystem of a game.
 * The filesystem consists of zip and 7z archives or directories (for debug builds).
 * The respective archives are "mounted" in the filesystem and any overlapping files are
 * overwritten with those from the latest mounted archive. An archive can be mounted as the
 * root of a filesystem ("/") or as any other folder inside it. The virtual directory does not have
 * to exist.
 * \note If the archive extension was not provided, it will be deducted automatically (note that zip archives have more priority than 7z archives).
 * \note Symlinks are not supported for security reasons.
 * Usage example:
 * \code
 * if (!sge::Filesystem::mount("archive", "/")) {
 *     // error mounting...
 * }
 * std::size_t size = sge::Filesystem::getFileSize("file.txt");
 * sge::filesystem::unmount("archive");
 * \endcode
 */
class SGE_API Filesystem {
public:
    /**
     * \brief File type
     *
     *
     * Indicates the type of a file.
     */
    enum class FileType {
        Regular,  ///< Regular file
        Directory,///< Directory
        Other     ///< Other files (device files, etc)
    };

    /**
     * \brief File Exists
     *
     *
     * Searches the virtual filesystem for a file and returns whether it was found.
     * \param path Path to the file
     * \return true if file exists, false otherwise
     */
    [[nodiscard]] static bool exists(const std::filesystem::path& path);

    /**
     * \brief Get File Size
     *
     *
     * Returns the size of a virtual file. If the file does not exist or it is empty 0 is returned.
     * \param path Path to the file
     * \return Size of the file, or 0 if it doesn't exist or it is empty
     */
    [[nodiscard]] static std::size_t getFileSize(const std::filesystem::path& path);

    /**
     * \brief Is File Read-Only
     *
     *
     * Returns whether the file is read-only or not.
     * \param path Path to the file
     * \return true if file is read-only or was not found, false otherwise
     */
    [[nodiscard]] static bool isFileReadOnly(const std::filesystem::path& path);

    /**
     * \brief Get File Type
     *
     *
     * Returns the type of the virtual file.
     * \param path Path to the file
     * \return The type of the file, or FileType::Other if there was a problem
     * \sa Filesystem::FileType
     */
    [[nodiscard]] static FileType getFileType(const std::filesystem::path& path);

    /**
     * \brief Mount archive
     *
     *
     * Mounts an archive into the virtual filesystem. If no extension was provided, then it will be
     * deducted automatically.
     * \note When deducting extension the zip archives have a higher priority than the 7z ones.
     * \param archive The physical archive to be mounted
     * \param mountPoint The point on which to mount the archive in the virtual filesystem
     * \return true on success, false otherwise
     */
    static bool mount(const std::filesystem::path& archive, const std::filesystem::path& mountPoint);

    /**
     * \brief Unmount archive
     *
     *
     * Unmount a archive from the virtual filesystem.
     * \note If the archive was mounted without an extension, then it should be unmounted without one as well
     * \param archive The physical archive to be unmounted
     */
    static void unmount(const std::filesystem::path& archive);
};
}

#endif//SGE_FILESYSTEM_HPP
