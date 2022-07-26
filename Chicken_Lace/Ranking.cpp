#include "DxLib.h"
#include "SceneManager.h"
#include "Ranking.h"
#include "Input.h"

static int RankingImage;	//�����L���O�摜
static int WaitTime;		//�����L���O�\������
struct  RankingData Ranking[RANKCOUNT];	//�����L���O�f�[�^�Ǘ��p

//������
void Ranking_Initialize() {
	RankingImage = LoadGraph("Images/Ranking.png");
	WaitTime = 0;
	Ranking_Read();
}

//�I������
void Ranking_Finalize() {
	DeleteGraph(RankingImage);
}

//�X�V
void Ranking_Update() {
	//�p�b�h��B�{�^���������ꂽ��
	if (Input.Buttons[XINPUT_BUTTON_B]) {
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
		DrawFormatString(125, 150 + i * 30, GetColor(255, 255, 255), "%2d %10s %10d", Ranking[i].no, Ranking[i].name, Ranking[i].score);

	}

	//�����̕\��(�_�ł�����)
	if (++WaitTime < 50) {
		SetFontSize(15);
		DrawString(180, 420, "-- B�{�^���������ƃ^�C�g���ɖ߂� --",GetColor(255,255,255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}

//�����L���O���͏���
void Ranking_Input() {
	DrawGraph(0, 0, RankingImage, FALSE);
	//�t�H���g�T�C�Y�w��
	SetFontSize(20);
	//���O���͎w��������̕`��
	DrawString(150, 240, "�����L���O�ɓo�^���܂�", GetColor(0, 0, 0));
	DrawString(150, 270, "���O���p��(10�����ȓ�)�œ��͂��Ă�������", GetColor(0, 0, 0));
	// ���O�̓���
	DrawString(150, 310, "> ", GetColor(0, 0, 0));
	DrawBox(160, 305, 300, 335, GetColor(0, 0, 0), TRUE);
	KeyInputSingleCharString(170, 310, 10, Ranking[(RANKCOUNT - 1)].name, FALSE);
	//Ranking[(RANKCOUNT - 1)].score =  //�����L���O�f�[�^�̍Ō�ɃX�R�A��o�^
	Ranking[(RANKCOUNT - 1)].no = RANKCOUNT; //�����L���ONo.�͍Ō�ɂ��Ă���
	Ranking_Sort(); // �����L���O���בւ�
	Ranking_Save(); // �����L���O�f�[�^�̕ۑ�
	SceneManager_ChangeScene(SCENE_RANKING); //�����L���O�\����ʂֈڍs
}


//�����L���O���ёւ�
void Ranking_Sort() {
	int i, j;
	RankingData work;
	// �I��@�\�[�g
	for (i = 0; i < RANKCOUNT; i++) {
		for (j = i + 1; j < RANKCOUNT; j++) {
			if (Ranking[i].score <= Ranking[j].score) {
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
			if (Ranking[i].score > Ranking[j].score) {
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
			fprintf(fp, "%s %d %d\n", Ranking[i].name, Ranking[i].no, Ranking[i].score);
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
			fscanf_s(fp, "%s %d %d", Ranking[i].name, 10, &Ranking[i].no, &Ranking[i].score);
		}
		//�t�@�C�������
		fclose(fp);
	}
	//�t�@�C�����J���Ȃ��܂��͓ǂݍ��߂Ȃ���
	else {
		//�G���[����
		//printf("Ranking file Error\n");

		//�����L���O�f�[�^�̏�����
		for (i = 0; i < RANKCOUNT; i++) {
			Ranking[i].no = (i + 1);
			sprintf_s(Ranking[i].name, "...");
			Ranking[i].score = 1;
		}
	}
}