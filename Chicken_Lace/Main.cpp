//画面設定
#define WIN_MAX_X 640	//ウィンドウサイズ指定（x）
#define WIN_MAX_Y 480	//ウィンドウサイズ指定（y）

//ヘッダー読み込み用
#include "DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);	//ウィンドウモードで起動する
	DxLib_Init();			//ライブラリの初期化

	//ウィンドウの初期設定
	SetWindowText("CHICKEN LACE");		//画面タイトル設定
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);		//画面モードの設定
	SetBackgroundColor(255, 255, 255);			//画面の背景色の設定
	SetDrawScreen(DX_SCREEN_BACK);				//裏画面に設定

	//初期化処理


	while (ScreenFlip() == 0 &&
		ClearDrawScreen() == 0 &&
		ProcessMessage() == 0)
	{
		//更新処理

		//描画処理
	}
	WaitKey();				//キーの入力待ち

	//終了処理

	DxLib_End();			//ライブラリの終了
	return 0;
}