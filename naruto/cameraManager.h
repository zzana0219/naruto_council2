#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<imageManager>
{
private:
	POINT pt;		// ������
	int hit_x;		// �ǰݽ� ������ ���� ���� x
	int hit_y;		// �ǰݽ� ������ ���� ���� y ����� �������� ���Ͻø� x�� �����ϰ� ����Ͻø� �˴ϴ�.

	int count;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();


	// �÷��̾� left / top, ȭ�鿡�� ĳ���Ͱ� �����̴� ��ġ (ex) x ��ŭ ������, y ��ŭ �Ʒ��ʿ��� ���� ����Ʈ�� ȭ�� �߾�
	void playerPos(float playerLeft, float playerTop, float x = 0, float y = 0);

	// ��ġ ��ȯ�� �Լ�
	POINT cameraPos();

	// �÷��̾�� ���� �ε����� ������ �Ͼ
	void playerHit(RECT player, RECT enemy);
};
