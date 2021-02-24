#include "stdafx.h"
#include "minion_1.h"

void minion_1::update()
{
	
	if (!_isFind)
		move();
	else
	{
		if (_isAttack)
			attack();
		else
		{
			_count_attack = 0;
			if (_isLeft)
				moveToSasuke();
			else
				moveToSasuke_1();
		}
	}
	motion();
	location();

	_hpBar->setX(_x + 5);
	_hpBar->setY(_y - 20);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	_rc = RectMake(_x + 15, _y + 10, _imageName->getFrameWidth() - 30, _imageName->getFrameHeight() - 20);
}

// ���1 �Ϲ� ���� ������
void minion_1::move()
{
	_move_count--;
	if (_move_count >= 120)
	{
		_direction = ENEMY1_LEFT_IDLE;
		_x += 0;
	}
	else if (_move_count >= 90)
	{
		_direction = ENEMY1_RIGHT_WALK;
		_x += _speed;
	}
	else if (_move_count >= 60)
	{
		_direction = ENEMY1_RIGHT_IDLE;
		_x += 0;
	}
	else if (_move_count >= 30)
	{
		_direction = ENEMY1_LEFT_WALK;
		_x -= _speed;
	}
	else
	{
		_direction = ENEMY1_LEFT_IDLE;
		_x += 0;
	}

	if (_move_count <= 0)
		_move_count = 150;
}

// ���1 ���
void minion_1::motion()
{
	_count++;
	if (_count % 10 == 0)
	{
		switch (_direction)
		{
		case ENEMY1_RIGHT_IDLE:	// ���� ���ִ� ���

			_imageName = IMAGEMANAGER->findImage("���1");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY1_LEFT_IDLE:	// ������ ���ִ� ���

			_imageName = IMAGEMANAGER->findImage("���1");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case ENEMY1_RIGHT_WALK:	// ���� �ȴ� ���

			_imageName = IMAGEMANAGER->findImage("���1�ȱ�");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY1_LEFT_WALK:	// ������ �ȴ� ���

			_imageName = IMAGEMANAGER->findImage("���1�ȱ�");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;

		case ENEMY1_RIGHT_ATTACK:	// ���� ���� ���

			_imageName = IMAGEMANAGER->findImage("���1����");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY1_LEFT_ATTACK:	// ������ ���� ���

			_imageName = IMAGEMANAGER->findImage("���1����");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case ENEMY1_RIGHT_ATTACKED:	// ���� ���� ���

			_imageName = IMAGEMANAGER->findImage("���1�ǰ�1");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY1_LEFT_ATTACKED:	// ������ ���� ���

			_imageName = IMAGEMANAGER->findImage("���1�ǰ�1");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case ENEMY1_RIGHT_ATTACKED_1:	// ���� ���� ���

			_imageName = IMAGEMANAGER->findImage("���1�ǰ�2");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY1_LEFT_ATTACKED_1:	// ������ ���� ���

			_imageName = IMAGEMANAGER->findImage("���1�ǰ�2");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case ENEMY1_RIGHT_DEAD:	// ���� ���� ���

			_imageName = IMAGEMANAGER->findImage("���1����");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY1_LEFT_DEAD:	// ������ ���� ���

			_imageName = IMAGEMANAGER->findImage("���1����");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		}
		_count = 0;
	}
}

// �������� �� ���̱�
void minion_1::location()
{
	for (int i = _y - 100; i < _y + 100; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("�浹����")->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//���࿡ ������ Į���� 255�� (����)
		if ((r == 255 && g == 0 && b == 0))
		{
			_y = i - 50;
			break;
		}
	}
}

// �÷��̾�� ����
void minion_1::moveToSasuke()
{
	_direction = ENEMY1_LEFT_WALK;
	_x -= _speed - 2;
}

// �÷��̾�� ����
void minion_1::moveToSasuke_1()
{
	_direction = ENEMY1_RIGHT_WALK;
	_x += _speed - 2;
}

// �÷��̾ ���� (���������� ��Ʈ�� ������ �ǰ�Ʈ���Ÿ� ����)
void minion_1::attack()
{
	_count_attack++;
	if (_direction == ENEMY1_LEFT_IDLE && _count_attack >= 100)
	{
		if (!_attackStart)
			_currentFrameX = 0;
		_direction = ENEMY1_LEFT_ATTACK;
		_attackStart = true;
	}
	else if (_direction == ENEMY1_RIGHT_IDLE && _count_attack >= 100)
	{
		if (!_attackStart)
			_currentFrameX = 4;
		_direction = ENEMY1_RIGHT_ATTACK;
		_attackStart = true;
	}

	if (_direction == ENEMY1_LEFT_ATTACK && _currentFrameX >= 4)
	{
		_count_attack = 0; 
		_direction = ENEMY1_LEFT_IDLE;
		_attack_rc = RectMake(_rc.left - 15, (_rc.top + _rc.bottom) / 2, 10, 10);
		_attackStart = false;
	}
	else if (_direction == ENEMY1_RIGHT_ATTACK && _currentFrameX <= 0)
	{
		_count_attack = 0;
		_direction = ENEMY1_RIGHT_IDLE;
		_attack_rc = RectMake(_rc.right + 15, (_rc.top + _rc.bottom) / 2, 10, 10);
		_attackStart = false;
	}
}
