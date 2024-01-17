#include <scene.hpp>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <stopwatch.hpp>

#include <vector>
#include <model.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_writer.h>

char buf[9999999];


void Scene::render() {

    unsigned int frameCount = 0;
    double prevFpsTime = 0;
    double updateInterval = 0.5;
    double prevTime = 0;
    double startTime = glfwGetTime();
    int targetAnimationFps = 60;
    unsigned int animationFrameCount = 0;

    // Load OpenGL shaders
    Shader shader = Shader(
        std::string(
            #include <model.vs>
        ),
        std::string(
            #include <model.fs>
        )
    );
    shader.use();

    // Load object models
    Model cube = Model(cubeVertices, cubeIndices);
    createSphere();
    Model sphere = Model(sphereVertices, sphereIndices);
    for (int i = 0; i < sphereVertices.size(); i++) {
        std::cout << sphereVertices[i] << ' ';
    }

    Stopwatch sw;

    glEnable(GL_DEPTH_TEST);

    ///////////////////////////////////////////////////////////////////////
    // Render loop
    ///////////////////////////////////////////////////////////////////////

    while (!glfwWindowShouldClose(window)) {

        // Process reset button click
        if (reset) {
            collidables = Collidable::loadConfig(makeAbsolute("resources/collidables.txt"));
            Collidable ground = Collidable::constructRectangularCuboid(glm::dvec3(0.0), 1, 0.05, 1);
            ground.immovable = true;
            collidables.push_back(ground);
            gpuCD.setCollidables(collidables);
            reset = false;
        }

        // Calculate frame times
        double currentTime = glfwGetTime();
        double dt = currentTime - prevTime;
        prevTime = currentTime;

        // Calculate FPS
        frameCount++;
        if (currentTime - prevFpsTime > updateInterval) {
            fps = frameCount / (currentTime - prevFpsTime);
            prevFpsTime = currentTime;
            frameCount = 0;
        }

        // Process user input, i.e. camera movement
        processInput(window, dt);

        // Clear OpenGL buffers
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set camera view and proejction matrices
        shader.setMat4("view", camera.getView());
        shader.setMat4("projection", camera.getProjection());

        if (!pausePhysics) {
            sw.start();
            // Update position and velocity of each `Collidable`
            gpuCD.updatePhysics(dt / slowMotion);
            // std::cout << "update physics time: " << sw.reset() << '\n';
        }

        sw.start();
        // Set the model matrices of each `Collidable`
        cube.setModelMatrices(gpuCD.getModelMatrices());
        // std::cout << "setModelMatrices time: " << sw.reset() << '\n';

        sw.start();
        // Draw
        sphere.draw();
        // std::cout << "draw time: " << sw.reset() << '\n';

        // Output animation frame captures
        if (recording && (currentTime - startTime) * targetAnimationFps >= animationFrameCount) {
            glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, buf);
            stbi_write_bmp((std::to_string(currentTime) + std::string(".bmp")).c_str(), windowWidth, windowHeight, 3, buf);
            animationFrameCount++;
        }

        // Render GUI
        renderGui();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
