#pragma once

#include <string>
#include <vector>
#include <imgui.h>


namespace GUI
{
	enum CurrentWindow {
		cwMain,
		cwPlay,
		cwSettings,
		cwExit,
	};

	struct MainMenuState {
		bool isActiveScenario;
		CurrentWindow window;
		std::string scenarioName;
	};

	extern MainMenuState MenuState;
	extern ImGuiViewport* WindowViewport;
	extern ImGuiIO* ContextIO;
	extern std::vector<ImFont*> fonts;

	void Init();
	
	void SetupFrame();
	void FinishFrame();

	void DrawMainMenu();
}