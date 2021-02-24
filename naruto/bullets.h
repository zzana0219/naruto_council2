#pragma once
#include "gameNode.h"
#include <vector>

// �������� ���� ���� ����� �Ⱦ���
struct tagBullet
{
	image* bulletImage;		//�Ѿ��� �̹���
	RECT rc;				//�Ѿ��浹�� ���� ��Ʈ
	float x, y;				//���� ��ǥ
	float angle;			//����
	float radius;			//������
	float speed;			//���ǵ�
	float fireX, fireY;		//�߻���ġ
	bool isFire;			//�߻��ߴ�?
	int count;				//������ �̹��� ī��Ʈ��
};

//�������� �߻��� �� �ִ� �׷��� �Ѿ�
class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;
public:
	bullet() {};
	~bullet() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet()				{ return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};


//�̸� �����صΰ� �߻��ϴ� �Ѿ�
class missile : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;		// ��Ÿ� �� ����


public:
	missile() {};
	~missile() {};

	HRESULT init(int bulletMax, float range);	
	void release();
	void update();
	void render();

	void fire(float x, float y);	//�߻�
				
	void move();					//�̵�
};

//�߻�ɶ� �����Ǵ� �Ѿ�
class rectMissile : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	rectMissile() {};
	~rectMissile() {};

	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);

	void move();

	void removeMissile(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};