#pragma once
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel,Level)

public:
	SokobanLevel();

	//virtual bool CanPlayerMove(
	//	const Vector2& playerPosition,
	//	const Vector2& newPosition) override;
	//bool test = false;
private:
	void ReadMapFile(const char * filename);


	// ICanPlayerMove을(를) 통해 상속됨
	virtual bool CanPlayerMove(
		const Vector2& playerPosition, 
		const Vector2& newPosition) override;

};