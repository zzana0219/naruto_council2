#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<imageManager>
{
private:
	POINT pt;		// 포인터
	int hit_x;		// 피격시 진동을 위한 변수 x
	int hit_y;		// 피격시 진동을 위한 변수 y 사용은 안했지만 원하시면 x와 동일하게 사용하시면 됩니다.

	int count;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();


	// 플레이어 left / top, 화면에서 캐릭터가 움직이는 위치 (ex) x 만큼 오른쪽, y 만큼 아래쪽에서 고정 디폴트는 화면 중앙
	void playerPos(float playerLeft, float playerTop, float x = 0, float y = 0);

	// 위치 반환용 함수
	POINT cameraPos();

	// 플레이어와 적이 부딪히면 진동이 일어남
	void playerHit(RECT player, RECT enemy);
};
