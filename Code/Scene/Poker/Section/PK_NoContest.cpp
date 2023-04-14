#include <DxLib.h>
#include "PK_NoContest.h"

#include "Scene.h"
#include "Poker.h"
#include "ConstVal.h"

#include "PK_CPU.h"
#include "PK_Pot.h"
#include "PK_Player.h"
#include "PK_SectionLibrary.h"
#include "PokerFontData.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_Button_ClickCheck.h"
#include "ComponentArray.h"
#include "Cmp_ButtonOverlapGroup.h"

Poker::NoContest::NoContest(Poker& set) :parent(&set), count(0), payOutTime(60), clickStartTime(120), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false), actionRecord(std::deque<Cmp_BetActionRecord*>((int)Poker::Character::length)) {
	titlePos.SetXYZ(513, 189, 0); //�m�[�R���e�X�g�ł��鎖���������b�Z�[�W�̈ʒu�ݒ�
	explainPos.SetXYZ(484, 312, 0); //�{�^�������z�u�ʒu

	nextButton.EditClick()->SetCmp(new Cmp_Button_ClickCheck()); //�N���b�N�`�F�b�N�p�R���|�[�l���g�ǉ�
	parent->pauseButon->EditAlways()->EditCmp<Cmp_ButtonOverlapGroup>()->EditGroup()->push_back(&nextButton); //�|�[�Y�{�^���ɏd�Ȃ��Ă��鎟�V�[���ڍs�{�^�����d�Ȃ薳�����R���|�[�l���g�֊i�[����

	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}

void Poker::NoContest::Update() {
	nextButton.Update(); //�{�^��Update���s

	if (count == payOutTime) {
		PK_Chara* enableChara = nullptr; //�~��Ȃ������L����������
		std::deque<PK_Chara*> foldChara = std::deque<PK_Chara*>(); //�t�H�[���h�����L�����Z��(�s�k�ς݂͏���)

		for (int i = 0; i < parent->chara.size(); ++i) { //�L����������������L�����Afold�L�����A���O�L�����Ɏd������
			if (actionRecord[i]->GetIsLose()) { continue; } //�s�k�ς݂̏ꍇ�����������L�����ֈڍs
			if (actionRecord[i]->GetActionRecord(Cmp_BetActionRecord::Action::fold)) { foldChara.push_back(parent->chara[i]); continue; } //fold���Ă�ꍇfoldCara�֊i�[�����L�����ֈڍs
			enableChara = parent->chara[i]; //���݃L������enableChara�֊i�[
		}
		enableChara->SetCoin(enableChara->GetCoint() + parent->pot->PayOut(*enableChara)); //���z�����
		if (parent->pot->TotalAmount() <= 0) { ++count; return; } //���z���Ȃ��Ȃ�ΏI���
		FoldMemberPayOut(foldChara, *parent->pot); //�]���Ă����fold�L�����֕��z

	}

	if (count == clickStartTime) { //�N���b�N���m�J�n�^�C�~���O�ɂȂ�����

		LoseSet(parent->chara, actionRecord); //�s�k�󋵂̐ݒ�
		Poker::Section next = GameEndCheck(parent->chara, actionRecord); //�s�k�󋵂��玟�������ׂ��V�[�����擾

		if (next != Poker::Section::ini) { //ini(���s���ׂ�)�ȊO���������ꍇ
			parent->run = parent->list[(int)next]; //���̃V�[���Ɉڍs
			return; //�I���
		}

		nextButton.SetRunClickMonitor(true); //�N���b�N���m�J�n
	}

	if (nextButton.GetRunUpdateClick()) { //�N���b�N���ꂽ�ꍇ
		parent->run = parent->list[(int)Poker::Section::ini]; //�ŏ��̏�Ԃɖ߂�
		Reset(); //�e�퍀�ڂ����Z�b�g����
		return; //�I���
	}

	++count;
}

void Poker::NoContest::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "�m�[�R���e�X�g!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "��ʂ��N���b�N�Ŏ��Q�[����", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}

void Poker::NoContest::Reset() {
	nextButton.EditClick()->SetRunUpdate(false); //�N���b�N��Ԃ�߂�
	nextButton.EditClick()->SetRunDraw(false); //�O�̈�Draw���߂�
	nextButton.SetRunClickMonitor(false); //�N���b�N���m�̖�����
	count = 0; //�J�E���g���Z�b�g
}