#version 330 core
in vec3 fColor;
in vec3 fPos;
out vec4 color;
void main() { 
      vec3 lightDirection = vec3(
            0,2,1
      );
      float intensity = clamp(dot(fPos, lightDirection),0.1,1);
      if(fColor == vec3(0)){
            color = vec4(vec3(1)*intensity,1);
      }else{
            color = vec4(fColor, 1.0);
      }
}