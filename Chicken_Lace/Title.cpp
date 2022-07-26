#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "Input.h"

static int TitleImage;		//タイトル画像格納
static int TitleImage2;		//タイトル画像2格納
int TitleBGM, SelectSE, ClickSE;
static int MenuNumber = 0;
int PosY;
static int count = 0;		
int ButtonFlag;

//初期化
void Title_Initialize() {
	//画像読み込み
	TitleImage = LoadGraph("Images/Title1.png");
	//画像読込み
	TitleImage2 = LoadGraph("Images/Title2.png");
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
	DeleteGraph(TitleImage2);
}

//更新
void Title_Update() {
	if (iKeyFlg & PAD_INPUT_A) {
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
	DrawGraph(0, 15, TitleImage2, TRUE);
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

	//デバッグ用Line
	DrawLine(0, 240, 640, 240, 0x000000, 1);
	DrawLine(320, 0, 320, 480, 0x000000, 1);

	SetFontSize(55);
	////デバッグ用タイトル
	//DrawString(114, 100, "チキンレース！！", 0x000000);
	SetFontSize(34);
	if(MenuNumber!=0)DrawString(192, 254, "ゲームスタート！", 0x000000);
	if(MenuNumber!=1)DrawString(230, 304, "ランキング", 0x000000);
	if(MenuNumber!=2)DrawString(268, 354, "ヘルプ", 0x000000);
	if(MenuNumber!=3)DrawString(268, 400, "エンド", 0x000000);

	SetFontSize(45);
	PosY = MenuNumber * 49;
	if (MenuNumber == 0)
	{
		DrawBox(126, 237, 502, 288, 0x989898, TRUE);
		DrawString(132, 240, "ゲームスタート！", 0xffffff);
		//DrawTriangle(112, 245 + PosY, 142, 265 + PosY, 112, 285 + PosY, GetColor(255, 0, 0), TRUE);
		//DrawTriangle(115, 250 + PosY, 137, 265 + PosY, 115, 280 + PosY, 0x000000, TRUE);
	}
	else if (MenuNumber == 1)
	{
		DrawBox(193, 292, 440, 343, 0x989898, TRUE);
		DrawString(199, 295, "ランキング", 0xffffff);
		//DrawTriangle(161, 250 + PosY, 191, 270 + PosY, 161, 290 + PosY, GetColor(255, 0, 0), TRUE);
		//DrawTriangle(164, 255 + PosY, 186, 270 + PosY, 164, 285 + PosY, 0x000000, TRUE);
	}
	else if (MenuNumber == 2)
	{
		DrawBox(247, 342, 400, 393, 0x989898, TRUE);
		DrawString(250, 345, "ヘルプ", 0xffffff);
		//DrawTriangle(212, 250 + PosY, 242, 270 + PosY, 212, 290 + PosY, GetColor(255, 0, 0), TRUE);
		//DrawTriangle(215, 255 + PosY, 237, 270 + PosY, 215, 285 + PosY, 0x000000, TRUE);
	}
	else if (MenuNumber == 3)
	{
		DrawBox(247, 392, 400, 443, 0x989898, TRUE);
		DrawString(255, 395, "エンド", 0xffffff);
		//DrawTriangle(212, 250 + PosY, 242, 270 + PosY, 212, 290 + PosY, GetColor(255, 0, 0), TRUE);
		//DrawTriangle(215, 255 + PosY, 237, 270 + PosY, 215, 285 + PosY, 0x000000, TRUE);
	}


}