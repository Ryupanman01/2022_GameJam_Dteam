#pragma once

//�V�[���ꗗ
typedef enum {
	SCENE_TITLE,	//�^�C�g�����
	SCENE_GAME,		//�Q�[�����
	SCENE_CLEAR,
	SCENE_GAMEOVER,
	SCENE_HELP,		//�w���v���
	SCENE_RANKING,	//�����L���O��ʁi�\���j
	SCENE_NEWRANKING,//NewRecode�̃����L���O���
	SCENE_RANKINPUT,//�����L���O����
	SCENE_END,		//�G���h���
	SCENE_STOP,		//�X�g�b�v
	SCENE_NONE,		//�V�[������
}SCENE;

//�֐��ꗗ
void SceneManager_Initialize();	//������
void SceneManager_Finalize();	//�I��
void SceneManager_Update();		//�X�V
void SceneManager_Draw();		//�`��

//����nextScene�ɃV�[����ύX����
void SceneManager_ChangeScene(SCENE nextScene);

//�Q�[���I�����j���[���I�����ꂽ���ǂ�����Ԃ��l
int SceneManager_GameEnd_Status();