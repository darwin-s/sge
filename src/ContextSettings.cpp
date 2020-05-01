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

#include <SGE/ContextSettings.hpp>

namespace sge {
ContextSettings::ContextSettings(bool vsync, int samples, bool debugContext,
                                 bool srgbCapable, int depthBits, int stencilBits,
                                 int redBits, int greenBits, int blueBits, int alphaBits)
    : vsync(vsync), samples(samples), debugContext(debugContext),
      srgbCapable(srgbCapable), depthBits(depthBits),
      stencilBits(stencilBits), redBits(redBits), greenBits(greenBits),
      blueBits(blueBits), alphaBits(alphaBits) {
#ifdef SGE_DEBUG
    debugContext = true;
#endif
}
}
