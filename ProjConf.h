#pragma once

/*** システム設定 ***/
//#define DEF_SOUND_VALID			// サウンド有効

/*** ウィンドウ設定 ***/
#define WIN_MAX_X 1000			// ウィンドウの横幅
#define WIN_MAX_Y 850			// ウィンドウの縦幅
#define WIN_POS_X 350			// ウィンドウの初期位置X
#define WIN_POS_Y 200			// ウィンドウの初期位置Y

/*** キーボード設定 ***/
#define DEF_KEY_PRESS_TIME 100	// キーボード長押し回数

/*** FPS設定 ***/
#define MicroSecond 1000000.0f	// 1マイクロ秒
#define MillSecond 1000.0f		// 1ミリ秒
#define WaitTimeMill 3000		// 最大で待てるミリ数
#define GameFPS 60				// 設定したいFPS

/*** ブロックの個数 ***/
#define BLOCK_NUM_X (16)
#define BLOCK_NUM_Y (3)