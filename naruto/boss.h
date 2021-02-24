#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum SKILL
{
	LEFT_SNAKE,
	RIGHT_SNAKE,
	LEFT_WIND,
	RIGHT_WIND
};

enum BOSS_DIRECTION
{
	BOSS_LEFT_IDLE,
	BOSS_RIGHT_IDLE,
	BOSS_LEFT_WALK,
	BOSS_RIGHT_WALK,
	BOSS_SKILL,
	BOSS_LEFT_ATTACK_1,
	BOSS_RIGHT_ATTACK_1,
	BOSS_LEFT_ATTACK_2,
	BOSS_RIGHT_ATTACK_2,
	BOSS_LEFT_ATTACK_3,
	BOSS_RIGHT_ATTACK_3,
	BOSS_LEFT_ATTACKED,
	BOSS_RIGHT_ATTACKED,
	BOSS_LEFT_DEAD,
	BOSS_RIGHT_DEAD
};
class boss : public gameNode
{
private:
	image* _imageName;			//왠지 적의 이미지로 쓰일 것 같다
	image* _snake;
	image* _wind;

	RECT	_rc;				//왠지 적의 렉트
	RECT	_snake_rc;
	RECT	_wind_rc;
	RECT	_attack_rc;


	int		_currentFrameX;				//적의 프레임 번호 X
	int		_currentFrameY;				//적의 프레임 번호 Y
	int		_skill_currentFrameX;		//적의 프레임 번호 X
	int		_skill_currentFrameY;		//적의 프레임 번호 Y

	int		_count;				//카운트
	int		_move_count;		//카운트
	int		_count_skill;
	int		_count_attacked;

	float _x, _y;
	float _speed;

	float _currentHP, _maxHP;

	bool _isStart;
	bool _isAttacked;
	bool _isSkill;
	bool _isDead;

	progressBar* _hpBar;
	BOSS_DIRECTION _direction;
	SKILL _skill;

public:
	boss();
	~boss();

	virtual HRESULT init();
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void motion();
	void attacked();
	void location();

	void  hitDamage(float damage) { _currentHP -= damage; }


	inline void setRect(RECT rc) { _rc = rc; }
	inline RECT getRect() { return _rc; }
	inline void setSnakeRect(RECT rc) { _snake_rc = rc; }
	inline RECT getSnakeRect() { return _snake_rc; }
	inline void setWindRect(RECT rc) { _wind_rc = rc; }
	inline RECT getWindRect() { return _wind_rc; }
	inline void setAttackRect(RECT rc) { _attack_rc = rc; }
	inline RECT getAttackRect() { return _attack_rc; }

	inline  int getCurrentHP() { return _currentHP; }
	inline  int getMaxHP() { return _maxHP; }
	void setHP(int hp) { _currentHP = _maxHP = hp; }

	int getCurrentFrameX() { return _currentFrameX; };
	void setCurrentFrameX(int currentFrameX) { _currentFrameX = currentFrameX; };
	void setSkillCurrentFrameX(int currentFrameX) { _skill_currentFrameX = currentFrameX; };
	

	void setDirection(BOSS_DIRECTION direction) { _direction = direction; }
	void setSKILL(SKILL skill) { _skill = skill; }
	void setAttacted(bool attacked) { _isAttacked = attacked; }
	BOOL getAttacked() { return _isAttacked; }
	void setIsDead(bool isDead) { _isDead = isDead; }
	BOSS_DIRECTION getDirection() { return _direction; }


	image* getBossImage() { return _imageName; }
};