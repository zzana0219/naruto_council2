#pragma once
#include "gameNode.h"
#include <vector>
#include "hppotion.h"
#include "boom.h"
#include "boom2.h"

class sasuke;

class stage : public gameNode
{
private:
	typedef vector<hppotion*> vPotion;
	typedef vector<hppotion*>::iterator viPotion;
	typedef vector<boom*> vBoom;
	typedef vector<boom*>::iterator viBoom;
	typedef vector<boom2*> vBoom2;
	typedef vector<boom2*>::iterator viBoom2;
private:
	vPotion _vPotion;
	viPotion _viPotion;
	vBoom _vBoom;
	viBoom _viBoom;
	vBoom2 _vBoom2;
	viBoom2 _viBoom2;

	image* virtualMap;
	image* realMap;
	image* qidoriMap;
	image* qidoriMap_2;
	image* lionMap;

	RECT _rc[8];
	RECT _s_rc;

	sasuke* _sasuke;

	int left;
	int top;
	int _alphaValue;
public:
	stage();
	~stage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPotion();
	void setBoom();
	void setBoom2();

	void removePotion(int arrNum);
	void removeBoom(int arrNum);
	void removeBoom2(int arrNum);

	vector<hppotion*> getVPotion() { return _vPotion; }
	vector<hppotion*>::iterator getViPotion() { return _viPotion; }
	vector<boom*> getVBoom() { return _vBoom; }
	vector<boom*>::iterator getViBoom() { return _viBoom; }
	vector<boom2*> getVBoom2() { return _vBoom2; }
	vector<boom2*>::iterator getViBoom2() { return _viBoom2; }

	void collision();

	void setSasukeMemoryAddressLink(sasuke* sasuke) { _sasuke = sasuke; }
	RECT getRect(int i) { return _rc[i]; }
};

