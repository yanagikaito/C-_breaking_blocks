/*** Header File ***/
#include "DxLib.h"
#include "ProjConf.h"
#include "Sub.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_  HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, 
	_In_ int nShowCmd)
{
	Col color;
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

	/*** FPS������ ***/
	Fps.FPSInit();

	/*** Read ***/
	Col();
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