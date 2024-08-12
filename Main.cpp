/*** Header File ***/
#include "DxLib.h"
#include "ProjConf.h"
#include "Sub.h"
#include "Ract.h"
#include "math.h"

// �u���b�N��`
Ract Block[BLOCK_NUM_X][BLOCK_NUM_Y];

// �o�[��`
Ract Bar;

// �J���[��`
Col color;

// �{�[����`
Cir Ball;

// �{�[���̑��x��`
Speed Ball_Speed;

// �L�[�{�[�h���͏���`
char allkey[256];

// �Q�[���̕ϐ�������������֐�
void Game_Ini() {

    // �u���b�N�Ɋւ���ϐ�������
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            Block[x][y] = {
                // ����100
                x * 100 ,
                50 + y * 50,
                100,
                // ������50
                50,
                // �{�[�����S�đ��݂���
                TRUE };
        }
    }

    // �o�[�Ɋւ���ϐ�������
    Bar = { 400,600,150,30 };

    // �{�[���Ɋւ���ϐ�������
    Ball = { 450,500,10 };

    // �{�[���̑��x�Ɋւ���ϐ�������
    Ball_Speed = { 0,-10 };
}

// �u���b�N�ƃ{�[���̐ڐG����
bool HitJudg(Ract block, Cir ball) {

    // �~���̍��W���v�Z
    const double pi = 3.141592;
    double rad;
    double x;
    double y;
    int circum_x;
    int circum_y;
    for (int i = 0; i < 360; i = i + 1) {

        // �~���̍��W���v�Z
        rad = pi * i / 180;
        x = cos(rad);
        y = sin(rad);
        circum_x = Ball.X + Ball.R * x;
        circum_y = Ball.Y + Ball.R * y;

        // �{�[���ƃu���b�N���ڐG�����Ƃ�
        if (block.y <= circum_y &&
            circum_y <= block.y + block.h &&
            block.x <= circum_x &&
            circum_x <= block.x + block.w) {
            return TRUE;
        }
    }

    // �{�[���ƃu���b�N���ڐG���Ȃ������Ƃ�
    return FALSE;
}

// �Q�[�����v�Z����֐�
void Game_Cal() {

    if (allkey[KEY_INPUT_D] != 0)
    {
        Bar.x = Bar.x + 10;
    }
    if (allkey[KEY_INPUT_A] != 0)
    {
        Bar.x = Bar.x - 10;
    }

    // �u���b�N�ƃ{�[���̐ڐG����
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {

            // �u���b�N�ƃ{�[�����ڐG�����ꍇ
            if (Block[x][y].flag == TRUE &&
                HitJudg(Block[x][y], Ball) == TRUE) {

                // �{�[���̍��W�v�Z
                Ball_Speed.y = Ball_Speed.y * (-1);

                // �u���b�N����
                Block[x][y].flag = FALSE;

                // ���[�v������
                break;
            }
        }
    }

    // �{�[�����o�[�ɐڐG�����Ƃ�
    if (HitJudg(Bar, Ball) == TRUE) {

        // �{�[���̑��x�v�Z
        int x = (Ball.X - (Bar.x + Bar.w / 2)) / 10;
        Ball_Speed.x = x;
        Ball_Speed.y = Ball_Speed.y * (-1);
    }

    // �{�[�����V��ɐڐG�����Ƃ�
    if (Ball.Y < 0) {

        // �{�[���̑��x�v�Z
        Ball_Speed.y = Ball_Speed.y * (-1);
    }

    // �{�[�����ǂɐڐG�����Ƃ�
    if (Ball.X < 0 || Ball.X > 1600 - 2 * Ball.R) {

        // �{�[�����x�v�Z
        Ball_Speed.x = Ball_Speed.x * (-1);
    }

    // �{�[���̍��W�v�Z
    Ball.Y = Ball.Y + Ball_Speed.y;
    Ball.X = Ball.X + Ball_Speed.x;
}
// �Q�[����`�悷��֐�
void Game_Draw() {

    // �u���b�N
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            if (Block[x][y].flag == TRUE) {
                switch (y) {
                case 0:
                    // �u���b�N�̍����x���W
                    DrawBox(Block[x][y].x,
                        // �����y���W
                        Block[x][y].y,
                        // �E����x���W
                        Block[x][y].x + Block[x][y].w,
                        // �E����y���W
                        Block[x][y].y + Block[x][y].h,
                        color.Red,
                        TRUE);
                    break;
                case 1:
                    // �u���b�N�̍����x���W
                    DrawBox(Block[x][y].x,
                        // �����y���W
                        Block[x][y].y,
                        // �E����x���W
                        Block[x][y].x + Block[x][y].w,
                        // �E����y���W
                        Block[x][y].y + Block[x][y].h,
                        color.Green,
                        TRUE);
                    break;
                case 2:
                    // �u���b�N�̍����x���W
                    DrawBox(Block[x][y].x,
                        // �����y���W
                        Block[x][y].y,
                        // �E����x���W
                        Block[x][y].x + Block[x][y].w,
                        // �E����y���W
                        Block[x][y].y + Block[x][y].h,
                        color.Blue,
                        TRUE);
                    break;
                }

                // �Ԗ�
                DrawBox(Block[x][y].x,
                    Block[x][y].y,
                    Block[x][y].x + Block[x][y].w,
                    Block[x][y].y + Block[x][y].h,
                    color.Black,
                    FALSE);

                // ���W
            /**    DrawFormatString(
                    Block[x][y].x,
                    Block[x][y].y,
                    color.White,
                    "(%d.%d)",
                    Block[x][y].x,
                    Block[x][y].y);
                    **/
            }
        }
    }

    // �o�[
    DrawBox(Bar.x, Bar.y,
        Bar.x + Bar.w,
        Bar.y + Bar.h,
        color.White,
        TRUE);

    // �o�[���W
 /**   DrawFormatString(
        Bar.x,
        Bar.y,
        color.Black,
        "(%d.%d)",
        Bar.x,
        Bar.y);
          **/

          // Ball
    DrawCircle(
        Ball.X,
        Ball.Y,
        Ball.R,
        color.Red,
        TRUE);

    // ���W
 /**   DrawFormatString(
        Ball.X,
        Ball.Y,
        color.White,
        "(%d.%d)",
        Ball.X,
        Ball.Y);
        **/

        // Ball Speed
    /**   DrawFormatString(
           Ball.X,
           Ball.Y + 20,
           color.White,
           "(%d,%d)",
           Ball_Speed.x,
           Ball_Speed.y);
           **/

           // �X�R�A�J�E���g
    int score = 0;
    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {
            if (Block[x][y].flag == FALSE) {
                score = score + 1;
            }
        }
    }

    // �X�R�A�\��
    DrawFormatString(
        800,
        5,
        color.White,
        "Score = %d",
        score);
}

