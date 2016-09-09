#version 130

uniform vec3 camera_position;
uniform vec3 camera_eye;
uniform vec3 camera_up;

out vec3 out_vertex;
out vec3 normal;

void main() {

  // temporare uniforms
  float maxRange = 50;
  float im_height = 1000;

  // orthogonal distance;
  vec3 pos3d = (gl_ModelViewMatrix * gl_Vertex).xyz;

  // define the eco intensity
  normal = gl_NormalMatrix * gl_Normal;

  // compute distance object to camera center point (0,0,0)
  vec3 pos2 = vec3(pos3d.x * pos3d.x, pos3d.y * pos3d.y, pos3d.z * pos3d.z);
  float distance3d = sqrt( pos2.x + pos2.y + pos2.z );

  // compute angles between XZ and XY
  float distance2d_XZ = sqrt( pos2.x + pos2.z );
  float distance2d_YZ = sqrt( pos2.y + pos2.z );

  vec2 angles = vec2( acos( pos2.z/ (abs(pos3d.z) * distance2d_XZ )),
                      acos( pos2.z/ (abs(pos3d.z) * distance2d_YZ )) );

  // polar to cartesian points
  //float distance_relative = distance3d * im_height / maxRange;
  float distance_relative = distance3d / maxRange;
  vec2 pos_sonar = vec2( sin(angles.x), cos(angles.y)) * distance_relative;


  out_vertex =  vec3( pos_sonar.x + camera_position.x,
                      pos_sonar.y + camera_position.y,
                      0 + camera_position.z);

  //vec2 temp_pos = (gl_ModelViewMatrix * pos_sonar).xy;
  //gl_Position = gl_ProjectionMatrix * vec4(pos_sonar, 1.0);


  //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
  //gl_Position = gl_ModelViewMatrix * vec4(out_vertex, 1.0);
  gl_Position = gl_ModelMatrix * vec4(out_vertex, 1.0);

}
