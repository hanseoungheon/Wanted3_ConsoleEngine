#pragma once
#include "Core.h"
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
	//Ű�Է� Ȯ���� ���� ����ü ����
	struct KeyState
	{
		//���� �����ӿ� Ű�� ���ȴ��� ����
		bool isKeyDown = false;

		//���� �����ӿ� Ű�� ���ȴ��� ����
		bool previouseKeyDown = false;
	};
public:
	Engine();
	
	~Engine();

	//���� �����Լ�
	void Run();

	//���� �߰� �Լ�
	void AddLevel(Level* newLevel);

	//Ű Ȯ�� �Լ�
	bool GetKey(int KeyCode);
	bool GetKeyDown(int KeyCode);
	bool GetKeyUp(int KeyCode);

	//���� ���� �Լ�
	void Quit();

	//�̱��� ���� �Լ�
	static Engine& Get();

private:
	void ProcessInput();

	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();
private:
	//���� ���� �÷���
	bool isQuit = false;

	//Ű �Է� ���� ���� ����
	KeyState keyStates[255] = {};

	Level* mainLevel = nullptr;

	//�̱��� ����
	static Engine* instance;

};