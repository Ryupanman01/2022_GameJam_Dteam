#include "Game.h"
#include "Ranking.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"

int StartTime;	//カウントダウン初期値
int TimeLimit;	//時間経過保持変数
int Time;		//現在のカウントダウン値

bool StartFlg;	//ゲームが始まったかどうか
bool StopFlg;
int count;		//1回だけ呼び出す用

int gameScore;

// 初期化
void Game_Initialize() {

	StartTime = 10000;
	Time = StartTime;

	StartFlg = false;	//ゲームが始まったかどうか
	StopFlg = false;
	count = 0;			
}

// 終了処理
void Game_Finalize() {

}

// 更新
void Game_Update() {
	//スタートしていなくて、Bボタンが押されたらスタートフラグを立てる
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A] && StartFlg == false) {
		StartFlg = true;
		//Aボタンの連続入力を避けるため0に初期化している（他にいい方法があればそれを採用する）
		ButtonFlag = 0;
	}

		//ゲーム中にAボタンを押したら
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A] && StartFlg == true) {
		//カウントダウンが0より大きかったら
		if (Time > 0) {
			StopFlg = true;
		}
	}
}

// 描画
void Game_Draw() {
	//カウントダウンタイムを表示
	SetFontSize(100);
	DrawFormatString(0, 0, 0xffffff, "TIME : %.2f", (double)Time / 1000);

	//デバッグ用
	SetFontSize(20);
	DrawFormatString(30, 120, 0xffffff, "StartFlg：%d", StartFlg);
	DrawFormatString(30, 150, 0xffffff, "StopFlg：%d", StopFlg);

	//ゲーム開始
	Game_Start();

	//もしストップフラグがtrueなら
	if (StopFlg == true) {
		SceneManager_ChangeScene(SCENE_CLEAR);
	}
	//またはカウントダウンが0以下なら
	if (Time <= 0) {
		SceneManager_ChangeScene(SCENE_GAMEOVER);
	}
}

//ゲーム開始
void Game_Start(){
	//スタートフラグが１かつカウントが0なら
	if (StartFlg == true && count == 0) {
		//タイムリミットに現在の経過時間を入れる
		TimeLimit = GetNowCount();
		//カウントを1にすることで一回だけ呼び出す
		count = 1;
	}

	//スタートしたとき
	if (StopFlg == false) {
		if (StartFlg == true) {
			Time = StartTime - (GetNowCount() - TimeLimit);
		}
		//スタートしてないとき
		else {
			SetFontSize(30);
			DrawString(90, 230, "Bボタンを押すとスタートします", GetColor(255, 255, 255));
		}
	}
}