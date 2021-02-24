#include "stdafx.h"
#include "sasuke.h"
#include "stage.h"
#include "enemyManager.h"

sasuke::sasuke()
{
}

sasuke::~sasuke()
{
}

HRESULT sasuke::init()
{
	_sasuke = IMAGEMANAGER->findImage("사스케_일반");
	_direction = SASUKE_RIGHT_IDLE;

	_rc = RectMakeCenter(300, 900,
						_sasuke->getFrameWidth(),
						_sasuke->getFrameHeight());

	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;


	for (int i = 0; i < 4; i++)
	{
		_currentHP[i] = 150;
		_hp[i] = RectMake(_x - 58, _y - 412, _currentHP[i], 13);
	}

	_lion_1 = IMAGEMANAGER->findImage("사스케_사자련탄_1");
	_lion_2 = IMAGEMANAGER->findImage("사스케_사자련탄_2");
	_qidori_1 = IMAGEMANAGER->findImage("사스케_치도리_1");
	_qidori_2 = IMAGEMANAGER->findImage("사스케_치도리_2");

	// 이미지를 바꾸기 위해 2개로 나눔 (사자련탄)
	_ani1 = new animation;
	_ani1->init(_lion_1->getWidth(), _lion_1->getHeight(),
		_lion_1->getFrameWidth(), _lion_1->getFrameHeight());
	_ani1->setDefPlayFrame(false, false);
	_ani1->setFPS(1);

	// 이미지를 바꾸기 위해 2개로 나눔 (사자련탄)
	_ani2 = new animation;
	_ani2->init(_lion_2->getWidth(), _lion_2->getHeight(),
		_lion_2->getFrameWidth(), _lion_2->getFrameHeight());
	_ani2->setDefPlayFrame(false, false);
	_ani2->setFPS(1);

	// 이미지를 바꾸기 위해 2개로 나눔 (치도리)
	_ani3 = new animation;
	_ani3->init(_qidori_1->getWidth(), _qidori_1->getHeight(),
		_qidori_1->getFrameWidth(), _qidori_1->getFrameHeight());
	_ani3->setDefPlayFrame(false, false);
	_ani3->setFPS(1);

	// 이미지를 바꾸기 위해 2개로 나눔 (치도리)
	_ani4 = new animation;
	_ani4->init(_qidori_2->getWidth(), _qidori_2->getHeight(),
		_qidori_2->getFrameWidth(), _qidori_2->getFrameHeight());
	_ani4->setDefPlayFrame(false, false);
	_ani4->setFPS(1);

	_jumpPower = 0;
	_gravity = 0.3f;
	_motion_time = 0;
	_count_motion = 0;
	_speed = 0;

	_isAttacked = false;
	
	char str[128];

	_f_x = _x + 25;
	_f_y = _y - 25;

	return S_OK;
}

void sasuke::release()
{
}

void sasuke::update()
{
	_gravity = 0.3f;
	sasuke_move();
	sasuke_motion();
	sasuke_location();
	sasuke_skill_ani();
	collision();
	FindEnemy();
	AttackEnemy();
	EatObject();

	//_attack_rc = RectMake(0, 0, 0, 0);
}

