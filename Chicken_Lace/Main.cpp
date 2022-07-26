//��ʐݒ�
#define WIN_MAX_X 640	//�E�B���h�E�T�C�Y���w��
#define WIN_MAX_Y 480	//�E�B���h�E�T�C�Y�c�w��

#include "DxLib.h"
#include "SceneManager.h"
#include "Input.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�ŋN������
	DxLib_Init();			//���C�u�����̏�����

	//�E�B���h�E�̏����ݒ�
	SetWindowText("CHICKEN LACE");		//��ʃ^�C�g���ݒ�
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);		//��ʃ��[�h�̐ݒ�
	SetBackgroundColor(0, 0, 0);			//��ʂ̔w�i�F�̐ݒ�
	SetDrawScreen(DX_SCREEN_BACK);				//����ʂɐݒ�

	SceneManager_Initialize();			//������

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {	//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

		if (SceneManager_GameEnd_Status()) {//���j���[����I�����I�����ꂽ��
			break;
		}
		ClearDrawScreen();			//��ʏ���

		InputPad();					//����

		SceneManager_Update();		//�X�V
		SceneManager_Draw();		//�`��

		ScreenFlip();				//��ʍX�V
	}

	SceneManager_Finalize();		//�I������

	DxLib_End();
	return 0;
}