#include "Actor.h"

Actor::Actor()
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
	
}