#include "DxLib.h"
#include "Game.h"

#define BUTTONS 16

int iOldKey;
int iNowKey;

int iMouseX;
int iMouseY;

int ButtonFlag = 0;		//�����ꑱ���Ă���Ƃ�

XINPUT_STATE Input;

////�ύX�O�̃L�[���͎擾�֐�
//void InputKey(void) {
//	//���̓L�[�擾
//	iOldKey = iNowKey;
//	iNowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//	iKeyFlg = iNowKey & ~iOldKey;
//}

//�ύX��̃L�[���͎擾�֐�
void InputPad()
{
	// ���̓L�[�擾
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