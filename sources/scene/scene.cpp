#include <scene.hpp>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
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

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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


    std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    std::vector<unsigned int> indices = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;


    const Model cube = Model(cubeVertices, cubeIndices);



    // glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    // // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);




    while (!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();
        double dt = currentTime - prevTime;
        prevTime = currentTime;
        processInput(window, dt);

        frameCount++;
        if (currentTime - prevFpsTime > updateInterval) {
            fps = frameCount / (currentTime - prevFpsTime);
            prevFpsTime = currentTime;
            frameCount = 0;
        }

        glClearColor(0.5, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        renderGui();

        // shader.setMat4("model", glm::scale(glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, 0.0, 10.0)), glm::dvec3(1)));
        // shader.setMat4("view", camera.getView());
        // shader.setMat4("projection", camera.getProjection());


        //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
