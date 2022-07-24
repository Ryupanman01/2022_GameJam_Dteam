#include "End.h"
#include "SceneManager.h"
#include "DxLib.h"

//画像
static int EndImage;
//エンド画面表示時間
static int StopTime;

//初期化
void End_Initialize() {
	//画像読み込み
	EndImage = LoadGraph("Images/End.png");
	//止めるための時間
	StopTime = 0;
}

//終了処理
void End_Finalize() {
	//画像
	DeleteGraph(EndImage);
	//BGM
	StopMusic();
}

//描画
void End_Draw() {
	//画像
	DrawGraph(0, 0, EndImage, FALSE);

	//タイムの加算処理&終了（3秒後）
	if (++StopTime > 90) {
		SceneManager_ChangeScene(SCENE_STOP);
	}
}