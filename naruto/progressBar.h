#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	float _x, _y;
	float _width;

	image* _progressBarFront;		//�տ� ���� ������ �̹���
	image* _progressBarBack;	//�ڿ� �׷��� ������ �̹���

public:
	progressBar() {};
	~progressBar() {};

	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

};

