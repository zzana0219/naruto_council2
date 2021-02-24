#include "stdafx.h"
#include "playGround.h"
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	imageManager();
	gameNode::init(true);

	_ui = IMAGEMANAGER->findImage("사스케체력");

	_stage = new stage;
	_stage->init();
	_stage->setPotion();
	_stage->setBoom();
	_stage->setBoom2();

	_sasuke = new sasuke;
	_sasuke->init();

	_em = new enemyManager;
	_em->init();
	_em->setMinion_1();
	_em->setMinion_2();
	_em->setMinion_3();
	_em->setBoss();

	_em->setSasukeMemoryAddressLink(_sasuke);
	_stage->setSasukeMemoryAddressLink(_sasuke);

	_sasuke->setEnemyMemoryAddressLink(_em);
	_sasuke->setStageMemoryAddressLink(_stage);

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	SAFE_DELETE(_stage);
	SAFE_DELETE(_sasuke);
	SAFE_DELETE(_em);
}

void playGround::update()
{
	gameNode::update();

	_stage->update();
	_sasuke->update();
	_em->update();
	_camera.playerPos(_sasuke->getRectLeft(), _sasuke->getRectTop(), -200, 200);
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	_stage->render();
	_em->render();
	_sasuke->render();

	_ui->render(getMemDC(), _camera.cameraPos().x + 30, _camera.cameraPos().y + 70);

	TIMEMANAGER->render(getMemDC(), _camera.cameraPos().x, _camera.cameraPos().y);
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC(), 0, 0, _camera.cameraPos().x, _camera.cameraPos().y, WINSIZEX, WINSIZEY);
}

void playGround::imageManager()
{
	IMAGEMANAGER->addImage("충돌용배경",		"image/backmap/ground_2.bmp", 12000, 1100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경",			"image/map/background_2.bmp", 12000, 1100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("사자련탄배경",	"image/backmap/lionbackground.bmp", 800, 600, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("사스케_일반",		"image/sasuke/idle.bmp", 0, 0, 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_걷기",		"image/sasuke/walk.bmp", 0, 0, 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_뛰기",		"image/sasuke/run.bmp", 0, 0, 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_점프",		"image/sasuke/jump.bmp", 0, 0, 128, 128, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_점프다운",	"image/sasuke/jump_down.bmp", 0, 0, 128, 128, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_다운",		"image/sasuke/sasuke_down.bmp", 0, 0, 64, 128, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_스킬점프",   "image/sasuke/sasuke_Jump_up.bmp", 0, 0, 450, 130, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_죽음",		"image/sasuke/sasuke_dead.bmp", 0, 0, 960, 128, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_공격1",		"image/sasuke/Attack_1.bmp", 0, 0, 192, 128, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_공격2",		"image/sasuke/Attack_2.bmp", 0, 0, 256, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_공격3",		"image/sasuke/Attack_3.bmp", 0, 0, 320, 128, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_가드",		"image/sasuke/guard.bmp", 0, 0, 64, 128, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_사자련탄_1", "image/sasuke/sasuke_Skill_1.bmp", 0, 0, 480, 85, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_사자련탄_2", "image/sasuke/sasuke_Skill_2.bmp", 0, 0, 640, 170, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_치도리_1",	"image/sasuke/qidori.bmp", 0, 0, 665, 190, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("사스케_치도리_2",	"image/sasuke/qidori_2.bmp", 0, 0, 1320, 95, 11, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("잡몹1",		 "image/enemy/1/enemy_1_idle.bmp", 0, 0, 320, 128, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹1공격",  "image/enemy/1/enemy_1_Attack.bmp", 0, 0, 320, 128, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹1피격1", "image/enemy/1/enemy_1_Attacked_0.bmp", 0, 0, 64, 128, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹1피격2", "image/enemy/1/enemy_1_Attacked_1.bmp", 0, 0, 448, 128, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹1죽음",  "image/enemy/1/enemy_1_dead.bmp", 0, 0, 192, 128, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹1걷기",  "image/enemy/1/enemy_1_walk.bmp", 0, 0, 192, 128, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("잡몹2",		"image/enemy/2/enemy_2_idle.bmp", 0, 0, 400, 140, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹2공격", "image/enemy/2/enemy_2_Attack.bmp", 0, 0, 500, 140, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹2죽음", "image/enemy/2/enemy_2_dead.bmp", 0, 0, 600, 140, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹2걷기", "image/enemy/2/enemy_2_walk.bmp", 0, 0, 500, 140, 5, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("잡몹3",		"image/enemy/3/enemy_3_idle.bmp", 0, 0, 280, 140, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹3공격", "image/enemy/3/enemy_3_Attack.bmp", 0, 0, 1300, 140, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹3죽음", "image/enemy/3/enemy_3_dead.bmp", 0, 0, 500, 140, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("잡몹3손",	"image/enemy/3/hand.bmp", 0, 0, 160, 80, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("보스",		"image/enemy/b/boss_idle.bmp", 0, 0, 256, 170, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스공격1", "image/enemy/b/boss_Attack_1.bmp", 0, 0, 1200, 170, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스공격2", "image/enemy/b/boss_Attack_2.bmp", 0, 0, 640, 170, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스공격3", "image/enemy/b/boss_Attack_3.bmp", 0, 0, 1216, 170, 19, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스피격",  "image/enemy/b/boss_Attacked.bmp", 0, 0, 64, 170, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스죽음",  "image/enemy/b/boss_dead.bmp", 0, 0, 425, 170, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스이동", "image/enemy/b/boss_move.bmp", 0, 0, 450, 170, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("보스스킬", "image/enemy/b/boss_skill.bmp", 0, 0, 1600, 280, 25, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("뱀", "image/enemy/b/snake.bmp", 0, 0, 1320, 280, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("바람", "image/enemy/b/wind.bmp", 0, 0, 990, 220, 9, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("사스케체력", "image/UI/sasuke_hp.bmp", 281, 92, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("적체력", "image/UI/enemy_hp.bmp", 281, 92, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포션", "image/UI/Potion.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폭팔부적", "image/UI/bomb_1.bmp", 0, 0, 125, 35, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폭팔부적2", "image/UI/bomb_2.bmp", 0, 0, 125, 35, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폭팔", "image/UI/bomb_3.bmp", 0, 0, 300, 60, 6, 1, true, RGB(255, 0, 255));

}