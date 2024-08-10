#pragma once

/*** Font�N���X ***/
class
{
public:
	int FH[30 + 1];

	void Read()
	{
		for (int i = 0; i < 30 + 1; i++)
		{
			FH[i] = CreateFontToHandle("�l�r�@�S�V�b�N", i, 6, DX_FONTTYPE_NORMAL);
		}
	}
private:

}Fon;


struct Col {
	int Black, Red, Green, Blue, White;
	Col() 
		: Black(GetColor(0, 0, 0))
		, Red(GetColor(255, 0, 0))
		, Green(GetColor(0, 255, 0))
		, Blue(GetColor(0, 0, 255))
		, White(GetColor(255, 255, 255)) {
	}
};


#ifdef DEF_SOUND_VALID
/*** Sound�N���X ***/
class
{
public:
	int BgmSound;

	void Read()
	{
		BgmSound = LoadSoundMem("./sound/XXX.wav");
	}
private:

}Snd;
#endif /* DEF_SOUND_VALID */

/*** FPS�N���X ***/
class
{
public:
	LONGLONG FirsttakeTime = 0;		// 1�t���[���ڂ̌v������
	LONGLONG NowtakeTime = 0;		// ���݂̌v������
	LONGLONG OldtakeTime = 0;		// �ȑO�̌v������

	float Deltatime = 0.000001f;	// �f���^�^�C���i�o�ߎ��ԁj
	int FrameCount = 1;				// ���݂̃t���[�����i1�t���[���ڂ���MAX�t���[���ڂ܂Łj
	float Average = 0.0f;			// ���ς�FPS�l

	void FPSInit() {
		FirsttakeTime = GetNowHiPerformanceCount();

		NowtakeTime = FirsttakeTime;
		OldtakeTime = FirsttakeTime;
		Deltatime = 0.000001f;
		FrameCount = 1;
		Average = 0.0f;

		return;
	}

	void FPSCheck() {
		NowtakeTime = GetNowHiPerformanceCount();
		Deltatime = (NowtakeTime - OldtakeTime) / MicroSecond;
		OldtakeTime = NowtakeTime;

		if (FrameCount == GameFPS)
		{
			LONGLONG TotalFrameTIme = NowtakeTime - FirsttakeTime;
			float CalcAverage = static_cast<float>(TotalFrameTIme) / GameFPS;
			Average = MicroSecond / CalcAverage;
			FirsttakeTime = GetNowHiPerformanceCount();
			FrameCount = 1;
		}
		else
		{
			FrameCount++;
		}
		return;
	}

	void FPSWait() {
		int wait = 0;
		wait = (MicroSecond / GameFPS * FrameCount) - (NowtakeTime - FirsttakeTime);	/* wait����(micro sec) = ���z�̎��� - ���ۂ̎��� */
		wait /= MillSecond; /* wait����(ms) */

		if (wait > 0 && wait <= WaitTimeMill) {
			WaitTimer(wait);
		}
		return;
	}
private:

}Fps;

/*** Key�N���X ***/
class
{
public:
	int input[256];		// �L�[�{�[�h���͏��

	int GetKey()
	{
		char allkey[256];
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
