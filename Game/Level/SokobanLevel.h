#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel,Level)

public:
	SokobanLevel();

	// ICanPlayerMove��(��) ���� ��ӵ�
	virtual bool CanPlayerMove(
		const Vector2& playerPosition,
		const Vector2& newPosition) override;

	//virtual bool CanPlayerMove(
	//	const Vector2& playerPosition,
	//	const Vector2& newPosition) override;
	//bool test = false;
private:
	virtual void Render() override;

	//�������� �о ���� ��ü �����ϴ� �Լ�
	void ReadMapFile(const char * filename);

	//���� Ŭ���� üũ �Լ�
	bool CheckGameClear();

private:

	int targetScore = 0;

	bool isGameClear = false;
};