#include "stdafx.h"
#include "boss.h"

boss::boss()
{
}

boss::~boss()
{
}

HRESULT boss::init()
{
	return S_OK;
}

HRESULT boss::init(const char * imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_skill_currentFrameX = _skill_currentFrameY = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);
	_snake = IMAGEMANAGER->findImage("��");
	_wind = IMAGEMANAGER->findImage("�ٶ�");

	_rc = RectMakeCenter(position.x, position.y,
		_imageName->getFrameWidth(),
		_imageName->getFrameHeight());

	_currentHP = _maxHP = 300;

	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;

	_speed = 5;

	_move_count = 150;

	_hpBar = new progressBar;
	_hpBar->init(_rc.left, _rc.top - 20, 52, 10);
	_hpBar->setGauge(_currentHP, _maxHP);

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	motion();
	attacked();
	location();

	_hpBar->setX(_rc.left + 5);
	_hpBar->setY(_rc.top - 20);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();
}

void boss::render()
{
	// ��ġ ����
	if (_direction == BOSS_LEFT_ATTACK_1)
		_imageName->frameRender(getMemDC(), _rc.left - 40, _rc.top + 10, _currentFrameX, _currentFrameY);
	else if (_direction == BOSS_RIGHT_ATTACK_1)
		_imageName->frameRender(getMemDC(), _rc.left, _rc.top + 10, _currentFrameX, _currentFrameY);
	else
		_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);

	_snake->frameRender(getMemDC(), _snake_rc.left, _snake_rc.top, _skill_currentFrameX, _skill_currentFrameY);
	_wind->frameRender(getMemDC(), _wind_rc.left, _wind_rc.top, _skill_currentFrameX, _skill_currentFrameY);

	_hpBar->render();
}

