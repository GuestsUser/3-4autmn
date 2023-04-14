#include "DxLib.h"
#include "Cmp_PK_Pause.h"
#include "PK_Pause_DataSetting.h"

#include "PK_Pause_PauseEnd.h"
#include "PokerFontData.h"

#include "Button.h"
#include "Cmp_ButtonGroup.h"
#include "Cmp_Image.h"
#include "OriginMath.h"

#include <deque>
#include <string>

Cmp_PK_Pause::Cmp_PK_Pause(Button& set, Poker& poker) :parent(&set), poker(&poker), runClose(false) {
	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause_back.png")), 1); //�w�i�쐬

	std::deque<Cmp_Transform*> ts;
	for (int i = 0; i < 3; ++i) { //�{�^���쐬
		button.push_back(new Button(0, 0, 270 / 2, 80 / 2));
		ts.push_back(button[i]->EditTransform()); //	�{�^���ʒu�𑵂���ׂ�Transform�l��

		button[i]->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause_tile.png")), 1, ts[i]));
		button[i]->EditClick()->SetCmp(new Cmp_ButtonGroup(*button[i], button)); //�{�^���O���[�v�ǉ�
	}
	DataSetting::BackPlace(*back); //�w�i�̈ʒu�ݒ�
	DataSetting::ButtonNameImageSet(button); //�{�^���ɕ\�����郁�b�Z�[�W�̐ݒ�
	DataSetting::ButtonAppendCmpSet(*this, button); //�{�^���������ꂽ��ۂ̋@�\��ݒ�
	OriginMath::MatrixPlacePos(ts, 1, 0, 374 - 275, Vector3(640, 275)); //�{�^���̈ʒu�ݒ�
}

void Cmp_PK_Pause::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~�Ŏ��s���Ȃ�

	parent->SetRunClickMonitor(false); //�e�{�^���̃N���b�N���m��؂�

	back->Update(); //�w�iUpdate
	for (auto itr : button) { itr->Update(); } //�{�^��Update

	if (runClose) { //�{�^���R���|�[�l���g����I���̎w�����������ꍇ
		Cmp_PK_Pause::PauseEnd::Close(*this); //Update������Poker�̊esection�֖߂�����
		for (auto itr : button) { itr->Reset(); } //�ێ�����{�^���̃��Z�b�g
		runClose = false; //�I���w�߂�false�ɖ߂�
	}
}

void Cmp_PK_Pause::Draw() {
	if (!GetRunDraw()) { return; } //���s�֎~�Ŏ��s���Ȃ�
	back->Draw(); //�w�i�`��
	for (auto itr : button) { itr->Draw(); } //�{�^���`��
}
