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

// �÷��̾� left / top, ȭ�鿡�� ĳ���Ͱ� �����̴� ��ġ (ex) x ��ŭ ������, y ��ŭ �Ʒ��ʿ��� ���� ����Ʈ�� ȭ�� �߾�
void cameraManager::playerPos(float playerLeft, float playerTop, float x, float y)
{
	this->pt.x = playerLeft - WINSIZEX / 2 - x;			//ī�޶� ��ġ ���
	this->pt.y = playerTop - WINSIZEY / 2 - y;

	hit_x = pt.x;	// �ǰݽ� ������ ���� ����
	hit_y = pt.y;

	// ī�޶� x�� ����ó��
	if (pt.x <= 0) 
		pt.x = 0;
	if (pt.x >= MAPSIZEX - WINSIZEX)  
		pt.x = MAPSIZEX - WINSIZEX;

	// ī�޶� y�� ����ó��
	if (pt.y <= 0) 
		pt.y = 0;
	if (pt.y >= MAPSIZEY - WINSIZEY)  
		pt.y = MAPSIZEY - WINSIZEY;
}

// ��ġ ��ȯ�� �Լ�
POINT cameraManager::cameraPos()
{
	return pt;
}

// �÷��̾�� ���� �ε����� ������ �Ͼ
void cameraManager::playerHit(RECT player, RECT enemy)
{
	RECT temp;

	count++;
	
	if (IntersectRect(&temp, &player, &enemy))
	{
		if (count > 1)
		{
			pt.x = pt.x - 5;
			//pt.y = pt.y - 5; y�� ������ ���ϸ� ����Ͻø� �˴ϴ�.
			count = 0;
		}
		else
		{
			pt.x = pt.x + 5;
			//pt.y = pt.y + 5;
		}
	}
}
