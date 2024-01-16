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

void error_callback( int error, const char* description ) {
    fprintf( stderr, "Error: %s\n", description );
}

void Scene::init() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        exit(1);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(windowWidth, windowHeight, "GPU Collision Detection", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Failed to create OpenGL context" << '\n';
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
    
    glfwSwapInterval(vsync ? 1 : 0);
    handleMenu();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

    collidables = Collidable::loadConfig(makeAbsolute("resources/collidables.txt"));
    Collidable ground = Collidable::constructRectangularCuboid(glm::dvec3(0.5, 0.1, 0.5), 1, 0.05, 1);
    ground.immovable = true;
    collidables.push_back(ground);
    gpuCD.setCollidables(collidables);

}


Scene::~Scene() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

