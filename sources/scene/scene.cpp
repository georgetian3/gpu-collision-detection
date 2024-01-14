#include <scene.hpp>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include <vector>
#include <model.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_writer.h>

uint8_t buf[9999999];

Scene::Scene(const std::filesystem::path& cwd, int windowWidth, int windowHeight): windowWidth(windowWidth), windowHeight(windowHeight) {
    this->cwd = makeAbsolute(cwd);
    std::cout << "CWD: " << cwd << '\n';

    lastX = windowWidth / 2.0;
    lastY = windowHeight / 2.0;
    init();

}

void Scene::render() {

    ///////////////////////////////////////////////////////////////////////
    // Render loop
    ///////////////////////////////////////////////////////////////////////

    unsigned int frameCount = 0;
    double prevFpsTime = 0;
    double updateInterval = 0.5;
    double prevTime = 0;
    double startTime = glfwGetTime();
    int targetAnimationFps = 60;
    unsigned int animationFrameCount = 0;

    Shader shader = Shader(
        std::string(
            #include <model.vs>
        ),
        std::string(
            #include <model.fs>
        )
    );
    
    shader.use();

    Model cube = Model(cubeVertices, cubeIndices);

    std::vector<glm::vec3> positions = {
        glm::vec3(1.0f),
        glm::vec3(5.0f),
        glm::vec3(10.0f),
    };

    std::vector<glm::mat4> modelMatrices;
    for (const auto& position: positions) {
        modelMatrices.push_back(glm::translate(glm::mat4(1.0f), position));
    }

    int total = 0;

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();
        double dt = currentTime - prevTime;
        prevTime = currentTime;
        processInput(window, dt);

        frameCount++;
        total++;
        if (total > 100) {
            std::cout << "total > 100\n";
            break;
        }
        if (currentTime - prevFpsTime > updateInterval) {
            fps = frameCount / (currentTime - prevFpsTime);
            prevFpsTime = currentTime;
            frameCount = 0;
        }

        

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader.setMat4("view", camera.getView());
        shader.setMat4("projection", camera.getProjection());

        printLocation();

        gpuCD.updatePhysics(dt);
        cube.setModelMatrices(gpuCD.getModelMatrices());
        cube.draw();

        // if ((currentTime - startTime) * targetAnimationFps >= animationFrameCount) {
            // glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, buf);
            // animationFrameCount++;
            // if (animationFrameCount % targetAnimationFps == 0) {
            //     std::cout << animationFrameCount << '\n';
            // }
        // }
        renderGui();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
