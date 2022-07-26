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
bool SideCursor;
void Help_Update() {
	//���j���[�J�[�\���ړ�����
	if (Input.ThumbLX == 32767 && SideCursor == false)
	{
		SideCursor = true;
		if (++HelpMenuNo > 1)HelpMenuNo = 0;
	
	}
	if (Input.ThumbLX < 32767 && Input.ThumbLX > 128 && SideCursor)
	{
		SideCursor = false;
	}


	if (Input.ThumbLX == -32768 && SideCursor == false)
	{
		SideCursor = true;
		if (--HelpMenuNo < 0)HelpMenuNo = 1;
	}
	if (Input.ThumbLX > -32768 && Input.ThumbLX < 128 && SideCursor)
	{
		SideCursor = false;
	}
	
	//A�L�[�Ń��j���[�I��
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A]) {
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