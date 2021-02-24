#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "sasuke.h"
#include "stage.h"


class playGround : public gameNode
{
private:
	sasuke* _sasuke;
	enemyManager* _em;
	cameraManager _camera;
	stage* _stage;

	image* _ui;
	image* _ui_2;

	RECT _s_hp[4];

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void imageManager();
};

