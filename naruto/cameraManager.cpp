#include "stdafx.h"
#include "cameraManager.h"



cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}

// 플레이어 left / top, 화면에서 캐릭터가 움직이는 위치 (ex) x 만큼 오른쪽, y 만큼 아래쪽에서 고정 디폴트는 화면 중앙
void cameraManager::playerPos(float playerLeft, float playerTop, float x, float y)
{
	this->pt.x = playerLeft - WINSIZEX / 2 - x;			//카메라 위치 잡기
	this->pt.y = playerTop - WINSIZEY / 2 - y;

	hit_x = pt.x;	// 피격시 진동을 위한 변수
	hit_y = pt.y;

	// 카메라 x축 예외처리
	if (pt.x <= 0) 
		pt.x = 0;
	if (pt.x >= MAPSIZEX - WINSIZEX)  
		pt.x = MAPSIZEX - WINSIZEX;

	// 카메라 y축 예외처리
	if (pt.y <= 0) 
		pt.y = 0;
	if (pt.y >= MAPSIZEY - WINSIZEY)  
		pt.y = MAPSIZEY - WINSIZEY;
}

// 위치 반환용 함수
POINT cameraManager::cameraPos()
{
	return pt;
}

// 플레이어와 적이 부딪히면 진동이 일어남
void cameraManager::playerHit(RECT player, RECT enemy)
{
	RECT temp;

	count++;
	
	if (IntersectRect(&temp, &player, &enemy))
	{
		if (count > 1)
		{
			pt.x = pt.x - 5;
			//pt.y = pt.y - 5; y축 진동을 원하면 사용하시면 됩니다.
			count = 0;
		}
		else
		{
			pt.x = pt.x + 5;
			//pt.y = pt.y + 5;
		}
	}
}
