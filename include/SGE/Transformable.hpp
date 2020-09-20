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

#ifndef SGE_TRANSFORMABLE_HPP
#define SGE_TRANSFORMABLE_HPP

#include <SGE/Export.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace sge {
/**
 * \brief Transformable object
 *
 *
 * This is a base class for objects that can be transformed (moved, rotated, scaled) around an origin.
 */
class SGE_API Transformable {
public:
    /**
     * \brief Create transformable object
     *
     *
     * Creates a transformable object with (0, 0) origin and position and 0 rotation.
     */
    Transformable();

    virtual ~Transformable() = default;

    /**
     * \brief Set origin
     *
     *
     * Sets the origin of the transformable object.
     * \param x X value of origin
     * \param y Y value of origin
     * \param z Z value of origin
     */
    void setOrigin(float x, float y, float z = 0.0f);

    /**
     * \brief Set origin
     *
     *
     * Sets the origin of the transformable object.
     * \param origin Origin position
     */
    void setOrigin(const glm::vec3& origin);

    /**
     * \brief Set position
     *
     *
     * Sets the position of the transformable object.
     * \param x X value of position
     * \param y Y value of position
     * \param z Z value of position
     */
    void setPosition(float x, float y, float z = 0.0f);

    /**
     * \brief Set position
     *
     *
     * Sets the position of the transformable object.
     * \param position New Position
     */
    void setPosition(const glm::vec3& position);

    /**
     * \brief Set scale
     *
     *
     * Sets the scale factors of the transformable object.
     * \param xFactor X scale factor
     * \param yFactor Y scale factor
     * \param zFactor Z scale factor
     */
    void setScale(float xFactor, float yFactor, float zFactor = 1.0f);

    /**
     * \brief Set scale
     *
     *
     * Sets the scale factors of the transformable object.
     * \param factor Scale factor
     */
    void setScale(const glm::vec3& factor);

    /**
     * \brief Set rotation
     * 
     * 
     * Sets the rotation of the transformable object.
     * \param xDeg X axis rotation in degrees
     * \param yDeg Y axis rotation in degrees
     * \param zDeg Z axis rotation in degrees
     */
    void setRotation(float xDeg, float yDeg, float zDeg);

    /**
     * \brief Set rotation
     *
     *
     * Sets the rotation of the transformable object.
     * \param degrees Rotation vector in degrees
     */
    void setRotation(const glm::vec3& degrees);

    /**
     * \brief Move object
     *
     *
     * Move the transformable object.
     * \param x X offset
     * \param y Y offset
     * \param z Z offset
     */
    void move(float x, float y, float z = 0.0f);

    /**
     * \brief Move object
     *
     *
     * Move the transformable object.
     * \param offset Position offset
     */
    void move(const glm::vec3& offset);

    /**
     * \brief Scale object
     *
     *
     * Scales the transformable object.
     * \param xFactor X scale factor
     * \param yFactor Y scale factor
     * \param zFactor Z scale factor
     */
    void scale(float xFactor, float yFactor, float zFactor = 1.0f);

    /**
     * \brief Scale object
     *
     *
     * Scales the transformable object.
     * \param factor Scaling factor
     */
    void scale(const glm::vec3& factor);

    /**
     * \brief Rotate object
     * 
     * 
     * Rotate transformable object.
     * \param xDeg X axis rotation in degrees
     * \param yDeg Y axis rotation in degrees
     * \param zDeg Z axis rotation in degrees
     */
    void rotate(float xDeg, float yDeg, float zDeg);

    /**
     * \brief Rotate object
     *
     *
     * Rotate the transformable object.
     * \param degrees Rotation vector in degrees
     */
    void rotate(const glm::vec3& degrees);

    /**
     * \brief Get origin
     * \return Origin position
     */
    [[nodiscard]] const glm::vec3& getOrigin() const;

    /**
     * \brief Get position
     * \return Object position
     */
    [[nodiscard]] const glm::vec3& getPosition() const;

    /**
     * \brief Get scale
     * \return Object scale factor
     */
    [[nodiscard]] const glm::vec3& getScale() const;

    /**
     * \brief Get rotation
     * \return Object rotation vector in degrees
     */
    [[nodiscard]] glm::vec3 getRotation() const;

    /**
     * \brief Get transform
     *
     *
     * Get the object's transform matrix, updating it if needed.
     * \return The object's transform matrix
     */
    [[nodiscard]] const glm::mat4& getTransform() const;

private:
    glm::vec3 m_origin;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_rotation;
    mutable glm::mat4 m_transform;
    mutable bool m_transformNeedsUpdate;
};
}

#endif//SGE_TRANSFORMABLE_HPP
