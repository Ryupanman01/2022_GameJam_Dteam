#include "Help.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"

static int HelpImage;		//�^�C�g���摜�i�[
static int HelpMenuNo = 0;	//���j���[�J�[�\��

//������
void Help_Initialize() {
	//�摜�ǂݍ���
	HelpImage = LoadGraph("Images/Help.png");
}

//�I������
void Help_Finalize() {
	//�摜����
	DeleteGraph(HelpImage);
}

//�X�V
void Help_Update() {

	//���j���[�J�[�\���ړ�����
	if (iKeyFlg & PAD_INPUT_RIGHT) {
		if (++HelpMenuNo > 1)HelpMenuNo = 1;
	}
	if (iKeyFlg & PAD_INPUT_LEFT) {
		if (--HelpMenuNo < 0)HelpMenuNo = 0;
	}
	//B�L�[�Ń��j���[�I��
	if (iKeyFlg & PAD_INPUT_A) {
		//�^�C�g����
		if (HelpMenuNo == 0) {
			SceneManager_ChangeScene(SCENE_TITLE);
		}
		//�Q�[�����C����
		if (HelpMenuNo == 1) {
			SceneManager_ChangeScene(SCENE_GAME);
		}
	}
	//���j���[�J�[�\��

}

//�`��
void Help_Draw() {
	//�摜�z�u
	DrawGraph(0, 0, HelpImage, FALSE);
	//X 640 Y 480
	//���j���[�J�[�\���\��
	DrawBox(10 + (480 * HelpMenuNo), 50 - (5 * HelpMenuNo), 
		30 + (440 * HelpMenuNo), 30 - (5 * HelpMenuNo), 0xff0000, TRUE);

}