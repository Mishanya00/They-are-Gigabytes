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
    }

	void DrawEscMenu()
	{
		SetupFrame();
		
		ImGuiWindowFlags play_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse;
		ImGui::SetNextWindowPos(ImVec2(WindowViewport->WorkPos.x + WindowViewport->WorkSize.x / 4, WindowViewport->WorkPos.y + WindowViewport->WorkSize.y / 4));
		ImGui::SetNextWindowSize(WindowViewport->WorkSize);

		FinishFrame();
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

        FinishFrame();
    }
}
