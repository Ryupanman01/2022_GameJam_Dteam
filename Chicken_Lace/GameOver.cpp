#include "DxLib.h"
#include "Game.h";
#include "GameOver.h"
#include "SceneManager.h"
#include "Input.h"

int GameOverMenuNum;
bool WhideCursor;
int GameOverBGM;
bool BGMFlag;

void GameOver_Initialize() {
	GameOverBGM = LoadSoundMem("Sound/GameOverSE.mp3");
	BGMFlag = true;
	GameOverMenuNum = 0;
}

void GameOver_Finalize() {
	DeleteSoundMem(GameOverBGM);
}

void GameOver_Update() {
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A]) {
		switch (GameOverMenuNum)
		{
		case 0:
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
		    SceneManager_ChangeScene(SCENE_GAME);
			break;
		case 1:
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_TITLE);
			break;
		}
	}
}

void GameOver_Draw() {
	if (BGMFlag == true) {
		ChangeVolumeSoundMem(350, GameOverBGM);
		PlaySoundMem(GameOverBGM, DX_PLAYTYPE_BACK, TRUE);
		BGMFlag = false;
	}

	//メニューカーソル移動処理
	if (Input.ThumbLY == -32768 && WhideCursor == false)
	{
		WhideCursor = true;
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);
		if (++GameOverMenuNum > 1)GameOverMenuNum = 0;
	}
	if (Input.ThumbLY > -32768 && Input.ThumbLY < 128 && WhideCursor)
	{
		WhideCursor = false;
	}


	if (Input.ThumbLY == 32767 && WhideCursor == false) {
		WhideCursor = true;
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);
		if (--GameOverMenuNum < 0)GameOverMenuNum = 1;
	}
	if (Input.ThumbLY < 32767 && Input.ThumbLY > 128 && WhideCursor)
	{
		WhideCursor = false;
	}


	//デバッグ用Line
	/*DrawLine(0, 240, 640, 240, 0xffffff, 1);
	DrawLine(320, 0, 320, 480, 0xffffff, 1);*/

	SetFontSize(80);
	DrawString(157, 80, "GameOver", 0xffffff);
	SetFontSize(34);
	if (Time <= 0) {
		DrawString(60, 200, "あなたは・・・ド級チキンです！", 0xffffff);
	}
	if (GameOverMenuNum != 0)DrawString(198, 285, "もう一度遊ぶ！", 0xffffff);
	if (GameOverMenuNum != 1)DrawString(225, 355, "Titleに戻る", 0xffffff);

	SetFontSize(55);
	if (GameOverMenuNum == 0)
	{
		DrawBox(116, 275, 510, 338, 0xffffff, TRUE);
		DrawString(120, 280, "もう一度遊ぶ！", 0x000000);
	}
	if (GameOverMenuNum == 1)
	{
		DrawBox(156, 345, 490, 404, 0xffffff, TRUE);
		DrawString(164, 350, "Titleに戻る", 0x000000);
	}
}