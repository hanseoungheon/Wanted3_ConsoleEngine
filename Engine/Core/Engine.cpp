#include <iostream>
#include "Engine.h"
#include "Level/Level.h"
#include <Windows.h>

//2가지 추가
// 윈도우
//단순 입력 처리 컨트롤러<키보드>
//시간계산용 타이머


Engine* Engine::instance = nullptr;

Engine::Engine()
{
	instance = this;

	//콘솔 커서 끄기


	//HANDLE
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&info
	);
}

Engine::~Engine()
{
	//레벨 삭제
	if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
}

void Engine::Run()
{
	//밀리 세컨드 단위로 현재 시간 알려줌
	//float currentTime = timeGetTime();

	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;

	//Windosw 카운터
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	//하드웨어 시계의정밀도(주파수 가져오기)
	//나중에 초로 변환하기 위해
	LARGE_INTEGER freqeuncy;
	QueryPerformanceFrequency(&freqeuncy);

	//타겟 프레임
	float targetFramRate = 60.0f;

	//타겟 한 프레임 시간
	float oneFrameTime = 1.0f / targetFramRate;

	while (true)
	{
		if (isQuit)
		{
			//루프 종료
			break;
		}

		//프레임 시간 계산
		//(현재 시간 - 이전시간) / 주파수
		QueryPerformanceCounter(&currentTime);


		//프레임 시간
		float deltaTime =
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)freqeuncy.QuadPart;

		//입력은 최대한 빨리
		ProcessInput();

		//고정 프레임
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			//시간 업데이트
			previousTime = currentTime;

			//현재 프레임의 입력을 기록
			for (int ix = 0; ix < 255; ++ix)
			{
				keyStates[ix].previouseKeyDown
					= keyStates[ix].isKeyDown;
			}
		}

	}

	//정리
	//모든 텍스트 색상 변경
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED // = 7
	);
}

void Engine::AddLevel(Level* newLevel)
{
	//기존에 있던 레벨은 제거
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

Engine& Engine::Get()
{
	return *instance;
}

void Engine::ProcessInput()
{
	//키 입력 확인
	for (int ix = 0; ix < 255; ++ix)
	{
		keyStates[ix].isKeyDown 
			= GetAsyncKeyState(ix) && 0x8000;
	}

	//ESC키 눌림 확인
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

	//레벨 업데이트
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}

	//if (GetKeyDown(VK_ESCAPE))
	//{
	//	Quit();
	//}
}

void Engine::Render()
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED // = 7
	);

	if (mainLevel)
	{
		mainLevel->Render();
	}
}
