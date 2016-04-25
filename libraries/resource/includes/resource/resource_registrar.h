/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines ResourceRegistrar.
 */

#ifndef LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_REGISTRAR_H_
#define LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_REGISTRAR_H_

#include "std/ogle_std.inc"
#include "resource/resource.h"

namespace ogle {

/**
 * @brief Registers a Resource type for construction.
 */
class ResourceRegistrar {
 public:
  /**
   * @brief Constructor. Invoke to register loader function.
   * @param type Type of resource to create.
   * @param implementation Resource implementation created by loader.
   * @param loader Factory function to load resource from metadata.
   */
  ResourceRegistrar(const stl_string& type, const stl_string& implementation,
                    Resource::LoadFunction loader);
};

}  // namespace ogle

#endif  // LIBRARIES_RESOURCE_INCLUDES_RESOURCE_RESOURCE_REGISTRAR_H_
