#include "interface.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <vector>


ImGuiIO* ContextIO;
std::vector<ImFont*> fonts;

ImVec2 operator+(const ImVec2& a, const ImVec2& b)
{
    return ImVec2(a.x + b.x, a.y + b.y);
}


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
        fonts.push_back(ContextIO->Fonts->AddFontFromFileTTF("contents\\fonts\\ImGui\\DroidSans.ttf", 36));
        fonts.push_back(ContextIO->Fonts->AddFontFromFileTTF("contents\\fonts\\ImGui\\Karla-Regular.ttf", 36));
        fonts.push_back(ContextIO->Fonts->AddFontFromFileTTF("contents\\fonts\\ImGui\\ProggyClean.ttf", 36));
        fonts.push_back(ContextIO->Fonts->AddFontFromFileTTF("contents\\fonts\\ImGui\\ProggyTiny.ttf", 36));

        ImGui::StyleColorsDark();
    }

    void DrawMainMenu(MainMenuState& state)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        if (ImGui::Begin("Main menu", nullptr, window_flags))
        {
            ImVec2 btnSize = { viewport->Size.x / 4, viewport->Size.y / 8 };
            ImVec2 btnPos = { viewport->Size.x * 0.4f, viewport->Size.y * 0.25f };

            ImGui::PushFont(fonts[4]);

            ImGui::SetCursorPos(btnPos);
            if (ImGui::Button("Play", btnSize)) {
                state.isActiveScenario = true;
            }

            ImGui::SetCursorPos(ImVec2(btnPos.x, btnPos.y+btnSize.y));
            ImGui::Button("Settings", btnSize);

            ImGui::SetCursorPos(ImVec2(btnPos.x, btnPos.y + 2 * btnSize.y));
            ImGui::Button("Quit", btnSize);

            ImGui::PopFont();
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}