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
	// 최종 에셋 경로 완성
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Assets/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	//예외처리
	if (file == nullptr)
	{
		std::cout << "맵 파일 읽기 실패! : " << filename << "\n";
		__debugbreak();
		return;
	}

	//파싱(Parcing)하기 -> 파싱 = 구문분석,해석
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	//확인한 파일 크기를 활용해 버퍼 할당.
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	//if (fileSize != readSize)
	//{
	//	std::cout << "fileSize is not matched with readSize\n";
	//}

	//배열 순회를 위한 인덱스 변수
	int index = 0;

	//문자열 길이
	int size = (int)readSize;
	
	//x,y 좌표
	Vector2 position;

	//문자열 배열 순회
	while (index < size)
	{
		//맵 문자확인
		char mapChracater = buffer[index++];

		//개행 문자처리
		if (mapChracater == '\n')
		{
			//다음 줄로 넘기면서, x좌표 초기화.
			++position.y;
			position.x = 0;

			////@Todo: 테스트용도. 나중에 삭제해야댐.
			//std::cout << "\n";
			continue;
		}

		//각 문자별로 구분해서 처리
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
			//움직이는 객체이기 때문에 땅도 같이 생성
			AddActor(new Ground(position));

			//__Player액터 생성
			AddActor(new Player(position));
			//std::cout << "p";
			break;

		case 'b':
			//움직이는 객체이기 때문에 땅도 같이 생성
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

		//x좌표 증가 처리
		++position.x;
	}

	//버퍼 해제
	delete[] buffer;
 
	//파일 닫기
	fclose(file);
	//while (!feof(file))
	//{
	//	char buffer[256];

	//}
}

bool SokobanLevel::CheckGameClear()
{
	//박스가 타겟 위치에 모두 옮겨졌는지 확인.
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

	//박스와 타겟 액터 위치 비교하기.
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

	return currentScore >= targetScore; //currentScore = targetScore면 true
}

bool SokobanLevel::CanPlayerMove(
	const Vector2& playerPosition, 
	const Vector2& newPosition)
{
	//게임 클리아ㅓ 여부 확인 및 종료 처리
	//박스 처리

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

	//이동하려는 위치에 박스가 있는지 확인

	Box* searchedBox = nullptr;

	for (Box* const boxActor : boxActors)
	{
		if (boxActor->Position() == newPosition)
		{
			searchedBox = boxActor;
			break;
		}
	}

	//이동하려는 위치에 박스가 있는 경우 처리
	if (searchedBox)
	{
		//#1 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인.
		Vector2 direction = newPosition - playerPosition;
		Vector2 nextposition = searchedBox->Position() + direction;

		for (Box* const otherBox : boxActors)
		{
			if (otherBox == searchedBox)
			{
				continue;
			}

			// 박스를 이동시키려는 위치에 다른 박스가 있는지 확인
			if (otherBox->Position() == nextposition)
			{
				//false값 즉 플레이어 이동 못함
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->Position() == nextposition)
			{
				if (actor->As<Wall>())//#2 박스는 없지만, 벽이 있지 않은지 확인
				{
					return false;
				}

				//#3 이동 가능한 경우(그라운드, 타겟)에는 이동처리
				if (actor->As<Ground>() || actor->As<Target>())
				{
					//박스 이동 처리
					searchedBox->SetPosition(nextposition);

					//게임 클리어?
					isGameClear = CheckGameClear();

					//플레이어 이동 가능
					return true;
				}
			}
		}
	}

	//플레이어가 이동하려는 위치에 박스가 없는 겨우
	for (Actor* const actor : actors)
	{
		if (actor->Position() == newPosition)
		{
			//벽이면 이동 불가
			if (actor->As<Wall>())
			{
				return false;
			}

			//그라운드 or 타겟
			return true;
		}
	}

	//예외처리
	return false;
}
