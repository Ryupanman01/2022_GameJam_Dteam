#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "Input.h"

static int TitleImage;		//�^�C�g���摜�i�[
int TitleBGM, SelectSE, ClickSE;
static int MenuNumber = 0;
int PosY;
static int count = 0;
int ButtonFlag;

//������
void Title_Initialize() {
	//�摜�ǂݍ���
	TitleImage = LoadGraph("Images/Title1.png");
	//�^�C�g��BGM�Ǎ���
	TitleBGM = LoadSoundMem("Sound/TitleBGM.mp3");
	//�Z���N�gSE�Ǎ���
	SelectSE = LoadSoundMem("Sound/SelectSE.mp3");
	//�N���b�NSE�Ǎ���
	ClickSE = LoadSoundMem("Sound/ClickSE.mp3");

}

//�I������
void Title_Finalize() {
	//�摜����
	DeleteGraph(TitleImage);
}

//�X�V
void Title_Update() {
	if (iKeyFlg & PAD_INPUT_B) {
		switch (MenuNumber)
		{
		case 0:
			StopSoundMem(TitleBGM);
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_GAME);
			break;
		case 1:
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_RANKING);
			break;
		case 2:
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_HELP);
			break;
		case 3:
			StopSoundMem(TitleBGM);
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_END);
			break;
		}
	}
}

//�`��
void Title_Draw() {
	//�摜�z�u
	DrawGraph(0, 0, TitleImage, FALSE);
	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP, FALSE);

	//���j���[�J�[�\���ړ�����
	if (iKeyFlg & PAD_INPUT_DOWN)
	{
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);
		if (++MenuNumber > 3)MenuNumber = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) {
		
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);
		if (--MenuNumber < 0)MenuNumber = 3;
	}

	////�f�o�b�O�pLine
	//DrawLine(0, 240, 640, 240, 0x000000, 1);
	//DrawLine(320, 0, 320, 480, 0x000000, 1);

	SetFontSize(55);
	DrawString(114, 100, "�`�L�����[�X�I�I", 0x000000);
	SetFontSize(35);
	DrawString(190, 250, "�Q�[���X�^�[�g�I", 0x000000);
	DrawString(228, 300, "�����L���O", 0x000000);
	DrawString(268, 350, "�w���v", 0x000000);
	DrawString(268, 400, "�G���h", 0x000000);

	PosY = MenuNumber * 50;
	if (MenuNumber == 0)
	{
		DrawTriangle(150, 245 + PosY, 180, 265 + PosY, 150, 285 + PosY, GetColor(255, 0, 0), TRUE);
		DrawTriangle(153, 250 + PosY, 175, 265 + PosY, 153, 280 + PosY, 0x000000, TRUE);
	}
	else if (MenuNumber == 1)
	{
		DrawTriangle(190, 250 + PosY, 220, 270 + PosY, 190, 290 + PosY, GetColor(255, 0, 0), TRUE);
		DrawTriangle(193, 255 + PosY, 215, 270 + PosY, 193, 285 + PosY, 0x000000, TRUE);
	}
	else if (MenuNumber == 2 || MenuNumber == 3)
	{
		DrawTriangle(230, 250 + PosY, 260, 270 + PosY, 230, 290 + PosY, GetColor(255, 0, 0), TRUE);
		DrawTriangle(233, 255 + PosY, 255, 270 + PosY, 233, 285 + PosY, 0x000000, TRUE);
	}

}