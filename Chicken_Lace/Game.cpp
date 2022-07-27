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

static int ButtonImage;        // 通常ボタン画像
static int ButtonPushImage;    // 押されたボタン画像
static int GameImage;          // ゲームメインの白背景

int PushSE;         // ボタン押したときの効果音
int JamaBGM;        // お邪魔BGM

// 初期化
void Game_Initialize() {

	StartTime = 20000;
	Time = StartTime;

	StartFlg = false;	//ゲームが始まったかどうか
	StopFlg = false;
	count = 0;		

	ButtonImage = LoadGraph("Images/button.png");
	ButtonPushImage = LoadGraph("Images/buttonpush.png");
	GameImage = LoadGraph("Images/white.png");

	JamaBGM = LoadSoundMem("Sound/Timer.mp3");
	PushSE = LoadSoundMem("Sound/button.mp3");
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
	DrawGraph(0, 0, GameImage, TRUE);

	//カウントダウンタイムを表示
	SetFontSize(100);
	DrawFormatString(190, 20, 0x000000, "%.2lf", (double)Time / 1000);

	//ゲーム開始
	Game_Start();

	// 隠しの演出
	if (Time < 15000) {
		DrawBox(100, 0, 500, 150, 0xffffff, TRUE);
	}

	// お邪魔BGM
	if (Time < 15000) {
		ChangeVolumeSoundMem(400, JamaBGM);
		PlaySoundMem(JamaBGM, DX_PLAYTYPE_BACK, FALSE);
	}

	// 通常ボタンの表示
	if (StartFlg == true) {
		DrawRotaGraph(320, 300, 0.5, 0, ButtonImage, TRUE);
	}

	//もしストップフラグがtrueなら
	if (StopFlg == true) {
		DeleteSoundMem(JamaBGM);
		SceneManager_ChangeScene(SCENE_CLEAR);
	}
	//またはカウントダウンが0以下なら
	if (Time <= 0) {
		DeleteSoundMem(JamaBGM);
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
			DrawString(90, 230, "Aボタンを押すとスタートします", GetColor(0, 0, 0));
		}
	}
}