void sasuke::render()
{
	// 체력 - 나중에 카메라 따라가게 만들기
	HBRUSH brush = CreateSolidBrush(RGB(255, 50, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
	Rectangle(getMemDC(), _hp[0]);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(brush);
	HBRUSH brush1 = CreateSolidBrush(RGB(255, 100, 0));
	HBRUSH oldBrush1 = (HBRUSH)SelectObject(getMemDC(), brush1);
	Rectangle(getMemDC(), _hp[1]);
	SelectObject(getMemDC(), oldBrush1);
	DeleteObject(brush1);
	HBRUSH brush2 = CreateSolidBrush(RGB(50, 150, 200));
	HBRUSH oldBrush2 = (HBRUSH)SelectObject(getMemDC(), brush2);
	Rectangle(getMemDC(), _hp[2]);
	SelectObject(getMemDC(), oldBrush2);
	DeleteObject(brush2);
	HBRUSH brush3 = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH oldBrush3 = (HBRUSH)SelectObject(getMemDC(), brush3);
	Rectangle(getMemDC(), _hp[3]);
	SelectObject(getMemDC(), oldBrush3);
	DeleteObject(brush3);


	if(!_isStart_Skill_Ani && !_isStart_Qidori_Ani && !_isStart_Skill_Ani_2 && !_isStart_Qidori_Ani_2)
		_sasuke->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	if (_isStart_Skill_Ani)
		_lion_1->aniRender(getMemDC(), _x - 10, _y - 20, _ani1);
	if (_isStart_Skill_Ani_2)
		_lion_2->aniRender(getMemDC(), _x - 10, _y - 25, _ani2);
	if (_isStart_Qidori_Ani)
		_qidori_1->aniRender(getMemDC(), _x - 20, _y - 25, _ani3);
	if(_isStart_Qidori_Ani_2)
		_qidori_2->aniRender(getMemDC(), _x - 20, _y - 25, _ani4);

	Rectangle(getMemDC(), _attack_rc);
}

void sasuke::sasuke_motion()
{
	_count++;
	if (_count % 5 == 0)
	{
		switch (_direction)
		{
		case SASUKE_LEFT_IDLE:	// 왼쪽 서있는 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_일반");
			if (_currentFrameX <= 0) _currentFrameX = 6;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_IDLE:	// 오른쪽 서있는 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_일반");
			if (_currentFrameX >= 5) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_WALK:	// 왼쪽 걷는 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_걷기");
			if (_currentFrameX <= 0) _currentFrameX = 6;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_WALK:	// 오른쪽 걷는 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_걷기");
			if (_currentFrameX >= 5) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_RUN:	// 왼쪽 달리는 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_뛰기");
			if (_currentFrameX <= 0) _currentFrameX = 6;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_RUN:	// 오른쪽 달리는 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_뛰기");
			if (_currentFrameX >= 5) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_JUMP:	// 왼쪽 점프 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_점프");
			if (_currentFrameX <= 0) _currentFrameX = 2;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_JUMP:	// 오른쪽 점프 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_점프");
			if (_currentFrameX >= 1) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_JUMP_DOWN:	// 왼쪽 점프다운 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_점프다운");
			if (_currentFrameX <= 0) _currentFrameX = 2;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_JUMP_DOWN:	// 오른쪽 점프다운 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_점프다운");
			if (_currentFrameX >= 1) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_DOWN:	// 왼쪽 앉는 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_다운");
			_currentFrameX = 0;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			break; 
		case SASUKE_RIGHT_DOWN:	// 오른쪽 앉는 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_다운");
			_currentFrameX = 0;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			break; 
		case SASUKE_LEFT_JUMP_SKILL:	// 왼쪽 스킬점프 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_스킬점프");
			if (_currentFrameX <= -1) _currentFrameX = 7;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			if (_currentFrameX == 0)
			{
				_direction = SASUKE_LEFT_JUMP_DOWN;
			}
			_currentFrameX--;
			break;
		case SASUKE_RIGHT_JUMP_SKILL:	// 오른쪽 스킬점프 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_스킬점프");
			if (_currentFrameX >= 6) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			if (_currentFrameX == 5)
			{
				_direction = SASUKE_RIGHT_JUMP_DOWN;
			}
			_currentFrameX++;
			break;
		case SASUKE_LEFT_ATTACK:	// 왼쪽 공격 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_공격1");
			if (_currentFrameX <= 0) _currentFrameX = 3;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_ATTACK:	// 오른쪽 공격 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_공격1");
			if (_currentFrameX >= 2) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_ATTACK_1:	// 왼쪽 공격 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_공격1");
			if (_currentFrameX <= 0) _currentFrameX = 3;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_ATTACK_1:	// 오른쪽 공격 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_공격1");
			if (_currentFrameX >= 2) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_ATTACK_2:	// 왼쪽 공격2 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_공격2");
			if (_currentFrameX <= 0) _currentFrameX = 4;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_ATTACK_2:	// 오른쪽 공격2 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_공격2");
			if (_currentFrameX >= 3) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_ATTACK_3:	// 왼쪽 공격3 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_공격3");
			if (_currentFrameX <= 0) _currentFrameX = 5;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_ATTACK_3:	// 오른쪽 공격3 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_공격3");
			if (_currentFrameX >= 4) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_GUARD:	// 왼쪽 가드 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_가드");
			_currentFrameX = 0;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			break;
		case SASUKE_RIGHT_GUARD:	// 오른쪽 가드 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_가드");
			_currentFrameX = 0;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			break;
		case SASUKE_LEFT_DEAD:	// 왼쪽 피격 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_죽음");
			if (_currentFrameX <= 0) _currentFrameX = _sasuke->getMaxFrameX();
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_DEAD:	// 오른쪽 피격 모션

			_sasuke = IMAGEMANAGER->findImage("사스케_죽음");
			if (_currentFrameX >= _sasuke->getMaxFrameX()) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		}
		_count = 0;
	}
}

void sasuke::sasuke_move()
{
	// 커맨드 입력을 위한 변수
	if (_count_motion > 0)
	{
		_motion_time++;
	}

	// 피격시 움직이지 않게
	if (!(_isAttacked || _isBossAttacked))
	{
		if (_currentFrameX >= 11 && _direction == SASUKE_RIGHT_DEAD)
		{
			_direction = SASUKE_RIGHT_IDLE;
			_notmove = false;
		}
		if (_currentFrameX <= 0 && _direction == SASUKE_LEFT_DEAD)
		{
			_direction = SASUKE_LEFT_IDLE;
			_notmove = false;
		}
		if (!_notmove)
		{
			// 커맨드 입력을 위해 행동시 정수 배분
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				_count_motion += 1;
				cout << _count_motion << endl;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				_count_motion += 10;
				cout << _count_motion << endl;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				_count_motion += 100;
				cout << _count_motion << endl;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				_count_motion += 1000;
				cout << _count_motion << endl;
			}
			if (KEYMANAGER->isOnceKeyDown('Z'))
			{
				_count_motion += 10000;
				cout << _count_motion << endl;
				// 사자련탄
				if (_skill_time <= 9 && _skill_time > 1)
				{
					cout << "사자련탄" << endl;
					_isStart_Skill_Ani = true;
					_ani1->start();
				}
				// 치도리
				if (_skill_time <= 90 && _skill_time > 10)
				{
					cout << "치도리" << endl;
					_isStart_Qidori_Ani = true;
					_ani3->start();
				}
				// 공격모션 배분
				if (_direction == SASUKE_LEFT_ATTACK_2 && _currentFrameX <= 5)
				{
					_currentFrameX = 5;
					_direction = SASUKE_LEFT_ATTACK_3;
					if (_currentFrameX == 5)
						_attack_rc = RectMake(_x - 5, _y + 25, 5, 5);
				}
				else if (_direction == SASUKE_LEFT_ATTACK_1 && _currentFrameX <= 4)
				{
					_currentFrameX = 4;
					_direction = SASUKE_LEFT_ATTACK_2;
					if (_currentFrameX == 4)
						_attack_rc = RectMake(_x - 5, _y + 25, 5, 5);
				}
				else if (_direction == SASUKE_LEFT_ATTACK && _currentFrameX <= 2)
				{
					_currentFrameX = 3;
					_direction = SASUKE_LEFT_ATTACK_1;
					if (_currentFrameX == 3)
						_attack_rc = RectMake(_x - 5, _y + 25, 5, 5);
				}
				else if (_direction == SASUKE_LEFT_IDLE)
				{
					_currentFrameX = 3;
					_direction = SASUKE_LEFT_ATTACK;
					_attack_rc = RectMake(_x - 5, _y + 25, 5, 5);
				}


				if (_direction == SASUKE_RIGHT_ATTACK_2 && _currentFrameX >= 2)
				{
					_currentFrameX = -1;
					_direction = SASUKE_RIGHT_ATTACK_3;
					_attack_rc = RectMake(_x + 60, _y + 25, 5, 5);
				}
				else if (_direction == SASUKE_RIGHT_ATTACK_1 && _currentFrameX >= 1)
				{
					_currentFrameX = -1;
					_direction = SASUKE_RIGHT_ATTACK_2;
					_attack_rc = RectMake(_x + 60, _y + 25, 5, 5);
				}
				else if (_direction == SASUKE_RIGHT_ATTACK && _currentFrameX >= 0)
				{
					_currentFrameX = -1;
					_direction = SASUKE_RIGHT_ATTACK_1;
					_attack_rc = RectMake(_x + 60, _y + 25, 5, 5);
				}
				else if (_direction == SASUKE_RIGHT_IDLE)
				{
					_currentFrameX = -1;
					_direction = SASUKE_RIGHT_ATTACK;
					_attack_rc = RectMake(_x + 60, _y + 25, 5, 5);
				}

			}
			// 점프모션 
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				if (_count_motion == 100)
				{
					// 점프스킬일경우(방향키 위 + 점프키)
					if (_direction == SASUKE_LEFT_IDLE)
					{
						_direction = SASUKE_LEFT_JUMP_SKILL;
						_currentFrameX = 6;
						_y = _y - 200;
					}
					if (_direction == SASUKE_RIGHT_IDLE)
					{
						_direction = SASUKE_RIGHT_JUMP_SKILL;
						_currentFrameX = -1;
						_y = _y - 200;
					}

				}
				else
				{
					// 일반 점프 경우
					cout << _count_motion << endl;
					if (_direction == SASUKE_LEFT_IDLE)
						_direction = SASUKE_LEFT_JUMP;
					if (_direction == SASUKE_RIGHT_IDLE)
						_direction = SASUKE_RIGHT_JUMP;
					_jumpPower = 8;
					_gravity = 0.3f;
					_isJump = true;
				}
			}
			// 가드 모션
			if (KEYMANAGER->isStayKeyDown('X'))
			{
				if (_direction == SASUKE_LEFT_IDLE || _direction == SASUKE_LEFT_WALK || _direction == SASUKE_LEFT_RUN)
					_direction = SASUKE_LEFT_GUARD;
				if (_direction == SASUKE_RIGHT_IDLE || _direction == SASUKE_RIGHT_WALK || _direction == SASUKE_RIGHT_RUN)
					_direction = SASUKE_RIGHT_GUARD;
			}


			// 왼 달리기 모션 (방향키 2번이면 달리기/ 1번이면 걷기)
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (_isJump && _jumpPower >= 0)
					_direction = SASUKE_LEFT_JUMP;
				else if (_isJump && _jumpPower < 0)
					_direction = SASUKE_LEFT_JUMP_DOWN;
				else if (_count_motion % 10000 == 2)
				{
					_direction = SASUKE_LEFT_RUN;
					_speed = 10;
				}
				else
				{
					_direction = SASUKE_LEFT_WALK;
					_speed = 5;
				}
				_x -= _speed;
			}

			// 오른 달리기 모션 (방향키 2번이면 달리기/ 1번이면 걷기)
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (_isJump && _jumpPower >= 0)
					_direction = SASUKE_RIGHT_JUMP;
				else if (_isJump && _jumpPower < 0)
					_direction = SASUKE_RIGHT_JUMP_DOWN;
				else if (_count_motion % 10000 == 20)
				{
					_direction = SASUKE_RIGHT_RUN;
					_speed = 10;
				}
				else
				{
					_direction = SASUKE_RIGHT_WALK;
					_speed = 5;
				}
				_x += _speed;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				if (_direction == SASUKE_LEFT_IDLE)
					_direction = SASUKE_LEFT_DOWN;
				if (_direction == SASUKE_RIGHT_IDLE)
					_direction = SASUKE_RIGHT_DOWN;
			}

			// 왼쪽으로 방향키 뗄때
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
			{
				if (_motion_time >= 30 || _direction == SASUKE_LEFT_RUN)
				{
					cout << "카운트 모션 " << _count_motion << endl;
					cout << "모션 유지 타임" << _motion_time << endl;
					_count_motion = 0;
					_motion_time = 0;
				}
				_direction = SASUKE_LEFT_IDLE;
			}

			// 오른쪽으로 방향키 뗄때
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				if (_motion_time >= 30 || _direction == SASUKE_RIGHT_RUN)
				{
					cout << "카운트 모션 " << _count_motion << endl;
					cout << "모션 유지 타임" << _motion_time << endl;
					_count_motion = 0;
					_motion_time = 0;
				}
				_direction = SASUKE_RIGHT_IDLE;
			}

			// 방향키 위 키를 놓으면 커멘드입력
			if (KEYMANAGER->isOnceKeyUp(VK_UP))
			{
				_count_motion = 0;
				_motion_time = 0;
				_skill_time += 1;
				_count_skill_motion = 1;
			}

			// 방향키 아래 키를 놓으면 커멘드입력
			if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
			{
				if (_direction == SASUKE_LEFT_DOWN)
					_direction = SASUKE_LEFT_IDLE;
				if (_direction == SASUKE_RIGHT_DOWN)
					_direction = SASUKE_RIGHT_IDLE;
				_count_motion = 0;
				_motion_time = 0;
				_skill_time += 10;
				_count_skill_motion = 1;
			}

			// x키 놓으면 가드 해제
			if (KEYMANAGER->isOnceKeyUp('X'))
			{
				if (_direction == SASUKE_LEFT_GUARD)
					_direction = SASUKE_LEFT_IDLE;
				if (_direction == SASUKE_RIGHT_GUARD)
					_direction = SASUKE_RIGHT_IDLE;
			}
			if (_count_skill_motion > 0)
			{
				_count_skill_motion++;
				if (_count_skill_motion >= 50)
				{
					_count_skill_motion = 0;
					_skill_time = 0;
				}
			}

			// 떨어질때 점프 모션 변화
			if (_direction == SASUKE_LEFT_JUMP && _jumpPower < 0)
				_direction = SASUKE_LEFT_JUMP_DOWN;
			if (_direction == SASUKE_RIGHT_JUMP && _jumpPower < 0)
				_direction = SASUKE_RIGHT_JUMP_DOWN;

			// 3번째 공격모션이면 공격모션 처음으로 리셋
			if (_direction == SASUKE_LEFT_ATTACK_3 && _currentFrameX == 0)
			{
				_direction = SASUKE_LEFT_IDLE;
				_count_motion = 0;
			}
			if (_direction == SASUKE_RIGHT_ATTACK_3 && _currentFrameX == 4)
			{
				_direction = SASUKE_RIGHT_IDLE;
				_count_motion = 0;
			}
			// 공격모션중 z키 연타 안하면 공격모션 처음으로 리셋
			if (_direction == SASUKE_LEFT_ATTACK_2 && _currentFrameX == 0)
				_direction = SASUKE_LEFT_IDLE;
			if (_direction == SASUKE_RIGHT_ATTACK_2 && _currentFrameX == 3)
				_direction = SASUKE_RIGHT_IDLE;
			if (_direction == SASUKE_LEFT_ATTACK_1 && _currentFrameX == 0)
				_direction = SASUKE_LEFT_IDLE;
			if (_direction == SASUKE_RIGHT_ATTACK_1 && _currentFrameX == 2)
				_direction = SASUKE_RIGHT_IDLE;
			if (_direction == SASUKE_LEFT_ATTACK && _currentFrameX == 0)
				_direction = SASUKE_LEFT_IDLE;
			if (_direction == SASUKE_RIGHT_ATTACK && _currentFrameX == 2)
				_direction = SASUKE_RIGHT_IDLE;
		}
	}
	else
	{
		// 잡몹이나 보스에게 피격시 구분
		if(_isAttacked) AttackedMotion();
		if(_isBossAttacked) AttackedBossMotion();

		cout << "맞음" << endl;
		_notmove = true;
		_isAttacked = false;
		_isBossAttacked = false;
	}

	_y -= _jumpPower;
	_jumpPower -= _gravity;

	_rc = RectMake(_x + 10, _y + 5,
		_sasuke->getFrameWidth() - 25,
		_sasuke->getFrameHeight() - 10);

	for (int i = 0; i < 4; i++)
	{
		_hp[i] = RectMake(_x - 58, _y - 412, _currentHP[i], 13);
	}
}

