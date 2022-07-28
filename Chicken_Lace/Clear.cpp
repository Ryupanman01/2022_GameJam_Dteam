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
	Ranking_Read();
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A]) {
		if ((double)Time / 1000 < Ranking[6].score/*�����L���O��7�ʂ̒l������K�v������i���݂͉��̐��l�j*/ ){
			SceneManager_ChangeScene(SCENE_RANKINPUT);
		}
		else {
			Ranking_Sort(); // �����L���O���בւ�
			Ranking_Save(); // �����L���O�f�[�^�̕ۑ�
			SceneManager_ChangeScene(SCENE_GAMEOVER);
		}
	}
}

//�`��
void Clear_Draw() {
	DrawGraph(0, 0, ClearImage,FALSE);
	SetFontSize(30);
	DrawFormatString(140, 200, 0x0000000 ,"����̃X�R�A��%.2lf�ł�",(double)Time / 1000, 0x000000);
	////�f�o�b�O�p
	//DrawFormatString(140, 400, 0x000000, "%lf", (double)Time/1000);
	//DrawFormatString(140, 450, 0x000000, "%lf", Ranking[RANKCOUNT - 1].score);
}