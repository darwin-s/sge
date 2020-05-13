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

template<typename T> std::shared_ptr<T> ResourceManager::getResource(const std::filesystem::path& path) {
    static_assert(std::is_base_of_v<Resource, T>, "Type must be derived from sge::Resource!");
    static_assert(std::is_default_constructible_v<T>, "Resource type must be default constructible!");
    uint64_t hash = static_cast<std::uint64_t>(Hash(path.generic_u8string()));
    auto it = m_map.find(hash);

    if (it != m_map.end()) {
        if (!it->second.expired()) {
            return std::static_pointer_cast<T>(it->second.lock());
        } else {
            std::shared_ptr<T> r = std::make_shared<T>();
            loadResource(std::static_pointer_cast<Resource>(r), path, hash);
            it->second = std::static_pointer_cast<Resource>(r);
            return r;
        }
    } else {
        std::shared_ptr<T> r = std::make_shared<T>();
        loadResource(std::static_pointer_cast<Resource>(r), path, hash);
        m_map.insert({hash, std::static_pointer_cast<Resource>(r)});
        return r;
    }
}

template<typename T> std::shared_ptr<T> ResourceManager::getResource(std::uint64_t id) {
    static_assert(std::is_base_of_v<Resource, T>, "Type must be derived from sge::Resource!");
    static_assert(std::is_default_constructible_v<T>, "Resource type must be default constructible!");
    auto it = m_map.find(id);

    if (it != m_map.end()) {
        if (!it->second.expired()) {
            return std::static_pointer_cast<T>(it->second.lock());
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}