void sasuke::sasuke_location()
{
	// 배경중에 빨간색에는 발을 붙인다.
	for (int i = _y - 50; i < _y + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//만약에 가져온 칼라값이 255면 (빨강)
		if ((r == 255 && g == 0 && b == 0) && _y <= i)
		{
			//플레이어의 Y축은 해당 픽셀값에서 70만큼 뺀다

			if (_direction == SASUKE_LEFT_JUMP || _direction == SASUKE_LEFT_JUMP_DOWN)
				_direction = SASUKE_LEFT_IDLE;
			if (_direction == SASUKE_RIGHT_JUMP || _direction == SASUKE_RIGHT_JUMP_DOWN)
				_direction = SASUKE_RIGHT_IDLE;
			_y = i - _sasuke->getCenterY() / 2 - 64;
			_jumpPower = 0;
			_isJump = false;
			break;
		}

	}

	// 배경중에 파란색에는 점프가 떨어진다.
	for (int i = _x - 10; i < _x + 10; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		// 만약에 가져온 칼라값이 0,0,255면 (파랑)
		if ((r == 0 && g == 0 && b == 255))
		{
			cout << i << endl;

			if (_direction == SASUKE_LEFT_WALK ||
				_direction == SASUKE_LEFT_JUMP ||
				_direction == SASUKE_LEFT_JUMP_DOWN)
				_jumpPower = -1;
			if (_direction == SASUKE_RIGHT_WALK ||
				_direction == SASUKE_RIGHT_JUMP ||
				_direction == SASUKE_RIGHT_JUMP_DOWN)
				_jumpPower = -1;
			break;
		}
	}
}

