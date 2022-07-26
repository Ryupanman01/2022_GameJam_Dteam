#include "Help.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"

static int HelpImage;		//タイトル画像格納
static int HelpMenuNo = 0;	//メニューカーソル

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
void Help_Update() {

	//メニューカーソル移動処理
	if (iKeyFlg & PAD_INPUT_RIGHT) {
		if (++HelpMenuNo > 1)HelpMenuNo = 1;
	}
	if (iKeyFlg & PAD_INPUT_LEFT) {
		if (--HelpMenuNo < 0)HelpMenuNo = 0;
	}
	//Bキーでメニュー選択
	if (iKeyFlg & PAD_INPUT_A) {
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
	//メニューカーソル表示
	DrawBox(10 + (480 * HelpMenuNo), 50 - (5 * HelpMenuNo), 
		30 + (440 * HelpMenuNo), 30 - (5 * HelpMenuNo), 0xff0000, TRUE);

}