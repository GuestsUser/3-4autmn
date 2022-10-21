#include "DxLib.h"
#include "Scene_GameTitle.h"
#include "Scene_Select.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"

Scene_GameTitle::Scene_GameTitle() : keyOld(KEY_FREE), image(LoadGraph("Resource/image/Title.png")) {} //������
Scene_GameTitle::~Scene_GameTitle() { DeleteGraph(image); } //�ǂݍ��݉摜�̍폜

void Scene_GameTitle::Update() { //������s���鏈��
	int now = key->GetKeyState(REQUEST_MOUSE_LEFT); //���݂̃}�E�X���{�^���̓��͏�Ԃ̎擾

	if (keyOld != KEY_FREE && now == KEY_PULL) { SetNext(new Scene_GameTitle()); } //�O��܂ŃL�[���������ςȂ��łȂ����L�[�𗣂����u�Ԏ��V�[���ֈڍs

	keyOld = now; //����̒l��O��̕��ɋL�^����
}

void Scene_GameTitle::Draw() { DrawGraph(0, 0, image, FALSE); }
