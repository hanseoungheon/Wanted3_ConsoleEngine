#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}
Level::~Level()
{

}

// 레벨에 액터를 추가할 때 사용
void Level::AddActor(Actor* newActor)
{
	//예외처리(중복 여부 확인) 필수

	//push_back , emplace_back : 배열 맨 뒤에 새로운 항목 추가하는 변수
	//push_back = && 이중참조, emplace_back = &참조, &&이중참조 
	//&는 복사를 함, &&는 복사도 안함 즉 &&가 더 빠름

	actors.emplace_back(newActor);
	//actors.push_back(newActor);
}

// 엔진 이벤트 함수
void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//이미 호출 된 개체는 건너뛰기
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

void Level::Tick(float deltaTime)
{
	for (Actor* actor : actors)
	{
		actor->Tick(deltaTime);
	}
}

void Level::Render()
{
	for (Actor* actor : actors)
	{
		actor->Render();
	}

}