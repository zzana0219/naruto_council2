#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

class enemyManager;
class stage;

enum SASUKE_DIRECTION
{
	SASUKE_LEFT_IDLE,
	SASUKE_RIGHT_IDLE,
	SASUKE_LEFT_DOWN,
	SASUKE_RIGHT_DOWN,
	SASUKE_LEFT_WALK,
	SASUKE_RIGHT_WALK,
	SASUKE_LEFT_RUN,
	SASUKE_RIGHT_RUN,
	SASUKE_LEFT_JUMP,
	SASUKE_RIGHT_JUMP,
	SASUKE_LEFT_JUMP_DOWN,
	SASUKE_RIGHT_JUMP_DOWN,
	SASUKE_LEFT_JUMP_SKILL,
	SASUKE_RIGHT_JUMP_SKILL,
	SASUKE_LEFT_ATTACK,
	SASUKE_RIGHT_ATTACK,
	SASUKE_LEFT_ATTACK_1,
	SASUKE_RIGHT_ATTACK_1,
	SASUKE_LEFT_ATTACK_2,
	SASUKE_RIGHT_ATTACK_2,
	SASUKE_LEFT_ATTACK_3,
	SASUKE_RIGHT_ATTACK_3,
	SASUKE_LEFT_DEAD,
	SASUKE_RIGHT_DEAD,
	SASUKE_LEFT_GUARD,
	SASUKE_RIGHT_GUARD,
	SASUKE_SKILL_1,
	SASUKE_SKILL_2, 
	SASUKE_QIDORI_1,
	SASUKE_QIDORI_2
};

class sasuke : public gameNode
{
private:
	image* _sasuke;
	image* _lion_1;
	image* _lion_2;
	image* _qidori_1;
	image* _qidori_2;
	rectMissile* _rm;

	RECT _rc;
	RECT _attack_rc;
	RECT _find_rc;
	RECT _find_rc_2;

	RECT _hp[4];

	char str[128];		// 디버깅

	int _x;
	int _y;
	int _currentFrameX;
	int _currentFrameY;

	float _jumpPower;
	float _gravity;
	float _speed;

	float _currentHP[4];

	int	_count;				//카운트
	int _count_motion;
	int _count_skill_motion;
	int _motion_time;
	int _skill_time;
	int _first_enemy;

	int _f_x;
	int _f_y;

	bool _nofind;
	bool _isDead;
	bool _isJump;
	bool _isAttacked;
	bool _isBossAttacked;
	bool _notmove;
	bool _isStart_Skill_Ani;
	bool _isStart_Qidori_Ani;
	bool _isStart_Skill_Ani_2;
	bool _isStart_Qidori_Ani_2;

	progressBar* _hpBar;

	animation* _ani1;	// 사자련탄 재생용
	animation* _ani2;	// 사자련탄 재생용
	animation* _ani3;	// 치도리 재생용
	animation* _ani4;	// 치도리 재생용

	SASUKE_DIRECTION _direction;

	enemyManager* _em;
	stage* _stage;
public:
	sasuke();
	~sasuke();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void sasuke_motion();
	void sasuke_move();
	void sasuke_location();
	void sasuke_skill_ani();
	void FindEnemy();
	void MoveToEnemy();
	void AttackEnemy();
	void AttackedMotion();
	void AttackedBossMotion();
	void EatObject();


	image* getSasukeImage() { return _sasuke; }
	int getRectLeft() { return _rc.left; }
	int getRectTop() { return _rc.top; }
	RECT getRect() { return _rc; }
	void setRect(RECT rc) { _rc = rc; }
	RECT getHP() { return _hp[0]; }
	void setAttacked(bool attacked) { _isAttacked = attacked; }
	void setBossAttacked(bool attacked) { _isBossAttacked = attacked; }

	SASUKE_DIRECTION getDirection() { return _direction; }
	RECT getAttackRect() { return _attack_rc; }
	void setAttackRect(RECT rc) { _attack_rc = rc; }

	void collision();
	void hitDamage(float damage);

	void setEnemyMemoryAddressLink(enemyManager* em) { _em = em; }
	void setStageMemoryAddressLink(stage* stage) { _stage = stage; }
};