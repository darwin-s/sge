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

#ifndef SGE_CONTEXT_HPP
#define SGE_CONTEXT_HPP

#include <SGE/Export.hpp>
#include <SGE/Monitor.hpp>
#include <SGE/ContextSettings.hpp>
#include <string_view>

namespace sge {
class Window;
class Keyboard;
class Mouse;

/**
 * \brief Object representing an OpenGL context
 *
 *
 * This object is used to represent an OpenGL context.
 * It can use custom settings and can be made active on
 * the current thread. It can also be used to quarry the available
 * extensions. All objects are sharing resources with an internal "shared" context.
 * \note Contexts should be created only in the main thread, but they can be made current on other threads.
 * \note To make a context current on another thread, it should not be current on any other thread.
 */
class SGE_API Context {
public:
    /**
     * \brief Create a context
     *
     *
     * Creates an OpenGL context using the settings provided.
     * \note A created OpenGL context is not made current.
     * \note The context settings may not be respected exactly. Check the settings after creating the context.
     * \param settings Settings for the context
     */
    explicit Context(ContextSettings settings = ContextSettings());

    /**
     * \brief Destroy context
     *
     *
     * Destroys the context object and also unbinds it from the current thread if it was active.
     */
    ~Context();
    Context(const Context&) = delete;
    Context(Context&&) noexcept = delete;
    Context& operator=(const Context&) = delete;
    Context& operator=(Context&&) noexcept = delete;

    /**
     * \brief Get context settings
     *
     *
     * Returns the settings that were actually applied to the context on creation.
     * \return Settings actually used in the context
     */
    [[nodiscard]] const ContextSettings& getContextSettings() const;

    /**
     * \brief Activate or deactivate the context
     *
     *
     * Makes the context active on the current thread or deactivates it. If another context was
     * active and this object is trying to be active, then the previous context will be deactivated.
     * \note A context can be active only on one thread
     * \param current Whether to make this context active or deactivate it
     */
    void setCurrent(bool current);

    /**
     * \brief Quarry for OpenGL extension
     *
     *
     * Quarries the context whether the requested OpenGL extension is available.
     * \param extensionName Name of the extension
     * \return true if the extension is supported and available, false otherwise
     */
    [[nodiscard]] bool isExtensionAvailable(std::string_view extensionName) const;

    /**
     * \brief Get the active context on the current thread.
     *
     *
     * Returns the OpenGL context that is currently active on this thread.
     * \warning Do not try to memory-manage the provided pointer (call delete on it)
     * \return Pointer to the context that is active on the current thread, nullptr if there is no active context
     */
    static Context* getCurrentContext();
private:
    friend class Window;
    friend class Keyboard;
    friend class Mouse;
    void SGE_PRIVATE create(int refreshRate, const ContextSettings& settings);
    ContextSettings m_settings;
    void* m_handle;
};
}

#endif //SGE_CONTEXT_HPP
