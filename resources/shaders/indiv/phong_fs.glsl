// Fragment shader that assigns a flat color.

#version 400

uniform vec3 ambient_reflectance, diffuse_reflectance, specular_reflectance;
uniform float specular_exponent;
uniform vec3 light_position;  // World frame.
uniform vec3 light_ambient_color, light_diffuse_color, light_specular_color;

in vec3 position_eye, normal_eye;
out vec4 frag_color;

void main () {
  vec3 Ia = ambient_reflectance * light_ambient_color;
  vec3 I = Ia;
  frag_color = vec4 (I, 1.0);
}
