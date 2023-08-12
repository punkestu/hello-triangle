#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vColor;

uniform float ratio;
uniform float angle;
uniform vec3 rotateAx;
uniform vec3 camera;

out vec3 fColor;
out vec3 fPos;

mat4 rotateM() {
      if(rotateAx == vec3(0)){
            return mat4(
                  1,0,0,0,
                  0,1,0,0,
                  0,0,1,0,
                  0,0,0,1
            );
      }
      vec3 axis = normalize(rotateAx);
      float c = cos(angle);
      float s = sin(angle);
      float oc = 1-c;
      return mat4(
            oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
            oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
            oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
            0.0,                                0.0,                                0.0,                                1.0
      );
}

mat4 projection() {
      float n = -1;
      float f = 1;
      return mat4(
            n, 0, 0, 0,
            0, n, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
      );
}

void main() {
      vec4 localPos = (rotateM() * vec4(vPos, 1.0));
      vec4 worldPos =  projection() * (localPos - vec4(camera,0));
      gl_Position = vec4(worldPos.x * ratio/ worldPos.z, worldPos.y/ worldPos.z, worldPos.zw);
      fColor = vColor;
      fPos = localPos.xyz;
}