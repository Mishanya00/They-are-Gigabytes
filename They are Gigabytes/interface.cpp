#include "interface.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>


ImGuiIO* ContextIO;


namespace GUI
{
	void Init()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ContextIO = &ImGui::GetIO(); (void)ContextIO;
        ContextIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ContextIO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ContextIO->DeltaTime = 1.0f / 80.0f;

        ImGui::StyleColorsDark();
    }

    void DrawMainMenu()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Main menu");
        ImGui::Text("Will it work?");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}