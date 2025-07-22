#include "Engine.h"
#include <iostream>
//2가지 추가
// 윈도우
//단순 입력 처리 컨트롤러<키보드>
//시간계산용 타이머


Engine::Engine()
{

}

Engine::~Engine()
{

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
			Update(deltaTime);
			Render();

			//시간 업데이트
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
	//ESC키 눌림 확인
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
