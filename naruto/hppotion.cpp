#include "stdafx.h"
#include "hppotion.h"

hppotion::hppotion()
{
}

hppotion::~hppotion()
{
}

HRESULT hppotion::init()
{
	return S_OK;
}

HRESULT hppotion::init(const char* imageName, POINT position)
{
	_imageName = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y,
		_imageName->getWidth(),
		_imageName->getHeight());

	_x = position.x;
	_y = position.y;
	return S_OK;
}

void hppotion::release()
{
}

void hppotion::update()
{
}

void hppotion::render()
{
	_imageName->render(getMemDC(), _rc.left, _rc.top);
}
