// #include <glad/glad.h> 

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtx/string_cast.hpp>
// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// #include <shader.hpp>

// #include <string>
// #include <fstream>
// #include <sstream>
// #include <iostream>
// #include <map>
// #include <vector>

// #include <texture.hpp>

// #include <model.hpp>

// #include <utils.hpp>

// unsigned int Model::idCount = 0;


// const double yaws[6] = {180, 0, 90, 90, 90, -90};
// const double pitches[6] = {0, 0, -90, 90, 0, 0};

// Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
//     this->vertices = vertices;
//     this->indices = indices;
//     this->textures = textures;

//     if (indices.size() % 3 != 0) {
//         std::cerr << "Indices size not divisible by 3\n";
//         exit(1);
//     }

//     for (const Vertex& v: vertices) {
//         updateAABB(v.Position);
//     }

//     setupMesh();
// }

// void Mesh::draw(const Shader &shader) {
//     for (size_t i = 0; i < textures.size(); i++) {
//         glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + i)); // active proper texture unit before binding
//         if (textures[i].getType() == aiTextureType_DIFFUSE) {
//             shader.setInt("material.diffuse", i);
//         } else if (textures[i].getType() == aiTextureType_SPECULAR) {
//             shader.setInt("material.specular", i);
//         } else {
//             std::cout << "Unhandled texture type: " << textures[i].getType() << '\n';
//         }
//         glBindTexture(GL_TEXTURE_2D, textures[i].getId());
//     }
    
//     // draw mesh
//     glBindVertexArray(VAO);
//     glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);

//     glBindVertexArray(0);
//     glActiveTexture(GL_TEXTURE0);
// }


// void Mesh::setupMesh() {
//     glGenVertexArrays(1, &VAO);
//     glGenBuffers(1, &VBO);
//     glGenBuffers(1, &EBO);

//     glBindVertexArray(VAO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

//     glEnableVertexAttribArray(0);	
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//     glEnableVertexAttribArray(1);	
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//     glEnableVertexAttribArray(2);	
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//     glEnableVertexAttribArray(3);
//     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
//     glEnableVertexAttribArray(4);
//     glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
//     glEnableVertexAttribArray(5);
//     glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

//     glEnableVertexAttribArray(6);
//     glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
//     glBindVertexArray(0);
// }

// void Mesh::setPosition(const glm::dvec3& position) {
//     this->position = position;
// }

// unsigned int Model::getId() const {
//     return id;
// }

// void Model::setId() {
//     id = idCount++;
// }

// void Model::draw(const Shader& shader, Camera& camera) {
//     shader.setBool("reflective", surfaceProperty == SP_REFLECTIVE);
//     shader.setBool("refractive", surfaceProperty == SP_REFRACTIVE);
//     shader.setDouble("refractiveIndex", refractiveIndex);
//     shader.setBool("useColor", useColor);
//     shader.setVec4("color", color);
//     shader.setVec3("viewPos", camera.getPosition());
//     shader.setMat4("model", getModelMat());
//     shader.setMat4("view", camera.getView());
//     shader.setMat4("projection", camera.getProjection());
//     shader.use();
//     for (auto& mesh: meshes) {
//         mesh.draw(shader);
//     }
// }

    
// void Model::load(const std::filesystem::path& path) {

//     setId();


//     glGenFramebuffers(1, &framebuffer);
//     glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

//     glGenTextures(1, &cubeTexture);
//     glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
//     for (GLuint i = 0; i < 6; i++) {
//         glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, cubemapSize, cubemapSize, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//     }
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//     for (int i = 0; i < 6; i++) {
//         glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubeTexture, 0);
//     }

//     glGenRenderbuffers(1, &depthRenderbuffer);
//     glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
//     glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, cubemapSize, cubemapSize);
//     glBindRenderbuffer(GL_RENDERBUFFER, 0);
//     glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);

//     if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//         std::cerr << "Dynamic cubemap framebuffer not complete!" << std::endl;
//         exit(1);
//     }
//     glBindFramebuffer(GL_FRAMEBUFFER, 0);


//     Assimp::Importer importer;
//     const aiScene* scene = importer.ReadFile(path.string(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_SplitLargeMeshes);
//     if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
//         std::cerr << "ASSIMP cannot load model: " << importer.GetErrorString() << '\n';
//         exit(1);
//     }
//     directory = path.parent_path();
//     processNode(scene->mRootNode, scene);
// }

// void Model::processNode(aiNode *node, const aiScene *scene) {
//     for (unsigned int i = 0; i < node->mNumMeshes; i++) {
//         aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//         meshes.push_back(processMesh(mesh, scene));
//         updateAABB(meshes.back());
//     }
//     for (unsigned int i = 0; i < node->mNumChildren; i++) {
//         processNode(node->mChildren[i], scene);
//     }

