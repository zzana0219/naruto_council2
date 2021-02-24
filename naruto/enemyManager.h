#pragma once
#include "gameNode.h"
#include <vector>
#include "minion_1.h"
#include "minion_2.h"
#include "minion_3.h"
#include "boss.h"

class sasuke;

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy1;
	typedef vector<enemy*>::iterator viEnemy1;
	typedef vector<enemy*> vEnemy2;
	typedef vector<enemy*>::iterator viEnemy2;
	typedef vector<enemy*> vEnemy3;
	typedef vector<enemy*>::iterator viEnemy3;


	vEnemy1 _vMinion_1;
	viEnemy1 _viMinion_1;
	vEnemy2 _vMinion_2;
	viEnemy2 _viMinion_2;
	vEnemy3 _vMinion_3;
	viEnemy3 _viMinion_3;

	boss* _boss;
	sasuke* _sasuke;

	int count_move_boss;
	int count_attack_boss; 
	int attack_num;
	int attacked_count;

	bool _isBossAttack;
	bool _resetMotion;
	bool _isMinion_1;
	bool _isMinion_2;
	bool _isMinion_3;

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setMinion_1();
	void setMinion_2();
	void setMinion_3();
	void setBoss();

	void removeMinion1(int arrNum);
	void removeMinion2(int arrNum);
	void removeMinion3(int arrNum);

	vector<enemy*> getVMinion1() { return _vMinion_1; }
	vector<enemy*>::iterator getViMinion1() { return _viMinion_1; }
	vector<enemy*> getVMinion2() { return _vMinion_2; }
	vector<enemy*>::iterator getViMinion2() { return _viMinion_2; }
	vector<enemy*> getVMinion3() { return _vMinion_3; }
	vector<enemy*>::iterator getViMinion3() { return _viMinion_3; }
	boss* getBoss() { return _boss; }

	void setSasukeMemoryAddressLink(sasuke* sasuke) { _sasuke = sasuke; }

	void FindSasuke();
	void BossMoveToSasuke();
	void BossAttackSasuke();
	void AttackSasuke();
	void AttackedSasuke();

	BOOL getIsMinion1() { return _isMinion_1; };
	BOOL getIsMinion2() { return _isMinion_2; };
	BOOL getIsMinion3() { return _isMinion_3; };
	void setIsMinion1(bool _ishe) { _isMinion_1 = _ishe; }
	void setIsMinion2(bool _ishe) { _isMinion_2 = _ishe; }
	void setIsMinion3(bool _ishe) { _isMinion_3 = _ishe; }

	RECT getRect() { return _boss->getRect(); }
};

