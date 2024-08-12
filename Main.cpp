/*** Header File ***/
#include "DxLib.h"
#include "ProjConf.h"
#include "Sub.h"
#include "Ract.h"

// �u���b�N��`
Ract Block[BLOCK_NUM_X][BLOCK_NUM_Y];

// �o�[��`
Ract Bar;

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
	Bar = { 700,700,200,30 };
}

// �Q�[�����v�Z����֐�
void Game_Cal() {

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
						GetColor(255, 0, 0),
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
						GetColor(0, 255, 0),
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
						GetColor(0, 0, 255),
						TRUE);
					break;
				}

				// �Ԗ�
				DrawBox(Block[x][y].x,
					Block[x][y].y,
					Block[x][y].x + Block[x][y].w,
					Block[x][y].y + Block[x][y].h,
					GetColor(0, 0, 0),
					FALSE);

				// ���W
				DrawFormatString(
					Block[x][y].x,
					Block[x][y].y,
					GetColor(255, 255, 255),
					"(%d.%d)",
					Block[x][y].x,
						Block[x][y].y);
			}
		}
	}
}

// �Q�[���I�[�o�[���̏������s���֐�
void Game_End() {

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
	SetBackgroundColor(255, 255, 255);				// �E�B���h�E�̔w�i�F
	SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠉�ʂɂ���
	SetAlwaysRunFlag(TRUE);							// �E�C���h�E��A�N�e�B�u��Ԃł������𑱍s����

	Game_Ini();

	/*** FPS������ ***/
	Fps.FPSInit();

	// �J���[��`
	Col();
	Col color;

	/*** Read ***/
	Fon.Read();
#ifdef DEF_SOUND_VALID
	Snd.Read();

	/*** BGM�J�n ***/
	PlaySoundMem(Snd.BgmSound, DX_PLAYTYPE_LOOP);
#endif /* DEF_SOUND_VALID */

	/*** ���[�v���� ***/
	while (ScreenFlip() == 0 &&		// ����ʂ̓��e��\��ʂɔ��f
		ClearDrawScreen() == 0 &&	// ��ʂ�������
		Key.GetKey() == 0 &&		// �L�[�{�[�h���͏��擾
		ProcessMessage() == 0)		// �E�C���h�E�̃��b�Z�[�W������
	{
		Game_Cal();
		Game_Draw();

		/* FPS�v���J�n */
		Fps.FPSCheck();

		/* �{���� */


		/* FPS�\�� */
		DrawFormatStringFToHandle(10, 0, color.Black, Fon.FH[10], "FPS:%4.1f", Fps.Average);

		/* FPSWait */
		Fps.FPSWait();
	}

	WaitKey();						// �L�[���͑҂�

	DxLib_End();					// �c�w���C�u�����g�p�̏I������

	return 0;						// �\�t�g�̏I�� 
}