void sasuke::sasuke_skill_ani()
{
	// 이미지 배분을 위해 플레이를 나눔
	if (!_ani1->isPlay() && _isStart_Skill_Ani)
	{
		if (!_ani2->isPlay())
		{
			MoveToEnemy();
			_ani2->start();
			_isStart_Skill_Ani = false;
			_isStart_Skill_Ani_2 = true;
		}
	}
	if (!_ani2->isPlay())
	{
		_isStart_Skill_Ani_2 = false;
	}
	if (!_ani3->isPlay() && _isStart_Qidori_Ani)
	{
		if (!_ani4->isPlay())
		{
			_ani4->start();
			_isStart_Qidori_Ani = false;
			_isStart_Qidori_Ani_2 = true;
		}
	}
	if (!_ani4->isPlay())
	{
		_isStart_Qidori_Ani_2 = false;
	}

	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani4->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

// 스킬 적중을 위한 적 탐색 (고쳐야함)
void sasuke::FindEnemy()
{
	_find_rc = RectMake(_f_x, _y - 25, 100, 100);
	if (_nofind)
		_f_x += 100;
	else
		_f_x -= 100;
	if (_f_x >= _rc.left + 400)
	{
		_f_x = _x + 25;
		_nofind = false;
	}
	if (_f_x <= _rc.left - 400)
	{
		_f_x = _x + 25;
		_nofind = true;
	}
	Rectangle(getMemDC(), _find_rc);
}

// 스킬 적중을 위한 적에게 순간이동 (고쳐야함)
void sasuke::MoveToEnemy()
{
	for (int j = 0; j < _em->getVMinion1().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_find_rc, &_em->getVMinion1()[j]->getRect()))
		{
			cout << "찾기성공" << endl;
			_x = _em->getVMinion1()[j]->getRect().left - 25;
			//_f_x = _x + 25;
			break;
		}
	}
	for (int j = 0; j < _em->getVMinion2().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_find_rc, &_em->getVMinion2()[j]->getRect()))
		{
			cout << "찾기성공2" << endl;
			_x = _em->getVMinion2()[j]->getRect().left - 25;
			//_f_x = _x + 25;
			break;
		}
	}
	for (int j = 0; j < _em->getVMinion3().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_find_rc, &_em->getVMinion3()[j]->getRect()))
		{
			cout << "찾기성공3" << endl;
			_x = _em->getVMinion3()[j]->getRect().left - 25;
			//_f_x = _x + 25;
			break;
		}
	}
}

