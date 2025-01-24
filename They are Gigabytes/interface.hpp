#pragma once

#include <string>


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

	void Init();
	void DrawMainMenu();
	void DrawGameInterface();
}