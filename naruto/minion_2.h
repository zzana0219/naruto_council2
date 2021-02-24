#pragma once
#include "enemy.h"
class minion_2 : public enemy
{
private:
	int _count_attack;
	bool _attackStart;
public:
	virtual void update();

	void move();
	void motion();

	void moveToSasuke();
	void moveToSasuke_1();

	void attack();
};

