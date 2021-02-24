#include "stdafx.h"
#include "boom.h"

boom::boom()
{
}

boom::~boom()
{
}

HRESULT boom::init()
{
    return S_OK;
}

HRESULT boom::init(const char* imageName, POINT position)
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

	_alphaValue = 255;
	_boom_count_2 = 0;
	_isBoom = false;

    return S_OK;
}

void boom::release()
{
}

void boom::update()
{
	_count++;
	_boom_count++;
	if (_count % 2 == 0)
	{
		if (_currentFrameX >= _imageName->getMaxFrameX())  _currentFrameX = 0;

		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;

		_count = 0;
	}

	// Æ®¸®°Å°¡ trueµÇ¸é ¹ÝÂ¦¹ÝÂ¦
	if (_trigger)
	{
		_boom_count_2++;
		if (_boom_count % 4 == 0)
		{
			_alphaValue = 255;
		}
		else
		{
			_alphaValue = 0;
		}
		if (_boom_count_2 >= 40)
		{
			_isBoom = true;
		}
	}

}

void boom::render()
{
	if (_trigger)
	{
		_imageName->alphaFrameRender(getMemDC(), _rc.left, _rc.top,
			_currentFrameX, _currentFrameY, _alphaValue); 
	}
	else
		_imageName->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}