// 적 공격시
void sasuke::AttackEnemy()
{
	for (int j = 0; j < _em->getVMinion1().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_attack_rc, &_em->getVMinion1()[j]->getRect()))
		{
			_em->getVMinion1()[j]->hitDamage(50);
			if (_em->getVMinion1()[j]->getCurrentHP() <= 0)
				_em->removeMinion1(j);
			break;
		}
	}
	for (int j = 0; j < _em->getVMinion2().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_attack_rc, &_em->getVMinion2()[j]->getRect()))
		{
			_em->getVMinion2()[j]->hitDamage(50);
			if (_em->getVMinion2()[j]->getCurrentHP() <= 0)
				_em->removeMinion2(j);
			break;
		}
	}
	for (int j = 0; j < _em->getVMinion3().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_attack_rc, &_em->getVMinion3()[j]->getRect()))
		{
			_em->getVMinion3()[j]->hitDamage(50);
			if (_em->getVMinion3()[j]->getCurrentHP() <= 0)
				_em->removeMinion3(j);
			break;
		}
	}
	RECT temp;
	if (IntersectRect(&temp, &_attack_rc, &_em->getBoss()->getRect()))
	{
		_em->getBoss()->hitDamage(50);
		if (_em->getBoss()->getCurrentHP() <= 0)
			_em->getBoss()->setIsDead(true);
	}
}

