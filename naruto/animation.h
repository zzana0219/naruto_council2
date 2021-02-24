#pragma once
#include <vector>

class animation
{
public:
	typedef vector<POINT> vFrameList;	//������ ����Ʈ ���� ����
	typedef vector<int> vPlayList;		//�÷��� ����Ʈ ���� ����

private:
	int			_frameNum;		//������ �ѹ�
		
	vFrameList	_frameList;		//�ִϸ��̼� ������ ����Ʈ
	vPlayList	_playList;		//�ִϸ��̼� �÷��� �ε��� ����Ʈ

	int _frameWidth;
	int _frameHeight;

	BOOL _loop;

	float _frameUpdateSec;
	float _elapsedSec;

	DWORD _nowPlayIndex;
	BOOL _play;

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	//����Ʈ �ִϸ��̼� ���
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	//�迭�� �ִϸ��̼� ���
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	//���������Ӻ��� �������ӱ��� ������ �ִϸ��̼� ���
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	//������ ����
	void setFPS(int framePerSec);
	//������ ��� �ӵ� ����
	void frameUpdate(float elapsedTime);

	void start();	//�ִϸ��̼� ���
	void stop();	//�ִϸ��̼� ��ž
	void pause();	//�ִϸ��̼� �Ͻ�����
	void resume();	//�ִϸ��̼� �ٽ����

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }

};

