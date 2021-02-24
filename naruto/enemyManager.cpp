#include "stdafx.h"
#include "enemyManager.h"
#include "sasuke.h"

HRESULT enemyManager::init()
{
	count_move_boss = 0;
	count_attack_boss = 1;
	attack_num = 0;
	attacked_count = 0;
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	count_move_boss++;

	for (_viMinion_1 = _vMinion_1.begin(); _viMinion_1 != _vMinion_1.end(); ++_viMinion_1)
	{
		(*_viMinion_1)->update();
	}
	for (_viMinion_2 = _vMinion_2.begin(); _viMinion_2 != _vMinion_2.end(); ++_viMinion_2)
	{
		(*_viMinion_2)->update();
	}
	for (_viMinion_3 = _vMinion_3.begin(); _viMinion_3 != _vMinion_3.end(); ++_viMinion_3)
	{
		(*_viMinion_3)->update();
	}

	_boss->update();
	FindSasuke();

	if (getDistance(_sasuke->getRect().left, 0, _boss->getRect().left, 0) <= 500)
	{
		if (!_isBossAttack)
			BossMoveToSasuke();
		BossAttackSasuke();
	}
	AttackSasuke(); 
	AttackedSasuke();
}

void enemyManager::render()
{
	for (_viMinion_1 = _vMinion_1.begin(); _viMinion_1 != _vMinion_1.end(); ++_viMinion_1)
	{
		(*_viMinion_1)->render();
	}
	for (_viMinion_2 = _vMinion_2.begin(); _viMinion_2 != _vMinion_2.end(); ++_viMinion_2)
	{
		(*_viMinion_2)->render();
	}
	for (_viMinion_3 = _vMinion_3.begin(); _viMinion_3 != _vMinion_3.end(); ++_viMinion_3)
	{
		(*_viMinion_3)->render();
	}

	_boss->render();
}

// 잡몹1 세팅
void enemyManager::setMinion_1()
{
	enemy* mob;
	mob = new minion_1;
	mob->init("잡몹1", PointMake(1200, 885));
	mob->setHP(100);
	_vMinion_1.push_back(mob);

	mob = new minion_1;
	mob->init("잡몹1", PointMake(1250, 885));
	mob->setHP(100);
	_vMinion_1.push_back(mob);

	mob = new minion_1;
	mob->init("잡몹1", PointMake(2500, 885));
	mob->setHP(100);
	_vMinion_1.push_back(mob);

	mob = new minion_1;
	mob->init("잡몹1", PointMake(6300, 620));
	mob->setHP(100);
	_vMinion_1.push_back(mob);

	mob = new minion_1;
	mob->init("잡몹1", PointMake(10100, 940));
	mob->setHP(100);
	_vMinion_1.push_back(mob);
}

// 잡몹2 세팅
void enemyManager::setMinion_2()
{
	enemy* mob;
	mob = new minion_2;
	mob->init("잡몹2", PointMake(1350, 880));
	mob->setHP(300);
	_vMinion_2.push_back(mob);

	mob = new minion_2;
	mob->init("잡몹2", PointMake(1350, 880));
	mob->setHP(300);
	_vMinion_2.push_back(mob);

	mob = new minion_2;
	mob->init("잡몹2", PointMake(2300, 880));
	mob->setHP(300);
	_vMinion_2.push_back(mob);

	mob = new minion_2;
	mob->init("잡몹2", PointMake(1350, 880));
	mob->setHP(300);
	_vMinion_2.push_back(mob);

	mob = new minion_2;
	mob->init("잡몹2", PointMake(10200, 938));
	mob->setHP(300);
	_vMinion_2.push_back(mob);

}

// 잡몹3 세팅
void enemyManager::setMinion_3()
{
	enemy* mob;
	mob = new minion_3;
	mob->init("잡몹3", "잡몹3손", PointMake(1500, 880));
	mob->setHP(200);
	_vMinion_3.push_back(mob);

	mob = new minion_3;
	mob->init("잡몹3", "잡몹3손", PointMake(2400, 880));
	mob->setHP(200);
	_vMinion_3.push_back(mob);

	mob = new minion_3;
	mob->init("잡몹3", "잡몹3손", PointMake(10300, 936));
	mob->setHP(200);
	_vMinion_3.push_back(mob);
}

// 보스 세팅
void enemyManager::setBoss()
{
	_boss = new boss;
	_boss->init("보스", PointMake(11500, 970));
}

// 잡몹 1 삭제
void enemyManager::removeMinion1(int arrNum)
{
	SAFE_DELETE(_vMinion_1[arrNum]);
	_vMinion_1.erase(_vMinion_1.begin() + arrNum);
}

