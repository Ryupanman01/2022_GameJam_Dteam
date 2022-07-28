#include "DxLib.h"
#include "SceneManager.h"
#include "Ranking.h"
#include "Game.h"
#include "Input.h"

static int RankingImage;	//�����L���O�摜
static int WaitTime;		//�����L���O�\������
struct  RankingData Ranking[RANKCOUNT];	//�����L���O�f�[�^�Ǘ��p



//������
void Ranking_Initialize() {
	RankingImage = LoadGraph("Images/Ranking.png");
	WaitTime = 0;
	Ranking_Read();

	//�N���b�NSE�Ǎ���
	ClickSE = LoadSoundMem("Sound/ClickSE.mp3");
}

//�I������
void Ranking_Finalize() {
	DeleteGraph(RankingImage);
}

//�X�V
void Ranking_Update() {
	//�p�b�h��A�{�^���������ꂽ��
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A]) {
		PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
		//�V�[�����^�C�g���ɖ߂�
		SceneManager_ChangeScene(SCENE_TITLE);
	}
}

//�`��
void Ranking_Draw() {
	//�����L���O�w�i�摜�̕\��
	DrawGraph(0, 0, RankingImage, FALSE);
	SetFontSize(50);
	DrawString(135, 50, "�����L���O���", GetColor(255, 255, 255));

	//�����L���O�ꗗ��\������
	SetFontSize(30);
	for (int i = 0; i < RANKCOUNT; i++) {
		DrawFormatString(210, 150 + i * 30, GetColor(255, 255, 255), "%2d %10.2lf", Ranking[i].no, (double)Ranking[i].score);

	}

	//�����̕\��(�_�ł�����)
	if (++WaitTime < 50) {
		SetFontSize(15);
		DrawString(180, 420, "-- A�{�^���������ƃ^�C�g���ɖ߂� --",GetColor(255,255,255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}

//�`��
void Ranking_NewDraw() {
	//�����L���O�w�i�摜�̕\��
	DrawGraph(0, 0, RankingImage, FALSE);
	SetFontSize(50);
	DrawString(180, 50, "NewRecode!!", GetColor(255, 255, 255));

	//�����L���O�ꗗ��\������
	SetFontSize(30);
	for (int i = 0; i < RANKCOUNT; i++) {
		DrawFormatString(210, 150 + i * 30, GetColor(255, 255, 255), "%2d %10.2lf", Ranking[i].no, (double)Ranking[i].score);

	}

	//�����̕\��(�_�ł�����)
	if (++WaitTime < 50) {
		SetFontSize(15);
		DrawString(180, 420, "-- A�{�^���������ƃ^�C�g���ɖ߂� --", GetColor(255, 255, 255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}

//�����L���O���͏���
void Ranking_Input() {
	Ranking[(RANKCOUNT - 1)].score = (double)Time / 1000;//�����L���O�f�[�^�̍Ō�ɃX�R�A��o�^
	Ranking[(RANKCOUNT - 1)].no = RANKCOUNT; //�����L���ONo.�͍Ō�ɂ��Ă���
	Ranking_Sort(); // �����L���O���בւ�
	Ranking_Save(); // �����L���O�f�[�^�̕ۑ�
	SceneManager_ChangeScene(SCENE_NEWRANKING); //�����L���O�\����ʂֈڍs
}


//�����L���O���ёւ�
void Ranking_Sort() {
	int i, j;
	RankingData work;
	
	for (i = 0; i < RANKCOUNT; i++) {
		for (j = i + 1; j < RANKCOUNT; j++) {
			if (Ranking[i].score > Ranking[j].score) {
				work = Ranking[i];
				Ranking[i] = Ranking[j];
				Ranking[j] = work;
			}
		}
	}
	// ���ʕt��
	for (i = 0; i < RANKCOUNT; i++) {
		Ranking[i].no = 1;
	}
	// ���_�������ꍇ�́A�������ʂɂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂɂ���
	for (i = 0; i < RANKCOUNT; i++) {
		for (j = i + 1; j < RANKCOUNT; j++) {
			if (Ranking[i].score < Ranking[j].score) {
				Ranking[j].no++;
			}
		}
	}
}

//�����L���O�ۑ�
void Ranking_Save() {
	FILE* fp;
	// �t�@�C�����J��
	fopen_s(&fp, RANKING_FILE, "w");	//w�͏�������
	if (fp != NULL) {
		// �����L���O�f�[�^���A�z��f�[�^����������
		for (int i = 0; i < RANKCOUNT; i++) {
			fprintf(fp, "%d %10.2lf\n", Ranking[i].no, Ranking[i].score);
		}
		//�t�@�C�������
		fclose(fp);
	}
	else {
		//�G���[����
		// printf("Ranking Data Error\n");
	}

}


//�ǂݍ���
void Ranking_Read() {
	FILE* fp;
	int i;
	//�t�@�C�����J��
	fopen_s(&fp, RANKING_FILE, "r");	//r�͓ǂݍ���
	if (fp != NULL) {
		//�����L���O�f�[�^���A�z��f�[�^��ǂݍ���
		for (int i = 0; i < RANKCOUNT; i++) {
			fscanf_s(fp, "%d %lf\n", &Ranking[i].no, &Ranking[i].score);
		}
		//�t�@�C�������
		fclose(fp);
	}
	////�t�@�C�����J���Ȃ��܂��͓ǂݍ��߂Ȃ���
	//else {
	//	//�G���[����
	//	//printf("Ranking file Error\n");

	//	//�����L���O�f�[�^�̏�����
	//	for (i = 0; i < RANKCOUNT; i++) {
	//		Ranking[i].no = (i + 1);
	//		Ranking[i].score = 1;
	//	}
	//}
}