/*** Key�N���X ***/
class
{
public:
    int input[256];		// �L�[�{�[�h���͏��

    int GetKey()
    {
        GetHitKeyStateAll(allkey);
        for (int i = 0; i < 256; i++)
        {
            if (allkey[i] == 1) // ����̃L�[�͉�����Ă��邩
            {
                if (input[i] < DEF_KEY_PRESS_TIME) // ����������܂ŉ�����Ă��邩�ǂ���
                {
                    input[i] = input[i] + 1; // �ۑ�
                }
            }
            else if (allkey[i] == 0) // ����̃L�[�͉�����Ă��Ȃ���
            {
                input[i] = 0;
            }
        }
        return 0;
    }
private:

}Key;

// �Q�[���I�����̏������s���֐�
bool Game_End() {

    bool end = TRUE;

    for (int y = 0; y < BLOCK_NUM_Y; y = y + 1) {
        for (int x = 0; x < BLOCK_NUM_X; x = x + 1) {

            // �P�ł��u���b�N������΃Q�[�����s
            if (Block[x][y].flag == TRUE) {
                end = FALSE;
            }
        }
    }

    // �{�[���������Ă��܂����Ƃ�
    if (Ball.Y > 900) {

        end = TRUE;
    }

    return end;
}
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_  HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{

    ChangeWindowMode(TRUE);							// �E�B���h�E���[�h�ŋN��
    if (DxLib_Init() == -1)							// �c�w���C�u��������������
    {
        return -1;	// �G���[���N�����璼���ɏI��
    }

    /*** Window Init ***/
    SetWindowText("�u���b�N����");					// �E�B���h�E�̃^�C�g��
    SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);	// �E�B���h�E�̈ʒu
    SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);			// �E�B���h�E�̃T�C�Y
    SetBackgroundColor(0, 0, 0);					// �E�B���h�E�̔w�i�F
    SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠉�ʂɂ���
    SetAlwaysRunFlag(TRUE);							// �E�C���h�E��A�N�e�B�u��Ԃł������𑱍s����

    Game_Ini();

    /*** FPS������ ***/
    Fps.FPSInit();

    /*** Read ***/
    Fon.Read();

    /*** ���[�v���� ***/
    while (ScreenFlip() == 0 &&		// ����ʂ̓��e��\��ʂɔ��f
        ClearDrawScreen() == 0 &&	// ��ʂ�������
        Key.GetKey() == 0 &&		// �L�[�{�[�h���͏��擾
        ProcessMessage() == 0)		// �E�C���h�E�̃��b�Z�[�W������
    {
        Game_Cal();
        Game_Draw();

        if (Game_End() == TRUE) {

            Game_Ini();
        }

        /* FPS�v���J�n */
        Fps.FPSCheck();

        /* �{���� */


        /* FPS�\�� */
        DrawFormatStringFToHandle(10, 0, color.White, Fon.FH[10], "FPS:%4.1f", Fps.Average);

        /* FPSWait */
        Fps.FPSWait();
    }

    WaitKey();						// �L�[���͑҂�

    DxLib_End();					// �c�w���C�u�����g�p�̏I������

    return 0;						// �\�t�g�̏I�� 
}