#pragma once
#include "Core.h"
#include <vector> //ũ�Ⱑ �˾Ƽ� ����Ǵ� ���� �迭
//List�� �ҷ��ߴµ� �̹� �־ ��¿�� ���� vector�� �ߴٰ���
//�� ������ ���Ͱ� �ƴ�!
#include "RTTI.h"
class Actor;

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();

	// ������ ���͸� �߰��� �� ���
	void AddActor(Actor* newActor);

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();
private:
	std::vector<Actor*> actors;
};