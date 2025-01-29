#pragma once

#include <string>
#include <vector>
#include <imgui.h>


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