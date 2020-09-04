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

#ifndef SGE_SHADER_HPP
#define SGE_SHADER_HPP

#include <SGE/Export.hpp>
#include <glm/mat4x4.hpp>
#include <filesystem>
#include <string_view>
#include <string>
#include <unordered_map>

namespace sge {
/**
 * \brief Object representing a shader program
 *
 *
 * This object is used to represent an OpenGL shader program used for drawing.
 * The shaders are assumed to have a "main()" entry point.
 * \note This object does not work with GLSL shaders, it only loads SPIR-V binaries
 * Usage example:
 * \code
 * sge::Shader s;
 * s.load("shader.vert", sge::Shader::Vertex);
 * s.load("shader.frag", sge::Shader::Fragment);
 * s.use();
 * //...draw
 * \endcode
 */
class SGE_API Shader {
public:
    /**
     * \brief Shader type
     *
     * The supported types for shaders.
     */
    enum Type {
        Vertex, ///< Vertex Shader
        Fragment///< Fragment Shader
    };

    /**
     * \brief Construct shader
     *
     *
     * Creates an empty shader program.
     */
    Shader();

    /**
     * \brief Create shader
     *
     *
     * Move-constructs a shader object.
     * \param other The other shader object
     */
    Shader(Shader&& other) noexcept;

    /**
     * \brief Destroy shader
     *
     *
     * Deletes the shader program
     */
    ~Shader();

    /**
     * \brief Move-assign shader
     *
     *
     * Move-assigns the shader object
     * \param other The other shader
     * \return *this
     */
    Shader& operator=(Shader&& other) noexcept;

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    /**
     * \brief Load shader
     *
     *
     * Load a shader binary in SPIR-V format from a virtual file.
     * \param file Path to the virtual file
     * \param type Shader type
     * \return true on success, false otherwise
     */
    [[nodiscard]] bool load(const std::filesystem::path& file, Type type) const;

    /**
     * \brief Load shader
     *
     *
     * Load a shader binary in SPIR-V format from memory
     * \param size Size of shader in memory
     * \param data Pointer to shader binary data
     * \param type Shader type
     * \return true on success, false otherwise
     */
    [[nodiscard]] bool
    load(std::size_t size, const void* data, Type type) const;

    /**
     * \brief Link shader program
     *
     *
     * Link shader program after loading all the shaders.
     * \return true on success, false otherwise
     */
    [[nodiscard]] bool link();

    /**
     * \brief Use shader program
     *
     *
     * Use this shader program to draw geometry.
     */
    void use() const;

    /**
     * \brief Shader has uniform
     *
     *
     * Returns whether the shader contains a uniform,
     * \param name Uniform name
     * \return true if shader contains uniform, false otherwise
     */
    [[nodiscard]] bool hasUniform(std::string_view name);

    /**
     * \brief Set shader uniform
     *
     *
     * Sets a matrix shader uniform.
     * \param name Name of the uniform
     * \param mat Matrix to assign
     */
    void setUniform(std::string_view name, const glm::mat4& mat);

private:
    unsigned int m_id;
    std::unordered_map<std::string, int> m_uniforms;
};
}

#endif//SGE_SHADER_HPP
