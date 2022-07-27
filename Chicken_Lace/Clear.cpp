#include "DxLib.h"
#include "Clear.h"
#include "Game.h"
#include "SceneManager.h"
#include "Ranking.h"
#include "Input.h"

static int ClearImage;

//初期化
void Clear_Initialize() {
	ClearImage = LoadGraph("Images/Clear.png");
}

//終了処理
void Clear_Finalize() {
	DeleteGraph(ClearImage);
}

//更新
void Clear_Update() {
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A]) {
		if ((double)Time / 1000 < Ranking[RANKCOUNT-1].score/*ランキングの7位の値を入れる必要がある（現在は仮の数値）*/ ){
			SceneManager_ChangeScene(SCENE_RANKINPUT);
		}
		else {
			SceneManager_ChangeScene(SCENE_GAMEOVER);
		}
	}
}

//描画
void Clear_Draw() {
	DrawGraph(0, 0, ClearImage,FALSE);
	SetFontSize(30);
	DrawFormatString(140, 200, 0x0000000 ,"今回のスコアは%.2lfです",(double)Time / 1000, 0x000000);
}