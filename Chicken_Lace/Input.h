#pragma once

#define DEADZONE 17000
#define CURSOR_SPEED 10

extern int iOldKey;	//�O��̓��̓L�[
extern int iNowKey;	//����̓��̓L�[

extern int iKeyX;	//X���W
extern int iKeyY;	//Y���W

extern int ButtonFlag;

extern XINPUT_STATE Input;

//�L�[���͎擾�֐�
void InputPad(void);