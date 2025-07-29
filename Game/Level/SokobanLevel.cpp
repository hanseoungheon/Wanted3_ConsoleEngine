#include "SokobanLevel.h"

#include <iostream>
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Box.h"
#include "Actor/Ground.h"
#include "Actor/Target.h"

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map.txt");
}

void SokobanLevel::ReadMapFile(const char * filename)
{
	// ���� ���� ��� �ϼ�
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	//����ó��
	if (file == nullptr)
	{
		std::cout << "�� ���� �б� ����! : " << filename << "\n";
		__debugbreak();
		return;
	}

	//�Ľ�(Parcing)�ϱ� -> �Ľ� = �����м�,�ؼ�
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	//Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	//if (fileSize != readSize)
	//{
	//	std::cout << "fileSize is not matched with readSize\n";
	//}

	//�迭 ��ȸ�� ���� �ε��� ����
	int index = 0;

	//���ڿ� ����
	int size = (int)readSize;
	
	//x,y ��ǥ
	Vector2 position;

	//���ڿ� �迭 ��ȸ
	while (index < size)
	{
		//�� ����Ȯ��
		char mapChracater = buffer[index++];

		//���� ����ó��
		if (mapChracater == '\n')
		{
			//���� �ٷ� �ѱ�鼭, x��ǥ �ʱ�ȭ.
			++position.y;
			position.x = 0;

			////@Todo: �׽�Ʈ�뵵. ���߿� �����ؾߴ�.
			//std::cout << "\n";
			continue;
		}

		//�� ���ں��� �����ؼ� ó��
		switch (mapChracater)
		{
		case '#':
			AddActor(new Wall(position));
			//std::cout << "#";
			break;

		case '.':
			AddActor(new Ground(position));
			//std::cout << ".";
			break;

		case 'p':
			//�����̴� ��ü�̱� ������ ���� ���� ����
			AddActor(new Ground(position));

			//__Player���� ����
			AddActor(new Player(position));
			//std::cout << "p";
			break;

		case 'b':
			//�����̴� ��ü�̱� ������ ���� ���� ����
			AddActor(new Ground(position));

			AddActor(new Box(position));
			//std::cout << "b";
			break;

		case 't':
			AddActor(new Target(position));
			++targetScore;
			//std::cout << "t";
			break;
		}

		//x��ǥ ���� ó��
		++position.x;
	}

	//���� ����
	delete[] buffer;
 
	//���� �ݱ�
	fclose(file);
	//while (!feof(file))
	//{
	//	char buffer[256];

	//}
}

bool SokobanLevel::CheckGameClear()
{
	//�ڽ��� Ÿ�� ��ġ�� ��� �Ű������� Ȯ��.
	int currentScore = 0;

	std::vector<Target*> targetActors;
	std::vector<Box*> boxActors;
	
	for (Actor* const actor : actors)
	{
		if (actor->As<Box>())
		{
			boxActors.emplace_back(actor);
		}

		else if (actor->As<Target>())
		{
			targetActors.emplace_back(actor);
		}
	}

	//�ڽ��� Ÿ�� ���� ��ġ ���ϱ�.
	for (Actor* const targetActor : targetActors)
	{
		for (Actor* const boxActor : boxActors)
		{
			if (targetActor->Position() == boxActor->Position())
			{
				++currentScore;
			}
		}
	}

	return currentScore >= targetScore; //currentScore = targetScore�� true
}

bool SokobanLevel::CanPlayerMove(
	const Vector2& playerPosition, 
	const Vector2& newPosition)
{
	//���� Ŭ���Ƥ� ���� Ȯ�� �� ���� ó��
	//�ڽ� ó��

	if (isGameClear)
	{
		return false;
	}

	std::vector<Box*> boxActors;

	for (Actor* const actor : actors)
	{
		Box* box = actor->As<Box>();

		if (box)
		{
			boxActors.emplace_back(box);
		}
	}

	//�̵��Ϸ��� ��ġ�� �ڽ��� �ִ��� Ȯ��

	Box* searchedBox = nullptr;

	for (Box* const boxActor : boxActors)
	{
		if (boxActor->Position() == newPosition)
		{
			searchedBox = boxActor;
			break;
		}
	}

	//�̵��Ϸ��� ��ġ�� �ڽ��� �ִ� ��� ó��
	if (searchedBox)
	{
		//#1 �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �� �ִ��� Ȯ��.
		Vector2 direction = newPosition - playerPosition;
		Vector2 nextposition = searchedBox->Position() + direction;

		for (Box* const otherBox : boxActors)
		{
			if (otherBox == searchedBox)
			{
				continue;
			}

			// �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �ִ��� Ȯ��
			if (otherBox->Position() == nextposition)
			{
				//false�� �� �÷��̾� �̵� ����
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->Position() == nextposition)
			{
				if (actor->As<Wall>())//#2 �ڽ��� ������, ���� ���� ������ Ȯ��
				{
					return false;
				}

				//#3 �̵� ������ ���(�׶���, Ÿ��)���� �̵�ó��
				if (actor->As<Ground>() || actor->As<Target>())
				{
					//�ڽ� �̵� ó��
					searchedBox->SetPosition(nextposition);

					//���� Ŭ����?
					isGameClear = CheckGameClear();

					//�÷��̾� �̵� ����
					return true;
				}
			}
		}
	}

	//�÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ���� �ܿ�
	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			//���̸� �̵� �Ұ�
			if (actor->As<Wall>())
			{
				return false;
			}

			//�׶��� or Ÿ��
			return true;
		}
	}

	//����ó��
	return false;
}
