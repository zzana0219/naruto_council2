#pragma once
#include "gameNode.h"
#include "effect.h"

class boom : public gameNode
{
private:
	image* _imageName;			//���� ���� �̹����� ���� �� ����
	RECT	_rc;				//���� ���� ��Ʈ
	effect* _effect;

	int _currentFrameX, _currentFrameY;
	int _count;
	int _boom_count;
	int _boom_count_2;

	animation* _b;	// ���Ⱥ���

	bool _trigger;
	bool _isBoom;

	int _alphaValue;
public:
	boom();
	~boom();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	inline RECT getRect() { return _rc; }
	void setTrigger(bool tr) { _trigger = tr; }
	inline BOOL getIsBoom() { return _isBoom; }
};

