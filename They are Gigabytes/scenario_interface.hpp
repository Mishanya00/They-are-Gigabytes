#pragma once

namespace GUI {

	struct TGameState {
		bool isSelectedEffect;
		bool isInvisibleEffect;
		bool isPaused;
		bool isClosed;
		bool isEscMenuVisible;
	};

	extern TGameState GameState;

	void InitGameState();
	void DrawEscMenu();
	void DrawGameInterface();
}