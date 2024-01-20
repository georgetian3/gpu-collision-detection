#include <scene.hpp>

void Scene::processInput(GLFWwindow*, double dt) {
    if (menuOpen) {
        return;
    }
    for (size_t i = 0; i < 6; i++) {
        directionKeyStates[i] = glfwGetKey(window, directionKeys[i]) == GLFW_PRESS;
    }
    for (size_t i = 0; i < 6; i += 2) {
        if (directionKeyStates[i] && !directionKeyStates[i + 1]) {
            camera.pan(static_cast<Direction>(i), dt);
        } else if (!directionKeyStates[i] && directionKeyStates[i + 1]) {
            camera.pan(static_cast<Direction>(i + 1), dt);
        }
    }
}

void Scene::keyCallback(int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        menuOpen = !menuOpen;
        handleMenu();
    }
}

void Scene::windowSizeCallback(int width, int height) {
    windowWidth = width;
    windowHeight = height;
}

void Scene::mouseCallback(double x, double y) {
    if (menuOpen) {
        return;
    }
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }
    double dx = x - lastX;
    double dy = lastY - y;
    lastX = x;
    lastY = y;
    camera.dYaw(dx);
    camera.dPitch(dy);
}