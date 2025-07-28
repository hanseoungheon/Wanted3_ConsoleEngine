#include "Player.h"
#include "Engine.h"
Player::Player(const Vector2& position) 
	: Actor('P',Color::Red, position)
{	
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(3);

}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//�Է�ó�� 
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().Quit();
		return;
	}

	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		Vector2 position = Position();
		position.x += 1;
		SetPosition(position);
	}

	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		Vector2 position = Position();
		position.x -= 1;
		SetPosition(position);
	}

	if (Engine::Get().GetKeyDown(VK_UP))
	{
		Vector2 position = Position();
		position.y -= 1;
		SetPosition(position);
	}

	if (Engine::Get().GetKeyDown(VK_DOWN))
	{
		Vector2 position = Position();
		position.y += 1;
		SetPosition(position);
	}
}
