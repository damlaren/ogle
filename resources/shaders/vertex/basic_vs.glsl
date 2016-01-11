// Vertex shader that performs basic transforms.

#version 400

in vec3 vertex_position;

uniform mat4 model_matrix, view_matrix, projection_matrix;

void main () {
  gl_Position = projection_matrix * view_matrix * model_matrix * vec4 (vertex_position, 1.0);
}
