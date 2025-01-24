#pragma once

#include <string>


namespace GUI
{
	struct MainMenuState {
		bool isActiveScenario;
		std::string scenarioName;
	};

	void Init();
	void DrawMainMenu(MainMenuState & state);
}