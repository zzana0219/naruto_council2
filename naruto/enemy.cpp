#include "stdafx.h"
#include "enemy.h"
#include "sasuke.h"


// 잡몹을 위한 위 클래스 (잡몹들 피격 모션 만들어야함)
enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	_currentFrameX = _currentFrameY = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y,
		_imageName->getFrameWidth(),
		_imageName->getFrameHeight());


	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;

	_speed = 5;

	_move_count = 150;

	_hpBar = new progressBar;
	_hpBar->init(_x, _y - 20, 52, 10);
	_hpBar->setGauge(_currentHP, _maxHP);

	return S_OK;
}

HRESULT enemy::init(const char* imageName, const char* imageName2, POINT position)
{
	_currentFrameX = _currentFrameY = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);
	_imageName_2 = IMAGEMANAGER->findImage(imageName2);

	_rc = RectMakeCenter(position.x, position.y,
		_imageName->getFrameWidth(),
		_imageName->getFrameHeight());


	_x = (_rc.left + _rc.right) / 2;
	_y = (_rc.top + _rc.bottom) / 2;

	_h_x = _rc.left;
	_h_y = _rc.top;

	_h_rc = RectMake(_h_x, _h_y + 20, 40, 40);

	_speed = 5;

	_move_count = 150;

	_hpBar = new progressBar;
	_hpBar->init(_x, _y - 20, 52, 10);
	_hpBar->setGauge(_currentHP, _maxHP);

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_count++;

	move();
	motion();

}

void enemy::render()
{
	draw();
	_hpBar->render();
}

void enemy::move()
{
}

void enemy::draw()
{
	_imageName->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);
}
void enemy::motion()
{
}

void enemy::moveToSasuke()
{
}
