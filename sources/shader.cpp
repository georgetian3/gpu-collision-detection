#include <shader.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glad/glad.h>

Shader::Shader() {

}

unsigned int Shader::loadShaderSource(const std::string& shaderSource, int type) {
    // std::cout << "Loading shader (type " << type << "):\n" << shaderSource << '\n';
    auto ptr = shaderSource.c_str();
    unsigned int shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &ptr, nullptr);
    glCompileShader(shaderId);
    checkCompileErrors(shaderId, VERTEX);
    return shaderId;
}


Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    load(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader() {
    glDeleteProgram(shaderId);
}

void Shader::load(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    auto vertexShader = loadShaderSource(vertexShaderSource, GL_VERTEX_SHADER);
    auto fragmentShader = loadShaderSource(fragmentShaderSource, GL_FRAGMENT_SHADER);
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    checkCompileErrors(program, PROGRAM);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int Shader::getProgram() const {
    return program;
}

void Shader::use() const { 
    glUseProgram(program); 
}

int Shader::getUniformLocation(const std::string& name) const {
    int location = glGetUniformLocation(program, name.c_str());
    if (location == -1) {
        std::cerr << "Cannot get uniform location: " << name << '\n';
        exit(1);
    }
    return location;
}

void Shader::setBool(const std::string& name, const bool value) const {
    glProgramUniform1i(program, getUniformLocation(name), (int)value); 
}
void Shader::setInt(const std::string& name, const int value) const {
    glProgramUniform1i(program, getUniformLocation(name), value); 
}
void Shader::setDouble(const std::string& name, const double value) const {
    glProgramUniform1f(program, getUniformLocation(name), static_cast<float>(value)); 
}
void Shader::setVec3(const std::string& name, const glm::dvec3& value) const {
    glProgramUniform3fv(program, getUniformLocation(name), 1, &glm::vec3(value)[0]); 
}
void Shader::setVec4(const std::string& name, const glm::dvec4& value) const {
    glProgramUniform4fv(program, getUniformLocation(name), 1, &glm::vec4(value)[0]); 
}
void Shader::setMat4(const std::string& name, const glm::dmat4& value) const {
    glProgramUniformMatrix4fv(program, getUniformLocation(name), 1, GL_FALSE, &glm::mat4(value)[0][0]);
}

void Shader::checkCompileErrors(unsigned int shader, const ShaderType type) const {
    int success;
    char log[1024];
    if (type != PROGRAM) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, log);
            std::cerr << "Shader compilation error: " << log << '\n';
            exit(1);
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, log);
            std::cerr << "Shader linking error: " << log << '\n';
            exit(1);
        }
    }
}