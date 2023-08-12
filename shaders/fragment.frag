#version 330 core
in vec3 fColor;
in vec3 fPos;
out vec4 color;
void main() { 
      vec3 lightDirection = vec3(
            0,1,-2
      );
      float intensity = clamp(dot(fPos, lightDirection),0.1,1);
      color = vec4(fColor.xyz * intensity, 1.0);
}