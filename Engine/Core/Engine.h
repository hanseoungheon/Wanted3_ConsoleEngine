#pragma once
#include "Core.h"
#include <Windows.h>

/*
* Todo: 2025년 7월 23일 작업할 것.
	- 키 입력 관리(KeyState 배열). - 완료
	- 입력 확인 함수 (GetKey, GetKeyDown, GeyKeyUp) - 완료

	- Entity 추가(Actor). - 완료
	- 이벤트 함수 추가(BeginPlay, Tick, Render) - 완료
	- Level 추가(가상 공간에 배치된 물체(Actor) 관리 객체) 
*
*/

class Level;
class Engine_API Engine
{
	//키입력 확인을 위한 구조체 선언
	struct KeyState
	{
		//현재 프레임에 키가 눌렸는지 여부
		bool isKeyDown = false;

		//이전 프레임에 키가 눌렸는지 여부
		bool previouseKeyDown = false;
	};
public:
	Engine();
	
	~Engine();

	//엔진 실행함수
	void Run();

	//레벨 추가 함수
	void AddLevel(Level* newLevel);

	//키 확인 함수
	bool GetKey(int KeyCode);
	bool GetKeyDown(int KeyCode);
	bool GetKeyUp(int KeyCode);

	//엔진 종료 함수
	void Quit();

private:
	void ProcessInput();

	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();
private:
	//엔진 종료 플래그
	bool isQuit = false;

	//키 입력 정보 관리 변수
	KeyState keyStates[255] = {};

	Level* mainLevel = nullptr;
};