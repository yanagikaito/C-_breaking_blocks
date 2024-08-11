/*** Header File ***/
#include "DxLib.h"
#include "ProjConf.h"
#include "Sub.h"
#include "Ract.h"

// ブロック定義
Ract Block[BLOCK_NUM_X][BLOCK_NUM_Y];

// バー定義
Ract Bar;

// ゲームの変数を初期化する関数
void Game_Ini() {

	// ブロックに関する変数初期化
	for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
		for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
			Block[x][y] = {
				// 幅が100
				x * 100 ,
				100 + y * 50,
				100,
				// 高さが50
				50,
				// ボールが全て存在する
				TRUE };
		}
	}

	// バーに関する変数初期化
	Bar = { 700,700,200,30 };
}

// ゲームを計算する関数
void Game_Cal() {

	}
// ゲームを描画する関数
void Game_Draw() {

	}

// ゲームオーバー時の処理を行う関数
void Game_End() {

}
// プログラムは WinMain から始まります
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_  HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, 
	_In_ int nShowCmd)
{
	Col color;
	ChangeWindowMode(TRUE);							// ウィンドウモードで起動
	if (DxLib_Init() == -1)							// ＤＸライブラリ初期化処理
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	/*** Window Init ***/
	SetWindowText("ブロック崩し");					// ウィンドウのタイトル
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);	// ウィンドウの位置
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);			// ウィンドウのサイズ
	SetBackgroundColor(255, 255, 255);				// ウィンドウの背景色
	SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏画面にする
	SetAlwaysRunFlag(TRUE);							// ウインドウ非アクティブ状態でも処理を続行する

	Game_Ini();

	/*** FPS初期化 ***/
	Fps.FPSInit();

	/*** Read ***/
	Col();
	Fon.Read();
#ifdef DEF_SOUND_VALID
	Snd.Read();

	/*** BGM開始 ***/
	PlaySoundMem(Snd.BgmSound, DX_PLAYTYPE_LOOP);
#endif /* DEF_SOUND_VALID */

	/*** ループ処理 ***/
	while (ScreenFlip() == 0 &&		// 裏画面の内容を表画面に反映
		ClearDrawScreen() == 0 &&	// 画面を初期化
		Key.GetKey() == 0 &&		// キーボード入力情報取得
		ProcessMessage() == 0)		// ウインドウのメッセージを処理
	{
		Game_Cal();
		Game_Draw();

		/* FPS計測開始 */
		Fps.FPSCheck();

		/* 本処理 */


		/* FPS表示 */
		DrawFormatStringFToHandle(10, 0, color.Black, Fon.FH[10], "FPS:%4.1f", Fps.Average);

		/* FPSWait */
		Fps.FPSWait();
	}

	WaitKey();						// キー入力待ち

	DxLib_End();					// ＤＸライブラリ使用の終了処理

	return 0;						// ソフトの終了 
}