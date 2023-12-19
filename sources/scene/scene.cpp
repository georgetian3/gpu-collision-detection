#include <scene.hpp>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
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
    double lastTime = 0;
    double startTime = glfwGetTime();
    int targetAnimationFps = 60;
    unsigned int animationFrameCount = 0;

    // Shader shader = Shader(
    const Model cube = Model(cubeVertices, cubeIndices);


    glEnable(GL_DEPTH_TEST);


    while (!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();
        double dt = currentTime - lastTime;
        lastTime = currentTime;
        processInput(window, dt);

        frameCount++;
        if (currentTime - prevFpsTime > updateInterval) {
            fps = frameCount / (currentTime - prevFpsTime);
            prevFpsTime = currentTime;
            frameCount = 0;
        }

        glClearColor(0.5, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderGui();

        cube.draw();

        // collisionDetector->detectCollisions();

        // if ((currentTime - startTime) * targetAnimationFps >= animationFrameCount) {
            // glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, buf);
            // animationFrameCount++;
            // if (animationFrameCount % targetAnimationFps == 0) {
            //     std::cout << animationFrameCount << '\n';
            // }
        // }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