// 잡몹 2 삭제
void enemyManager::removeMinion2(int arrNum)
{
	SAFE_DELETE(_vMinion_2[arrNum]);
	_vMinion_2.erase(_vMinion_2.begin() + arrNum);
}

// 잡몹 3 삭제
void enemyManager::removeMinion3(int arrNum)
{
	SAFE_DELETE(_vMinion_3[arrNum]);
	_vMinion_3.erase(_vMinion_3.begin() + arrNum);
}

// 적들의 플레이어 발견
void enemyManager::FindSasuke()
{
	for (_viMinion_1 = _vMinion_1.begin(); _viMinion_1 != _vMinion_1.end(); ++_viMinion_1)
	{
		if (getDistance(_sasuke->getRect().left, 0, (*_viMinion_1)->getRect().left, 0) <= 50)
		{
			(*_viMinion_1)->setFind(true);
			(*_viMinion_1)->setIsAttack(true);

			if (_sasuke->getRectLeft() <= (*_viMinion_1)->getRect().left)
			{
				(*_viMinion_1)->setDirection_1(ENEMY1_LEFT_IDLE);
				(*_viMinion_1)->setIsLeft(true);
			}
			else
			{
				(*_viMinion_1)->setDirection_1(ENEMY1_RIGHT_IDLE);
				(*_viMinion_1)->setIsLeft(false);
			}
		}
		else if (getDistance(_sasuke->getRect().left, 0, (*_viMinion_1)->getRect().left, 0) <= 300 &&
			(*_viMinion_1)->getIsAttack() == false)
		{
			(*_viMinion_1)->setFind(true);
			if (_sasuke->getRectLeft() <= (*_viMinion_1)->getRect().left)
			{
				(*_viMinion_1)->setDirection_1(ENEMY1_LEFT_IDLE);
				(*_viMinion_1)->setIsLeft(true);
			}
			else
			{
				(*_viMinion_1)->setDirection_1(ENEMY1_RIGHT_IDLE);
				(*_viMinion_1)->setIsLeft(false);
			}
		}
		else
		{
			(*_viMinion_1)->setFind(false);
			(*_viMinion_1)->setIsAttack(false);
		}
	}
	for (_viMinion_2 = _vMinion_2.begin(); _viMinion_2 != _vMinion_2.end(); ++_viMinion_2)
	{
		if (getDistance(_sasuke->getRect().left, 0, (*_viMinion_2)->getRect().left, 0) <= 50)
		{
			(*_viMinion_2)->setFind(true);
			(*_viMinion_2)->setIsAttack(true);

			if (_sasuke->getRectLeft() <= (*_viMinion_2)->getRect().left)
			{
				(*_viMinion_2)->setDirection_2(ENEMY2_LEFT_IDLE);
				(*_viMinion_2)->setIsLeft(true);
			}
			else
			{
				(*_viMinion_2)->setDirection_2(ENEMY2_RIGHT_IDLE);
				(*_viMinion_2)->setIsLeft(false);
			}
		}
		else if (getDistance(_sasuke->getRect().left, 0, (*_viMinion_2)->getRect().left, 0) <= 300 &&
			(*_viMinion_2)->getIsAttack() == false)
		{
			(*_viMinion_2)->setFind(true);
			//bool 반환형인 그 함수가 true면~ 이란 뜻입니당
			if (_sasuke->getRectLeft() <= (*_viMinion_2)->getRect().left)
			{
				(*_viMinion_2)->setDirection_2(ENEMY2_LEFT_IDLE);
				(*_viMinion_2)->setIsLeft(true);
			}
			else
			{
				(*_viMinion_2)->setDirection_2(ENEMY2_RIGHT_IDLE);
				(*_viMinion_2)->setIsLeft(false);
			}
		}
		else
		{
			(*_viMinion_2)->setFind(false);
			(*_viMinion_2)->setIsAttack(false);
		}
	}

	for (_viMinion_3 = _vMinion_3.begin(); _viMinion_3 != _vMinion_3.end(); ++_viMinion_3)
	{
		if (getDistance(_sasuke->getRect().left, 0, (*_viMinion_3)->getRect().left, 0) <= 500)
		{
			(*_viMinion_3)->setFind(true);
			(*_viMinion_3)->setIsAttack(true);

			if (_sasuke->getRectLeft() <= (*_viMinion_3)->getRect().left)
			{
				(*_viMinion_3)->setDirection_3(ENEMY3_LEFT_IDLE);
				(*_viMinion_3)->setIsLeft(true);
			}
			else
			{
				(*_viMinion_3)->setDirection_3(ENEMY3_RIGHT_IDLE);
				(*_viMinion_3)->setIsLeft(false);
			}
		}
		else
		{
			(*_viMinion_3)->setFind(false);
			(*_viMinion_3)->setIsAttack(false);
		}
	}

	if (!_boss->getAttacked())
	{
		if (_sasuke->getRectLeft() <= _boss->getRect().left)
			_boss->setDirection(BOSS_LEFT_IDLE);
		else
			_boss->setDirection(BOSS_RIGHT_IDLE);
	}
}

