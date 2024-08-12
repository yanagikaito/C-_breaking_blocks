/*** Header File ***/
#include "DxLib.h"
#include "ProjConf.h"
#include "Sub.h"
#include "Ract.h"

// ブロック定義
Ract Block[BLOCK_NUM_X][BLOCK_NUM_Y];

// バー定義
Ract Bar;

// カラー定義
Col color;

// ボール定義
Cir Ball;

// ボールの速度定義
Speed Ball_Speed;

// キーボード入力情報定義
char allkey[256];

// ゲームの変数を初期化する関数
void Game_Ini() {

    // ブロックに関する変数初期化
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            Block[x][y] = {
                // 幅が100
                x * 100 ,
                50 + y * 50,
                100,
                // 高さが50
                50,
                // ボールが全て存在する
                TRUE };
        }
    }

    // バーに関する変数初期化
    Bar = { 400,600,150,30 };

    // ボールに関する変数初期化
    Ball = { 450,500,10 };

    // ボールの速度に関する変数初期化
    Ball_Speed = { 0,-10 };
}

// ゲームを計算する関数
void Game_Cal() {

    if (allkey[KEY_INPUT_D] != 0)
    {
        Bar.x = Bar.x + 10;
    }
    if (allkey[KEY_INPUT_A] != 0)
    {
        Bar.x = Bar.x - 10;
    }
}
// ゲームを描画する関数
void Game_Draw() {

    // ブロック
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            if (Block[x][y].flag == TRUE) {
                switch (y) {
                case 0:
                    // ブロックの左上のx座標
                    DrawBox(Block[x][y].x,
                        // 左上のy座標
                        Block[x][y].y,
                        // 右下のx座標
                        Block[x][y].x + Block[x][y].w,
                        // 右下のy座標
                        Block[x][y].y + Block[x][y].h,
                        color.Red,
                        TRUE);
                    break;
                case 1:
                    // ブロックの左上のx座標
                    DrawBox(Block[x][y].x,
                        // 左上のy座標
                        Block[x][y].y,
                        // 右下のx座標
                        Block[x][y].x + Block[x][y].w,
                        // 右下のy座標
                        Block[x][y].y + Block[x][y].h,
                        color.Green,
                        TRUE);
                    break;
                case 2:
                    // ブロックの左上のx座標
                    DrawBox(Block[x][y].x,
                        // 左上のy座標
                        Block[x][y].y,
                        // 右下のx座標
                        Block[x][y].x + Block[x][y].w,
                        // 右下のy座標
                        Block[x][y].y + Block[x][y].h,
                        color.Blue,
                        TRUE);
                    break;
                }

                // 網目
                DrawBox(Block[x][y].x,
                    Block[x][y].y,
                    Block[x][y].x + Block[x][y].w,
                    Block[x][y].y + Block[x][y].h,
                    color.Black,
                    FALSE);

                // 座標
                DrawFormatString(
                    Block[x][y].x,
                    Block[x][y].y,
                    color.White,
                    "(%d.%d)",
                    Block[x][y].x,
                    Block[x][y].y);
            }
        }
    }

    // バー
    DrawBox(Bar.x, Bar.y,
        Bar.x + Bar.w,
        Bar.y + Bar.h,
        color.White,
        TRUE);

    // バー座標
    DrawFormatString(
        Bar.x,
        Bar.y,
        color.Black,
        "(%d.%d)",
        Bar.x,
        Bar.y);

    // Ball
    DrawCircle(
        Ball.X,
        Ball.Y,
        Ball.R,
        color.Red,
        TRUE);

    // 座標
    DrawFormatString(
        Ball.X,
        Ball.Y,
        color.White,
        "(%d.%d)",
        Ball.X,
        Ball.Y);

    // Ball Speed
    DrawFormatString(
        Ball.X,
        Ball.Y + 20,
        color.White,
        "(%d,%d)",
        Ball_Speed.x,
        Ball_Speed.y);
}

/*** Keyクラス ***/
class
{
public:
    int input[256];		// キーボード入力情報

    int GetKey()
    {
        GetHitKeyStateAll(allkey);
        for (int i = 0; i < 256; i++)
        {
            if (allkey[i] == 1) // 特定のキーは押されているか
            {
                if (input[i] < DEF_KEY_PRESS_TIME) // 長押し上限まで押されているかどうか
                {
                    input[i] = input[i] + 1; // 保存
                }
            }
            else if (allkey[i] == 0) // 特定のキーは押されていないか
            {
                input[i] = 0;
            }
        }
        return 0;
    }
private:

}Key;

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

    ChangeWindowMode(TRUE);							// ウィンドウモードで起動
    if (DxLib_Init() == -1)							// ＤＸライブラリ初期化処理
    {
        return -1;	// エラーが起きたら直ちに終了
    }

    /*** Window Init ***/
    SetWindowText("ブロック崩し");					// ウィンドウのタイトル
    SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);	// ウィンドウの位置
    SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);			// ウィンドウのサイズ
    SetBackgroundColor(0, 0, 0);					// ウィンドウの背景色
    SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏画面にする
    SetAlwaysRunFlag(TRUE);							// ウインドウ非アクティブ状態でも処理を続行する

    Game_Ini();

    /*** FPS初期化 ***/
    Fps.FPSInit();

    /*** Read ***/
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
        DrawFormatStringFToHandle(10, 0, color.White, Fon.FH[10], "FPS:%4.1f", Fps.Average);

        /* FPSWait */
        Fps.FPSWait();
    }

    WaitKey();						// キー入力待ち

    DxLib_End();					// ＤＸライブラリ使用の終了処理

    return 0;						// ソフトの終了 
}