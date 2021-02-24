#pragma once
#include "enemy.h"

enum HAND_DIRECTION
{
	LEFT, 
	RIGHT
};

class minion_3 : public enemy
{
private:
	int _count_attack;
	int _hand_count;
	int _hand_currentFrameX, _hand_currentFrameY;

	bool _attackStart;
	bool _location;

	HAND_DIRECTION _hand_direction;
public:
	virtual void update();
	virtual void render();

	void move();
	void motion();
	void motion_2();

	void attack();

	void draw();
	RECT getRect() { return _rc; }
};