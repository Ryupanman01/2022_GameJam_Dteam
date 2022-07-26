//画面設定
#define WIN_MAX_X 640	//ウィンドウサイズ横指定
#define WIN_MAX_Y 480	//ウィンドウサイズ縦指定

#include "DxLib.h"
#include "SceneManager.h"
#include "Input.h"

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
		SceneManager_Draw();		//描画

		ScreenFlip();				//画面更新
	}

	SceneManager_Finalize();		//終了処理

	DxLib_End();
	return 0;
}