// 잡몹에게 피격시 모션
void sasuke::AttackedMotion()
{
	// 잡몹1쪽에서 맞을경우
	if (_em->getIsMinion1())
	{
		for (int j = 0; j < _em->getVMinion1().size(); j++)
		{
			if (_em->getVMinion1()[j]->getDirection_1() == ENEMY1_LEFT_IDLE)
			{
				cout << "여기니?" << endl;
				_currentFrameX = 0;
				_direction = SASUKE_RIGHT_DEAD;
				_x -= 30;
				_em->setIsMinion1(false);
			}
			if (_em->getVMinion1()[j]->getDirection_1() == ENEMY1_RIGHT_IDLE)
			{
				cout << "아님 여기?" << endl;
				_currentFrameX = 11;
				_direction = SASUKE_LEFT_DEAD;
				_x += 30;
				_em->setIsMinion1(false);
			}
		}
	}

	// 잡몹2쪽에서 맞을경우
	if (_em->getIsMinion2())
	{
		for (int j = 0; j < _em->getVMinion2().size(); j++)
		{
			if (_em->getVMinion2()[j]->getDirection_2() == ENEMY2_LEFT_IDLE)
			{
				_currentFrameX = 0;
				_direction = SASUKE_RIGHT_DEAD;
				_x -= 30;
				_em->setIsMinion2(false);
			}
			if (_em->getVMinion2()[j]->getDirection_2() == ENEMY2_RIGHT_IDLE)
			{
				_currentFrameX = 11;
				_direction = SASUKE_LEFT_DEAD;
				_x += 30;
				_em->setIsMinion2(false);
			}
		}
	}

	// 잡몹3쪽에서 맞을경우
	if (_em->getIsMinion3())
	{
		for (int j = 0; j < _em->getVMinion3().size(); j++)
		{
			if (_em->getVMinion3()[j]->getDirection_3() == ENEMY3_LEFT_IDLE)
			{
				_currentFrameX = 0;
				_direction = SASUKE_RIGHT_DEAD;
				_x -= 100;
				_em->setIsMinion3(false);
			}
			if (_em->getVMinion3()[j]->getDirection_3() == ENEMY3_RIGHT_IDLE)
			{
				_currentFrameX = 11;
				_direction = SASUKE_LEFT_DEAD;
				_x += 100;
				_em->setIsMinion3(false);
			}
		}
	}
}

