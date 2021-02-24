#include "stdafx.h"
#include "boom2.h"

boom2::boom2()
{
}

boom2::~boom2()
{
}

HRESULT boom2::init()
{
    return S_OK;
}

HRESULT boom2::init(const char* imageName, POINT position)
{
	_imageName = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(position.x, position.y,
		_imageName->getFrameWidth(),
		_imageName->getFrameHeight());

	_b = new animation;
	_b->init(_imageName->getWidth(), _imageName->getHeight(),
		_imageName->getFrameWidth(), _imageName->getFrameHeight());
	_b->setDefPlayFrame(false, true);
	_b->setFPS(1);

	_b->start();

    return S_OK;
}

void boom2::release()
{
}

void boom2::update()
{
	_b->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
}

void boom2::render()
{
	//_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	_imageName->aniRender(getMemDC(), _rc.left, _rc.top, _b);
}
