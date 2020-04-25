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

template<typename T>
Vector2<T>::Vector2()
    : x(static_cast<T>(0)), y(static_cast<T>(0)) {

}

template<typename T>
Vector2<T>::Vector2(T x, T y)
    : x(x), y(y) {

}

template<typename T>
template<typename U>
Vector2<T>::Vector2(const Vector2<U>& vec)
    : x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y)) {

}

template<typename T>
Vector2<T> Vector2<T>::operator-() const {
    return Vector2<T>(-x, -y);
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const {
    return Vector2<T>(x + other.x, y + other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const {
    return Vector2<T>(x - other.x, y - other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T value) const {
    return Vector2<T>(x * value, y * value);
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other) {
    x = x + other.x;
    y = y + other.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other) {
    x = x - other.x;
    y = y - other.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(T value) {
    x = x * value;
    y = y * value;
    return *this;
}

template<typename T>
T Vector2<T>::dot(const Vector2<T>& first, const Vector2<T>& second) {
    return first.x * second.x + first.y * second.y;
}

template<typename T>
T Vector2<T>::getMagnitude() const {
    return static_cast<T>(std::sqrt(x * x + y * y));
}

template<typename T>
void Vector2<T>::normalize() {
    T mag = getMagnitude();
    x /= mag;
    y /= mag;
}

template<typename T>
Vector2<T> Vector2<T>::getNormalized() const {
    T mag = getMagnitude();
    return Vector2<T>(x / mag, y / mag);
}