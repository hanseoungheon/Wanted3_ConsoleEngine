#include <iostream>
#include "Demo/DemoLevel.h"
#include "Level/SokobanLevel.h"
#include "Game/Game.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Level/MenuLevel.h"

//¡¯¿‘¡°
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game sokobanGame;
	//engine.AddLevel(new DemoLevel());
	//sokobanGame.AddLevel(new SokobanLevel());
	//sokobanGame.AddLevel(new MenuLevel());
	sokobanGame.Run();
	return 0;
}