// 보스에게 피격시
void sasuke::AttackedBossMotion()
{
	if(_em->getBoss()->getDirection() == BOSS_LEFT_ATTACK_1)
	{
		_currentFrameX = 0;
		_direction = SASUKE_RIGHT_DEAD;
		_x -= 50;
	}
	else if (_em->getBoss()->getDirection() == BOSS_LEFT_ATTACK_2 ||
			_em->getBoss()->getDirection() == BOSS_LEFT_ATTACK_3)
	{
		_currentFrameX = 0;
		_direction = SASUKE_RIGHT_DEAD;
		_x -= 100;
	}

	if (_em->getBoss()->getDirection() == BOSS_RIGHT_ATTACK_1)
	{
		_currentFrameX = 11;
		_direction = SASUKE_LEFT_DEAD;
		_x += 50;
	}
	else if (_em->getBoss()->getDirection() == BOSS_RIGHT_ATTACK_2 ||
		_em->getBoss()->getDirection() == BOSS_RIGHT_ATTACK_3)
	{
		_currentFrameX = 11;
		_direction = SASUKE_LEFT_DEAD;
		_x += 100;
	}
}

// 포션이나 부적을 먹었을 경우
void sasuke::EatObject()
{
	// 물약을 먹었을때 체력을 채움
	for (int j = 0; j < _stage->getVPotion().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_rc, &_stage->getVPotion()[j]->getRect()))
		{
			if (_currentHP[3] > 50) _currentHP[3] = 150;
			else if (_currentHP[3] > 0) _currentHP[3] += 100;
			else if (_currentHP[3] <= 0 && _currentHP[2] > 50)
			{
				_currentHP[3] = 100 - (150 - _currentHP[2]);
				_currentHP[2] = 150;
			}
			else if (_currentHP[2] > 0) _currentHP[2] += 100;
			else if (_currentHP[2] <= 0 && _currentHP[1] > 50)
			{
				_currentHP[2] = 100 - (150 - _currentHP[1]);
				_currentHP[1] = 150;
			}
			else if (_currentHP[1] > 0) _currentHP[1] += 100;
			else if (_currentHP[1] <= 0 && _currentHP[0] > 50)
			{
				_currentHP[1] = 100 - (150 - _currentHP[0]);
				_currentHP[0] = 150;
			}
			else if (_currentHP[0] > 0) _currentHP[0] += 100;

			_stage->removePotion(j);
			break;
		}
	}

	// 폭탄1을 먹었을 경우
	for (int j = 0; j < _stage->getVBoom().size(); j++)
	{
		if (_stage->getVBoom()[j]->getIsBoom())
		{
			RECT temp;
			if (IntersectRect(&temp, &_rc, &_stage->getVBoom()[j]->getRect()))
			{
				if (_direction == SASUKE_RIGHT_JUMP ||
					_direction == SASUKE_RIGHT_WALK ||
					_direction == SASUKE_RIGHT_RUN ||
					_direction == SASUKE_RIGHT_IDLE ||
					_direction == SASUKE_RIGHT_JUMP_DOWN)
				{
					_currentFrameX = 0;
					_direction = SASUKE_RIGHT_DEAD;
					_notmove = true;
					_isAttacked = false;
				}
				if (_direction == SASUKE_LEFT_JUMP ||
					_direction == SASUKE_LEFT_WALK ||
					_direction == SASUKE_LEFT_RUN ||
					_direction == SASUKE_LEFT_IDLE ||
					_direction == SASUKE_LEFT_JUMP_DOWN)
				{
					_currentFrameX = 11;
					_direction = SASUKE_LEFT_DEAD;
					_notmove = true;
					_isAttacked = false;
				}
				_jumpPower = -1;
				_stage->removeBoom(j);
				hitDamage(80);
				_count_motion = 0;
				_motion_time = 0;
				break;
			}
			_stage->removeBoom(j);
		}
	}
	// 폭탄2를 먹었을 경우
	for (int j = 0; j < _stage->getVBoom2().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_rc, &_stage->getVBoom2()[j]->getRect()))
		{
			if (_direction == SASUKE_RIGHT_JUMP ||
				_direction == SASUKE_RIGHT_WALK ||
				_direction == SASUKE_RIGHT_RUN ||
				_direction == SASUKE_RIGHT_IDLE ||
				_direction == SASUKE_RIGHT_JUMP_DOWN)
			{
				_currentFrameX = 0;
				_direction = SASUKE_RIGHT_DEAD;
				_notmove = true;
				_isAttacked = false;
			}
			if (_direction == SASUKE_LEFT_JUMP ||
				_direction == SASUKE_LEFT_WALK ||
				_direction == SASUKE_LEFT_RUN ||
				_direction == SASUKE_LEFT_IDLE ||
				_direction == SASUKE_LEFT_JUMP_DOWN)
			{
				_currentFrameX = 11;
				_direction = SASUKE_LEFT_DEAD;
				_notmove = true;
				_isAttacked = false;
			}
			_jumpPower = -1;
			_stage->removeBoom2(j);
			hitDamage(80);
			_count_motion = 0;
			_motion_time = 0;
			break;
		}
	}
}

