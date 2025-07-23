#include <iostream>
#include "Engine.h"
#include "Level/Level.h"

//2���� �߰�
// ������
//�ܼ� �Է� ó�� ��Ʈ�ѷ�<Ű����>
//�ð����� Ÿ�̸�


Engine::Engine()
{

}

Engine::~Engine()
{
	//���� ����
	if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
}

void Engine::Run()
{
	//�и� ������ ������ ���� �ð� �˷���
	//float currentTime = timeGetTime();

	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;

	//Windosw ī����
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	//�ϵ���� �ð������е�(���ļ� ��������)
	//���߿� �ʷ� ��ȯ�ϱ� ����
	LARGE_INTEGER freqeuncy;
	QueryPerformanceFrequency(&freqeuncy);

	//Ÿ�� ������
	float targetFramRate = 60.0f;

	//Ÿ�� �� ������ �ð�
	float oneFrameTime = 1.0f / targetFramRate;

	while (true)
	{
		if (isQuit)
		{
			//���� ����
			break;
		}

		//������ �ð� ���
		//(���� �ð� - �����ð�) / ���ļ�
		QueryPerformanceCounter(&currentTime);


		//������ �ð�
		float deltaTime = 
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)freqeuncy.QuadPart;
		
		//�Է��� �ִ��� ����
		ProcessInput();

		//���� ������
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			//�ð� ������Ʈ
			previousTime = currentTime;

			//���� �������� �Է��� ���
			for (int ix = 0; ix < 255; ++ix)
			{
				keyStates[ix].previouseKeyDown 
					= keyStates[ix].isKeyDown;
			}
		}

	}
}

void Engine::AddLevel(Level* newLevel)
{
	//������ �ִ� ������ ����
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

bool Engine::GetKey(int KeyCode)
{
	return keyStates[KeyCode].isKeyDown;

}

bool Engine::GetKeyDown(int KeyCode)
{
	return !keyStates[KeyCode].previouseKeyDown
		&& keyStates[KeyCode].isKeyDown;
}

bool Engine::GetKeyUp(int KeyCode)
{
	return keyStates[KeyCode].previouseKeyDown
		&& !keyStates[KeyCode].isKeyDown;
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	//Ű �Է� Ȯ��
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown 
			= GetAsyncKeyState(ix) && 0x8000;
	}

	//ESCŰ ���� Ȯ��
	//if (GetAsyncKeyState(VK_ESCAPE) && 0x8000)
	//{
	//	Quit();
	//}
}


void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}
void Engine::Tick(float deltaTime)
{
	//std::cout 
	//	<< "DeltaTime : " << deltaTime 
	//	<< ", FPS: "<< (1.0f/deltaTime)
	//	<< "\n";

	//if (GetKeyDown('A'))
	//{
	//	std::cout << "KeyDown\n";
	//}
	//if (GetKey('A'))
	//{
	//	std::cout << "Key\n";
	//}
	//if (GetKeyUp('A'))
	//{
	//	std::cout << "KeyUp\n";
	//}

	//���� ������Ʈ
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}
	if (GetKeyDown(VK_ESCAPE))
	{
		Quit();
	}
}

void Engine::Render()
{
	if (mainLevel)
	{
		mainLevel->Render();
	}
}