// ���� ��� �Լ�
void boss::motion()
{
	_count++;
	_count_skill++;
	if (_count % 5 == 0)
	{
		switch (_direction)
		{
		case BOSS_RIGHT_IDLE:	// ���� ���ִ� ���

			_imageName = IMAGEMANAGER->findImage("����");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			if (_currentFrameX > _imageName->getMaxFrameX()) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case BOSS_LEFT_IDLE:	// ������ ���ִ� ���

			_imageName = IMAGEMANAGER->findImage("����");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case BOSS_LEFT_WALK:	// ���� �ȴ� ���

			_imageName = IMAGEMANAGER->findImage("�����̵�");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			if (_currentFrameX > _imageName->getMaxFrameX()) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case BOSS_RIGHT_WALK:	// ������ �ȴ� ���

			_imageName = IMAGEMANAGER->findImage("�����̵�");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;

		case BOSS_LEFT_ATTACK_1:	// ���� ���� ���

			_imageName = IMAGEMANAGER->findImage("��������1");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			if (_currentFrameX > _imageName->getMaxFrameX()) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case BOSS_RIGHT_ATTACK_1:	// ������ ���� ���

			_imageName = IMAGEMANAGER->findImage("��������1");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case BOSS_LEFT_ATTACK_2:	// ���� ���� ���

			_imageName = IMAGEMANAGER->findImage("��������2");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			if (_currentFrameX > _imageName->getMaxFrameX()) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case BOSS_RIGHT_ATTACK_2:	// ������ ���� ���

			_imageName = IMAGEMANAGER->findImage("��������2");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case BOSS_LEFT_ATTACK_3:	// ���� ���� ���

			_imageName = IMAGEMANAGER->findImage("��������3");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			if (_currentFrameX > _imageName->getMaxFrameX()) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case BOSS_RIGHT_ATTACK_3:	// ������ ���� ���

			_imageName = IMAGEMANAGER->findImage("��������3");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case BOSS_RIGHT_ATTACKED:	// ������ �ǰ� ���

			_imageName = IMAGEMANAGER->findImage("�����ǰ�");
			_currentFrameX = 0;
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);
			break;
		case BOSS_LEFT_ATTACKED:	// ���� �ǰ� ���

			_imageName = IMAGEMANAGER->findImage("�����ǰ�");
			_currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);
			break;
		case BOSS_RIGHT_DEAD:	// ������ �ǰ�(�ٿ�) ���

			_imageName = IMAGEMANAGER->findImage("��������");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			if (_currentFrameX > _imageName->getMaxFrameX()) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case BOSS_LEFT_DEAD:	// ���� �ǰ�(�ٿ�) ���

			_imageName = IMAGEMANAGER->findImage("��������");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case BOSS_SKILL:	// ��ų ���

			_imageName = IMAGEMANAGER->findImage("������ų");
			if (_currentFrameX >= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		}
		_count = 0;
	}

	if (_count_skill % 5 == 0)
	{
		switch (_skill)
		{
		case RIGHT_SNAKE:	// ������ ��

			_snake = IMAGEMANAGER->findImage("��");
			if (_skill_currentFrameX >= _snake->getMaxFrameX()) _skill_currentFrameX = 0;
			_skill_currentFrameY = 0;
			_snake->setFrameY(_skill_currentFrameY);
			_snake->setFrameX(_skill_currentFrameX);

			_skill_currentFrameX++;
			break;
		case LEFT_SNAKE:	// ���� ��

			_snake = IMAGEMANAGER->findImage("��");
			if (_skill_currentFrameX <= 0) _skill_currentFrameX = _snake->getMaxFrameX();
			if (_skill_currentFrameX > _snake->getMaxFrameX()) _skill_currentFrameX = _snake->getMaxFrameX();
			_skill_currentFrameY = 1;
			_snake->setFrameY(_skill_currentFrameY);
			_snake->setFrameX(_skill_currentFrameX);

			_skill_currentFrameX--;
			break;
		case RIGHT_WIND:	// ������ �ٶ�

			_wind = IMAGEMANAGER->findImage("�ٶ�");
			if (_skill_currentFrameX >= _wind->getMaxFrameX()) _skill_currentFrameX = 0;
			_skill_currentFrameY = 0;
			_wind->setFrameY(_skill_currentFrameY);
			_wind->setFrameX(_skill_currentFrameX);

			_skill_currentFrameX++;
			break;
		case LEFT_WIND:	// ���� �ٶ�

			_wind = IMAGEMANAGER->findImage("�ٶ�");
			if (_skill_currentFrameX <= 0) _skill_currentFrameX = _wind->getMaxFrameX();
			if (_skill_currentFrameX > _wind->getMaxFrameX()) _skill_currentFrameX = _wind->getMaxFrameX();
			_skill_currentFrameY = 1;
			_wind->setFrameY(_skill_currentFrameY);
			_wind->setFrameX(_skill_currentFrameX);

			_skill_currentFrameX--;
			break;
		
		}
	}
}

// ���� �ǰݽ� �Ϲ� �ǰ��� �������� �ְ� �ٿ��� �������� ��������
void boss::attacked()
{
	if (_isAttacked)
	{
		_count_attacked++;

		if ((_direction == BOSS_RIGHT_ATTACKED || _direction == BOSS_LEFT_ATTACKED) && 
			 _count_attacked > 100)
		{
			_isAttacked = false;
			_count_attacked = 0;
		}
		if (_direction == BOSS_RIGHT_DEAD && _currentFrameX <= 0)
		{
			_isAttacked = false;
			_count_attacked = 0;
		}
		if (_direction == BOSS_LEFT_DEAD && _currentFrameX >= 4)
		{
			_isAttacked = false;
			_count_attacked = 0;
		}
	}
}

// �������� �� ���̱�
void boss::location()
{
	for (int i = (_rc.top + _rc.bottom) / 2 - 50; i < (_rc.top + _rc.bottom) / 2 + 50; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("�浹����")->getMemDC(), (_rc.left + _rc.right) / 2, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//���࿡ ������ Į���� 255�� (����)
		if ((r == 255 && g == 0 && b == 0))
		{
			_rc.top = i - 70;
			_rc.bottom = i + 15;
			break;
		}
	}
}
