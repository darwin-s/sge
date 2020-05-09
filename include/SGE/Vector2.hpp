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

#ifndef SGE_VECTOR2_HPP
#define SGE_VECTOR2_HPP

#include <cmath>

namespace sge {
/**
 * \brief Object used to represent a 2D vector
 *
 *
 * This object is used to represent a 2D vector. It's 2 components
 * can be referred to by different names (x, r or u for the first element and y, g or v for the second one).
 * This class allows basic operations on vectors (addition, subtraction, scalar multiplication, etc.) The
 * most commonly used specializations are already typedeffed:
 * \li typedef Vector2<int> Vector2I;
 * \li typedef Vector2<float> Vector2F;
 * \li typedef Vector2<double> Vector2D;
 * \tparam T Underlying type of components
 *
 * Usage example:
 * \code
 * sge::Vector2F v1(1.4f, 1.2f);
 * sge::Vector2F v2(1.2f, 1.4f);
 * sge::Vector2F res = v1 + v2;
 * \endcode
 */
template<typename T> class Vector2 {
public:
    /**
     * \brief First vector component
     */
    union {
        T x;
        T r;
        T u;
    };

    /**
     * \brief Second vector component
     */
    union {
        T y;
        T g;
        T v;
    };

    /**
     * \brief Default-construct a vector
     *
     *
     * Constructs a vector and set's it's components to 0.
     */
    Vector2();

    /**
     * \brief Construct a vector from 2 separate values
     *
     *
     * Constructs a vectors and sets it's components.
     * \param x First component
     * \param y Second component
     */
    Vector2(T x, T y);

    /**
     * \brief Construct vector from another vector of another type
     *
     *
     * Creates a vector from another type of vector by casting it's components.
     * \tparam U Type of the other vector
     * \param vec The other vector
     */
    template<typename U> explicit Vector2(const Vector2<U>& vec);

    /**
     * \brief Negate vector
     *
     *
     * Negates a vector by flipping the sign on it's components.
     * \return Vector with negated components
     */
    Vector2<T> operator-() const;

    /**
     * \brief Add two vectors
     *
     *
     * Performs the addition operation on two vectors.
     * \param other The second vector
     * \return Vector resulting from addition
     */
    Vector2<T> operator+(const Vector2<T>& other) const;

    /**
     * \brief Subtract two vectors
     *
     *
     * Performs the subtraction operation on two vectors.
     * \param other The second vector
     * \return Vector resulting from subtraction
     */
    Vector2<T> operator-(const Vector2<T>& other) const;

    /**
     * \brief Multiply vector
     *
     *
     * Performs scalar multiplication on the elements of the vector.
     * \param value The scalar multiplier
     * \return Vector resulting from scalar multiplication
     */
    Vector2<T> operator*(T value) const;

    /**
     * \brief Add two vectors
     *
     *
     * Performs the addition operation on two vectors and sets the internal value.
     * \param other The second vector
     * \return *this
     */
    Vector2<T>& operator+=(const Vector2<T>& other);

    /**
     * \brief Subtract two vectors
     *
     *
     * Performs the subtraction operation on two vectors and sets the internal value.
     * \param other The second vector
     * \return *this
     */
    Vector2<T>& operator-=(const Vector2<T>& other);

    /**
     * \brief Multiply vector
     *
     *
     * Performs scalar multiplication on the elements of the vector and sets the internal value.
     * \param value The scalar multiplier
     * \return *this
     */
    Vector2<T>& operator*=(T value);

    /**
     * \brief Dot product of two vectors
     *
     *
     * Calculates the dot product of two vectors of the same type.
     * \param first First vector
     * \param second Second vector
     * \return Dot product of the two vectors
     */
    static T dot(const Vector2<T>& first, const Vector2<T>& second);

    /**
     * \brief Get vector magnitude
     *
     *
     * Returns the magnitude(length) of a vector.
     * \return Magnitude of the vector
     */
    T getMagnitude() const;

    /**
     * \brief Normalize vector
     *
     *
     * Normalize the vector, making all components have a value between 0 and 1.
     */
    void normalize();

    /**
     * \brief Get normalized vector
     *
     * Get the normalized version of the current vector.
     * \return Normalized vector
     */
    Vector2<T> getNormalized() const;
};

#include <SGE/Vector2.inl>

typedef Vector2<int> Vector2I;
typedef Vector2<float> Vector2F;
typedef Vector2<double> Vector2D;
}

#endif//SGE_VECTOR2_HPP
