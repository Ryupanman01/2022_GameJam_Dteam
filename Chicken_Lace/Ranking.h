#pragma once

struct RankingData {
	int no;
	double score;
};

#define RANKCOUNT 7
#define RANKING_FILE "rankingdata.txt"

void Ranking_Initialize();	//‰Šú‰»
void Ranking_Finalize();	//I—¹ˆ—
void Ranking_Update();		//XV
void Ranking_Draw();		//•`‰æ
void Ranking_NewDraw();

void Ranking_Input();		//“ü—Í
void Ranking_Sort();		//•À‚Ñ‘Ö‚¦
void Ranking_Save();		//•Û‘¶
void Ranking_Read();		//“Ç‚İ‚İ

extern struct RankingData Ranking[RANKCOUNT];