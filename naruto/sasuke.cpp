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
	_sasuke = IMAGEMANAGER->findImage("�罺��_�Ϲ�");
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

	_lion_1 = IMAGEMANAGER->findImage("�罺��_���ڷ�ź_1");
	_lion_2 = IMAGEMANAGER->findImage("�罺��_���ڷ�ź_2");
	_qidori_1 = IMAGEMANAGER->findImage("�罺��_ġ����_1");
	_qidori_2 = IMAGEMANAGER->findImage("�罺��_ġ����_2");

	// �̹����� �ٲٱ� ���� 2���� ���� (���ڷ�ź)
	_ani1 = new animation;
	_ani1->init(_lion_1->getWidth(), _lion_1->getHeight(),
		_lion_1->getFrameWidth(), _lion_1->getFrameHeight());
	_ani1->setDefPlayFrame(false, false);
	_ani1->setFPS(1);

	// �̹����� �ٲٱ� ���� 2���� ���� (���ڷ�ź)
	_ani2 = new animation;
	_ani2->init(_lion_2->getWidth(), _lion_2->getHeight(),
		_lion_2->getFrameWidth(), _lion_2->getFrameHeight());
	_ani2->setDefPlayFrame(false, false);
	_ani2->setFPS(1);

	// �̹����� �ٲٱ� ���� 2���� ���� (ġ����)
	_ani3 = new animation;
	_ani3->init(_qidori_1->getWidth(), _qidori_1->getHeight(),
		_qidori_1->getFrameWidth(), _qidori_1->getFrameHeight());
	_ani3->setDefPlayFrame(false, false);
	_ani3->setFPS(1);

	// �̹����� �ٲٱ� ���� 2���� ���� (ġ����)
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
	// ü�� - ���߿� ī�޶� ���󰡰� �����
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
		case SASUKE_LEFT_IDLE:	// ���� ���ִ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�Ϲ�");
			if (_currentFrameX <= 0) _currentFrameX = 6;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_IDLE:	// ������ ���ִ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�Ϲ�");
			if (_currentFrameX >= 5) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_WALK:	// ���� �ȴ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�ȱ�");
			if (_currentFrameX <= 0) _currentFrameX = 6;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_WALK:	// ������ �ȴ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�ȱ�");
			if (_currentFrameX >= 5) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_RUN:	// ���� �޸��� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�ٱ�");
			if (_currentFrameX <= 0) _currentFrameX = 6;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_RUN:	// ������ �޸��� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�ٱ�");
			if (_currentFrameX >= 5) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_JUMP:	// ���� ���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����");
			if (_currentFrameX <= 0) _currentFrameX = 2;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_JUMP:	// ������ ���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����");
			if (_currentFrameX >= 1) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_JUMP_DOWN:	// ���� �����ٿ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�����ٿ�");
			if (_currentFrameX <= 0) _currentFrameX = 2;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_JUMP_DOWN:	// ������ �����ٿ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�����ٿ�");
			if (_currentFrameX >= 1) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_DOWN:	// ���� �ɴ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�ٿ�");
			_currentFrameX = 0;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			break; 
		case SASUKE_RIGHT_DOWN:	// ������ �ɴ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_�ٿ�");
			_currentFrameX = 0;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			break; 
		case SASUKE_LEFT_JUMP_SKILL:	// ���� ��ų���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_��ų����");
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
		case SASUKE_RIGHT_JUMP_SKILL:	// ������ ��ų���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_��ų����");
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
		case SASUKE_LEFT_ATTACK:	// ���� ���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����1");
			if (_currentFrameX <= 0) _currentFrameX = 3;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_ATTACK:	// ������ ���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����1");
			if (_currentFrameX >= 2) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_ATTACK_1:	// ���� ���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����1");
			if (_currentFrameX <= 0) _currentFrameX = 3;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_ATTACK_1:	// ������ ���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����1");
			if (_currentFrameX >= 2) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_ATTACK_2:	// ���� ����2 ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����2");
			if (_currentFrameX <= 0) _currentFrameX = 4;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_ATTACK_2:	// ������ ����2 ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����2");
			if (_currentFrameX >= 3) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_ATTACK_3:	// ���� ����3 ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����3");
			if (_currentFrameX <= 0) _currentFrameX = 5;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_ATTACK_3:	// ������ ����3 ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����3");
			if (_currentFrameX >= 4) _currentFrameX = -1;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case SASUKE_LEFT_GUARD:	// ���� ���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����");
			_currentFrameX = 0;
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			break;
		case SASUKE_RIGHT_GUARD:	// ������ ���� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����");
			_currentFrameX = 0;
			_currentFrameY = 0;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			break;
		case SASUKE_LEFT_DEAD:	// ���� �ǰ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����");
			if (_currentFrameX <= 0) _currentFrameX = _sasuke->getMaxFrameX();
			_currentFrameY = 1;
			_sasuke->setFrameY(_currentFrameY);
			_sasuke->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case SASUKE_RIGHT_DEAD:	// ������ �ǰ� ���

			_sasuke = IMAGEMANAGER->findImage("�罺��_����");
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
	// Ŀ�ǵ� �Է��� ���� ����
	if (_count_motion > 0)
	{
		_motion_time++;
	}

	// �ǰݽ� �������� �ʰ�
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
			// Ŀ�ǵ� �Է��� ���� �ൿ�� ���� ���
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
				// ���ڷ�ź
				if (_skill_time <= 9 && _skill_time > 1)
				{
					cout << "���ڷ�ź" << endl;
					_isStart_Skill_Ani = true;
					_ani1->start();
				}
				// ġ����
				if (_skill_time <= 90 && _skill_time > 10)
				{
					cout << "ġ����" << endl;
					_isStart_Qidori_Ani = true;
					_ani3->start();
				}
				// ���ݸ�� ���
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
			// ������� 
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				if (_count_motion == 100)
				{
					// ������ų�ϰ��(����Ű �� + ����Ű)
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
					// �Ϲ� ���� ���
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
			// ���� ���
			if (KEYMANAGER->isStayKeyDown('X'))
			{
				if (_direction == SASUKE_LEFT_IDLE || _direction == SASUKE_LEFT_WALK || _direction == SASUKE_LEFT_RUN)
					_direction = SASUKE_LEFT_GUARD;
				if (_direction == SASUKE_RIGHT_IDLE || _direction == SASUKE_RIGHT_WALK || _direction == SASUKE_RIGHT_RUN)
					_direction = SASUKE_RIGHT_GUARD;
			}


			// �� �޸��� ��� (����Ű 2���̸� �޸���/ 1���̸� �ȱ�)
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

			// ���� �޸��� ��� (����Ű 2���̸� �޸���/ 1���̸� �ȱ�)
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

			// �������� ����Ű ����
			if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
			{
				if (_motion_time >= 30 || _direction == SASUKE_LEFT_RUN)
				{
					cout << "ī��Ʈ ��� " << _count_motion << endl;
					cout << "��� ���� Ÿ��" << _motion_time << endl;
					_count_motion = 0;
					_motion_time = 0;
				}
				_direction = SASUKE_LEFT_IDLE;
			}

			// ���������� ����Ű ����
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				if (_motion_time >= 30 || _direction == SASUKE_RIGHT_RUN)
				{
					cout << "ī��Ʈ ��� " << _count_motion << endl;
					cout << "��� ���� Ÿ��" << _motion_time << endl;
					_count_motion = 0;
					_motion_time = 0;
				}
				_direction = SASUKE_RIGHT_IDLE;
			}

			// ����Ű �� Ű�� ������ Ŀ����Է�
			if (KEYMANAGER->isOnceKeyUp(VK_UP))
			{
				_count_motion = 0;
				_motion_time = 0;
				_skill_time += 1;
				_count_skill_motion = 1;
			}

			// ����Ű �Ʒ� Ű�� ������ Ŀ����Է�
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

			// xŰ ������ ���� ����
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

			// �������� ���� ��� ��ȭ
			if (_direction == SASUKE_LEFT_JUMP && _jumpPower < 0)
				_direction = SASUKE_LEFT_JUMP_DOWN;
			if (_direction == SASUKE_RIGHT_JUMP && _jumpPower < 0)
				_direction = SASUKE_RIGHT_JUMP_DOWN;

			// 3��° ���ݸ���̸� ���ݸ�� ó������ ����
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
			// ���ݸ���� zŰ ��Ÿ ���ϸ� ���ݸ�� ó������ ����
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
		// ����̳� �������� �ǰݽ� ����
		if(_isAttacked) AttackedMotion();
		if(_isBossAttacked) AttackedBossMotion();

		cout << "����" << endl;
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
	// ����߿� ���������� ���� ���δ�.
	for (int i = _y - 50; i < _y + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("�浹����")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//���࿡ ������ Į���� 255�� (����)
		if ((r == 255 && g == 0 && b == 0) && _y <= i)
		{
			//�÷��̾��� Y���� �ش� �ȼ������� 70��ŭ ����

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

	// ����߿� �Ķ������� ������ ��������.
	for (int i = _x - 10; i < _x + 10; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("�浹����")->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		// ���࿡ ������ Į���� 0,0,255�� (�Ķ�)
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
	// �̹��� ����� ���� �÷��̸� ����
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

// ��ų ������ ���� �� Ž�� (���ľ���)
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

// ��ų ������ ���� ������ �����̵� (���ľ���)
void sasuke::MoveToEnemy()
{
	for (int j = 0; j < _em->getVMinion1().size(); j++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_find_rc, &_em->getVMinion1()[j]->getRect()))
		{
			cout << "ã�⼺��" << endl;
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
			cout << "ã�⼺��2" << endl;
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
			cout << "ã�⼺��3" << endl;
			_x = _em->getVMinion3()[j]->getRect().left - 25;
			//_f_x = _x + 25;
			break;
		}
	}
}

// �� ���ݽ�
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

// ������� �ǰݽ� ���
void sasuke::AttackedMotion()
{
	// ���1�ʿ��� �������
	if (_em->getIsMinion1())
	{
		for (int j = 0; j < _em->getVMinion1().size(); j++)
		{
			if (_em->getVMinion1()[j]->getDirection_1() == ENEMY1_LEFT_IDLE)
			{
				cout << "�����?" << endl;
				_currentFrameX = 0;
				_direction = SASUKE_RIGHT_DEAD;
				_x -= 30;
				_em->setIsMinion1(false);
			}
			if (_em->getVMinion1()[j]->getDirection_1() == ENEMY1_RIGHT_IDLE)
			{
				cout << "�ƴ� ����?" << endl;
				_currentFrameX = 11;
				_direction = SASUKE_LEFT_DEAD;
				_x += 30;
				_em->setIsMinion1(false);
			}
		}
	}

	// ���2�ʿ��� �������
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

	// ���3�ʿ��� �������
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

// �������� �ǰݽ�
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

// �����̳� ������ �Ծ��� ���
void sasuke::EatObject()
{
	// ������ �Ծ����� ü���� ä��
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

	// ��ź1�� �Ծ��� ���
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
	// ��ź2�� �Ծ��� ���
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

// ���� ������� �����ְ�
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

// �ǰݽ� ü�� �Ҹ�
void sasuke::hitDamage(float damage)
{
	if (!_isDead)
	{
		if (_hp[0].right - _hp[0].left <= 0)
		{
			cout << "���" << endl;
			_isDead = true;
		}
		else if (_currentHP[3] <= 0 && _currentHP[2] <= 0 && _currentHP[1] <= 0) _currentHP[0] -= damage;
		else if (_currentHP[3] <= 0 && _currentHP[2] <= 0) _currentHP[1] -= damage;
		else if (_currentHP[3] <= 0) _currentHP[2] -= damage;
		else if (_currentHP[3] >= 0) _currentHP[3] -= damage;
	}
}
