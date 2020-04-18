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

#ifndef SGE_APPLICATION_HPP
#define SGE_APPLICATION_HPP

#include <SGE/Export.hpp>
#include <string>
#include <list>

namespace sge {
class SGE_API Application {
public:
    Application(int argc, char** argv);
    virtual ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    std::list<std::string> getArgs() const;
private:
    int m_argc;
    char** m_argv;
};
}

#endif //SGE_APPLICATION_HPP
