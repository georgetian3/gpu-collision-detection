#include <scene.hpp>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>

// https://stackoverflow.com/a/39213604
#define genericCallback(functionName)\
    [](GLFWwindow* window, auto... args) {\
        static_cast<Scene*>(glfwGetWindowUserPointer(window))->functionName(args...);\
    }

void Scene::handleMenu() {
    firstMouse = true;
    glfwSetInputMode(window, GLFW_CURSOR, menuOpen ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}


void Scene::init() {
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #ifdef __APPLE__
//     glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_TRUE);
// #endif
//     glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

//     bool fullscreen = false;
//     auto primaryMonitor = glfwGetPrimaryMonitor();

//     printLocation();
//     std::cout << "ww wh " << windowWidth << ' ' << windowHeight << '\n';
//     window = glfwCreateWindow(windowWidth, windowHeight, "GPU Collision Detection", nullptr, nullptr);

//     printLocation();
//     if (window == nullptr) {
//         std::cerr << "Failed to create OpenGL context" << '\n';
//         exit(1);
//     }
//     glfwMakeContextCurrent(window);

glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Scene", nullptr, nullptr);
    // fullscreen:

    // auto primaryMonitor = glfwGetPrimaryMonitor();
    // window = glfwCreateWindow(
    //     glfwGetVideoMode(primaryMonitor)->width,
    //     glfwGetVideoMode(primaryMonitor)->height,
    //     "OpenGL Scene", primaryMonitor, nullptr
    // );

    if (window == nullptr) {
        std::cerr << "Failed to Create OpenGL Context";
        exit(1);
    }
    glfwMakeContextCurrent(window);

    
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, genericCallback(windowSizeCallback));
    glfwSetCursorPosCallback(window, genericCallback(mouseCallback));
    glfwSetKeyCallback(window, genericCallback(keyCallback));

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << '\n';
        exit(1);
    }
    printLocation();
    
    glfwSwapInterval(vsync ? 1 : 0);
    handleMenu();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

    collidables = Collidable::loadConfig(makeAbsolute("resources/collidables.txt"));
    gpuCD.setCollidables(collidables);

}


Scene::~Scene() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

