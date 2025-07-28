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
	fopen_s(&file, filepath, "rb");

	//예외처리

	if (file == nullptr)
	{
		std::cout << "맵 파일 읽기 실패! : " << filename ;
		__debugbreak();
		return;
	}

	//파싱(Parcing)하기 -> 파싱 = 구문분석,해석
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	//확인한 파일 크기를 활용해 버퍼 할당.
	char* buffer = new char[fileSize + 1];
	buffer[fileSize] = '\0';
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize\n";
	}

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

			//@Todo: 테스트용도. 나중에 삭제해야댐.
			std::cout << "\n";
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
