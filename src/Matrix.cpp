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

#include <SGE/Matrix.hpp>

namespace sge {
const Matrix Matrix::identity;

Matrix::Matrix() : m_mat{1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f} {
    
}

Matrix::Matrix(const float a00, const float a01, const float a02, 
               const float a10, const float a11, const float a12, 
               const float a20, const float a21, const float a22)
                   : m_mat{a00,  a10,  0.0f, a20,
                           a01,  a11,  0.0f, a21,
                           0.0f, 0.0f, 1.0f, 0.0f,
                           a02,  a12,  0.0f, a22} {
    
}

const float* Matrix::getData() const {
    return static_cast<const float*>(m_mat);
}

Matrix Matrix::operator*(const Matrix& other) const{
    const auto* a = static_cast<const float*>(m_mat);
    const auto* b = static_cast<const float*>(other.m_mat);

    return Matrix(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                  a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                  a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                  a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                  a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                  a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                  a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                  a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                  a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);
}

Matrix& Matrix::operator*=(const Matrix& other) {
    const auto* a = static_cast<const float*>(m_mat);
    const auto* b = static_cast<const float*>(other.m_mat);

    *this = Matrix(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                   a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                   a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                   a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                   a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                   a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                   a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                   a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                   a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);

    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    const auto* a = static_cast<const float*>(m_mat);
    const auto* b = static_cast<const float*>(other.m_mat);

    return ((a[0]  == b[0])  && (a[1]  == b[1])  && (a[3]  == b[3]) &&
            (a[4]  == b[4])  && (a[5]  == b[5])  && (a[7]  == b[7]) &&
            (a[12] == b[12]) && (a[13] == b[13]) && (a[15] == b[15]));
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}
}