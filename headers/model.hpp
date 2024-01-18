#ifndef MODEL_HPP
#define MODEL_HPP

#include <glm/glm.hpp>
#include <glad/glad.h> 
#include <vector>
#include <cmath>

class Model {

    unsigned int VAO, VBO, EBO, IBO;

public:

    std::vector<glm::dvec3>     vertices;
    std::vector<unsigned int>   indices;

    unsigned int indicesCount;
    unsigned int instanceCount = 1;

    Model(const std::vector<float>& vertices, std::vector<unsigned int> indices) {
        indicesCount = indices.size();
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &IBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        // set attribute pointers for matrix (4 times vec4)
        glBindBuffer(GL_ARRAY_BUFFER, IBO);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

    }

    ~Model() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &IBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void setModelMatrices(const std::vector<glm::mat4>& modelMatrices) {
        instanceCount = modelMatrices.size();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, IBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instanceCount, modelMatrices.data(), GL_STATIC_DRAW);
    }

    void draw() const {
        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0, instanceCount);
    }

};


const std::vector<float> cubeVertices = {
    // front
    0.0, 0.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 1.0, 1.0,
    0.0, 1.0, 1.0,
    // back
    0.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 1.0, 0.0,
    0.0, 1.0, 0.0
};

const std::vector<unsigned int> cubeIndices = {
    // front
    0, 1, 2,
    2, 3, 0,
    // right
    1, 5, 6,
    6, 2, 1,
    // back
    7, 6, 5,
    5, 4, 7,
    // left
    4, 0, 3,
    3, 7, 4,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // top
    3, 2, 6,
    6, 7, 3
};



std::vector<float> sphereVertices;
std::vector<unsigned int> sphereIndices;

void createSphere() {

    sphereVertices.clear();
    sphereIndices.clear();

    const float PI = acos(-1.0f);
    const double r = 1.0;
    const int sectorCount = 8;
    const int stackCount = 8;

    float x, y, z, phi, theta;

    sphereVertices.push_back(0.0f);
    sphereVertices.push_back(0.0f);
    sphereVertices.push_back(1.0f);

    for (int stack = 1; stack < stackCount; stack++) {
        phi = PI - 2 * PI * stack / stackCount;
        z = r * sin(phi);
        for (int sector = 0; sector < sectorCount; sector++) {
            theta = 2 * PI * sector / sectorCount;
            x = r * cos(phi) * cos(theta);
            y = r * cos(phi) * sin(theta);
            sphereVertices.push_back(x);
            sphereVertices.push_back(y);
            sphereVertices.push_back(z);
        }

    }

    sphereVertices.push_back(0.0f);
    sphereVertices.push_back(0.0f);
    sphereVertices.push_back(-1.0f);

    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0) {
                sphereIndices.push_back(k1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k1 + 1);
            }

            if (i != (stackCount-1)) {
                sphereIndices.push_back(k1 + 1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k2 + 1);
            }
        }
    }



}


#endif