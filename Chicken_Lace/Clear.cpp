#include "DxLib.h"
#include "Clear.h"
#include "Game.h"
#include "SceneManager.h"
#include "Ranking.h"
#include "Input.h"

static int ClearImage;

//������
void Clear_Initialize() {
	ClearImage = LoadGraph("Images/Clear.png");
}

//�I������
void Clear_Finalize() {
	DeleteGraph(ClearImage);
}

//�X�V
void Clear_Update() {
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A]) {
		if ((double)Time / 1000 < Ranking[RANKCOUNT-1].score/*�����L���O��7�ʂ̒l������K�v������i���݂͉��̐��l�j*/ ){
			SceneManager_ChangeScene(SCENE_RANKINPUT);
		}
		else {
			SceneManager_ChangeScene(SCENE_GAMEOVER);
		}
	}
}

//�`��
void Clear_Draw() {
	DrawGraph(0, 0, ClearImage,FALSE);
	SetFontSize(30);
	DrawFormatString(140, 200, 0x0000000 ,"����̃X�R�A��%.2lf�ł�",(double)Time / 1000, 0x000000);
}