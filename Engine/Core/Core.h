#pragma once
#pragma warning(disable: 4251) //DLL 외부로 템플릿 내보낼 때 발생하는 경고 끄기
#pragma warning(disable: 4172) //지역변수의 주소를 반환할 때 발생하는 경고 끄기

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if BuildEngineDLL
#define Engine_API __declspec(dllexport)

#else
#define Engine_API __declspec(dllimport)
#endif
