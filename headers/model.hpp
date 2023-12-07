// #ifndef MODEL_H
// #define MODEL_H

// #include <glad/glad.h> 

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// #include <camera.hpp>
// #include <hittable.hpp>
// #include <shader.hpp>

// #include <filesystem>
// #include <string>
// #include <fstream>
// #include <sstream>
// #include <iostream>
// #include <map>
// #include <vector>

// #include <texture.hpp>
// #include <utils.hpp>
// #include <limits>

// #define MAX_BONE_INFLUENCE 4

// struct Vertex {
//     glm::vec3 Position;
//     glm::vec3 Normal;
//     glm::vec2 TexCoords;
//     glm::vec3 Tangent;
//     glm::vec3 Bitangent;
// 	int m_BoneIDs[MAX_BONE_INFLUENCE];
// 	double m_Weights[MAX_BONE_INFLUENCE];
// };

// enum SurfaceProperty {
//     SP_NONE,
//     SP_REFLECTIVE,
//     SP_REFRACTIVE
// };

// class Mesh: public Hittable {

//     unsigned int VBO, EBO;
//     void setupMesh();

// public:

//     std::vector<Vertex>         vertices;
//     std::vector<unsigned int>   indices;
//     std::vector<Texture>        textures;
//     unsigned int VAO;
//     void setPosition(const glm::dvec3& position);
//     Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
//     void draw(const Shader &shader);
//     std::vector<HitRecord> directlyHits(const Hittable& other) const;

// };

// class Model: public Hittable {

//     static unsigned int idCount;

//     unsigned int id;

//     glm::dvec3 minPos = glm::dvec3(std::numeric_limits<double>::infinity());
//     glm::dvec3 maxPos = glm::dvec3(-std::numeric_limits<double>::infinity());

//     void processNode(aiNode *node, const aiScene *scene);
//     Mesh processMesh(aiMesh *mesh, const aiScene *scene);
//     std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type);
    


//     std::vector<Texture> texturesLoaded;
//     std::vector<Mesh>    meshes;
//     std::filesystem::path directory;

//     glm::dvec4 color = glm::dvec4(1.0);


//     void setId();

//     GLuint framebuffer, depthRenderbuffer;
// 	int cubemapSize = 1024;

// public:

//     bool useColor = false;

//     int surfaceProperty = SP_NONE;
//     double refractiveIndex = 1.5;

//     void setPosition(const glm::dvec3& position);
//     std::vector<HitRecord> directlyHits(const Hittable& other) const;

// 	GLuint cubeTexture;
//     unsigned int getId() const;

//     std::string name;


//     void setUseColor(bool useColor) {
//         this->useColor = useColor;
//     }

//     void setColor(glm::dvec4 color) {
//         this->color = color;
//     }

//     void load(const std::filesystem::path& path);
//     void draw(const Shader& shader, Camera& camera);

//     glm::dvec3 midpoint() const {
//         return (getMinAABB() + getMaxAABB()) * 0.5 + getPosition();
//     }

// };


// #endif
