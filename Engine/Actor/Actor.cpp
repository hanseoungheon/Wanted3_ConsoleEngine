#include "Actor.h"
#include <Windows.h>
#include <iostream>
#include "Engine.h"
#include "Utils/Utils.h"

Actor::Actor(const char image,Color color, const Vector2& position) : image(image), color(color) , position(position)
{

}
Actor::~Actor()
{
	
}
//이벤트 함수

//객체 생애주기(LifeTime)에 1번만 호출됨 (초기화가 목적임)
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

//프레임 마다 호출 (반복성 작업/지속성이 필요한 작업)
void Actor::Tick(float deltaTime)
{

}

//그리기 함수
void Actor::Render()
{
	//Win32 API 중 일부
	//커서 위치 이동
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	//커서 위치 값 생성
	COORD coord; 
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	//커서이동
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(coord);

	//색상 설정
	//SetConsoleTextAttribute(handle, (WORD)color);
	Utils::SetConsoleTextColor(static_cast<WORD>(color));

	//그리기
	std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	//커서 위치 값 생성
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	//커서이동
	//SetConsoleCursorPosition(handle, coord);
	Utils::SetConsolePosition(coord);

	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}
