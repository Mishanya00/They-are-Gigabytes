#pragma once

namespace GUI {

	struct TGameState {
		bool isSelectedEffect;
		bool isInvisibleEffect;
		
		bool isEscMenuVisible;
	};

	extern TGameState GameState;

	void InitGameState();
	void DrawEscMenu();
	void DrawGameInterface();
}