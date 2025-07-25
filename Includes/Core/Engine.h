#pragma once
#include "Core.h"
#include <Windows.h>

/*
* Todo: 2025년 7월 24일 작업할 것.
*	- RTTI 적용 -> 완료
*	- Engine을 싱글톤(SingleTon)으로 만들기 -> 미완
*	//싱글톤 - 인스턴트를 한개로 고정하는 기법
*	//gameprogrmmingpattern책에 나와있음
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

	//싱글톤 접근 함수
	static Engine& Get();

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

	//싱글톤 변수
	static Engine* instance;

};