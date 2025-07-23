#include "Level.h"
#include "Actor/Actor.h"

Level::Level()
{

}
Level::~Level()
{

}

// ������ ���͸� �߰��� �� ���
void Level::AddActor(Actor* newActor)
{
	//����ó��(�ߺ� ���� Ȯ��) �ʼ�

	//push_back , emplace_back : �迭 �� �ڿ� ���ο� �׸� �߰��ϴ� ����
	//push_back = && ��������, emplace_back = &����, &&�������� 
	//&�� ���縦 ��, &&�� ���絵 ���� �� &&�� �� ����

	actors.emplace_back(newActor);
	//actors.push_back(newActor);
}

// ���� �̺�Ʈ �Լ�
void Level::BeginPlay()
{
	for (Actor* actor : actors)
	{
		//�̹� ȣ�� �� ��ü�� �ǳʶٱ�
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