// 벽에 닿았을때 멈춰있게
void sasuke::collision()
{
	RECT temp;
	for (int i = 0; i < 8; i++)
	{
		if (IntersectRect(&temp, &_stage->getRect(i), &_rc))
		{
			if (_direction == SASUKE_LEFT_JUMP ||
				_direction == SASUKE_LEFT_WALK ||
				_direction == SASUKE_LEFT_RUN  ||
				_direction == SASUKE_LEFT_IDLE ||
				_direction == SASUKE_LEFT_JUMP_DOWN)
			{
				_x = _stage->getRect(i).right - 10;
			}
			if (_direction == SASUKE_RIGHT_JUMP ||
				_direction == SASUKE_RIGHT_WALK ||
				_direction == SASUKE_RIGHT_RUN  ||
				_direction == SASUKE_RIGHT_IDLE ||
				_direction == SASUKE_RIGHT_JUMP_DOWN)
			{
				_x = _stage->getRect(i).left - 49;
			}
		}
	}
}

// 피격시 체력 소모
void sasuke::hitDamage(float damage)
{
	if (!_isDead)
	{
		if (_hp[0].right - _hp[0].left <= 0)
		{
			cout << "사망" << endl;
			_isDead = true;
		}
		else if (_currentHP[3] <= 0 && _currentHP[2] <= 0 && _currentHP[1] <= 0) _currentHP[0] -= damage;
		else if (_currentHP[3] <= 0 && _currentHP[2] <= 0) _currentHP[1] -= damage;
		else if (_currentHP[3] <= 0) _currentHP[2] -= damage;
		else if (_currentHP[3] >= 0) _currentHP[3] -= damage;
	}
}
