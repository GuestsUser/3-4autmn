#include "DxLib.h"
#include "Title.h"
#include "Title_Select.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"

Title::Title() : keyOld(KEY_FREE), image(LoadGraph("Resource/image/Title.png")),BGM(LoadSoundMem("Resource/bgm/Title.wav")),Click(LoadSoundMem("Resource/se/Pause_Click.wav")) {} //������
Title::~Title() { DeleteGraph(image); } //�ǂݍ��݉摜�̍폜

void Title::Update() { //������s���鏈��
	if (CheckSoundMem(BGM) == 0) {
		ChangeVolumeSoundMem(110, BGM);
		PlaySoundMem(BGM, DX_PLAYTYPE_LOOP);
	}
	int now = key->GetKeyState(REQUEST_MOUSE_LEFT); //���݂̃}�E�X���{�^���̓��͏�Ԃ̎擾
	

	if (keyOld != KEY_FREE && now == KEY_PULL) { 
		PlaySoundMem(Click, DX_PLAYTYPE_BACK);
		SetNext(new Title_Select());
		StopSoundMem(BGM);
	} //�O��܂ŃL�[���������ςȂ��łȂ����L�[�𗣂����u�Ԏ��V�[���ֈڍs

	keyOld = now; //����̒l��O��̕��ɋL�^����
}

void Title::Draw() { DrawGraph(0, 0, image, FALSE); }
