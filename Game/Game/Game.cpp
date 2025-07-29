#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/SokobanLevel.h"
Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	//메인 레벨 생성
	AddLevel(new SokobanLevel());

	//메뉴 레벨 생성
	menuLevel = new MenuLevel();

}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu()
{
	//화면 정리
	//clear screen 약자, 명령어 실행
	system("cls");

	showMenu = !showMenu;

	if (showMenu)
	{
		//게임 레벨을 뒤로 밀기
		backLevel = mainLevel;

		//메뉴 레벨을 메인 레벨로 설정
		mainLevel = menuLevel;
	}
	else
	{
		//게임 레벨을 메인 레벨로 설정.
		mainLevel = backLevel;
	}
}

void Game::CleanUp()
{
	//이때는 enigne의 mainlevel이 menulevel
	if (showMenu)
	{
		//게임 레벨 제거
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	//else // mainlevel이 게임레벨이고 이떄는 engone에서 하던대로정리하면 끝
	//{

	//}
	SafeDelete(menuLevel);
	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}