#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <vector>

class Model {

    unsigned int VAO, VBO, EBO;
    void setupMesh() {};

public:

    std::vector<glm::dvec3>     vertices;
    std::vector<unsigned int>   indices;
    void draw(const Shader &shader) {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

};

#endif