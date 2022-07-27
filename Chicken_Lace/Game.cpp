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

static int ButtonImage;        // �ʏ�{�^���摜
static int ButtonPushImage;    // �����ꂽ�{�^���摜
static int GameImage;          // �Q�[�����C���̔��w�i

int PushSE;         // �{�^���������Ƃ��̌��ʉ�
int JamaBGM;        // ���ז�BGM

// ������
void Game_Initialize() {

	StartTime = 20000;
	Time = StartTime;

	StartFlg = false;	//�Q�[�����n�܂������ǂ���
	StopFlg = false;
	count = 0;		

	ButtonImage = LoadGraph("Images/button.png");
	ButtonPushImage = LoadGraph("Images/buttonpush.png");
	GameImage = LoadGraph("Images/white.png");

	JamaBGM = LoadSoundMem("Sound/Timer.mp3");
	PushSE = LoadSoundMem("Sound/button.mp3");
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
	DrawGraph(0, 0, GameImage, TRUE);

	//�J�E���g�_�E���^�C����\��
	SetFontSize(100);
	DrawFormatString(190, 20, 0x000000, "%.2lf", (double)Time / 1000);

	//�Q�[���J�n
	Game_Start();

	// �B���̉��o
	if (Time < 15000) {
		DrawBox(100, 0, 500, 150, 0xffffff, TRUE);
	}

	// ���ז�BGM
	if (Time < 15000) {
		ChangeVolumeSoundMem(400, JamaBGM);
		PlaySoundMem(JamaBGM, DX_PLAYTYPE_BACK, FALSE);
	}

	// �ʏ�{�^���̕\��
	if (StartFlg == true) {
		DrawRotaGraph(320, 300, 0.5, 0, ButtonImage, TRUE);
	}

	//�����X�g�b�v�t���O��true�Ȃ�
	if (StopFlg == true) {
		DeleteSoundMem(JamaBGM);
		SceneManager_ChangeScene(SCENE_CLEAR);
	}
	//�܂��̓J�E���g�_�E����0�ȉ��Ȃ�
	if (Time <= 0) {
		DeleteSoundMem(JamaBGM);
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
			DrawString(90, 230, "A�{�^���������ƃX�^�[�g���܂�", GetColor(0, 0, 0));
		}
	}
}