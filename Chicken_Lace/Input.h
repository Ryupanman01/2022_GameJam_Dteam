#pragma once

#define DEADZONE 17000
#define CURSOR_SPEED 10

extern int iOldKey;	//前回の入力キー
extern int iNowKey;	//今回の入力キー

extern int iKeyX;	//X座標
extern int iKeyY;	//Y座標

extern int ButtonFlag;

extern XINPUT_STATE Input;

//キー入力取得関数
void InputPad(void);