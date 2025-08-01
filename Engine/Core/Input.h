#pragma once

#include "Core.h"

class Engine_API Input
{
	friend class Engine;

	//키입력 확인을 위한 구조체 선언
	struct KeyState
	{
		//현재 프레임에 키가 눌렸는지 여부
		bool isKeyDown = false;

		//이전 프레임에 키가 눌렸는지 여부
		bool previouseKeyDown = false;
	};

public:
	Input();

	//키 확인 함수
	bool GetKey(int KeyCode);
	bool GetKeyDown(int KeyCode);
	bool GetKeyUp(int KeyCode);


	static Input& Get();
private:
	void ProcessInput();
	void SavePreviouseKeyStates();

	//키 입력 정보 관리 변수
	KeyState keyStates[255] = { };

	static Input* instance;
};