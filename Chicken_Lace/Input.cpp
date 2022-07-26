#include "DxLib.h"
#include "Game.h"

#define BUTTONS 16

int iOldKey;
int iNowKey;

int iMouseX;
int iMouseY;

int ButtonFlag = 0;		//押され続けているとき

XINPUT_STATE Input;

////変更前のキー入力取得関数
//void InputKey(void) {
//	//入力キー取得
//	iOldKey = iNowKey;
//	iNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//	iKeyFlg = iNowKey & ~iOldKey;
//}

//変更後のキー入力取得関数
void InputPad()
{
	// 入力キー取得
	GetJoypadXInputState(DX_INPUT_PAD1, &Input);
	iOldKey = iNowKey;
	for (int i = 0; i < BUTTONS; i++)
	{
		if (Input.Buttons[i])
		{
			iNowKey = i;
			break;
		}
		iNowKey = 0;
	}
	if (iNowKey)
	{
		if (iNowKey && ~iOldKey)
		{
			ButtonFlag = 1;
		}
		if (iNowKey && iOldKey)
		{
			ButtonFlag = 2;
		}
	}
	else
	{
		ButtonFlag = 0;
	}
}