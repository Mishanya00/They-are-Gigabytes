#include "scenario_interface.hpp"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

#include "interface.hpp"

namespace GUI {

    TGameState GameState;

    void InitGameState()
    {
        GameState.isInvisibleEffect = false;
        GameState.isSelectedEffect = false;
        GameState.isEscMenuVisible = false;
        GameState.isPaused = false;
    }

	void DrawEscWindow()
    {	
		ImGuiWindowFlags esc_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse;

        ImVec2 btnSize = { WindowViewport->Size.x / 4, WindowViewport->Size.y / 16 };
        ImVec2 btnPos = { WindowViewport->Size.x * 0.4f, WindowViewport->Size.y * 0.1f };

		ImGui::SetNextWindowPos(ImVec2(WindowViewport->Size.x / 4, WindowViewport->Size.y / 4));
	    ImGui::SetNextWindowSize(ImVec2(WindowViewport->Size.x / 2, WindowViewport->Size.y / 2));

        if (ImGui::Begin("Esc menu", nullptr, esc_flags))
        {
            ImGui::Text("Just a test text!");
            if (ImGui::Button("Back to game"))
            {
                GameState.isPaused = false;
                GameState.isEscMenuVisible = false;
            }
        }
        ImGui::End();
	}

    void DrawGameInterface()
    {
        SetupFrame();

        static ImGuiWindowFlags upper_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground;
        static ImGuiWindowFlags lower_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse;

        ImGui::SetNextWindowPos(WindowViewport->WorkPos);
        ImGui::SetNextWindowSize(ImVec2(WindowViewport->WorkSize.x, 100));

        if (ImGui::Begin("Upper panel", nullptr, upper_flags))
        {
            ImGui::Text(std::to_string(ContextIO->Framerate).c_str());
        }
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(WindowViewport->WorkPos.x, WindowViewport->WorkSize.y - 100));
        ImGui::SetNextWindowSize(ImVec2(WindowViewport->WorkSize.x, 100));

        if (ImGui::Begin("Lower panel", nullptr, lower_flags))
        {
            ImGui::Text(std::to_string(ContextIO->Framerate).c_str());
        }
        ImGui::End();

        if (GameState.isEscMenuVisible) {
            DrawEscWindow();
        }

        FinishFrame();
    }
}
