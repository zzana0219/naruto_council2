﻿#pragma once


#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <iostream>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//==============  매니저들 =============
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "timeManager.h"
#include "effectManager.h"
#include "cameraManager.h"
#include "utils.h"
#include "txtData.h"

using namespace std;
using namespace TFIVE_UTIL;

//==================================
// ## 디파인 문 ## 20.11.12 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("25기 API"))
#define WINSTARTX 50		//윈도우 시작좌표 X지점
#define WINSTARTY 50		//윈도우 시작좌표 Y지점
#define WINSIZEX 800		//윈도우 가로크기
#define WINSIZEY 600		//윈도우 세로크기

#define MAPSIZEX 12000		// 전체 맵	가로크기
#define MAPSIZEY 1100		// 전체 맵	세로크기

#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()


#define SAFE_DELETE(p) {if(p) {delete(p); (p)=NULL;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL;}}

//==================================
// ## extern ## 20.11.16 ##
//==================================

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;