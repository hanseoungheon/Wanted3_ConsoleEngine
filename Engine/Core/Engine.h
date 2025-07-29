#pragma once
#include "Core.h"
#include "Input.h"
#include <Windows.h>

/*
* Todo: 2025�� 7�� 24�� �۾��� ��.
*	- RTTI ���� -> �Ϸ�
*	- Engine�� �̱���(SingleTon)���� ����� -> �̿�
*	//�̱��� - �ν���Ʈ�� �Ѱ��� �����ϴ� ���
*	//gameprogrmmingpatternå�� ��������
*
*/



class Level;
class Engine_API Engine
{
public:
	Engine();
	
	~Engine();

	//���� �����Լ�
	void Run();

	//���� �߰� �Լ�
	void AddLevel(Level* newLevel);



	//�޸� ���� �Լ�
	void CleanUp();

	//���� ���� �Լ�
	void Quit();

	//�̱��� ���� �Լ�
	static Engine& Get();

private:


	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();
private:
	//���� ���� �÷���
	bool isQuit = false;

	Level* mainLevel = nullptr;

	Input input;
	//�̱��� ����
	static Engine* instance;

};