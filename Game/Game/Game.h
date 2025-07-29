#pragma once

#include "Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	//�޴��� ��ȯ��Ű�� �Լ�
	void ToggleMenu();

	virtual void CleanUp() override;
	static Game& Get();

private:

	//�޴� ����
	Level* menuLevel = nullptr;

	//ȭ�鿡 �Ⱥ��̴� ����
	Level* backLevel = nullptr;

	bool showMenu = false;

	static Game* instance;
};