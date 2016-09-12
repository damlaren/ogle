// Fragment shader that assigns a flat color.

#version 400

uniform mat4 view_matrix;
uniform vec3 ambient_reflectance, diffuse_reflectance, specular_reflectance;
uniform float specular_exponent;
uniform vec3 light_position;  // World frame.
uniform vec3 light_ambient_color, light_diffuse_color, light_specular_color;

in vec3 position_eye, normal_eye;
out vec4 frag_color;

void main () {
  // Ambient component.
  vec3 Ia = ambient_reflectance * light_ambient_color;
  
  // Diffuse component.
  vec3 light_position_eye = vec3(view_matrix * vec4(light_position, 1));
  vec3 light_dir_eye = normalize(light_position_eye - position_eye);
  vec3 Id = diffuse_reflectance * light_diffuse_color * max(dot(light_dir_eye, normal_eye), 0);

  frag_color = vec4 (Ia + Id, 1.0);
}
