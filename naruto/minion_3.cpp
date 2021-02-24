#include "stdafx.h"
#include "minion_3.h"

void minion_3::update()
{
	if (!_isFind)
		move();
	else
		attack();

	motion();
	motion_2();

	_hpBar->setX(_x + 10);
	_hpBar->setY(_y - 20);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();

}

void minion_3::render()
{
	draw();
	_hpBar->render();
}

void minion_3::move()
{
	_h_rc = RectMake(0, 0, 0, 0);
	_rc = RectMake(_x + 20, _y, _imageName->getFrameWidth() - 30, _imageName->getFrameHeight());
}

void minion_3::motion()
{
	_count++;
	if (_count % 8 == 0)
	{
		switch (_direction_3)
		{
		case ENEMY3_RIGHT_IDLE:	// 왼쪽 서있는 모션

			_imageName = IMAGEMANAGER->findImage("잡몹3");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY3_LEFT_IDLE:	// 오른쪽 서있는 모션

			_imageName = IMAGEMANAGER->findImage("잡몹3");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;
		
		case ENEMY3_RIGHT_ATTACK:	// 왼쪽 공격 모션

			_imageName = IMAGEMANAGER->findImage("잡몹3공격");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY3_LEFT_ATTACK:	// 오른쪽 공격 모션

			_imageName = IMAGEMANAGER->findImage("잡몹3공격");
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameY = 0;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX++;
			break;

		case ENEMY3_RIGHT_DEAD:	// 왼쪽 피격 모션

			_imageName = IMAGEMANAGER->findImage("잡몹3죽음");
			if (_currentFrameX <= 0) _currentFrameX = _imageName->getMaxFrameX();
			_currentFrameY = 1;
			_imageName->setFrameY(_currentFrameY);
			_imageName->setFrameX(_currentFrameX);

			_currentFrameX--;
			break;
		case ENEMY3_LEFT_DEAD:	// 오른쪽 피격 모션

			_imageName = IMAGEMANAGER->findImage("잡몹3죽음");
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

// 손 발사
void minion_3::motion_2()
{
	_hand_count++;
	if (_hand_count % 10 == 0)
	{
		switch (_hand_direction)
		{
		case LEFT:
			if (_hand_currentFrameX >= _imageName_2->getMaxFrameX()) _hand_currentFrameX = 0;
			_hand_currentFrameY = 0;
			_imageName_2->setFrameY(_hand_currentFrameY);
			_imageName_2->setFrameX(_hand_currentFrameX);

			_hand_currentFrameX++;
			break;
		case RIGHT:
			if (_hand_currentFrameX <= 0) _hand_currentFrameX = _imageName_2->getMaxFrameX();
			_hand_currentFrameY = 1;
			_imageName_2->setFrameY(_hand_currentFrameY);
			_imageName_2->setFrameX(_hand_currentFrameX);

			_hand_currentFrameX--;
			break;
		}
		_hand_count = 0;
	}
}

// 공격 모션
void minion_3::attack()
{
	_count_attack++;
	if (_direction_3 == ENEMY3_LEFT_IDLE && _count_attack >= 100)
	{
		if (!_attackStart)
		{
			_currentFrameX = 0;
			_h_x = _rc.left;
		}
		_direction_3 = ENEMY3_LEFT_ATTACK;
		_hand_direction = LEFT;

		if (_location)
		{
			_h_x -= 4;
			if (_h_x < _rc.left - 200)
				_location = false;
		}
		else
		{
			_h_x += 4;
			if (_h_x > _rc.left)
				_location = true;
		}

		_h_rc = RectMake(_h_x, _h_y + 40, 40, 40);
		_attackStart = true;
	}
	else if (_direction_3 == ENEMY3_RIGHT_IDLE && _count_attack >= 100)
	{
		if (!_attackStart)
		{
			_currentFrameX = 12;
			_h_x = _rc.right;
		}
		_direction_3 = ENEMY3_RIGHT_ATTACK;
		_hand_direction = RIGHT;

		if (!_location)
		{
			_h_x += 4;
			if (_h_x > _rc.right + 200)
				_location = true;
		}
		else
		{
			_h_x -= 4;
			if (_h_x < _rc.right)
				_location = false;
		}

		_h_rc = RectMake(_h_x, _h_y + 40, 40, 40);
		_attackStart = true;
	}

	if (_direction_3 == ENEMY3_LEFT_ATTACK && _currentFrameX >= _imageName->getMaxFrameX())
	{
		_count_attack = 0;
		_direction_3 = ENEMY3_LEFT_IDLE;
		_attackStart = false;

		_h_rc = RectMake(0,0,0,0);
	}
	else if (_direction_3 == ENEMY3_RIGHT_ATTACK && _currentFrameX <= 0)
	{
		_count_attack = 0;
		_direction_3 = ENEMY3_RIGHT_IDLE;
		_attackStart = false;

		_h_rc = RectMake(0, 0, 0, 0);
	}
}

void minion_3::draw()
{
	_imageName->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
	_imageName_2->frameRender(getMemDC(), _h_rc.left, _h_rc.top, _hand_currentFrameX, _hand_currentFrameY);
}
