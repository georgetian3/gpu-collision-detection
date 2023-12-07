#include <scene.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <functional>

#include <glm/gtx/string_cast.hpp>

// std::string addId(const std::string& label, const Model& model) {
//     return label + "##" + std::to_string(model.getId());
// }

bool SliderDouble(const char *label, double *v, double v_min, double v_max, const char *format = "%.3f", ImGuiSliderFlags flags = 0) {
    float fv = static_cast<float>(*v);
    bool pressed = ImGui::SliderFloat(label, &fv, static_cast<float>(v_min), static_cast<float>(v_max), format, flags);
    *v = static_cast<double>(fv);
    return pressed;
}

void Scene::renderGui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (menuOpen) {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5));
        ImGui::Begin("menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::PopStyleColor();
        ImGui::SetWindowSize(ImVec2(static_cast<float>(windowWidth), static_cast<float>(windowWidth)));
        if (ImGui::Checkbox("VSync", &vsync)) glfwSwapInterval(vsync ? 1 : 0); ImGui::SameLine();
        if (ImGui::Checkbox("Wireframe", &wireframe)) glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

        double sensitivity = camera.getSensitivity(), cameraSpeed = camera.getSpeed();

        if (SliderDouble("Mouse sensitivity", &sensitivity, 0.01, 1.0)) camera.setSensitivity(sensitivity);
        if (SliderDouble("Camera movement speed", &cameraSpeed, 0.1, 100.0)) camera.setSpeed(cameraSpeed);

        // ImGui::ShowDemoWindow();

        ImGui::End();

    } else {
        ImGui::Begin("fps", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize(ImVec2(600, 40));
        ImGui::Text("FPS: %d", (int)fps);
        ImGui::End();
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}