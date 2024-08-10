#pragma once

/*** Fontクラス ***/
class
{
public:
	int FH[30 + 1];

	void Read()
	{
		for (int i = 0; i < 30 + 1; i++)
		{
			FH[i] = CreateFontToHandle("ＭＳ　ゴシック", i, 6, DX_FONTTYPE_NORMAL);
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
/*** Soundクラス ***/
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

/*** FPSクラス ***/
class
{
public:
	LONGLONG FirsttakeTime = 0;		// 1フレーム目の計測時間
	LONGLONG NowtakeTime = 0;		// 現在の計測時間
	LONGLONG OldtakeTime = 0;		// 以前の計測時間

	float Deltatime = 0.000001f;	// デルタタイム（経過時間）
	int FrameCount = 1;				// 現在のフレーム数（1フレーム目からMAXフレーム目まで）
	float Average = 0.0f;			// 平均のFPS値

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
		wait = (MicroSecond / GameFPS * FrameCount) - (NowtakeTime - FirsttakeTime);	/* wait時間(micro sec) = 理想の時間 - 実際の時間 */
		wait /= MillSecond; /* wait時間(ms) */

		if (wait > 0 && wait <= WaitTimeMill) {
			WaitTimer(wait);
		}
		return;
	}
private:

}Fps;

/*** Keyクラス ***/
class
{
public:
	int input[256];		// キーボード入力情報

	int GetKey()
	{
		char allkey[256];
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
