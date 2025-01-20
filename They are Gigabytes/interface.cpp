#include "interface.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <vector>


ImGuiIO* ContextIO;
std::vector<ImFont*> fonts;


namespace GUI
{
    const ImVec4 cBlack = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    const ImVec4 cWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    const ImVec4 cRed = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    const ImVec4 cGreen = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
    const ImVec4 cBlue = ImVec4(0.00f, 0.00f, 1.00f, 1.00f);
    const ImVec4 cYellow = ImVec4(1.00f, 1.00f, 0.00f, 1.00f);
    const ImVec4 cMagenta = ImVec4(1.00f, 0.00f, 1.00f, 1.00f);
    const ImVec4 cCyan = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
    const ImVec4 cTransparent = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);


	void Init()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ContextIO = &ImGui::GetIO(); (void)ContextIO;
        ContextIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ContextIO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ContextIO->DeltaTime = 1.0f / 80.0f;

        fonts.push_back(ContextIO->Fonts->AddFontFromFileTTF("contents\\fonts\\ImGui\\Roboto-Medium.ttf", 36));

        ImGui::StyleColorsDark();
    }

    void DrawMainMenu()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        ImGui::Begin("Main menu", nullptr, window_flags);
        
        ImGui::Text("Will it work?");
        ImGui::Text("Will it work?");
        ImGui::Text("Will it work?");
        ImGui::Text("Will it work?");
        ImGui::Text("Will it work?");
        ImGui::Text("Will it work?");

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}