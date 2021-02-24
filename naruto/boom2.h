#pragma once
#include "gameNode.h"
#include "effect.h"

class boom2 : public gameNode
{
private:
	image* _imageName;			//���� ���� �̹����� ���� �� ����
	RECT	_rc;				//���� ���� ��Ʈ
	effect* _effect;

	int _currentFrameX, _currentFrameY;

	animation* _b;	// ���Ⱥ���
public:
	boom2();
	~boom2();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	inline RECT getRect() { return _rc; }
};

