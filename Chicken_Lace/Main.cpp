//��ʐݒ�
#define WIN_MAX_X 640	//�E�B���h�E�T�C�Y�w��ix�j
#define WIN_MAX_Y 480	//�E�B���h�E�T�C�Y�w��iy�j

//�w�b�_�[�ǂݍ��ݗp
#include "DxLib.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�ŋN������
	DxLib_Init();			//���C�u�����̏�����

	//�E�B���h�E�̏����ݒ�
	SetWindowText("CHICKEN LACE");		//��ʃ^�C�g���ݒ�
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);		//��ʃ��[�h�̐ݒ�
	SetBackgroundColor(255, 255, 255);			//��ʂ̔w�i�F�̐ݒ�
	SetDrawScreen(DX_SCREEN_BACK);				//����ʂɐݒ�

	//����������


	while (ScreenFlip() == 0 &&
		ClearDrawScreen() == 0 &&
		ProcessMessage() == 0)
	{
		//�X�V����

		//�`�揈��
	}
	WaitKey();				//�L�[�̓��͑҂�

	//�I������

	DxLib_End();			//���C�u�����̏I��
	return 0;
}