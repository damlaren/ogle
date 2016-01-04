// Vertex shader that performs basic transforms.

#version 400

in vec3 vertex_position;

uniform mat4 model_matrix;

void main () {
  gl_Position = model_matrix * vec4 (vertex_position, 1.0);
}
