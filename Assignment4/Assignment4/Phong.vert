
#version 150 core

in vec3 position;
const vec3 inColor = vec3(0.f,0.7f,0.f);
in vec3 inNormal;
in vec2 inUVs;
const vec3 inlightDir = normalize(vec3(1,0,0));
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 Color;
out vec3 normal;
out vec3 pos;
out vec3 eyePos;
out vec3 lightDir;
out vec2 uvs;

void main() {
   Color = inColor;
   vec4 pos4 = view * model * vec4(position,1.0);
   vec4 norm4 = transpose(inverse(view*model)) * vec4(inNormal,0.0);
   normal = norm4.xyz;
   lightDir = (view * vec4(inlightDir,0)).xyz;  //Transform light into to view space
   gl_Position = proj * pos4;
};