#include "DxLib.h"
#include "SceneManager.h"
#include "Ranking.h"
#include "Game.h"
#include "Input.h"

static int RankingImage;	//ランキング画像
static int WaitTime;		//ランキング表示時間
struct  RankingData Ranking[RANKCOUNT];	//ランキングデータ管理用



//初期化
void Ranking_Initialize() {
	RankingImage = LoadGraph("Images/Ranking.png");
	WaitTime = 0;
	Ranking_Read();

	//クリックSE読込み
	ClickSE = LoadSoundMem("Sound/ClickSE.mp3");
}

//終了処理
void Ranking_Finalize() {
	DeleteGraph(RankingImage);
}

//更新
void Ranking_Update() {
	//パッドのAボタンが押されたら
	if (ButtonFlag == 1 && Input.Buttons[XINPUT_BUTTON_A]) {
		PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
		//シーンをタイトルに戻す
		SceneManager_ChangeScene(SCENE_TITLE);
	}
}

//描画
void Ranking_Draw() {
	//ランキング背景画像の表示
	DrawGraph(0, 0, RankingImage, FALSE);
	SetFontSize(50);
	DrawString(135, 50, "ランキング画面", GetColor(255, 255, 255));

	//ランキング一覧を表示する
	SetFontSize(30);
	for (int i = 0; i < RANKCOUNT; i++) {
		DrawFormatString(210, 150 + i * 30, GetColor(255, 255, 255), "%2d %10.2lf", Ranking[i].no, (double)Ranking[i].score);

	}

	//文字の表示(点滅をする)
	if (++WaitTime < 50) {
		SetFontSize(15);
		DrawString(180, 420, "-- Aボタンを押すとタイトルに戻る --",GetColor(255,255,255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}

//描画
void Ranking_NewDraw() {
	//ランキング背景画像の表示
	DrawGraph(0, 0, RankingImage, FALSE);
	SetFontSize(50);
	DrawString(180, 50, "NewRecode!!", GetColor(255, 255, 255));

	//ランキング一覧を表示する
	SetFontSize(30);
	for (int i = 0; i < RANKCOUNT; i++) {
		DrawFormatString(210, 150 + i * 30, GetColor(255, 255, 255), "%2d %10.2lf", Ranking[i].no, (double)Ranking[i].score);

	}

	//文字の表示(点滅をする)
	if (++WaitTime < 50) {
		SetFontSize(15);
		DrawString(180, 420, "-- Aボタンを押すとタイトルに戻る --", GetColor(255, 255, 255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}

//ランキング入力処理
void Ranking_Input() {
	Ranking[(RANKCOUNT - 1)].score = (double)Time / 1000;//ランキングデータの最後にスコアを登録
	Ranking[(RANKCOUNT - 1)].no = RANKCOUNT; //ランキングNo.は最後にしておく
	Ranking_Sort(); // ランキング並べ替え
	Ranking_Save(); // ランキングデータの保存
	SceneManager_ChangeScene(SCENE_NEWRANKING); //ランキング表示画面へ移行
}


//ランキング並び替え
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
	// 順位付け
	for (i = 0; i < RANKCOUNT; i++) {
		Ranking[i].no = 1;
	}
	// 得点が同じ場合は、同じ順位にする
	// 同順位があった場合の次の順位はデータ個数が加算された順位にする
	for (i = 0; i < RANKCOUNT; i++) {
		for (j = i + 1; j < RANKCOUNT; j++) {
			if (Ranking[i].score < Ranking[j].score) {
				Ranking[j].no++;
			}
		}
	}
}

//ランキング保存
void Ranking_Save() {
	FILE* fp;
	// ファイルを開く
	fopen_s(&fp, RANKING_FILE, "w");	//wは書き込み
	if (fp != NULL) {
		// ランキングデータ分、配列データを書き込む
		for (int i = 0; i < RANKCOUNT; i++) {
			fprintf(fp, "%d %10.2lf\n", Ranking[i].no, Ranking[i].score);
		}
		//ファイルを閉じる
		fclose(fp);
	}
	else {
		//エラー処理
		// printf("Ranking Data Error\n");
	}

}


//読み込み
void Ranking_Read() {
	FILE* fp;
	int i;
	//ファイルを開く
	fopen_s(&fp, RANKING_FILE, "r");	//rは読み込み
	if (fp != NULL) {
		//ランキングデータ分、配列データを読み込む
		for (int i = 0; i < RANKCOUNT; i++) {
			fscanf_s(fp, "%d %lf\n", &Ranking[i].no, &Ranking[i].score);
		}
		//ファイルを閉じる
		fclose(fp);
	}
	////ファイルが開けないまたは読み込めない時
	//else {
	//	//エラー処理
	//	//printf("Ranking file Error\n");

	//	//ランキングデータの初期化
	//	for (i = 0; i < RANKCOUNT; i++) {
	//		Ranking[i].no = (i + 1);
	//		Ranking[i].score = 1;
	//	}
	//}
}