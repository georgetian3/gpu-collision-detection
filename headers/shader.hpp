#ifndef SHADER_H
#define SHADER_H

#include <filesystem>
#include <string>
#include <glm/glm.hpp>

enum ShaderType {
    VERTEX,
    FRAGMENT,
    PROGRAM
};

class Shader {

    unsigned int program;
    void checkCompileErrors(unsigned int shader, const ShaderType shaderType) const;
    unsigned int loadShaderSource(const std::string& shaderSource, int type);
    int getUniformLocation(const std::string& name) const;

public:

    Shader();
    Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    void load(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    void use() const;
    void setBool(const std::string& name, const bool value) const;
    void setInt(const std::string& name, const int value) const;
    void setDouble(const std::string& name, const double value) const;
    void setVec3(const std::string& name, const glm::dvec3& value) const;
    void setVec4(const std::string& name, const glm::dvec4& value) const;
    void setMat4(const std::string& name, const glm::dmat4& value) const;
    unsigned int getProgram() const;

};

#endif