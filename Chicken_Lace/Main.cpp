//��ʐݒ�
#define WIN_MAX_X 640	//�E�B���h�E�T�C�Y���w��
#define WIN_MAX_Y 480	//�E�B���h�E�T�C�Y�c�w��

#include <math.h>
#include "DxLib.h"
#include "SceneManager.h"
#include "Input.h"

static int mStartTime;      //����J�n����
static int mCount;          //�J�E���^
static float mFps;          //fps
static const int N = 60;	//���ς����T���v����
static const int FPS = 60;	//�ݒ肵��FPS

bool Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Draw() {
	//DrawFormatString(0, 0, GetColor(255, 255, 0), "%.1f", mFps);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}





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
		Update();
		
		SceneManager_Draw();		//�`��
		Draw();

		ScreenFlip();				//��ʍX�V
		Wait();
	}

	SceneManager_Finalize();		//�I������

	DxLib_End();
	return 0;
}