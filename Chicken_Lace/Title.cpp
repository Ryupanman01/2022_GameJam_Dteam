#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "Input.h"

static int TitleImage;		//タイトル画像格納

//初期化
void Title_Initialize() {
	//画像読み込み
	TitleImage = LoadGraph("Images/Title.png");
}

//終了処理
void Title_Finalize() {
	//画像消去
	DeleteGraph(TitleImage);
}

//更新
void Title_Update() {
	if (iKeyFlg & PAD_INPUT_B) {
		SceneManager_ChangeScene(SCENE_HELP);
	}
}

//描画
void Title_Draw() {
	//画像配置
	DrawGraph(0, 0, TitleImage, FALSE);
}