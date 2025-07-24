#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "RTTI.h"
//��ü �� �ؾ��ұ�?�� ����.
//��ġ ����.
//�ܼ� â�� �׸���(How?What?).
//������ �̺�Ʈ �Լ� ȣ��.
//BeginPlay/Tick/Draw.

class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI);
public:
	Actor();
	virtual ~Actor();

	//�̺�Ʈ �Լ�

	//��ü �����ֱ�(LifeTime)�� 1���� ȣ��� (�ʱ�ȭ�� ������)
	virtual void BeginPlay();	
	
	//������ ���� ȣ�� (�ݺ��� �۾�/���Ӽ��� �ʿ��� �۾�)
	virtual void Tick(float deltaTime);

	//�׸��� �Լ�
	virtual void Render();

	// BeginPlay ȣ�⿩�� Ȯ��.
	inline bool HasBeganPlay() const { return hasBeganPlay; }
private:
	//��ü�� ��ġ
	Vector2 position;

	//�׸� ��
	char image = ' ';

	//BeginPlay ȣ���� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;
};