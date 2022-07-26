#include "Game.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"

int StartTime;
int TIMELIMIT;
int Time;

// ������
void Game_Initialize() {
	StartTime = 20000;
	TIMELIMIT= GetNowCount();
}

// �I������
void Game_Finalize() {

}

// �X�V
void Game_Update() {

	Time = StartTime - (GetNowCount() - TIMELIMIT);

	//�f�o�b�O�p
	if (Time < 0)
	{
		SceneManager_ChangeScene(SCENE_RANKING);
	}
}

// �`��
void Game_Draw() {
	SetFontSize(100);
	DrawFormatString(0, 0, 0xffffff, "TIME : %2d", Time / 1000);
}