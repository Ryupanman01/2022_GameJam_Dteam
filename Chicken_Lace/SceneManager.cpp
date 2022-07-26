#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "Game.h"
#include "Help.h"
#include "Ranking.h"
#include "End.h"

static SCENE Scene = SCENE_TITLE;		//�V�[���Ǘ��ϐ�
static SCENE NextScene = SCENE_NONE;	//���̃V�[���Ǘ��ϐ�

static void SceneManager_InitializeModule(SCENE scene);	//�w�胂�W���[���̏�����
static void SceneManager_FinalizeModule(SCENE scene);	//�w�胂�W���[���̏I������

//������
void SceneManager_Initialize() {
	SceneManager_InitializeModule(Scene);
}

//�I������
void SceneManager_Finalize() {
	SceneManager_FinalizeModule(Scene);
}

//�X�V
void SceneManager_Update() {
	//���̃V�[�����Z�b�g����Ă�����
	if (NextScene != SCENE_NONE) {
		SceneManager_FinalizeModule(Scene);		//���݂̃V�[���̏I�����������s
		Scene = NextScene;						//���̃V�[�������݂̃V�[���Z�b�g
		NextScene = SCENE_NONE;					//���̃V�[�������N���A
		SceneManager_InitializeModule(Scene);	//���݂̃V�[����������
	}

	//�V�[���ɂ���ď����𕪊򂷂�
	switch (Scene) {
	case SCENE_TITLE:	//���݂̉�ʂ��^�C�g���Ȃ�
		Title_Update();
		break;
	case SCENE_GAME:	//���݂̉�ʂ��Q�[���Ȃ�
		Game_Update();
		break;
	case SCENE_HELP:	//���݂̉�ʂ��w���v�Ȃ�
		Help_Update();
		break;
	case SCENE_RANKING:	//���݂̉�ʂ������L���O�i�\���j�Ȃ�
		Ranking_Update();
		break;
	case SCENE_END:		//���݂̉�ʂ��G���h�Ȃ�
		break;
	}
}

//�`��
void SceneManager_Draw() {
	switch (Scene) {
	case SCENE_TITLE:	//���݂̉�ʂ��^�C�g���Ȃ�
		Title_Draw();
		break;
	case SCENE_GAME:	//���݂̉�ʂ��Q�[���Ȃ�
		Game_Draw();
		break;
	case SCENE_HELP:	//���݂̉�ʂ��w���v�Ȃ�
		Help_Draw();
		break;
	case SCENE_RANKING:	//���݂̉�ʂ������L���O�i�\���j�Ȃ�
		Ranking_Draw();
		break;
	case SCENE_END:		//���݂̉�ʂ��G���h�Ȃ�
		End_Draw();
		break;
	}
}

//����nextScene�ɃV�[����ύX����
void SceneManager_ChangeScene(SCENE nextScene){
	NextScene = nextScene;	//���̃V�[�����Z�b�g����
}

//����scene���W���[��������������
static void SceneManager_InitializeModule(SCENE scene) {
	switch (scene) {
	case SCENE_TITLE:	//���݂̉�ʂ��^�C�g���Ȃ�
		Title_Initialize();
		break;
	case SCENE_GAME:	//���݂̉�ʂ��Q�[���Ȃ�
		Game_Initialize();
		break;
	case SCENE_HELP:	//���݂̉�ʂ��w���v�Ȃ�
		Help_Initialize();
		break;
	case SCENE_RANKING:	//���݂̉�ʂ������L���O�i�\���j�Ȃ�
		Ranking_Initialize();
		break;
	case SCENE_END:		//���݂̉�ʂ��G���h�Ȃ�
		End_Initialize();
		break;
	}
}

//����scene���W���[���̏I���������s��
static void SceneManager_FinalizeModule(SCENE scene) {
	switch (scene) {
	case SCENE_TITLE:	//���݂̉�ʂ��^�C�g���Ȃ�
		Title_Finalize();
		break;
	case SCENE_GAME:	//���݂̉�ʂ��Q�[���Ȃ�
		Game_Finalize();
		break;
	case SCENE_HELP:	//���݂̉�ʂ��w���v�Ȃ�
		Help_Finalize();
		break;
	case SCENE_RANKING:	//���݂̉�ʂ������L���O�i�\���j�Ȃ�
		Ranking_Finalize();
		break;
	case SCENE_END:		//���݂̉�ʂ��G���h�Ȃ�
		End_Finalize();
		break;
	}
}

//���j���[��"�Q�[���G���h"���I�����ꂽ���ǂ�����Ԃ�
int SceneManager_GameEnd_Status() {
	if (Scene == SCENE_STOP) {	//�Q�[�����~�߂�
		return 1;
	}
	else {
		return 0;
	}
}