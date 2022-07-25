#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "Input.h"

static int TitleImage;		//タイトル画像格納
int TitleBGM, SelectSE, ClickSE;
static int MenuNumber = 0;
int PosY;
static int count = 0;
int ButtonFlag;

//初期化
void Title_Initialize() {
	//画像読み込み
	TitleImage = LoadGraph("Images/Title1.png");
	//タイトルBGM読込み
	TitleBGM = LoadSoundMem("Sound/TitleBGM.mp3");
	//セレクトSE読込み
	SelectSE = LoadSoundMem("Sound/SelectSE.mp3");
	//クリックSE読込み
	ClickSE = LoadSoundMem("Sound/ClickSE.mp3");

}

//終了処理
void Title_Finalize() {
	//画像消去
	DeleteGraph(TitleImage);
}

//更新
void Title_Update() {
	if (iKeyFlg & PAD_INPUT_B) {
		switch (MenuNumber)
		{
		case 0:
			StopSoundMem(TitleBGM);
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_GAME);
			break;
		case 1:
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_RANKING);
			break;
		case 2:
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_HELP);
			break;
		case 3:
			StopSoundMem(TitleBGM);
			PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
			SceneManager_ChangeScene(SCENE_END);
			break;
		}
	}
}

//描画
void Title_Draw() {
	//画像配置
	DrawGraph(0, 0, TitleImage, FALSE);
	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP, FALSE);

	//メニューカーソル移動処理
	if (iKeyFlg & PAD_INPUT_DOWN)
	{
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);
		if (++MenuNumber > 3)MenuNumber = 0;
	}
	if (iKeyFlg & PAD_INPUT_UP) {
		
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);
		if (--MenuNumber < 0)MenuNumber = 3;
	}

	////デバッグ用Line
	//DrawLine(0, 240, 640, 240, 0x000000, 1);
	//DrawLine(320, 0, 320, 480, 0x000000, 1);

	SetFontSize(55);
	DrawString(114, 100, "チキンレース！！", 0x000000);
	SetFontSize(35);
	DrawString(190, 250, "ゲームスタート！", 0x000000);
	DrawString(228, 300, "ランキング", 0x000000);
	DrawString(268, 350, "ヘルプ", 0x000000);
	DrawString(268, 400, "エンド", 0x000000);

	PosY = MenuNumber * 50;
	if (MenuNumber == 0)
	{
		DrawTriangle(150, 245 + PosY, 180, 265 + PosY, 150, 285 + PosY, GetColor(255, 0, 0), TRUE);
		DrawTriangle(153, 250 + PosY, 175, 265 + PosY, 153, 280 + PosY, 0x000000, TRUE);
	}
	else if (MenuNumber == 1)
	{
		DrawTriangle(190, 250 + PosY, 220, 270 + PosY, 190, 290 + PosY, GetColor(255, 0, 0), TRUE);
		DrawTriangle(193, 255 + PosY, 215, 270 + PosY, 193, 285 + PosY, 0x000000, TRUE);
	}
	else if (MenuNumber == 2 || MenuNumber == 3)
	{
		DrawTriangle(230, 250 + PosY, 260, 270 + PosY, 230, 290 + PosY, GetColor(255, 0, 0), TRUE);
		DrawTriangle(233, 255 + PosY, 255, 270 + PosY, 233, 285 + PosY, 0x000000, TRUE);
	}

}