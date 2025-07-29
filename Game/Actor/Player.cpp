#include "Player.h"
#include "Engine.h"
#include "Game/Game.h"

#include "Input.h"
#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

#include <iostream>

Player::Player(const Vector2& position) 
	: Actor('P',Color::Red, position)
{	
	// �׸� �� ����� ���� ���� ����.
	SetSortingOrder(3);

}

void Player::BeginPlay()
{
	super::BeginPlay();

	//�������̽� ������

	if (GetOwner())
	{
		canPlayerMoveInterface =
			dynamic_cast<ICanPlayerMove*>(GetOwner());

		if (!canPlayerMoveInterface)
		{
			std::cout << "Can not cast owener level to ICanPlayerMove.\n";
		}
	}
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//�Է�ó�� 
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
	/*	QuitGame();*/
		Game::Get().ToggleMenu();
		return;
	}


	//�Է�ó��

	//�Է� ���� - �̵��ϱ� ���� ��ġ�� �� �� �ִ��� �Ǵ� �� �̵�
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x + 1, Position().y)))
		{
			Vector2 position = Position();
			position.x += 1;
			SetPosition(position);
		}

	}

	if (Input::Get().GetKeyDown(VK_LEFT))
	{
	/*	bool result = canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x - 1, Position().y)
			);*/

		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x - 1, Position().y)))
		{
			Vector2 position = Position();
			position.x -= 1;
			SetPosition(position);
		}

	}

	if (Input::Get().GetKeyDown(VK_UP))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x, Position().y-1)))
		{
			Vector2 position = Position();
			position.y -= 1;
			SetPosition(position);
		}
	}

	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		if (canPlayerMoveInterface->CanPlayerMove(
			Position(),
			Vector2(Position().x, Position().y+1)))
		{
			Vector2 position = Position();
			position.y += 1;
			SetPosition(position);
		}
	}
}
