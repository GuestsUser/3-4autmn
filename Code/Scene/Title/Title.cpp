#include "DxLib.h"
#include "Title.h"
#include "Title_Select.h"
#include "Title_SoundSetting.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"

#include "Cmp_Sound.h"

Title::Title() : keyOld(KEY_FREE), image(LoadGraph("Resource/image/Title.png")) { //������
	bgm = new Cmp_Sound(LoadSoundMem("Resource/bgm/Title.wav"));
	click = new Cmp_Sound(LoadSoundMem("Resource/se/Pause_Click.wav"));

	Title_SoundSetting::SetUpTitleSelectBGM(*bgm); //bgm�̃X�e�[�^�X��ݒ�
	Title_SoundSetting::SetUpTitleClick(*click); //click�̃X�e�[�^�X��ݒ�
	bgm->Play(); //bgm�𗬂�
}
Title::~Title() { 
	DeleteGraph(image); //�ǂݍ��݉摜�̍폜
	delete bgm; //�쐬�����T�E���h�̍폜
	delete click;
}

void Title::Update() { //������s���鏈��
	int now = key->GetKeyState(REQUEST_MOUSE_LEFT); //���݂̃}�E�X���{�^���̓��͏�Ԃ̎擾
	
	if (keyOld != KEY_FREE && now == KEY_PULL) { 
		click->Play(); //�N���b�N����炷
		bgm->Stop(); //bgm���~�߂�
		SetNext(new Title_Select());
	} //�O��܂ŃL�[���������ςȂ��łȂ����L�[�𗣂����u�Ԏ��V�[���ֈڍs

	keyOld = now; //����̒l��O��̕��ɋL�^����
}

void Title::Draw() { DrawGraph(0, 0, image, FALSE); }
