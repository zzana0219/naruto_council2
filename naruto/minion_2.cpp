#include "stdafx.h"
#include "minion_2.h"

// 세부적인 숫자만 다르고 잡몹1이랑 같음
void minion_2::update()
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

	_hpBar->setX(_x + 25);
	_hpBar->setY(_y - 20);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

	_rc = RectMake(_x + 20, _y, _imageName->getFrameWidth() - 35, _imageName->getFrameHeight());
}

void minion_2::move()
{
	_move_count--;
	if (_move_count >= 120)
	{
		_direction_2 = ENEMY2_LEFT_IDLE;
		_x += 0;
	}
	else if (_move_count >= 90)
	{
		_direction_2 = ENEMY2_RIGHT_WALK;
		_x += _speed / 2;
	}
	else if (_move_count >= 60)
	{
		_direction_2 = ENEMY2_RIGHT_IDLE;
		_x += 0;
	}
	else if (_move_count >= 30)
	{
		_direction_2 = ENEMY2_LEFT_WALK;
		_x -= _speed / 2;
	}
	else
	{
		_direction_2 = ENEMY2_LEFT_IDLE;
		_x += 0;
	}

	if (_move_count <= 0)
		_move_count = 150;
}

void minion_2::motion()
{
	_count++;
	if (_count % 8 == 0)
	{
		switch (_direction_2)
		{
		case ENEMY2_RIGHT_IDLE:	// 왼쪽 서있는 모션

			_imageName = IMAGEMANAGER->findImage("잡몹2");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY2_LEFT_IDLE:	// 오른쪽 서있는 모션

			_imageName = IMAGEMANAGER->findImage("잡몹2");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case ENEMY2_RIGHT_WALK:	// 왼쪽 걷는 모션

			_imageName = IMAGEMANAGER->findImage("잡몹2걷기");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY2_LEFT_WALK:	// 오른쪽 걷는 모션

			_imageName = IMAGEMANAGER->findImage("잡몹2걷기");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case ENEMY2_RIGHT_ATTACK:	// 왼쪽 공격 모션

			_imageName = IMAGEMANAGER->findImage("잡몹2공격");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			if (_currentFrameX < 0) _currentFrameX = 0;
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		case ENEMY2_LEFT_ATTACK:	// 오른쪽 공격 모션

			_imageName = IMAGEMANAGER->findImage("잡몹2공격");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			if (_currentFrameX > _imageName->getMaxFrameX())_currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY2_RIGHT_DEAD:	// 왼쪽 공격 모션

			_imageName = IMAGEMANAGER->findImage("잡몹2죽음");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY2_LEFT_DEAD:	// 오른쪽 공격 모션

			_imageName = IMAGEMANAGER->findImage("잡몹2죽음");
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

void minion_2::moveToSasuke()
{
	_direction_2 = ENEMY2_LEFT_WALK;
	_x -= _speed - 3;
}

void minion_2::moveToSasuke_1()
{
	_direction_2 = ENEMY2_RIGHT_WALK;
	_x += _speed - 3;
}

void minion_2::attack()
{
	_count_attack++;
	if (_direction_2 == ENEMY2_LEFT_IDLE && _count_attack >= 100)
	{
		if (!_attackStart)
			_currentFrameX = 5;
		_direction_2 = ENEMY2_LEFT_ATTACK;
		_attackStart = true;
	}
	else if (_direction_2 == ENEMY2_RIGHT_IDLE && _count_attack >= 100)
	{
		if (!_attackStart)
			_currentFrameX = 0;
		_direction_2 = ENEMY2_RIGHT_ATTACK;
		_attackStart = true;
	}

	if (_direction_2 == ENEMY2_LEFT_ATTACK && _currentFrameX <= 0)
	{
		_count_attack = 0;
		_direction_2 = ENEMY2_LEFT_IDLE;
		_attack_rc = RectMake(_rc.left - 15, (_rc.top + _rc.bottom) / 2, 10, 10);
		_attackStart = false;
	}
	else if (_direction_2 == ENEMY2_RIGHT_ATTACK && _currentFrameX >= 4)
	{
		_count_attack = 0;
		_direction_2 = ENEMY2_RIGHT_IDLE;
		_attack_rc = RectMake(_rc.right + 15, (_rc.top + _rc.bottom) / 2, 10, 10);
		_attackStart = false;
	}
}
