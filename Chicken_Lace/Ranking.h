#pragma once

struct RankingData {
	int no;
	double score;
};

#define RANKCOUNT 7
#define RANKING_FILE "rankingdata.txt"

void Ranking_Initialize();	//初期化
void Ranking_Finalize();	//終了処理
void Ranking_Update();		//更新
void Ranking_Draw();		//描画
void Ranking_NewDraw();

void Ranking_Input();		//入力
void Ranking_Sort();		//並び替え
void Ranking_Save();		//保存
void Ranking_Read();		//読み込み

extern struct RankingData Ranking[RANKCOUNT];