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
Rectangle<T>::Rectangle()
    : left(static_cast<T>(0)), top(static_cast<T>(0)), width(static_cast<T>(0)),
      height(static_cast<T>(0)) {
}

template<typename T>
Rectangle<T>::Rectangle(T left, T top, T width, T height)
    : left(left), top(top), width(width), height(height) {
}

template<typename T>
Rectangle<T>::Rectangle(const glm::vec<2, T, glm::defaultp>& position,
                        const glm::vec<2, T, glm::defaultp>& size)
    : left(position.x), top(position.y), width(size.x), height(size.y) {
}

template<typename T>
template<typename U>
Rectangle<T>::Rectangle(const Rectangle<U>& rect)
    : left(static_cast<T>(rect.left)), top(static_cast<T>(rect.top)),
      width(static_cast<T>(rect.width)), height(static_cast<T>(rect.height)) {
}

template<typename T> bool Rectangle<T>::contains(T x, T y) const {
    T minX = std::min(left, left + width);
    T maxX = std::max(left, left + width);
    T minY = std::min(top, top + height);
    T maxY = std::max(top, top + height);

    return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
}

template<typename T>
bool Rectangle<T>::contains(const glm::vec<2, T, glm::defaultp>& point) const {
    return contains(point.x, point.y);
}

template<typename T>
bool Rectangle<T>::intersects(const Rectangle<T>& rect) const {
    T r1MinX = std::min(left, left + width);
    T r1MaxX = std::max(left, left + width);
    T r1MinY = std::min(top, top + height);
    T r1MaxY = std::max(top, top + height);

    T r2MinX = std::min(rect.left, rect.left + rect.width);
    T r2MaxX = std::max(rect.left, rect.left + rect.width);
    T r2MinY = std::min(rect.top, rect.top + rect.height);
    T r2MaxY = std::max(rect.top, rect.top + rect.height);

    T intersLeft   = std::max(r1MinX, r2MinX);
    T intersTop    = std::max(r1MinY, r2MinY);
    T intersRight  = std::min(r1MaxX, r2MaxX);
    T intersBottom = std::min(r1MaxY, r2MaxY);

    return intersLeft < intersRight && intersTop < intersBottom;
}

template<typename T>
Rectangle<T> Rectangle<T>::getIntersection(const Rectangle<T>& rect) const {
    if (!intersects(rect)) {
        return Rectangle<T>(0, 0, 0, 0);
    }

    T r1MinX = std::min(left, left + width);
    T r1MaxX = std::max(left, left + width);
    T r1MinY = std::min(top, top + height);
    T r1MaxY = std::max(top, top + height);

    T r2MinX = std::min(rect.left, rect.left + rect.width);
    T r2MaxX = std::max(rect.left, rect.left + rect.width);
    T r2MinY = std::min(rect.top, rect.top + rect.height);
    T r2MaxY = std::max(rect.top, rect.top + rect.height);

    T intersLeft   = std::max(r1MinX, r2MinX);
    T intersTop    = std::max(r1MinY, r2MinY);
    T intersRight  = std::min(r1MaxX, r2MaxX);
    T intersBottom = std::min(r1MaxY, r2MaxY);

    return Rectangle<T>(intersLeft,
                        intersTop,
                        intersRight - intersLeft,
                        intersBottom - intersTop);
}

template<typename T> glm::vec<2, T, glm::defaultp> Rectangle<T>::getPosition() const {
    return {left, top};
}

template<typename T> glm::vec<2, T, glm::defaultp> Rectangle<T>::getSize() const {
    return {width, height};
}

template<typename T>
bool Rectangle<T>::operator==(const Rectangle<T>& other) const {
    return left == other.left && top == other.top && width == other.width &&
        height == other.height;
}

template<typename T>
bool Rectangle<T>::operator!=(const Rectangle<T>& other) const {
    return !(*this == other);
}