// 보스가 플레이어에게 움직임
void enemyManager::BossMoveToSasuke()
{
	RECT rc;
	rc = _boss->getRect();

	if (getDistance(_sasuke->getRect().left, _sasuke->getRect().top, _boss->getRect().left, _boss->getRect().top) >= 60)
	{
		if (count_move_boss > 60)
			count_move_boss = 0;
		else if (count_move_boss > 50)
		{
			if (_boss->getDirection() == BOSS_LEFT_IDLE)
			{
				_boss->setDirection(BOSS_LEFT_WALK);

				rc.left -= 5;
				rc.right -= 5;
			}
			else
			{
				_boss->setDirection(BOSS_RIGHT_WALK);

				rc.left += 5;
				rc.right += 5;
			}

			_boss->setRect(rc);
		}
	}
}

// 보스 공격 패턴
void enemyManager::BossAttackSasuke()
{
	if (!_isBossAttack && count_attack_boss >= 1) count_attack_boss++;

	// 공격범위내에있으면 공격모션 랜덤지정
	if (getDistance(_sasuke->getRect().left, _sasuke->getRect().top, _boss->getRect().left, _boss->getRect().top) <= 60 &&
		!_isBossAttack && count_attack_boss > 100)
	{
		_isBossAttack = true;
		attack_num = RND->getFromIntTo(1, 4);
	}

	// 랜덤으로 지정된 공격모션을 실행
	if (_isBossAttack)
	{
		switch (attack_num)
		{
		case 1:
			if (_boss->getDirection() == BOSS_LEFT_IDLE || _boss->getDirection() == BOSS_LEFT_WALK)
			{
				if (_boss->getCurrentFrameX() != _boss->getBossImage()->getMaxFrameX() && !_resetMotion)
				{
					_boss->setCurrentFrameX(11);
					_resetMotion = true;
				}
				_boss->setDirection(BOSS_LEFT_ATTACK_1);				
				_boss->setAttackRect({ _boss->getRect().left - 40,
										_boss->getRect().top +25,
										_boss->getRect().right - 40,
										_boss->getRect().bottom - 25});

			}

			if (_boss->getDirection() == BOSS_RIGHT_IDLE || _boss->getDirection() == BOSS_RIGHT_WALK)
			{
				if (_boss->getCurrentFrameX() != 0 && !_resetMotion)
				{
					_boss->setCurrentFrameX(0);
					_resetMotion = true;
				}
				_boss->setDirection(BOSS_RIGHT_ATTACK_1);
				_boss->setAttackRect({ _boss->getRect().left + 30,
										_boss->getRect().top + 25,
										_boss->getRect().right + 30,
										_boss->getRect().bottom - 25 });
			}

			if (_boss->getCurrentFrameX() == 1 && _boss->getDirection() == BOSS_LEFT_ATTACK_1)
			{
				count_attack_boss = 1;
				_boss->setAttackRect({ 0,0,0,0 });
				_isBossAttack = false;
			}
			else if (_boss->getCurrentFrameX() >= _boss->getBossImage()->getMaxFrameX() && _boss->getDirection() == BOSS_RIGHT_ATTACK_1)
			{
				count_attack_boss = 1;
				_boss->setAttackRect({ 0,0,0,0 });
				_isBossAttack = false;
			}
			break;
		case 2:
			if (_boss->getDirection() == BOSS_LEFT_IDLE || _boss->getDirection() == BOSS_LEFT_WALK)
			{
				if (_boss->getCurrentFrameX() != _boss->getBossImage()->getMaxFrameX() && !_resetMotion)
				{
					_boss->setCurrentFrameX(7);
					_boss->setSkillCurrentFrameX(8);
					_resetMotion = true;
				}
				_boss->setDirection(BOSS_LEFT_ATTACK_2);				
				_boss->setWindRect({ _boss->getRect().left - 90,
										_boss->getRect().top,
										_boss->getRect().right - 90,
										_boss->getRect().bottom });
				_boss->setSKILL(LEFT_WIND);
			}

			if (_boss->getDirection() == BOSS_RIGHT_IDLE || _boss->getDirection() == BOSS_RIGHT_WALK)
			{
				if (_boss->getCurrentFrameX() != 0 && !_resetMotion)
				{
					_boss->setCurrentFrameX(0);
					_boss->setSkillCurrentFrameX(0);
					_resetMotion = true;
				}
				_boss->setDirection(BOSS_RIGHT_ATTACK_2);
				_boss->setWindRect({  _boss->getRect().left + 50,
										_boss->getRect().top,
										_boss->getRect().right + 50,
										_boss->getRect().bottom});
				_boss->setSKILL(RIGHT_WIND);
			}

			if (_boss->getCurrentFrameX() == 1 && _boss->getDirection() == BOSS_LEFT_ATTACK_2)
			{
				count_attack_boss = 1;
				_boss->setWindRect({ 0,0,0,0 });
				_isBossAttack = false;
			}
			else if (_boss->getCurrentFrameX() >= _boss->getBossImage()->getMaxFrameX() && _boss->getDirection() == BOSS_RIGHT_ATTACK_2)
			{
				count_attack_boss = 1;
				_boss->setWindRect({ 0,0,0,0 });
				_isBossAttack = false;
			}
			break;
		case 3:
			if (_boss->getDirection() == BOSS_LEFT_IDLE || _boss->getDirection() == BOSS_LEFT_WALK)
			{
				if (_boss->getCurrentFrameX() != _boss->getBossImage()->getMaxFrameX() && !_resetMotion)
				{
					_boss->setCurrentFrameX(18);
					_boss->setSkillCurrentFrameX(10);
					_resetMotion = true;
				}
				_boss->setDirection(BOSS_LEFT_ATTACK_3);				
				_boss->setSnakeRect({ _boss->getRect().left - 85,
										_boss->getRect().top - 25,
										_boss->getRect().right - 85,
										_boss->getRect().bottom - 25 });
				_boss->setSKILL(LEFT_SNAKE);
			}

			if (_boss->getDirection() == BOSS_RIGHT_IDLE || _boss->getDirection() == BOSS_RIGHT_WALK)
			{
				if (_boss->getCurrentFrameX() != 0 && !_resetMotion)
				{
					_boss->setCurrentFrameX(0);
					_boss->setSkillCurrentFrameX(0);
					_resetMotion = true;
				}
				_boss->setDirection(BOSS_RIGHT_ATTACK_3);
				_boss->setSnakeRect({ _boss->getRect().left + 35,
										_boss->getRect().top - 25,
										_boss->getRect().right + 35,
										_boss->getRect().bottom - 25 });
				_boss->setSKILL(RIGHT_SNAKE);
			}

			if (_boss->getCurrentFrameX() == 1 && _boss->getDirection() == BOSS_LEFT_ATTACK_3)
			{
				count_attack_boss = 1;
				_boss->setSnakeRect({ 0,0,0,0 });
				_isBossAttack = false;
			}
			else if (_boss->getCurrentFrameX() >= _boss->getBossImage()->getMaxFrameX() && _boss->getDirection() == BOSS_RIGHT_ATTACK_3)
			{
				count_attack_boss = 1;
				_boss->setSnakeRect({ 0,0,0,0 });
				_isBossAttack = false;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		_resetMotion = false;
	}
}

// 적 공격시 플레이어는 데미지를 입고 날라간다. 가드시에 공격을 무효화
void enemyManager::AttackSasuke()
{
	RECT temp;
	for (_viMinion_1 = _vMinion_1.begin(); _viMinion_1 != _vMinion_1.end(); ++_viMinion_1)
	{
		if (IntersectRect(&temp, &_sasuke->getRect(), &(*_viMinion_1)->getAttackRect()))
		{
			// 가드시
			if (_sasuke->getDirection() == SASUKE_LEFT_GUARD || _sasuke->getDirection() == SASUKE_RIGHT_GUARD)
			{
			}
			else
			{
				_sasuke->setAttacked(true);
				_sasuke->hitDamage(10);
				_isMinion_1 = true;
			}
			(*_viMinion_1)->setAttackRect(RectMake(0, 0, 0, 0));
		}
	}
	for (_viMinion_2 = _vMinion_2.begin(); _viMinion_2 != _vMinion_2.end(); ++_viMinion_2)
	{
		if (IntersectRect(&temp, &_sasuke->getRect(), &(*_viMinion_2)->getAttackRect()))
		{
			// 가드시
			if (_sasuke->getDirection() == SASUKE_LEFT_GUARD || _sasuke->getDirection() == SASUKE_RIGHT_GUARD)
			{
			}
			else
			{
				_sasuke->setAttacked(true);
				_sasuke->hitDamage(20);
				_isMinion_2 = true;
			}
			(*_viMinion_2)->setAttackRect(RectMake(0, 0, 0, 0));
		}
	}
	for (_viMinion_3 = _vMinion_3.begin(); _viMinion_3 != _vMinion_3.end(); ++_viMinion_3)
	{
		if (IntersectRect(&temp, &_sasuke->getRect(), &(*_viMinion_3)->getHandRect()))
		{
			// 가드시
			if (_sasuke->getDirection() == SASUKE_LEFT_GUARD || _sasuke->getDirection() == SASUKE_RIGHT_GUARD)
			{
			}
			else
			{
				_sasuke->setAttacked(true);
				_sasuke->hitDamage(30);
				_isMinion_3 = true;
			}
			(*_viMinion_3)->setAttackRect(RectMake(0, 0, 0, 0));
		}
	}

	if (IntersectRect(&temp, &_sasuke->getRect(), &_boss->getSnakeRect()))
	{
		// 가드시
		if (_sasuke->getDirection() == SASUKE_LEFT_GUARD || _sasuke->getDirection() == SASUKE_RIGHT_GUARD)
		{
		}
		else
		{
			_sasuke->setBossAttacked(true);
			_sasuke->hitDamage(40);
		}
	}
	if (IntersectRect(&temp, &_sasuke->getRect(), &_boss->getWindRect()))
	{
		// 가드시
		if (_sasuke->getDirection() == SASUKE_LEFT_GUARD || _sasuke->getDirection() == SASUKE_RIGHT_GUARD)
		{
		}
		else
		{
			_sasuke->setBossAttacked(true);
			_sasuke->hitDamage(30);
		}
	}
	if (IntersectRect(&temp, &_sasuke->getRect(), &_boss->getAttackRect()))
	{
		// 가드시
		if (_sasuke->getDirection() == SASUKE_LEFT_GUARD || _sasuke->getDirection() == SASUKE_RIGHT_GUARD)
		{
		}
		else
		{
			_sasuke->setBossAttacked(true);
			_sasuke->hitDamage(25);
		}
	}
}

// 보스가 플레이어한테 피격시 2번은 경직, 3번째에 다운
void enemyManager::AttackedSasuke()
{
	RECT temp;
	RECT rc;
	rc = _boss->getRect();
	if (IntersectRect(&temp, &_sasuke->getAttackRect(), &_boss->getRect()))
	{
		attacked_count++;
		if (_boss->getDirection() == BOSS_RIGHT_IDLE ||
			_boss->getDirection() == BOSS_RIGHT_WALK ||
			_boss->getDirection() == BOSS_RIGHT_ATTACKED ||
			_boss->getDirection() == BOSS_RIGHT_ATTACK_1 ||
			_boss->getDirection() == BOSS_RIGHT_ATTACK_2 ||
			_boss->getDirection() == BOSS_RIGHT_ATTACK_3)
		{
			_boss->setAttacted(true);

			if (attacked_count < 3)
			{
				cout << "emfdha?" << endl;
				_boss->setDirection(BOSS_RIGHT_ATTACKED);
				_boss->setCurrentFrameX(0);
			}
			else
			{
				_boss->setDirection(BOSS_LEFT_DEAD);
				_boss->setCurrentFrameX(0);
				rc.left -= 10;
				rc.right -= 10;
				_boss->setRect(rc);
				attacked_count = 0;
			}
		}
		if (_boss->getDirection() == BOSS_LEFT_IDLE ||
			_boss->getDirection() == BOSS_LEFT_WALK ||
			_boss->getDirection() == BOSS_LEFT_ATTACKED ||
			_boss->getDirection() == BOSS_LEFT_ATTACK_1 ||
			_boss->getDirection() == BOSS_LEFT_ATTACK_2 ||
			_boss->getDirection() == BOSS_LEFT_ATTACK_3)
		{
			_boss->setAttacted(true);

			if (attacked_count < 3)
			{
				_boss->setDirection(BOSS_LEFT_ATTACKED);
				_boss->setCurrentFrameX(0);
			}
			else
			{
				_boss->setDirection(BOSS_RIGHT_DEAD);
				_boss->setCurrentFrameX(4);
				rc.left += 10;
				rc.right += 10;
				_boss->setRect(rc);
				attacked_count = 0;
			}
		}
		_sasuke->setAttackRect({ 0,0,0,0 });
	}
	else
		_sasuke->setAttackRect({ 0,0,0,0 });
}
