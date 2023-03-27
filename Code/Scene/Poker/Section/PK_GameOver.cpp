#include <DxLib.h>
#include "PK_GameOver.h"

#include "Scene.h"
#include "Poker.h"
#include "ConstVal.h"

#include "PK_SectionLibrary.h"
#include "PokerFontData.h"

#include "Button.h"
#include "Cmp_Button_ClickCheck.h"

Poker::GameOver::GameOver(Poker& set) :parent(&set), count(0), clickStartTime(60), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false) {
	titlePos.SetXYZ(513, 189, 0); //�Q�[���I�[�o�[�ł��鎖���������b�Z�[�W�̈ʒu�ݒ�
	explainPos.SetXYZ(472, 312, 0); //�{�^�������z�u�ʒu

	nextButton.EditClick()->SetCmp(new Cmp_Button_ClickCheck()); //�N���b�N�`�F�b�N�p�R���|�[�l���g�ǉ�
}

void Poker::GameOver::Update() {
	nextButton.Update(); //�{�^��Update���s
	if (count == clickStartTime) { nextButton.SetRunClickMonitor(true); } //�J�n�^�C�~���O�ɂȂ�����N���b�N���m�J�n

	if (nextButton.GetRunUpdateClick()) { //�N���b�N���ꂽ�ꍇ
		FullReset(parent->chara, *parent->pot, *parent->dealer, *parent->cardDealer); //�V�����Q�[���̏���������
		parent->run = parent->list[(int)Poker::Section::pre]; //�ŏ��̏�Ԃɖ߂�

		nextButton.EditClick()->SetRunUpdate(false); //�N���b�N��Ԃ�߂�
		nextButton.EditClick()->SetRunDraw(false); //�O�̈�Draw���߂�
		nextButton.SetRunClickMonitor(false); //�N���b�N���m�̖�����
		count = -1; //�J�E���g���Z�b�g
	}

	++count;
}

void Poker::GameOver::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "�Q�[���I�[�o�[!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "��ʂ��N���b�N�ŐV�����n�߂�", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}