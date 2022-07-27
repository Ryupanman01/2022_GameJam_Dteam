//画面設定
#define WIN_MAX_X 640	//ウィンドウサイズ横指定
#define WIN_MAX_Y 480	//ウィンドウサイズ縦指定

#include <math.h>
#include "DxLib.h"
#include "SceneManager.h"
#include "Input.h"

static int mStartTime;      //測定開始時刻
static int mCount;          //カウンタ
static float mFps;          //fps
static const int N = 60;	//平均を取るサンプル数
static const int FPS = 60;	//設定したFPS

bool Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Draw() {
	//DrawFormatString(0, 0, GetColor(255, 255, 0), "%.1f", mFps);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}





int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	ChangeWindowMode(TRUE);	//ウィンドウモードで起動する
	DxLib_Init();			//ライブラリの初期化

	//ウィンドウの初期設定
	SetWindowText("CHICKEN LACE");		//画面タイトル設定
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);		//画面モードの設定
	SetBackgroundColor(0, 0, 0);			//画面の背景色の設定
	SetDrawScreen(DX_SCREEN_BACK);				//裏画面に設定

	SceneManager_Initialize();			//初期化

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {	//画面更新 & メッセージ処理 & 画面消去

		if (SceneManager_GameEnd_Status()) {//メニューから終了が選択されたら
			break;
		}
		ClearDrawScreen();			//画面消去

		InputPad();					//入力
		
		SceneManager_Update();		//更新
		Update();
		
		SceneManager_Draw();		//描画
		Draw();

		ScreenFlip();				//画面更新
		Wait();
	}

	SceneManager_Finalize();		//終了処理

	DxLib_End();
	return 0;
}