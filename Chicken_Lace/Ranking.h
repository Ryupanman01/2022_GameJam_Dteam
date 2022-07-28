#pragma once

struct RankingData {
	int no;
	double score;
};

#define RANKCOUNT 7
#define RANKING_FILE "rankingdata.txt"

void Ranking_Initialize();	//������
void Ranking_Finalize();	//�I������
void Ranking_Update();		//�X�V
void Ranking_Draw();		//�`��
void Ranking_NewDraw();

void Ranking_Input();		//����
void Ranking_Sort();		//���ёւ�
void Ranking_Save();		//�ۑ�
void Ranking_Read();		//�ǂݍ���

extern struct RankingData Ranking[RANKCOUNT];