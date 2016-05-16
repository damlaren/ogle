// Vertex shader that converts input vertices
// to vec4 and passes them on.

#version 400

in vec3 vp;

void main () {
  gl_Position = vec4 (vp, 1.0);
}
