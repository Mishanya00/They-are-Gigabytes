#pragma once

namespace GUI {

	struct TGameState {
		bool isNoiseEffect;
		bool isSelectedEffect;
		bool isInvisibleEffect;
		bool isColorGradingEffect;

		bool isPaused;
		bool isClosed;
		
		bool isEscMenuVisible;
	};

	extern TGameState GameState;

	void InitGameState();
	void DrawEscMenu();
	void DrawGameInterface();
}