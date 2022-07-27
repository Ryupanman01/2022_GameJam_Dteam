#include "Game.h"
#include "Ranking.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "Input.h"

int StartTime;	//�J�E���g�_�E�������l
int TimeLimit;	//���Ԍo�ߕێ��ϐ�
int Time;		//���݂̃J�E���g�_�E���l

bool StartFlg;	//�Q�[�����n�܂������ǂ���
bool StopFlg;
int count;		//1�񂾂��Ăяo���p

int gameScore;

// ������
void Game_Initialize() {

	StartTime = 10000;
	Time = StartTime;

	StartFlg = false;	//�Q�[�����n�܂������ǂ���
	StopFlg = false;
	count = 0;			
}

// �I������
void Game_Finalize() {

}

// �X�V
void Game_Update() {
	//�X�^�[�g���Ă��Ȃ��āAB�{�^���������ꂽ��X�^�[�g�t���O�𗧂Ă�
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A] && StartFlg == false) {
		StartFlg = true;
		//A�{�^���̘A�����͂�����邽��0�ɏ��������Ă���i���ɂ������@������΂�����̗p����j
		ButtonFlag = 0;
	}

		//�Q�[������A�{�^������������
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A] && StartFlg == true) {
		//�J�E���g�_�E����0���傫��������
		if (Time > 0) {
			StopFlg = true;
		}
	}
}

// �`��
void Game_Draw() {
	//�J�E���g�_�E���^�C����\��
	SetFontSize(100);
	DrawFormatString(0, 0, 0xffffff, "TIME : %.2f", (double)Time / 1000);

	//�f�o�b�O�p
	SetFontSize(20);
	DrawFormatString(30, 120, 0xffffff, "StartFlg�F%d", StartFlg);
	DrawFormatString(30, 150, 0xffffff, "StopFlg�F%d", StopFlg);

	//�Q�[���J�n
	Game_Start();

	//�����X�g�b�v�t���O��true�Ȃ�
	if (StopFlg == true) {
		SceneManager_ChangeScene(SCENE_CLEAR);
	}
	//�܂��̓J�E���g�_�E����0�ȉ��Ȃ�
	if (Time <= 0) {
		SceneManager_ChangeScene(SCENE_GAMEOVER);
	}
}

//�Q�[���J�n
void Game_Start(){
	//�X�^�[�g�t���O���P���J�E���g��0�Ȃ�
	if (StartFlg == true && count == 0) {
		//�^�C�����~�b�g�Ɍ��݂̌o�ߎ��Ԃ�����
		TimeLimit = GetNowCount();
		//�J�E���g��1�ɂ��邱�Ƃň�񂾂��Ăяo��
		count = 1;
	}

	//�X�^�[�g�����Ƃ�
	if (StopFlg == false) {
		if (StartFlg == true) {
			Time = StartTime - (GetNowCount() - TimeLimit);
		}
		//�X�^�[�g���ĂȂ��Ƃ�
		else {
			SetFontSize(30);
			DrawString(90, 230, "B�{�^���������ƃX�^�[�g���܂�", GetColor(255, 255, 255));
		}
	}
}