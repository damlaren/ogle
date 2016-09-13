// Vertex shader that performs basic transforms.

#version 400

uniform mat4 model_matrix, view_matrix, projection_matrix;

in layout (location = 0) vec3 vertex_position;
in layout (location = 1) vec3 vertex_normal;

out vec3 position_eye, normal_eye;

void main () {
  position_eye = vec3(view_matrix * model_matrix * vec4(vertex_position, 1.0));
  normal_eye = normalize(vec3(transpose(inverse(view_matrix * model_matrix)) * vec4(vertex_normal, 1.0)));
  gl_Position = projection_matrix * vec4(position_eye, 1.0);
}
