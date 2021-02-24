#pragma once
#include "gameNode.h"
class hppotion : public gameNode
{
private:
	image* _imageName;			//���� ���� �̹����� ���� �� ����
	RECT	_rc;				//���� ���� ��Ʈ

	int _x, _y;
public:
	hppotion();
	~hppotion();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	inline RECT getRect() { return _rc; }
};

