#include "End.h"
#include "SceneManager.h"
#include "DxLib.h"

//�摜
static int EndImage;
//�G���h��ʕ\������
static int StopTime;

//������
void End_Initialize() {
	//�摜�ǂݍ���
	EndImage = LoadGraph("Images/End.png");
	//�~�߂邽�߂̎���
	StopTime = 0;
}

//�I������
void End_Finalize() {
	//�摜
	DeleteGraph(EndImage);
	//BGM
	StopMusic();
}

//�`��
void End_Draw() {
	//�摜
	DrawGraph(0, 0, EndImage, FALSE);

	//�^�C���̉��Z����&�I���i3�b��j
	if (++StopTime > 90) {
		SceneManager_ChangeScene(SCENE_STOP);
	}
}