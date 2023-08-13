#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;

uniform float ratio;
uniform vec3 rotation = vec3(0);
uniform vec3 scales;
uniform vec3 transforms = vec3(0);
uniform vec3 camPos;
uniform vec3 camTgt;

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
            c,-s, 0, 0,
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

mat4 view() {
      vec3 vevt = camPos - camTgt;
      vec3 f = vevt/abs(vevt);
      vec3 left = vec3(0,1,0)*f;
      vec3 l = left/abs(left);
      vec3 u = f * l;
      return mat4(
            l.xyz, 0,
            u.xyz, 0,
            f.xyz, 0,
            0, 0, 0, 1
      );
}

mat4 projection() {
      float n = 1;
      float f = 2;
      float e = 1/tan(radians(45/2));
      return mat4(
            -e, 0, 0, 0,
            0, e, 0, 0,
            0, 0, (f+n)/(n-f), (2*f*n)/(n-f),
            0, 0, -1, 0
      );
}

void main() {
      vec4 worldPos = vec4(vPos, 1.0) * scale() * rotate() * transform();
      vec4 projPos = projection()*(worldPos - vec4(camPos,0));
      gl_Position = vec4(projPos.x*ratio,projPos.y, projPos.z, projPos.w)/projPos.w;
      fColor = vColor;
      // gl_Position = vec4(vPos.x*ratio,vPos.yz,1)*scale() *rotate() *transform();
      fPos = worldPos.xyz;
}