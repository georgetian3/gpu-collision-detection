R"(
    
#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main() {
    const double brightness = 0.7;
    FragColor = vec4(brightness, brightness, brightness, 1.0);
}

)"