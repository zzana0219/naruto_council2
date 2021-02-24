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
	IMAGEMANAGER->findImage("���")->render(getMemDC());
	//IMAGEMANAGER->findImage("�浹����")->render(getMemDC());


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

// ���� ��ġ ����
void stage::setPotion()
{
	hppotion* _p;
	_p = new hppotion;
	_p->init("����", PointMake(1921, 760));
	_vPotion.push_back(_p);

	_p = new hppotion;
	_p->init("����", PointMake(3136, 760));
	_vPotion.push_back(_p);

	_p = new hppotion;
	_p->init("����", PointMake(5005, 680));
	_vPotion.push_back(_p);

	_p = new hppotion;
	_p->init("����", PointMake(8100, 820));
	_vPotion.push_back(_p);

	_p = new hppotion;
	_p->init("����", PointMake(9252, 820));
	_vPotion.push_back(_p);
}

// ��ź1 ��ġ ����
void stage::setBoom()
{
	boom* _b;
	_b = new boom;
	_b->init("���Ⱥ���", PointMake(1580, 890));
	_vBoom.push_back(_b);

	_b = new boom;
	_b->init("���Ⱥ���", PointMake(4820, 730));
	_vBoom.push_back(_b);

	_b = new boom;
	_b->init("���Ⱥ���", PointMake(6615, 500));
	_vBoom.push_back(_b);

	_b = new boom;
	_b->init("���Ⱥ���", PointMake(7825, 900));
	_vBoom.push_back(_b);

	_b = new boom;
	_b->init("���Ⱥ���", PointMake(9252, 930));
	_vBoom.push_back(_b);
}

// ��ź2 ��ġ ����
void stage::setBoom2()
{
	boom2* _b;
	_b = new boom2;
	_b->init("���Ⱥ���2", PointMake(2360, 880));
	_vBoom2.push_back(_b);

	_b = new boom2;
	_b->init("���Ⱥ���2", PointMake(3865, 680));
	_vBoom2.push_back(_b);

	_b = new boom2;
	_b->init("���Ⱥ���2", PointMake(4820, 770));
	_vBoom2.push_back(_b);

	_b = new boom2;
	_b->init("���Ⱥ���2", PointMake(7825, 950));
	_vBoom2.push_back(_b);

	_b = new boom2;
	_b->init("���Ⱥ���2", PointMake(8305, 450));
	_vBoom2.push_back(_b);
}

// ���� ����
void stage::removePotion(int arrNum)
{
	SAFE_DELETE(_vPotion[arrNum]);
	_vPotion.erase(_vPotion.begin() + arrNum);
}

// ��ź1 ����
void stage::removeBoom(int arrNum)
{
	SAFE_DELETE(_vBoom[arrNum]);
	_vBoom.erase(_vBoom.begin() + arrNum);
}

// ��ź2 ����
void stage::removeBoom2(int arrNum)
{
	SAFE_DELETE(_vBoom2[arrNum]);
	_vBoom2.erase(_vBoom2.begin() + arrNum);
}

// ������ź�� ���� �ε��� ��� Ʈ���� on
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
