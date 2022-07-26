#include "Game.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"

int StartTime;
int TIMELIMIT;
int Time;

// 初期化
void Game_Initialize() {
	StartTime = 20000;
	TIMELIMIT= GetNowCount();
}

// 終了処理
void Game_Finalize() {

}

// 更新
void Game_Update() {

	Time = StartTime - (GetNowCount() - TIMELIMIT);

	//デバッグ用
	if (Time < 0)
	{
		SceneManager_ChangeScene(SCENE_RANKING);
	}
}

// 描画
void Game_Draw() {
	SetFontSize(100);
	DrawFormatString(0, 0, 0xffffff, "TIME : %2d", Time / 1000);
}