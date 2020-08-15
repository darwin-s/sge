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

#ifndef SGE_MATRIX_HPP
#define SGE_MATRIX_HPP

#include <SGE/Export.hpp>

namespace sge {
/**
 * \brief Matrix object
 *
 *
 * This object is used to represent a 3x3 matrix for translation, rotation, scaling, etc.
 * Internally it is transposed so as to make it work with OpenGL.
 * \note The actual data is of a 4x4 matrix, so when giving the matrix data to OpenGL it should be transmitted as a 4x4 matrix.
 */
class SGE_API Matrix {
public:
    static constexpr int matrixSize = 16; ///< Number of elements inside the matrix (4x4 internally)
    static const Matrix identity; ///< Identity matrix

    /**
     * \brief Create matrix
     *
     *
     * Creates an identity matrix.
     */
    Matrix();

    /**
     * \brief Create matrix
     *
     *
     * Creates a matrix with data.
     * \param a00 row 0, column 0 of the matrix
     * \param a01 row 0, column 1 of the matrix
     * \param a02 row 0, column 2 of the matrix
     * \param a10 row 1, column 0 of the matrix
     * \param a11 row 1, column 1 of the matrix
     * \param a12 row 1, column 2 of the matrix
     * \param a20 row 2, column 0 of the matrix
     * \param a21 row 2, column 1 of the matrix
     * \param a22 row 2, column 2 of the matrix
     */
    Matrix(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);


    /**
     * \brief Get matrix data
     *
     *
     * Returns the raw transposed matrix data.
     * \return Pointer to the matrix raw data
     */
    [[nodiscard]] const float* getData() const;


    /**
     * \brief Matrix multiplication
     *
     *
     * Multiplies two matrices and returns the result.
     * \param other The second matrix
     * \return Result of matrix multiplication
     */
    Matrix operator*(const Matrix& other) const;


    /**
     * \brief Matrix multiplication
     *
     *
     * Multiplies two matrices and assigns the result.
     * \param other The second matrix
     * \return *this
     */
    Matrix& operator*=(const Matrix& other);


    /**
     * \brief Matrix comparison
     *
     *
     * Compares two matrices.
     * \param other The second matrix
     * \return true if the matrices are equal, false otherwise
     */
    bool operator==(const Matrix& other) const;

    /**
     * \brief Matrix comparison
     *
     *
     * Compares two matrices.
     * \param other The second matrix
     * \return true if the matrices are NOT equal, false otherwise
     */
    bool operator!=(const Matrix& other) const;

private:
    float m_mat[matrixSize];
};
}

#endif//SGE_MATRIX_HPP