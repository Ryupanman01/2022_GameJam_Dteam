#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "Input.h"

static int TitleImage;		//�^�C�g���摜�i�[

//������
void Title_Initialize() {
	//�摜�ǂݍ���
	TitleImage = LoadGraph("Images/Title.png");
}

//�I������
void Title_Finalize() {
	//�摜����
	DeleteGraph(TitleImage);
}

//�X�V
void Title_Update() {
	if (iKeyFlg & PAD_INPUT_B) {
		SceneManager_ChangeScene(SCENE_HELP);
	}
}

//�`��
void Title_Draw() {
	//�摜�z�u
	DrawGraph(0, 0, TitleImage, FALSE);
}