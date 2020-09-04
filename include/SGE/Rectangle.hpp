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

#ifndef SGE_RECTANGLE_HPP
#define SGE_RECTANGLE_HPP

#include <SGE/Export.hpp>
#include <glm/glm.hpp>
#include <algorithm>

namespace sge {
/**
 * \brief Class representing a rectangle
 *
 *
 * This object is used to represent a rectangle with it's origin in int's top left corner.
 * It is used for computations, as it does not hold any other data with it. The rectangles are
 * always axis aligned, because they hold the coordinates of the top-left corner and width and height of the
 * rectangle.
 * \tparam T Underlying type of coordinates
 */
template<typename T> class Rectangle {
public:
    /**
     * \brief Create rectangle
     *
     *
     * Create a rectangle in (0, 0) with 0 width and length.
     */
    Rectangle();

    /**
     * \brief Create rectangle
     *
     *
     * Create a rectangle in a certain position, with a certain size.
     * \param left Left coordinate
     * \param top Top coordinate
     * \param width Width of rectangle
     * \param height Height of rectangle
     */
    Rectangle(T left, T top, T width, T height);

    /**
     * \brief Create rectangle
     *
     *
     * Create a rectangle in a certain position, with a certain size.
     * \param position Rectangle position
     * \param size Rectangle size
     */
    Rectangle(const glm::vec<2, T, glm::defaultp>& position,
              const glm::vec<2, T, glm::defaultp>& size);

    /**
     * \brief Convert rectangle
     *
     *
     * Convert from rectangle containing another type.
     * \tparam U Underlying type of the other rectangle
     * \param rect The rectangle
     */
    template<typename U> explicit Rectangle(const Rectangle<U>& rect);

    /**
     * \brief Rectangle contains point
     * \param x X coordinate of point
     * \param y Y coordinate of point
     * \return true if point is contained, false otherwise
     */
    bool contains(T x, T y) const;

    /**
     * \brief Rectangle contains point
     * \param point Point position
     * \return true if point is contained, false otherwise
     */
    [[nodiscard]]
    bool contains(const glm::vec<2, T, glm::defaultp>& point) const;

    /**
     * \brief Rectangle intersects rectangle
     * \param rect The other rectangle
     * \return true if rectangles intersect, false otherwise
     */
    bool intersects(const Rectangle<T>& rect) const;

    /**
     * \brief Get rectangle intersection
     *
     *
     * Returns the intersection rectangle between two rectangles.
     * \param rect The other rectangle
     * \return Intersection rectangle
     */
    Rectangle<T> getIntersection(const Rectangle<T>& rect) const;

    /**
     * \brief Get position
     * \return Rectangle position
     */
    glm::vec<2, T, glm::defaultp> getPosition() const;

    /**
     * \brief Get size
     * \return Rectangle size
     */
    glm::vec<2, T, glm::defaultp> getSize() const;

    /**
     * \brief Compare rectangles
     *
     *
     * Compares the coordinates of two rectangles.
     * \param other The other rectangle
     * \return true if the coordinates match, false otherwise
     */
    bool operator==(const Rectangle<T>& other) const;

    /**
     * \brief Compare rectangles
     *
     *
     * Compares the coordinates of two rectangles.
     * \param other The other rectangle
     * \return true if the coordinates DO NOT match, false otherwise
     */
    bool operator!=(const Rectangle<T>& other) const;

    T left;  ///< Left coordinate
    T top;   ///< Top coordinate
    T width; ///< Width of rectangle
    T height;///< Height of rectangle
};

#include <SGE/Rectangle.inl>

using RectangleInt   = Rectangle<int>;
using RectangleFloat = Rectangle<float>;
}

#endif//SGE_RECTANGLE_HPP
