#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "Game.h"
#include "Help.h"
#include "Ranking.h"
#include "End.h"

static SCENE Scene = SCENE_TITLE;		//シーン管理変数
static SCENE NextScene = SCENE_NONE;	//次のシーン管理変数

static void SceneManager_InitializeModule(SCENE scene);	//指定モジュールの初期化
static void SceneManager_FinalizeModule(SCENE scene);	//指定モジュールの終了処理

//初期化
void SceneManager_Initialize() {
	SceneManager_InitializeModule(Scene);
}

//終了処理
void SceneManager_Finalize() {
	SceneManager_FinalizeModule(Scene);
}

//更新
void SceneManager_Update() {
	//次のシーンがセットされていたら
	if (NextScene != SCENE_NONE) {
		SceneManager_FinalizeModule(Scene);		//現在のシーンの終了処理を実行
		Scene = NextScene;						//次のシーンを現在のシーンセット
		NextScene = SCENE_NONE;					//次のシーン情報をクリア
		SceneManager_InitializeModule(Scene);	//現在のシーンを初期化
	}

	//シーンによって処理を分岐する
	switch (Scene) {
	case SCENE_TITLE:	//現在の画面がタイトルなら
		Title_Update();
		break;
	case SCENE_GAME:	//現在の画面がゲームなら
		Game_Update();
		break;
	case SCENE_HELP:	//現在の画面がヘルプなら
		Help_Update();
		break;
	case SCENE_RANKING:	//現在の画面がランキング（表示）なら
		Ranking_Update();
		break;
	case SCENE_END:		//現在の画面がエンドなら
		break;
	}
}

//描画
void SceneManager_Draw() {
	switch (Scene) {
	case SCENE_TITLE:	//現在の画面がタイトルなら
		Title_Draw();
		break;
	case SCENE_GAME:	//現在の画面がゲームなら
		Game_Draw();
		break;
	case SCENE_HELP:	//現在の画面がヘルプなら
		Help_Draw();
		break;
	case SCENE_RANKING:	//現在の画面がランキング（表示）なら
		Ranking_Draw();
		break;
	case SCENE_END:		//現在の画面がエンドなら
		End_Draw();
		break;
	}
}

//引数nextSceneにシーンを変更する
void SceneManager_ChangeScene(SCENE nextScene){
	NextScene = nextScene;	//次のシーンをセットする
}

//引数sceneモジュールを初期化する
static void SceneManager_InitializeModule(SCENE scene) {
	switch (scene) {
	case SCENE_TITLE:	//現在の画面がタイトルなら
		Title_Initialize();
		break;
	case SCENE_GAME:	//現在の画面がゲームなら
		Game_Initialize();
		break;
	case SCENE_HELP:	//現在の画面がヘルプなら
		Help_Initialize();
		break;
	case SCENE_RANKING:	//現在の画面がランキング（表示）なら
		Ranking_Initialize();
		break;
	case SCENE_END:		//現在の画面がエンドなら
		End_Initialize();
		break;
	}
}

//引数sceneモジュールの終了処理を行う
static void SceneManager_FinalizeModule(SCENE scene) {
	switch (scene) {
	case SCENE_TITLE:	//現在の画面がタイトルなら
		Title_Finalize();
		break;
	case SCENE_GAME:	//現在の画面がゲームなら
		Game_Finalize();
		break;
	case SCENE_HELP:	//現在の画面がヘルプなら
		Help_Finalize();
		break;
	case SCENE_RANKING:	//現在の画面がランキング（表示）なら
		Ranking_Finalize();
		break;
	case SCENE_END:		//現在の画面がエンドなら
		End_Finalize();
		break;
	}
}

//メニューで"ゲームエンド"が選択されたかどうかを返す
int SceneManager_GameEnd_Status() {
	if (Scene == SCENE_STOP) {	//ゲームを止める
		return 1;
	}
	else {
		return 0;
	}
}