#pragma once
#include "gameNode.h"
class hppotion : public gameNode
{
private:
	image* _imageName;			//왠지 적의 이미지로 쓰일 것 같다
	RECT	_rc;				//왠지 적의 렉트

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

