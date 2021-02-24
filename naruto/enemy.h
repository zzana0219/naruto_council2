#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum ENEMY1_DIRECTION
{
	ENEMY1_LEFT_IDLE,
	ENEMY1_RIGHT_IDLE,
	ENEMY1_LEFT_WALK,
	ENEMY1_RIGHT_WALK,
	ENEMY1_LEFT_ATTACK,
	ENEMY1_RIGHT_ATTACK,
	ENEMY1_LEFT_ATTACKED,
	ENEMY1_RIGHT_ATTACKED,
	ENEMY1_LEFT_ATTACKED_1,
	ENEMY1_RIGHT_ATTACKED_1,
	ENEMY1_LEFT_DEAD,
	ENEMY1_RIGHT_DEAD
};

enum ENEMY2_DIRECTION
{
	ENEMY2_LEFT_IDLE,
	ENEMY2_RIGHT_IDLE,
	ENEMY2_LEFT_WALK,
	ENEMY2_RIGHT_WALK,
	ENEMY2_LEFT_ATTACK,
	ENEMY2_RIGHT_ATTACK,
	ENEMY2_LEFT_DEAD,
	ENEMY2_RIGHT_DEAD
};

enum ENEMY3_DIRECTION
{
	ENEMY3_LEFT_IDLE,
	ENEMY3_RIGHT_IDLE,
	ENEMY3_LEFT_ATTACK,
	ENEMY3_RIGHT_ATTACK,
	ENEMY3_LEFT_DEAD,
	ENEMY3_RIGHT_DEAD
};

class enemy : public gameNode
{
protected:
	image* _imageName;			//왠지 적의 이미지로 쓰일 것 같다
	image* _imageName_2;
	RECT	_rc;				//왠지 적의 렉트
	RECT	_attack_rc;
	RECT	_h_rc;

	int		_currentFrameX;		//적의 프레임 번호 X
	int		_currentFrameY;		//적의 프레임 번호 Y

	int		_count;				//카운트
	int		_move_count;		//카운트


	float _x, _y;
	float _h_x, _h_y;
	float _speed;

	float _currentHP, _maxHP;

	bool _isFind;
	bool _isLeft;
	bool _isAttack;
	bool _isAttacked;

	progressBar* _hpBar;

	ENEMY1_DIRECTION _direction;
	ENEMY2_DIRECTION _direction_2;
	ENEMY3_DIRECTION _direction_3;

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init(const char* imageName, const char* imageName2, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void draw();
	void motion();
	void moveToSasuke();

	void  hitDamage(float damage) { _currentHP -= damage; }

	inline RECT getRect() { return _rc; }
	inline  int getCurrentHP() { return _currentHP; }
	inline  int getMaxHP() { return _maxHP; }
	void setHP(int hp) { _currentHP = _maxHP = hp; }

	void setFind(bool find) { _isFind = find; }
	bool getFind() { return _isFind; }

	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	void setIsAttack(bool attack) { _isAttack = attack; }
	BOOL getIsAttack() { return _isAttack; }

	RECT getAttackRect() { return _attack_rc; }
	void setAttackRect(RECT rc) { _attack_rc = rc; }
	RECT getHandRect() { return _h_rc; }
	void setHandRect(RECT rc) { _h_rc = rc; }
	void setAttacked(bool attacked) { _isAttacked = attacked; }

	void setDirection_1(ENEMY1_DIRECTION direction) { _direction = direction; }
	void setDirection_2(ENEMY2_DIRECTION direction) { _direction_2 = direction; }
	void setDirection_3(ENEMY3_DIRECTION direction) { _direction_3 = direction; }
	ENEMY1_DIRECTION getDirection_1() { return _direction; }
	ENEMY2_DIRECTION getDirection_2() { return _direction_2; }
	ENEMY3_DIRECTION getDirection_3() { return _direction_3; }
};

