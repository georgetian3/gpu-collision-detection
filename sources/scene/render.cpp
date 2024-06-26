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

void Scene::render() {

    unsigned int frameCount = 0;
    double prevFpsTime = 0;
    double updateInterval = 0.5;
    double prevTime = 0;
    double startTime = glfwGetTime();

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
    Model cuboid = Model(cubeVertices, cubeIndices);
    createSphere();
    Model sphere = Model(sphereVertices, sphereIndices);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    ///////////////////////////////////////////////////////////////////////
    // Render loop
    ///////////////////////////////////////////////////////////////////////

    while (!glfwWindowShouldClose(window)) {

        // Process reset button click
        if (reset) {
            // load collidables from file
            collidables = Collidable::loadConfig(makeAbsolute("resources/collidables.txt"));
            // construct 6 more immovables collidables as the box for all other collidables
            double delta = 0.005;
            double delta2 = delta * 2;
            double inv_delta = 1 - delta;
            double inv_delta2 = 1 - delta * 2;
            glm::dvec3 positions[] = {
                glm::dvec3(0, delta, delta),
                glm::dvec3(delta, 0, delta),
                glm::dvec3(delta, delta, 0),
                glm::dvec3(inv_delta, delta, delta),
                glm::dvec3(delta, inv_delta, delta),
                glm::dvec3(delta, delta, inv_delta),
            };
            double xls[] = {delta, inv_delta2, inv_delta2, delta, inv_delta2, inv_delta2};
            double yls[] = {inv_delta2, delta, inv_delta2, inv_delta2, delta, inv_delta2};
            double zls[] = {inv_delta2, inv_delta2, delta, inv_delta2, inv_delta2, delta};
            for (int i = 0; i < 6; i++) {
                collidables.push_back(Collidable(CollidableType::cuboid, positions[i], glm::dvec3(0.0), 1.0, 1.0, xls[i], yls[i], zls[i]));
                collidables.back().immovable = true;
            }
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
            // Update position and velocity of each `Collidable`
            gpuCD.updatePhysics(dt / slowMotion);
        }

        // Set the model matrices of each `Collidable`
        gpuCD.calculateModelMatrices();
        cuboid.setModelMatrices(gpuCD.getCuboidModelMatrices());
        sphere.setModelMatrices(gpuCD.getSphereModelMatrices());

        // Draw
        cuboid.draw();
        sphere.draw();

        // Render GUI
        renderGui();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
