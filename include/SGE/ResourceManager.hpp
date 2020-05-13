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

#ifndef SGE_RESOURCEMANAGER_HPP
#define SGE_RESOURCEMANAGER_HPP

#include <SGE/Export.hpp>
#include <SGE/Resource.hpp>
#include <SGE/Hash.hpp>
#include <unordered_map>
#include <memory>
#include <thread>
#include <type_traits>

namespace sge {

/**
 * \brief Resource manager class
 *
 *
 * This class is used for managing resources in the engine. It does not load the same
 * resource two times and loads a resource if it is not yet available. Resource objects
 * must be default constructible and derived from sge::Resource.
 * Usage example:
 * \code
 * auto r = sge::ResourceManager::instance().getResource("res.txt");
 * // use resource...
 * \endcode
 * \sa sge::Resource
 */
class SGE_API ResourceManager {
public:
    /**
     * \brief Get Instance
     *
     *
     * Returns the instance of the resource manager class.
     * \return Resource manager instance
     */
    static ResourceManager& instance();

    /**
     * \brief Get Resource
     *
     *
     * Returns a resource by either loading it, or returning the existing one.
     * \note The resource type must by default constructible and derived from sge::resource
     * \tparam T Resource type
     * \param path Path to the virtual file of the resource
     * \return Shared pointer to the resource
     */
    template<typename T>
    std::shared_ptr<T> getResource(const std::filesystem::path& path);

    /**
     * \brief Get Resource
     *
     *
     * Returns a resource by it's id if it already exists.
     * \note The resource type must by default constructible and derived from sge::resource
     * \tparam T Resource type
     * \param id id of the resource
     * \return Shared pointer to the resource, ot nullptr if it doesn't exist
     */
    template<typename T>
    std::shared_ptr<T> getResource(std::uint64_t id);
private:
    ResourceManager() = default;
    void loadResource(std::shared_ptr<Resource> r, const std::filesystem::path& path, std::uint64_t hash);
    std::unordered_map<std::uint64_t, std::weak_ptr<Resource>> m_map;
};

#include <SGE/ResourceManager.inl>
}

#endif//SGE_RESOURCEMANAGER_HPP
