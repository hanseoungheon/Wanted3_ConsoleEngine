#include "DemoLevel.h"
#include "TestActor.h"
#include <iostream>

DemoLevel::DemoLevel()
{
	AddActor(new TestActor());

	// �׽�Ʈ�� �� ���� �б�
	FILE* file = nullptr;

	fopen_s(&file, "../Assets/Map.txt", "rb");

	//����ó��
	if (file == nullptr)
	{
		std::cout << "Failed to Open Map.txt file.\n";
		__debugbreak(); //���� ����� ����ó�� ������(��, ����׸�忡����)
		
		return;
	}

	//���� ũ�� Ȯ��
	fseek(file, 0, SEEK_END);//���� ��ġ(File Position) Ŀ���� ���� ������ �̵�
	size_t fileSize = ftell(file);//�̵��� ������ ��ġ ��ȯ
	fseek(file, 0, SEEK_SET);//���� ��ġ Ŀ�� �ǵ�����
	//rewind(file) //�굵 �Ȱ��� Ŀ�� �ǵ���

	//������ ������ ���� ���� �Ҵ�

	//char* buffer = new char[fileSize + 1];
	char buffer[265] = {};
	while (!feof(file)) //������ ����������� �ݺ�
	{
		//�� �پ� �б�.
		fgets(buffer, 256, file);
		int lineLength = (int)strlen(buffer); //���� ���ڿ��� ���̰� ���ϱ�

		//�Ľ� (Parcing) - �ؼ�
		for (int i = 0; i < lineLength; ++i)
		{
			char mapCharacter = buffer[i];

			switch (mapCharacter)
			{
			case '#':
				std::cout << "#";
				break;

			case '.':
				std::cout << ".";
				break;

			case 'p':
				std::cout << "p";
				break;

			case 'b':
				std::cout << "b";
				break;

			case 't':
				std::cout << "t";
				break;
			}
		}
		//����(����)
		std::cout << '\n';
	}

	fclose(file);


}
