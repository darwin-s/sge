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
#include <SGE/Vector2.hpp>
#include <SGE/Matrix.hpp>

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
     */
    void setOrigin(float x, float y);

    /**
     * \brief Set origin
     *
     *
     * Sets the origin of the transformable object.
     * \param origin Origin position
     */
    void setOrigin(const Vector2F& origin);

    /**
     * \brief Set position
     *
     *
     * Sets the position of the transformable object.
     * \param x X value of position
     * \param y Y value of position
     */
    void setPosition(float x, float y);

    /**
     * \brief Set position
     *
     *
     * Sets the position of the transformable object.
     * \param position New Position
     */
    void setPosition(const Vector2F& position);

    /**
     * \brief Set scale
     *
     *
     * Sets the scale factors of the transformable object.
     * \param xFactor X scale factor
     * \param yFactor Y scale factor
     */
    void setScale(float xFactor, float yFactor);

    /**
     * \brief Set scale
     *
     *
     * Sets the scale factors of the transformable object.
     * \param factor Scale factor
     */
    void setScale(const Vector2F& factor);

    /**
     * \brief Set rotation
     *
     *
     * Sets the rotation of the transformable object.
     * \param degrees Rotation in degrees
     */
    void setRotation(float degrees);

    /**
     * \brief Move object
     *
     *
     * Move the transformable object.
     * \param x X offset
     * \param y Y offset
     */
    void move(float x, float y);

    /**
     * \brief Move object
     *
     *
     * Move the transformable object.
     * \param offset Position offset
     */
    void move(const Vector2F& offset);

    /**
     * \brief Scale object
     *
     *
     * Scales the transformable object.
     * \param xFactor X scale factor
     * \param yFactor Y scale factor
     */
    void scale(float xFactor, float yFactor);

    /**
     * \brief Scale object
     *
     *
     * Scales the transformable object.
     * \param factor Scaling factor
     */
    void scale(const Vector2F& factor);

    /**
     * \brief Rotate object
     *
     *
     * Rotate the transformable object.
     * \param degrees Degrees to rotate
     */
    void rotate(float degrees);

    /**
     * \brief Get origin
     * \return Origin position
     */
    [[nodiscard]] const Vector2F& getOrigin() const;

    /**
     * \brief Get position
     * \return Object position
     */
    [[nodiscard]] const Vector2F& getPosition() const;

    /**
     * \brief Get scale
     * \return Object scale factor
     */
    [[nodiscard]] const Vector2F& getScale() const;

    /**
     * \brief Get rotation
     * \return Object rotation in degrees
     */
    [[nodiscard]] float getRotation() const;

    /**
     * \brief Get transform
     *
     *
     * Get the object's transform matrix, updating it if needed.
     * \return The object's transform matrix
     */
    [[nodiscard]] const Matrix& getTransform() const;

private:
    Vector2F m_origin;
    Vector2F m_position;
    Vector2F m_scale;
    float m_rotation;
    mutable Matrix m_transform;
    mutable bool m_transformNeedsUpdate;
};
}

#endif//SGE_TRANSFORMABLE_HPP