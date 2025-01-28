#include "interface.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <vector>

#include "mishanya_utils.hpp"

ImVec2 operator+(const ImVec2& a, const ImVec2& b)
{
    return ImVec2(a.x + b.x, a.y + b.y);
}

namespace GUI
{
    ImGuiIO* ContextIO;
    std::vector<ImFont*> fonts;

    MainMenuState MenuState;                // State of the menu to exchange this info with game kernel
    ImGuiViewport* WindowViewport;          // Global var for getting window parameters each frame

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

        MenuState.window = cwMain;
        MenuState.isActiveScenario = false;
        MenuState.scenarioName = "contents/scenarios/map.txt";
    }

    void ShowPlayWindow()
    {
        static std::vector<std::string> saves;
        std::string session_name;

        if (saves.size() == 0) {
            saves = mishanya::GetFileList("contents/scenarios");
        }

        ImGuiWindowFlags play_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse;
        ImGui::SetNextWindowPos(WindowViewport->WorkPos);
        ImGui::SetNextWindowSize(WindowViewport->WorkSize);

        if (ImGui::Begin("Play menu", nullptr, play_flags))
        {
            if (ImGui::Button("BACK"))
            {
                MenuState.window = cwMain;
            }
            
            ImVec2 btnSize = { WindowViewport->Size.x / 4, WindowViewport->Size.y / 16 };
            ImVec2 btnPos = { WindowViewport->Size.x * 0.4f, WindowViewport->Size.y * 0.1f };

            ImGui::SetCursorPos(ImVec2(WindowViewport->Size.x * 0.4f, WindowViewport->Size.y * 0.1f - 50));
            ImGui::TextColored(cGreen, "Available maps:", btnSize);

            ImGui::SetCursorPos(btnPos);

            for (auto& save : saves) {
                session_name = mishanya::GetFileFromPath(save);
                mishanya::RemoveFileExtension(session_name);

                if (ImGui::Button( session_name.c_str(), btnSize) ) {
                    MenuState.isActiveScenario = true;
                    MenuState.scenarioName = save;
                }

                btnPos.y += btnSize.y;
                ImGui::SetCursorPos(btnPos);
            }
        }
        ImGui::End();
    }

    void ShowMainWindow()
    {
        static const ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground;

        ImGui::SetNextWindowPos(WindowViewport->WorkPos);
        ImGui::SetNextWindowSize(WindowViewport->WorkSize);

        if (ImGui::Begin("Main menu", nullptr, window_flags))
        {
            ImVec2 btnSize = { WindowViewport->Size.x / 4, WindowViewport->Size.y / 8 };
            ImVec2 btnPos = { WindowViewport->Size.x * 0.4f, WindowViewport->Size.y * 0.25f };

            ImGui::SetCursorPos(btnPos);
            if (ImGui::Button("Play", btnSize)) {
                MenuState.window = cwPlay;
            }

            ImGui::SetCursorPos(ImVec2(btnPos.x, btnPos.y + btnSize.y));
            ImGui::Button("Settings", btnSize);

            ImGui::SetCursorPos(ImVec2(btnPos.x, btnPos.y + 2 * btnSize.y));
            if (ImGui::Button("Quit", btnSize)) {
                exit(0);
            }
        }
        ImGui::End();
    }

    void DrawMainMenu()
    {
        SetupFrame();

        WindowViewport = ImGui::GetMainViewport();

        ImGui::PushFont(fonts[4]);

        switch (MenuState.window)
        {
        case cwMain:
            ShowMainWindow();
            break;
        case cwPlay:
            ShowPlayWindow();
            break;
        }

        ImGui::PopFont();

        FinishFrame();
    }

    void SetupFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        WindowViewport = ImGui::GetMainViewport();
    }

    void FinishFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}