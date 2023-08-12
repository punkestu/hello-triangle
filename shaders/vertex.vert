#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;

uniform float ratio;
uniform vec3 rotation = vec3(0);
uniform vec3 scales;
uniform vec3 transforms = vec3(0);
uniform vec3 camera;

out vec3 fColor;
out vec3 fPos;

mat4 rotateX() {
      float c = cos(rotation.x);
      float s = sin(rotation.x);
      return mat4(
            1, 0, 0, 0,
            0, c,-s, 0,
            0, s, c, 0,
            0, 0, 0, 1
      );
}

mat4 rotateY() {
      float c = cos(rotation.y);
      float s = sin(rotation.y);
      return mat4(
            c, 0, s, 0,
            0, 1, 0, 0,
           -s, 0, c, 0,
            0, 0, 0, 1
      );
}

mat4 rotateZ() {
      float c = cos(rotation.z);
      float s = sin(rotation.z);
      return mat4(
            c, 0,-s, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
      );
}

mat4 rotate() {
      return rotateX() * rotateY() * rotateZ();
}

mat4 scale() 
{
      return mat4(
            scales.x, 0,        0,        0,
            0,        scales.y, 0,        0,
            0,        0,        scales.z, 0,
            0,        0,        0,        1
      );
}

mat4 transform()
{
      return mat4(
            1, 0, 0, transforms.x,
            0, 1, 0, transforms.y,
            0, 0, 1, transforms.z,
            0, 0, 0, 1
      );
}

mat4 projection() {
      float n = -1;
      float f = 1;
      float r = 1;
      float t = 1;
      return mat4(
            n/r, 0, 0, 0,
            0, n/t, 0, 0,
            0, 0, 1, 0,
            0, 0, -1, 0
      );
}

void main() {
      vec4 localPos = vec4(vPos, 1.0) * scale() * rotate() * transform();
      vec4 worldPos = (localPos - vec4(camera, 0)) * projection();
      gl_Position = vec4((worldPos.x * ratio)/worldPos.w, worldPos.y/worldPos.w, worldPos.z, 1.0);
      fColor = vColor;
      fPos = localPos.xyz;
}