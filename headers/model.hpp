#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <vector>

std::vector<float> cubeVertices = {
    // // front
    // -1.0, -1.0,  1.0,
    // 1.0, -1.0,  1.0,
    // 1.0,  1.0,  1.0,
    // -1.0,  1.0,  1.0,
    // // back
    // -1.0, -1.0, -1.0,
    // 1.0, -1.0, -1.0,
    // 1.0,  1.0, -1.0,
    // -1.0,  1.0, -1.0

     0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
};

std::vector<unsigned int> cubeIndices = {
    // // front
    // 0, 1, 2,
    // 2, 3, 0,
    // // right
    // 1, 5, 6,
    // 6, 2, 1,
    // // back
    // 7, 6, 5,
    // 5, 4, 7,
    // // left
    // 4, 0, 3,
    // 3, 7, 4,
    // // bottom
    // 4, 5, 1,
    // 1, 0, 4,
    // // top
    // 3, 2, 6,
    // 6, 7, 3

    0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
};

class Model {

    unsigned int VAO, VBO, EBO;
    void setupMesh() {};

public:

    std::vector<glm::dvec3>     vertices;
    std::vector<unsigned int>   indices;

    Model(std::vector<float> vertices, std::vector<unsigned int> indices) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    ~Model() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void draw() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    }

};


#endif