#pragma once

#include "Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	//메뉴를 전환시키는 함수
	void ToggleMenu();

	virtual void CleanUp() override;
	static Game& Get();

private:

	//메뉴 레벨
	Level* menuLevel = nullptr;

	//화면에 안보이는 레벨
	Level* backLevel = nullptr;

	bool showMenu = false;

	static Game* instance;
};