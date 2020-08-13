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

#ifndef SGE_RESOURCE_HPP
#define SGE_RESOURCE_HPP

#include <SGE/Export.hpp>
#include <filesystem>
#include <string_view>
#include <mutex>
#include <cstdint>//std::uint64_t

namespace sge {
class ResourceManager;

/**
 * \brief Base Class for resources
 *
 *
 * This class must be used for any resources that are to be loaded from files.
 * It is used for resource managing.
 * \note Resources most be default constructible for the Resource Manager to work with them
 */
class SGE_API Resource {
public:
    /**
     * \brief Create new resource
     *
     *
     * Creates a new empty un-initialized resource object.
     */
    Resource();

    virtual ~Resource() = default;

    /**
     * \brief Load resource
     *
     *
     * Loads the resource from a virtual file.
     * \param path Path to the virtual file
     * \return true on success, false otherwise
     */
    virtual bool loadFromFile(const std::filesystem::path& path) = 0;

    /**
     * \brief Load resource
     *
     *
     * Loads the resource for memory
     * \param size Size of data buffer
     * \param data Pointer to buffer containing the data
     * \return true on success, false otherwise
     */
    virtual bool loadFromMemory(std::size_t size, const void* data) = 0;

    /**
     * \brief Get file id
     *
     *
     * Returns the internal id of the file.
     * \return internal id of the file, used for faster resource management
     */
    [[nodiscard]] std::uint64_t getId() const;

    /**
     * \brief Is Resource Ready
     *
     *
     * Returns whether the file was loaded at this point.
     * \note If the resource is not loaded through the ResourceManager, then it is the obligation of the
     * \note resource to set the ready flag.
     * \return true if resource is loaded, false otherwise
     */
    [[nodiscard]] bool isReady() const;

    /**
     * \brief Did Resource Fail
     *
     *
     * Returns whether there was an error loading the resource.
     * \note It is de responsibility of the resource to set this flag.
     * \return true if there was an error, false otherwise
     */
    [[nodiscard]] bool isFailed() const;

protected:

    /**
     * \brief Fail Resource
     *
     *
     * Set the fail state of the resource with a reason to be logged.
     * \param reason Reason of failure
     */
    void fail(std::string_view reason);

    /**
     * \brief Set Ready Flag
     *
     *
     * Sets the ready flag of the resource
     * \param ready State of the ready flag
     */
    void setReady(bool ready);

private:
    friend class ResourceManager;
    std::uint64_t m_id;
    bool m_ready;
    bool m_failed;
    mutable std::mutex m_readyMutex;
    mutable std::mutex m_idMutex;
};
}

#endif//SGE_RESOURCE_HPP
