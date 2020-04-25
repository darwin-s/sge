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

#include <SGE/SGE.hpp>
#include <string>
#include <gtest/gtest.h>

TEST(Hash, Equality) {
    sge::Hash h1(0x38d1334144987bf4);
    sge::Hash h2("Hello, world!");
    sge::Hash h4(h1);
    auto h5 = sge::Hash(0x38d1334144987bf4);

    EXPECT_EQ(h1, h2);
    EXPECT_EQ(h1, h4);
    EXPECT_EQ(h1, h5);
}

TEST(Hash, Conversion) {
    sge::Hash h1(0x38d1334144987bf4);
    auto h = static_cast<std::uint64_t>(h1);

    EXPECT_EQ(h1, h);
}

TEST(Vector, Arithmetic) {
    sge::Vector2F v1(1.0f, 1.5f);
    sge::Vector2F inv = -v1;
    EXPECT_FLOAT_EQ(inv.x, -1.0f);
    EXPECT_FLOAT_EQ(inv.v, -1.5f);
    sge::Vector2D v2(v1);
    EXPECT_DOUBLE_EQ(v2.u, 1.0);
    EXPECT_DOUBLE_EQ(v2.g, 1.5);
    sge::Vector2F v3 = v1 + inv;
    EXPECT_FLOAT_EQ(v3.r, 0.0f);
    EXPECT_FLOAT_EQ(v3.y, 0.0f);
    sge::Vector2F v4 = v1 - inv;
    EXPECT_FLOAT_EQ(v4.x, 2.0f);
    EXPECT_FLOAT_EQ(v4.y, 3.0f);
    sge::Vector2F v5 = v1 * 3.0f;
    EXPECT_FLOAT_EQ(v5.x, 3.0f);
    EXPECT_FLOAT_EQ(v5.y, 4.5f);
    v1 += inv;
    EXPECT_FLOAT_EQ(v1.x, 0.0f);
    EXPECT_FLOAT_EQ(v1.y, 0.0f);
    v1 -= inv;
    EXPECT_FLOAT_EQ(v1.x, 1.0f);
    EXPECT_FLOAT_EQ(v1.y, 1.5f);
    v1 *= 3.0f;
    EXPECT_FLOAT_EQ(v1.x, 3.0f);
    EXPECT_FLOAT_EQ(v1.y, 4.5f);
}

TEST(Vector, Operations) {
    sge::Vector2I v1(1, 2);
    sge::Vector2I v2(3, 4);
    int dot = sge::Vector2I::dot(v1, v2);
    EXPECT_EQ(dot, 11);
    int mag1 = v1.getMagnitude();
    EXPECT_EQ(mag1, 2);
    sge::Vector2I norm = v1.getNormalized();
    EXPECT_EQ(norm.x, 0);
    EXPECT_EQ(norm.y, 1);
    v1.normalize();
    EXPECT_EQ(v1.x, 0);
    EXPECT_EQ(v1.y, 1);
}