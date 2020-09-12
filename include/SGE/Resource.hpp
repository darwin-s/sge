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
#include <SGE/Types.hpp>
#include <filesystem>

namespace sge {
class ResourceManager;

/**
 * \brief Base Class for resources
 *
 *
 * This class must be used for any resources that are to be loaded from files.
 * It is used for resource managing.
 */
class SGE_API Resource {
public:
    virtual ~Resource() = default;

    /**
     * \brief Load resource
     *
     *
     * Loads the resource from a virtual file.
     * \param path Path to the virtual file
     * \return true on success, false otherwise
     */
    virtual bool loadFromFile(const char* path) = 0;

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
};
}

#endif//SGE_RESOURCE_HPP
