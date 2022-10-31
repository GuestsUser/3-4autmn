#include "DxLib.h"

#include "Scene_Explain.h"
#include "Cmp_SelectSelector.h"
#include "../Code/OriginMath.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/Component/Cmp_ButtonGroup.h"
#include "../Code/Component/Button.h"
#include "../Code/Scene/Scene.h"

#include "Scene_GameTitle.h" //�V�[���W�����v�̃e�X�g�Ƃ��ă^�C�g����ʂ𗘗p����

#include <deque>
#include <string>
#include <sstream>

Scene_Explain::Scene_Explain(std::deque<Cmp_Image*>& setImage, Scene* playGame) :image(&setImage), cursor(std::deque<Cmp_Image*>()), page(0) {
	run = this; //������s�ɂ̓j���[�g�����Ƃ��Ď��g�����Ă���

	for (auto itr : *image) { itr->EditTranform()->EditPos().SetXYZ(640, 360, 0); } //�����Ő����摜�̕\���ʒu��ݒ肷��

	if (image->size() > 1) { //�����摜������������ꍇ
		for (int i = 0; i < 2; ++i) {
			cursor.push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Cursor.png")), 1)); //�����ɖ��摜�̓ǂݍ��݂�����
			cursor[i]->EditTranform()->EditRotate().SetZ((270 - 180 * i) * OriginMath::Deg2Rad); //�摜�����̐ݒ�Ai==0�͏�����Ai==1�͉�����
			cursor[i]->EditTranform()->EditPos().SetXYZ(1280 / 2, 640 * (i % 2) + 80 / 2, 0); //�����Ɉʒu�ݒ������
		}
	}
	
	for (int i = 0; i < 2; ++i) { //�{�^���ݒ�
		button.push_back(new Button(1165 - 200 * i, 680, 150, 60)); //��{�^����ǉ�
		
		const char* name = nullptr;
		Scene* playScene = nullptr;
		switch (i) { //�Ǎ��摜����p���O�ݒ�ƃN���b�N���Ɉڍs����V�[���̐ݒ�
		case 0: name = "Resource/image/Explain_Button1.png"; playScene = playGame;  break; //playScene = new Scene_GameTitle(); //��������g���΃^�C�g����ʂֈڍs����
		case 1: name = "Resource/image/Explain_Button2.png"; playScene = nullptr;  break;
		}

		button[i]->SetAlways(new Cmp_Image(*new int(LoadGraph(name)), 1, button[i]->EditTransform())); //�{�^���ɉ摜��ǉ�
		button[i]->SetClick(new Cmp_ButtonGroup(*button[i], button)); //�{�^���������ꂽ�ہA�����ꂽ�{�^���ȊO���~����@�\�̒ǉ�
		button[i]->SetClick(new Cmp_SelectSelector(playScene, &run, button)); //�{�^���������ꂽ�ہArun��explain[i]������@�\�̒ǉ�
	}
}

Scene_Explain::~Scene_Explain() {
	for (auto itr : *image) { delete itr; } //�e�v�f��new�Ő�������Ă���̂ŏ����Ă���
	for (auto itr : cursor) { delete itr; }
	for (auto itr : button) { delete itr; }

	delete image; //image�͑����ō��ꂽ�Q�Ƃ�������ŊǗ�����`���Ȃ̂ŏ����Ă���
}

void Scene_Explain::Update() {
	for (auto itr : *image) { itr->Update(); } //�e��X�V����
	for (auto itr : cursor) { itr->Update(); }
	for (auto itr : button) { itr->Update(); }

	//�\���y�[�W�X�V����
	int max = image->size(); //�y�[�W�ő吔
	if (max > 1) { //�y�[�W����������ꍇ
		int rotate = GetMouseWheelRotVol(); //�}�E�X�z�C�[����]��
		if (rotate <= -1) { page = (page + 1) % max; } //�O���ɂ܂킵����y�[�W+1
		if (rotate >= 1) { page = page - 1 < 0 ? (page + max - 1) % max : (page - 1) % max; } //���ɂ܂킵���ꍇ�y�[�W-1
	}
	
	if (run != this) { 
		SetNext(run); //���g�ȊO��run�ɐݒ肳�ꂽ�炻���֌������Ƃ����Ӗ������Ȃ̂�SetNext
		page = 0; //���g���p�̏�����
		run = this; //���g�����p�ɖ߂��Ă���
	}
}
void Scene_Explain::Draw() {
	GetMouseWheelRotVol(); //�ŏ��̎��s��Draw�̕��������̂Ń}�E�X�z�C�[���̉�]�ʂ�����������Ӗ������ł�����L��
	SetNext(this); //���g���������炪�����̂�SetNext�̏������p��

	std::string pageNum = std::to_string(page + 1) + "/" + std::to_string(image->size()); //���݂̃y�[�W���\��
	DrawString(1100, 32, pageNum.c_str(), GetColor(255, 255, 255)); //�J���[�͉��̕�
	(*image)[page]->Draw();
	//for (auto itr : *image) { itr->Draw(); } //�e��X�V����
	for (auto itr : cursor) { itr->Draw(); }
	for (auto itr : button) { itr->Draw(); }

}