#pragma once

extern int iOldKey;	//前回の入力キー
extern int iNowKey;	//今回の入力キー
extern int iKeyFlg;	//入力キー情報

extern int iKeyX;	//X座標
extern int iKeyY;	//Y座標

//キー入力取得関数
void InputKey(void);