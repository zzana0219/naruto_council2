#pragma once
#include "gameNode.h"
#include "effect.h"

class boom2 : public gameNode
{
private:
	image* _imageName;			//왠지 적의 이미지로 쓰일 것 같다
	RECT	_rc;				//왠지 적의 렉트
	effect* _effect;

	int _currentFrameX, _currentFrameY;

	animation* _b;	// 폭팔부적
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

