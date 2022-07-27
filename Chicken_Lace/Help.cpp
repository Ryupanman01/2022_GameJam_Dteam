#include "Help.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"

static int HelpImage;		//タイトル画像格納
static int HelpMenuNo = 0;	//メニューカーソル
int HelpPosY;

//初期化
void Help_Initialize() {
	//画像読み込み
	HelpImage = LoadGraph("Images/Help.png");
}

//終了処理
void Help_Finalize() {
	//画像消去
	DeleteGraph(HelpImage);
}

//更新
bool SideCursor;
void Help_Update() {
	//メニューカーソル移動処理
	if (Input.ThumbLX == 32767 && SideCursor == false)
	{
		SideCursor = true;
		if (++HelpMenuNo > 1)HelpMenuNo = 0;
	
	}
	if (Input.ThumbLX < 32767 && Input.ThumbLX > 128 && SideCursor)
	{
		SideCursor = false;
	}


	if (Input.ThumbLX == -32768 && SideCursor == false)
	{
		SideCursor = true;
		if (--HelpMenuNo < 0)HelpMenuNo = 1;
	}
	if (Input.ThumbLX > -32768 && Input.ThumbLX < 128 && SideCursor)
	{
		SideCursor = false;
	}
	
	//Aキーでメニュー選択
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A]) {
		//タイトルへ
		if (HelpMenuNo == 0) {
			SceneManager_ChangeScene(SCENE_TITLE);
		}
		//ゲームメインへ
		if (HelpMenuNo == 1) {
			SceneManager_ChangeScene(SCENE_GAME);
		}
	}
	//メニューカーソル

}

//描画
void Help_Draw() {
	//画像配置
	DrawGraph(0, 0, HelpImage, FALSE);
	//X 640 Y 480

	SetFontSize(30);
	if (HelpMenuNo != 0)DrawString(40, 400, "もどる", 0x000000);
	if (HelpMenuNo != 1)DrawString(340, 400, "ゲームスタート！", 0x000000);

	SetFontSize(40);
	//HelpPosY = HelpMenuNo * 49;
	if (HelpMenuNo == 0)
	{
		DrawBox(40, 440, 170, 400, 0x989898, TRUE);
		DrawString(40, 400, "もどる", 0xffffff);
	}
	else if (HelpMenuNo == 1)
	{
		DrawBox(260, 440, 580, 400, 0x989898, TRUE);
		DrawString(260, 400, "ゲームスタート！", 0xffffff);
	}
}

