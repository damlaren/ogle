/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implements MeshGraph.
 */

#include "geometry/mesh_graph.h"
#include "easylogging++.h"
#include "geometry/mesh_attributes.h"

namespace ogle {

const bool operator<(const MeshGraph::MeshVertex& lhs,
                     const MeshGraph::MeshVertex& rhs) {
  if (lhs.vertex < rhs.vertex) {
    return true;
  } else if (lhs.vertex > rhs.vertex) {
    return false;
  }

  if (lhs.uv < rhs.uv) {
    return true;
  } else if (lhs.uv > rhs.uv) {
    return false;
  }

  if (lhs.vertex_normal < rhs.vertex_normal) {
    return true;
  } else {
    return false;
  }
}

bool MeshGraph::Load(const MeshAttributes *mesh_data) {
  if (!mesh_data) {
    LOG(ERROR) << "Cannot create MeshGraph from null attributes.";
    return false;
  }



  return true;
}

}  // namespace ogle
