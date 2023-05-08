#include "DxLib.h"

#include "Title_Select_Explain.h"
#include "Cmp_SelectSelector.h"
#include "../Code/OriginMath.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/Component/Cmp_ButtonGroup.h"
#include "../Code/Component/Button.h"
#include "../Code/Scene/Scene.h"
#include "Cmp_3DSoundListener.h"
#include "Cmp_Button_ClickSound.h"
#include "Cmp_Sound.h"
#include "Title_Select_Explain_PageScrollExplain.h"
#include "Title_SoundSetting.h"
#include "SoundSetting.h"

#include <deque>
#include <string>
#include <sstream>
#include <functional>

Title_Select_Explain::Title_Select_Explain(std::deque<Cmp_Image*>& setImage, std::function<Scene* ()> sceneCreator) :image(&setImage), page(0), scrollExplain(new Title_Select_Explain_PageScrollExplain()){
	run = this; //������s�ɂ̓j���[�g�����Ƃ��Ď��g�����Ă���

	for (auto itr : *image) { itr->EditTranform()->EditPos().SetXYZ(640, 360, 0); } //�����Ő����摜�̕\���ʒu��ݒ肷��
	scroll = new Cmp_Sound(LoadSoundMem("Resource/se/scroll.wav")); //�X�N���[�����쐬
	Title_SoundSetting::SetUpExplainScroll(*scroll); //�X�N���[�����X�e�[�^�X�ݒ�

	if (image->size() <= 1) { scrollExplain->SetRunUpdateDraw(false, false); } //�X�N���[���s�ȃy�[�W���̏ꍇexplain�͎��s�֎~�ɂ���
	for (int i = 0; i < 2; ++i) { //�{�^���ݒ�
		button.push_back(new Button(1165 - 200 * i, 680, 150 / 2, 60 / 2)); //��{�^����ǉ�
		
		const char* name = nullptr;
		switch (i) { //�Ǎ��摜����p���O�ݒ�
		case 0: name = "Resource/image/Explain_Button1.png"; break;
		case 1: name = "Resource/image/Explain_Button2.png"; break;
		}

		button[i]->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph(name)), 1, button[i]->EditTransform())); //�{�^���ɉ摜��ǉ�
		button[i]->EditClick()->SetCmp(new Cmp_ButtonGroup(*button[i], button)); //�{�^���������ꂽ�ہA�����ꂽ�{�^���ȊO���~����@�\�̒ǉ�
		button[i]->EditClick()->SetCmp(new Cmp_Button_ClickSound(*SoundSetting::CreateDefaultButtonClickSound(Cmp_3DSoundListener::EditTransform()))); //�N���b�N���ꂽ���ɖ鉹��ǉ�
	}
	button[0]->EditClick()->SetCmp(new Cmp_SelectSelector(sceneCreator, &run)); //����{�^���������ꂽ��sceneCreator�ō쐬�����V�[���ֈڍs����ݒ�
	button[1]->EditClick()->SetCmp(new Cmp_SelectSelector([]() -> Scene* { return nullptr; }, &run)); //�߂�{�^���������ꂽ��Q�[���Z���N�g�֖߂�ݒ�

}

Title_Select_Explain::~Title_Select_Explain() {
	for (auto itr : *image) { delete itr; } //�e�v�f��new�Ő�������Ă���̂ŏ����Ă���
	for (auto itr : button) { delete itr; }

	delete image; //image�͑����ō��ꂽ�Q�Ƃ�������ŊǗ�����`���Ȃ̂ŏ����Ă���
	delete scroll; //�X�N���[�����̍폜
	delete scrollExplain; //�X�N���[���\�������̍폜
}

void Title_Select_Explain::Update() {
	for (auto itr : *image) { itr->Update(); } //�e��X�V����
	for (auto itr : button) { itr->Update(); }
	scrollExplain->Update();

	//�\���y�[�W�X�V����
	int max = image->size(); //�y�[�W�ő吔
	int oldPage = page; //�y�[�W��������m����ׂ̌��݃y�[�W�L�^�ϐ�
	if (max > 1) { //�y�[�W����������ꍇ
		int rotate = GetMouseWheelRotVol(); //�}�E�X�z�C�[����]��
		if (rotate <= -1) { page = (page + 1) % max; } //�O���ɂ܂킵����y�[�W+1
		if (rotate >= 1) { page = page - 1 < 0 ? (page + max - 1) % max : (page - 1) % max; } //���ɂ܂킵���ꍇ�y�[�W-1
		if (oldPage != page) { scroll->Play(); } //�y�[�W���삪�������ꍇ�T�E���h��炷
	}
	
	if (run != this) { 
		SetNext(run); //���g�ȊO��run�ɐݒ肳�ꂽ�炻���֌������Ƃ����Ӗ������Ȃ̂�SetNext
		Reset(); //���g�����ׂ̈�Reset���Ă�ł���
	}
}
void Title_Select_Explain::Draw() {
	GetMouseWheelRotVol(); //�ŏ��̎��s��Draw�̕��������̂Ń}�E�X�z�C�[���̉�]�ʂ�����������Ӗ������ł�����L��
	SetNext(this); //���g���������炪�����̂�SetNext�̏������p��

	std::string pageNum = std::to_string(page + 1) + "/" + std::to_string(image->size()); //���݂̃y�[�W���\��
	DrawString(1100, 32, pageNum.c_str(), GetColor(255, 255, 255)); //�J���[�͉��̕�
	scrollExplain->Draw(); //�y�[�W�������������ꍇ�y�[�W�߂���\�ł��鎖��\������

	(*image)[page]->Draw();
	for (auto itr : button) { itr->Draw(); }

}

void Title_Select_Explain::Reset() {
	page = 0; //�����y�[�W�ɖ߂�
	run = this; //���s�V�[�������g�ɖ߂�
	for (auto itr : button) { itr->Reset(); } //�{�^���̏�Ԃ����Z�b�g
}