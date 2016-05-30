/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Defines Entity.
 */

#ifndef OGLE_INCLUDES_ENTITY_COMPONENT_H_
#define OGLE_INCLUDES_ENTITY_COMPONENT_H_

#include "std/ogle_std.inc"

namespace ogle {

class Entity;

/**
 * @brief An object that can be attached to an Entity.
 *
 * It is owned by its Entity.
 */
class Component {
 public:
  /// Destructor. Allows inheritance.
  virtual ~Component() = default;

  /// Returns owning Entity.
  Entity* entity() const;

 private:
  /// Entity this Component is attached to.
  Entity* entity_;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_ENTITY_COMPONENT_H_
