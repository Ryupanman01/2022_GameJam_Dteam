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

int TimerSE;
int MetronomeSE;
// ������
void Game_Initialize() {

	StartTime = 10000;
	Time = StartTime;

	StartFlg = false;	//�Q�[�����n�܂������ǂ���
	StopFlg = false;
	count = 0;	
	TimerSE = LoadSoundMem("Sound/TimerSE.mp3"); 
	//MetronomeSE = LoadSoundMem("Sound/MetronomeSE.mp3"); 
}

// �I������
void Game_Finalize() {
	DeleteSoundMem(TimerSE);
	//DeleteSoundMem(MetronomeSE);
}

// �X�V
void Game_Update() {
	
	//�X�^�[�g���Ă��Ȃ��āAB�{�^���������ꂽ��X�^�[�g�t���O�𗧂Ă�
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_B] && StartFlg == false) {
		
		StartFlg = true;
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
	//����
	//�J�E���g�_�E���^�C����\��
	SetFontSize(100);
	DrawFormatString(0, 0, 0xffffff, "TIME : %2d", Time / 1000);



	//�f�o�b�O�p
	SetFontSize(20);
	DrawFormatString(30, 120, 0xffffff, "StartFlg�F%d", StartFlg);
	DrawFormatString(30, 150, 0xffffff, "StopFlg�F%d", StopFlg);
	//DrawFormatString(10, 0, 0xffffff, "%d", StartFlg);


	//�Q�[���J�n
	Game_Start();

	//�����X�g�b�v�t���O��true�Ȃ�
	if (StopFlg == true) {
		SceneManager_ChangeScene(SCENE_CLEAR);
	}
	//�܂��̓J�E���g�_�E����0�ȉ��Ȃ�
	else if (Time <= 0) {
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
			//PlaySoundMem(MetronomeSE, DX_PLAYTYPE_BACK, FALSE);
			//ChangeVolumeSoundMem(350, MetronomeSE);
			Time = StartTime - (GetNowCount() - TimeLimit);
			PlaySoundMem(TimerSE, DX_PLAYTYPE_LOOP, FALSE);
			
		}

		//�X�^�[�g���ĂȂ��Ƃ�
		else {
			SetFontSize(30);
			DrawString(90, 230, "B�{�^���������ƃX�^�[�g���܂�", GetColor(255, 255, 255));
		}
	}
}