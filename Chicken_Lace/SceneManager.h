#pragma once

//シーン一覧
typedef enum {
	SCENE_TITLE,	//タイトル画面
	SCENE_GAME,		//ゲーム画面
	SCENE_CLEAR,
	SCENE_GAMEOVER,
	SCENE_HELP,		//ヘルプ画面
	SCENE_RANKING,	//ランキング画面（表示）
	SCENE_NEWRANKING,//NewRecodeのランキング画面
	SCENE_RANKINPUT,//ランキング入力
	SCENE_END,		//エンド画面
	SCENE_STOP,		//ストップ
	SCENE_NONE,		//シーン無し
}SCENE;

//関数一覧
void SceneManager_Initialize();	//初期化
void SceneManager_Finalize();	//終了
void SceneManager_Update();		//更新
void SceneManager_Draw();		//描画

//引数nextSceneにシーンを変更する
void SceneManager_ChangeScene(SCENE nextScene);

//ゲーム終了メニューが選択されたかどうかを返す値
int SceneManager_GameEnd_Status();