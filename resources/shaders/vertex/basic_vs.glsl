// Vertex shader that performs basic transforms.

#version 400

in vec3 vertex_position;
out vec3 color;

uniform mat4 model_matrix, view_matrix, projection_matrix;

void main () {
  color = vertex_position;  // TODO: Temporary, for debug.
  gl_Position = projection_matrix * view_matrix * model_matrix * vec4 (vertex_position, 1.0);
}
