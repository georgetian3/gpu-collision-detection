R"(

#version 400 core
layout (location = 0) in vec3 aPos;

out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    // FragPos = vec3(model * vec4(aPos, 1.0));
    // gl_Position = projection * view * vec4(FragPos, 1.0);
}

)"