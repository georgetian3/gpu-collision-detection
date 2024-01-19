R"(

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in mat4 aInstanceMatrix;

out vec3 FragPos;
out vec3 Normal;


uniform mat4 projection;
uniform mat4 view;

void main() {
    FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0); 
}

)"