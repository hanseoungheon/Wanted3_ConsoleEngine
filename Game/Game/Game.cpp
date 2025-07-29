#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/SokobanLevel.h"
Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;

	//���� ���� ����
	AddLevel(new SokobanLevel());

	//�޴� ���� ����
	menuLevel = new MenuLevel();

}

Game::~Game()
{
	CleanUp();
}

void Game::ToggleMenu()
{
	//ȭ�� ����
	//clear screen ����, ��ɾ� ����
	system("cls");

	showMenu = !showMenu;

	if (showMenu)
	{
		//���� ������ �ڷ� �б�
		backLevel = mainLevel;

		//�޴� ������ ���� ������ ����
		mainLevel = menuLevel;
	}
	else
	{
		//���� ������ ���� ������ ����.
		mainLevel = backLevel;
	}
}

void Game::CleanUp()
{
	//�̶��� enigne�� mainlevel�� menulevel
	if (showMenu)
	{
		//���� ���� ����
		SafeDelete(backLevel);
		mainLevel = nullptr;
	}
	//else // mainlevel�� ���ӷ����̰� �̋��� engone���� �ϴ���������ϸ� ��
	//{

	//}
	SafeDelete(menuLevel);
	Engine::CleanUp();
}

Game& Game::Get()
{
	return *instance;
}