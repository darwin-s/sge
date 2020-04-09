// Copyright 2020 Sirbu Dan
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

#include <sge/hash.hpp>
#include <string>
#include <gtest/gtest.h>

const char* msg = "Hello, world!";

TEST(Hash, Equality)
{
    sge::Hash h1(0x38d1334144987bf4);
    sge::Hash h2("Hello, world!");
    sge::Hash h3((const uint8_t*)msg, 13);

    EXPECT_EQ(h1, h2);
    EXPECT_EQ(h1, h3);
}

TEST(Hash, Conversion)
{
    sge::Hash h1(0x38d1334144987bf4);
    std::uint64_t h = h1;

    EXPECT_EQ(h1, h);
}