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

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void imageManager();
};

