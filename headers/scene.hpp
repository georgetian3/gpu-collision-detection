#ifndef SCENE_HPP
#define SCENE_HPP

#include <GLFW/glfw3.h>
#include <shader.hpp>
#include <camera.hpp>

#include <filesystem>
#include <glm/glm.hpp>
#include <utils.hpp>
#include <gpu_collision_detector.hpp>

class Scene {


    int windowWidth;
    int windowHeight;

    bool wireframe = true;

    double lastX, lastY;
    bool firstMouse = true;
    GLFWwindow* window = nullptr;

    double fps = 0.0;

    Camera camera;
    bool menuOpen = false;
    bool pausePhysics = true;
    bool reset = true;
    bool recording = false;
    double slowMotion = 1.0;

    void handleMenu();


    std::filesystem::path cwd;
    std::filesystem::path makeAbsolute(std::filesystem::path path) const {
        return (path.is_absolute() ? path : (cwd / path)).make_preferred();
    }

    bool vsync = false;

    void renderGui();

    int directionKeys[6] = {
        GLFW_KEY_W,         // forward
        GLFW_KEY_S,         // backward
        GLFW_KEY_D,         // right
        GLFW_KEY_A,         // left
        GLFW_KEY_SPACE,     // up
        GLFW_KEY_LEFT_SHIFT // down
    };

    bool directionKeyStates[6] = {
        false,
        false,
        false,
        false,
        false,
        false,
    };

    void processInput(GLFWwindow*, double dt);
    void keyCallback(int key, int scancode, int action, int mods);
    void mouseCallback(double xposIn, double yposIn);
    void windowSizeCallback(int width, int height);
    void init();

    std::vector<Collidable> collidables;
    GpuCollisionDetector gpuCD;


public:

    Scene(const std::filesystem::path& cwd, int windowWidth = 1280, int windowHeight = 720);
    ~Scene();
    void render();
    GLFWwindow* getWindow() const {
        return window;
    }

};

#endif