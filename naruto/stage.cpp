#include "stdafx.h"
#include "stage.h"
#include "sasuke.h"

stage::stage()
{

}

stage::~stage()
{
}

HRESULT stage::init()
{
	_rc[0] = { 0, 454, 7, 1001 };
	_rc[1] = { 3826, 805, 3885, 1001 };
	_rc[2] = { 5173, 585, 5244, 915 };
	_rc[3] = { 7571, 529, 7651, 1094 };
	_rc[4] = { 8018, 940, 8091, 1094 };
	_rc[5] = { 8226, 568, 8292, 869 };
	_rc[6] = { 8509, 631, 8585, 1058 };
	_rc[7] = { 11991, 460, 12000, 1058 };

	_alphaValue = 255;

    return S_OK;
}

void stage::release()
{
}

void stage::update()
{
	collision();

	for (_viPotion = _vPotion.begin(); _viPotion != _vPotion.end(); ++_viPotion)
	{
		(*_viPotion)->update();
	}
	for (_viBoom = _vBoom.begin(); _viBoom != _vBoom.end(); ++_viBoom)
	{
		(*_viBoom)->update();
	}	
	for (_viBoom2 = _vBoom2.begin(); _viBoom2 != _vBoom2.end(); ++_viBoom2)
	{
		(*_viBoom2)->update();
	}
}

void stage::render()
{
	IMAGEMANAGER->findImage("硅版")->render(getMemDC());
	//IMAGEMANAGER->findImage("面倒侩硅版")->render(getMemDC());


	for (_viPotion = _vPotion.begin(); _viPotion != _vPotion.end(); ++_viPotion)
	{
		(*_viPotion)->render();
	}
	for (_viBoom = _vBoom.begin(); _viBoom != _vBoom.end(); ++_viBoom)
	{
		(*_viBoom)->render();
	}
	for (_viBoom2 = _vBoom2.begin(); _viBoom2 != _vBoom2.end(); ++_viBoom2)
	{
		(*_viBoom2)->render();
	}

	for (int i = 0; i < 8; i++)
	{
		Rectangle(getMemDC(), _rc[i]);
	}
}

// 器记 困摹 汲沥
void stage::setPotion()
{
	hppotion* _p;
	_p = new hppotion;
	_p->init("器记", PointMake(1921, 760));
	_vPotion.push_back(_p);

	_p = new hppotion;
	_p->init("器记", PointMake(3136, 760));
	_vPotion.push_back(_p);

	_p = new hppotion;
	_p->init("器记", PointMake(5005, 680));
	_vPotion.push_back(_p);

	_p = new hppotion;
	_p->init("器记", PointMake(8100, 820));
	_vPotion.push_back(_p);

	_p = new hppotion;
	_p->init("器记", PointMake(9252, 820));
	_vPotion.push_back(_p);
}

// 气藕1 困摹 汲沥
void stage::setBoom()
{
	boom* _b;
	_b = new boom;
	_b->init("气迫何利", PointMake(1580, 890));
	_vBoom.push_back(_b);

	_b = new boom;
	_b->init("气迫何利", PointMake(4820, 730));
	_vBoom.push_back(_b);

	_b = new boom;
	_b->init("气迫何利", PointMake(6615, 500));
	_vBoom.push_back(_b);

	_b = new boom;
	_b->init("气迫何利", PointMake(7825, 900));
	_vBoom.push_back(_b);

	_b = new boom;
	_b->init("气迫何利", PointMake(9252, 930));
	_vBoom.push_back(_b);
}

// 气藕2 困摹 汲沥
void stage::setBoom2()
{
	boom2* _b;
	_b = new boom2;
	_b->init("气迫何利2", PointMake(2360, 880));
	_vBoom2.push_back(_b);

	_b = new boom2;
	_b->init("气迫何利2", PointMake(3865, 680));
	_vBoom2.push_back(_b);

	_b = new boom2;
	_b->init("气迫何利2", PointMake(4820, 770));
	_vBoom2.push_back(_b);

	_b = new boom2;
	_b->init("气迫何利2", PointMake(7825, 950));
	_vBoom2.push_back(_b);

	_b = new boom2;
	_b->init("气迫何利2", PointMake(8305, 450));
	_vBoom2.push_back(_b);
}

// 器记 昏力
void stage::removePotion(int arrNum)
{
	SAFE_DELETE(_vPotion[arrNum]);
	_vPotion.erase(_vPotion.begin() + arrNum);
}

// 气藕1 昏力
void stage::removeBoom(int arrNum)
{
	SAFE_DELETE(_vBoom[arrNum]);
	_vBoom.erase(_vBoom.begin() + arrNum);
}

// 气藕2 昏力
void stage::removeBoom2(int arrNum)
{
	SAFE_DELETE(_vBoom2[arrNum]);
	_vBoom2.erase(_vBoom2.begin() + arrNum);
}

// 矫茄气藕俊 个阑 何碟鳃 版快 飘府芭 on
void stage::collision()
{
	RECT temp;
	for (_viBoom = _vBoom.begin(); _viBoom != _vBoom.end(); ++_viBoom)
	{
		if (IntersectRect(&temp, &_sasuke->getRect(), &(*_viBoom)->getRect()))
		{
			(*_viBoom)->setTrigger(true);
		}
	}
}