// }

// Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
//     std::vector<Vertex> vertices;
//     std::vector<unsigned int> indices;
//     std::vector<Texture> textures;
//     for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//         Vertex vertex;
//         glm::dvec3 vector;
//         vector.x = mesh->mVertices[i].x;
//         vector.y = mesh->mVertices[i].y;
//         vector.z = mesh->mVertices[i].z;
//         vertex.Position = vector;

//         if (mesh->HasNormals()) {
//             vector.x = mesh->mNormals[i].x;
//             vector.y = mesh->mNormals[i].y;
//             vector.z = mesh->mNormals[i].z;
//             vertex.Normal = vector;
//         }
//         if (mesh->mTextureCoords[0]) {
//             glm::dvec2 vec;

//             vec.x = mesh->mTextureCoords[0][i].x; 
//             vec.y = mesh->mTextureCoords[0][i].y;
//             vertex.TexCoords = vec;
//             vector.x = mesh->mTangents[i].x;
//             vector.y = mesh->mTangents[i].y;
//             vector.z = mesh->mTangents[i].z;
//             vertex.Tangent = vector;

//             vector.x = mesh->mBitangents[i].x;
//             vector.y = mesh->mBitangents[i].y;
//             vector.z = mesh->mBitangents[i].z;
//             vertex.Bitangent = vector;
//         }  else {
//             vertex.TexCoords = glm::dvec2(0.0, 0.0);
//         }
//         vertices.push_back(vertex);
//     }
//     for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
//         aiFace face = mesh->mFaces[i];
//         for(unsigned int j = 0; j < face.mNumIndices; j++)
//             indices.push_back(face.mIndices[j]);        
//     }
//     aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];    

//     std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
//     textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//     std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
//     textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

//     return Mesh(vertices, indices, textures);
// }

// std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type) {
//     std::vector<Texture> textures;
//     for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
//         aiString str;
//         mat->GetTexture(type, i, &str);
//         std::filesystem::path texturePath = directory / std::filesystem::path(str.C_Str());
//         bool skip = false;
//         for (const auto& texture: texturesLoaded) {
//             if (texture.getPath() == texturePath) {
//                 textures.push_back(texture);
//                 skip = true;
//                 break;
//             }
//         }
//         if (!skip) {
//             Texture texture;
//             texture.load(texturePath);
//             texture.setType(type);
//             textures.push_back(texture);
//             texturesLoaded.push_back(texture);
//         }
//     }
//     return textures;
// }


// double avg(double a, double b) {
//     return (a + b) / 2;
// }

// void Model::updateCubemap(const Shader& modelShader, const Skybox& skybox, Model& targetModel, std::vector<Model>& models, int width, int height) {
//     if (targetModel.getSurfaceProperty() == SP_NONE) {
//         return;
//     }
//     glViewport(0, 0, cubemapSize, cubemapSize); // Set size of the viewport as size of cube map

//     Camera camera;
//     camera.setPosition(targetModel.midpoint());

//     glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

//     for (GLuint face = 0; face < 6; face++) {
//         glDrawBuffer(GL_COLOR_ATTACHMENT0 + face);
//         glClear(GL_DEPTH_BUFFER_BIT);

//         camera.setYaw(yaws[face]);
//         camera.setPitch(pitches[face]);

//         camera.setZoom(90.0);
//         camera.setAspectRatio(1.0);
//         glViewport(0, 0, cubemapSize, cubemapSize); // Set size of the viewport as size of cube map

//         skybox.draw(camera);

//         // camera.setZoom(45.0);
//         // camera.setAspectRatio((double)width / (double)height);
//         // glViewport(0, 0, width, height);


//         for (auto& model: models) {
//             if (model.getId() != targetModel.getId()) {
//                 model.draw(modelShader, camera);
//             }
//         }
//     }

//     // modelShader.setInt("cubemap", cubeTexture);

//     glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind FBO, set default framebuffer
//     glActiveTexture(GL_TEXTURE0);
//     glViewport(0, 0, width, height);

// }

// std::vector<HitRecord> Model::directlyHits(const Hittable& other) const {
//     std::vector<HitRecord> hitRecords;
//     for (auto& mesh: meshes) {
//         std::vector<HitRecord> meshHitRecords = mesh.hits(ray);
//         hitRecords.insert(hitRecords.end(), meshHitRecords.begin(), meshHitRecords.end());
//     }
//     if (useColor) {
//         for (auto& hitRecord: hitRecords) {
//             hitRecord.color = color;
//         }
//     }
//     return hitRecords;
// }

// void Model::setPosition(const glm::dvec3& position) {
//     this->position = position;
//     for (auto& mesh: meshes) {
//         mesh.setPosition(position);
//     }
// }