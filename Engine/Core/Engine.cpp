#include "Engine.h"
#include <iostream>
//2���� �߰�
// ������
//�ܼ� �Է� ó�� ��Ʈ�ѷ�<Ű����>
//�ð����� Ÿ�̸�


Engine::Engine()
{

}

Engine::~Engine()
{

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
			Update(deltaTime);
			Render();

			//�ð� ������Ʈ
			previousTime = currentTime;
		}

	}
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	//ESCŰ ���� Ȯ��
	if (GetAsyncKeyState(VK_ESCAPE) && 0x8000)
	{
		Quit();
	}
}

void Engine::Update(float deltaTime)
{
	std::cout 
		<< "DeltaTime : " << deltaTime 
		<< ", FPS: "<< (1.0f/deltaTime)
		<< "\n";
}

void Engine::Render()
{
	
}
