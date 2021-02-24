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

	_ui = IMAGEMANAGER->findImage("�罺��ü��");

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
	//================ ���� �ǵ��� ���� ==============================

	_stage->render();
	_em->render();
	_sasuke->render();

	_ui->render(getMemDC(), _camera.cameraPos().x + 30, _camera.cameraPos().y + 70);

	TIMEMANAGER->render(getMemDC(), _camera.cameraPos().x, _camera.cameraPos().y);
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC(), 0, 0, _camera.cameraPos().x, _camera.cameraPos().y, WINSIZEX, WINSIZEY);
}

void playGround::imageManager()
{
	IMAGEMANAGER->addImage("�浹����",		"image/backmap/ground_2.bmp", 12000, 1100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���",			"image/map/background_2.bmp", 12000, 1100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ڷ�ź���",	"image/backmap/lionbackground.bmp", 800, 600, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�罺��_�Ϲ�",		"image/sasuke/idle.bmp", 0, 0, 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_�ȱ�",		"image/sasuke/walk.bmp", 0, 0, 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_�ٱ�",		"image/sasuke/run.bmp", 0, 0, 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_����",		"image/sasuke/jump.bmp", 0, 0, 128, 128, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_�����ٿ�",	"image/sasuke/jump_down.bmp", 0, 0, 128, 128, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_�ٿ�",		"image/sasuke/sasuke_down.bmp", 0, 0, 64, 128, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_��ų����",   "image/sasuke/sasuke_Jump_up.bmp", 0, 0, 450, 130, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_����",		"image/sasuke/sasuke_dead.bmp", 0, 0, 960, 128, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_����1",		"image/sasuke/Attack_1.bmp", 0, 0, 192, 128, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_����2",		"image/sasuke/Attack_2.bmp", 0, 0, 256, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_����3",		"image/sasuke/Attack_3.bmp", 0, 0, 320, 128, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_����",		"image/sasuke/guard.bmp", 0, 0, 64, 128, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_���ڷ�ź_1", "image/sasuke/sasuke_Skill_1.bmp", 0, 0, 480, 85, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_���ڷ�ź_2", "image/sasuke/sasuke_Skill_2.bmp", 0, 0, 640, 170, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_ġ����_1",	"image/sasuke/qidori.bmp", 0, 0, 665, 190, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�罺��_ġ����_2",	"image/sasuke/qidori_2.bmp", 0, 0, 1320, 95, 11, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���1",		 "image/enemy/1/enemy_1_idle.bmp", 0, 0, 320, 128, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���1����",  "image/enemy/1/enemy_1_Attack.bmp", 0, 0, 320, 128, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���1�ǰ�1", "image/enemy/1/enemy_1_Attacked_0.bmp", 0, 0, 64, 128, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���1�ǰ�2", "image/enemy/1/enemy_1_Attacked_1.bmp", 0, 0, 448, 128, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���1����",  "image/enemy/1/enemy_1_dead.bmp", 0, 0, 192, 128, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���1�ȱ�",  "image/enemy/1/enemy_1_walk.bmp", 0, 0, 192, 128, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���2",		"image/enemy/2/enemy_2_idle.bmp", 0, 0, 400, 140, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���2����", "image/enemy/2/enemy_2_Attack.bmp", 0, 0, 500, 140, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���2����", "image/enemy/2/enemy_2_dead.bmp", 0, 0, 600, 140, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���2�ȱ�", "image/enemy/2/enemy_2_walk.bmp", 0, 0, 500, 140, 5, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���3",		"image/enemy/3/enemy_3_idle.bmp", 0, 0, 280, 140, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���3����", "image/enemy/3/enemy_3_Attack.bmp", 0, 0, 1300, 140, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���3����", "image/enemy/3/enemy_3_dead.bmp", 0, 0, 500, 140, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���3��",	"image/enemy/3/hand.bmp", 0, 0, 160, 80, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("����",		"image/enemy/b/boss_idle.bmp", 0, 0, 256, 170, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������1", "image/enemy/b/boss_Attack_1.bmp", 0, 0, 1200, 170, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������2", "image/enemy/b/boss_Attack_2.bmp", 0, 0, 640, 170, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������3", "image/enemy/b/boss_Attack_3.bmp", 0, 0, 1216, 170, 19, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ǰ�",  "image/enemy/b/boss_Attacked.bmp", 0, 0, 64, 170, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������",  "image/enemy/b/boss_dead.bmp", 0, 0, 425, 170, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����̵�", "image/enemy/b/boss_move.bmp", 0, 0, 450, 170, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų", "image/enemy/b/boss_skill.bmp", 0, 0, 1600, 280, 25, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��", "image/enemy/b/snake.bmp", 0, 0, 1320, 280, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ٶ�", "image/enemy/b/wind.bmp", 0, 0, 990, 220, 9, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�罺��ü��", "image/UI/sasuke_hp.bmp", 281, 92, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ü��", "image/UI/enemy_hp.bmp", 281, 92, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "image/UI/Potion.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ⱥ���", "image/UI/bomb_1.bmp", 0, 0, 125, 35, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ⱥ���2", "image/UI/bomb_2.bmp", 0, 0, 125, 35, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "image/UI/bomb_3.bmp", 0, 0, 300, 60, 6, 1, true, RGB(255, 0, 255));

}