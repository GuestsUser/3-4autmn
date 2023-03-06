#include "PK_Main.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"

#include "../Code/Component/ComponentArray.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "Cmp_BetActionRecord.h"


Poker::Main::Main(Poker& set) :parent(&set), phase(0), count(0), actionRecord(std::deque<Cmp_BetActionRecord*>((int)Poker::Character::length)), playerGage(nullptr), playerGageBorder(nullptr) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��

	playerGage = parent->chara[(int)Poker::Character::player]->EditAppendCmp()->EditCmp<Gage>(); //�Q�[�W���o��
	playerGageBorder = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_Border>(); //�Q�[�W����e��@�\�����o��
	playerGageUpper = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_UpperBorder>(); //�v���C���[�Q�[�W�������ݒ�@�\�̎��o��
}

void Poker::Main::Update() {
	int access = parent->dealer->GetActionCharaSub(); //����A�N�V�������s���L�����ւ̓Y�������L�^����A�N�Z�X�V���[�g�J�b�g

	parent->chara[access]->SectionUpdate(); //����L�����̃Z�N�V�����pUpdate�����s
	Cmp_BetActionRecord::Action result = actionRecord[access]->GetFinalAction(); //�A�N�V�������ʂ��擾

	if (result == Cmp_BetActionRecord::Action::noAction) { return; } //�A�N�V�������ĂȂ��ꍇ�ȉ������͎��s�����I���
	if (result == Cmp_BetActionRecord::Action::raise) {
		for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allIn�����Ă��Ȃ��ꍇ���A�N�V������ԂɍX�V����
		playerGageBorder->SetBorder((float)(parent->pot->GetCurrentMaxBet()) / (parent->dealer->GetBB() * parent->dealer->GetMaxBet())); //�Q�[�W�̍Œ�l���X�V
		actionRecord[access]->SetIsAction(true); //���C�Y�����L�����̃A�N�V�����͏I���ς݂ɐݒ肷��
	}
	if (result == Cmp_BetActionRecord::Action::fold) { //�t�H�[���h�����ꍇ���E���h���f�`�F�b�N���s��
		for (auto itr : *parent->chara[access]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //��D��fold�\���֕ύX

		if (FoldCount(actionRecord, access) >= (int)Poker::Character::length - 1) { //1�L�����ȊO�S�ăL�������������ꍇ�m�[�R���e�X�g��
			SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
			parent->run = parent->list[(int)Poker::Section::nocontest]; //�m�[�R���e�X�g�ֈڍs
			return; //�����I���
		}
	}

	int endCount = ActionEndCount(actionRecord, access); //�A�N�V�����I���ς݃L�����̃`�F�b�N���s��
	parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //�I���ς݃L�������΂����̃L�����փA�N�V����������

	if (endCount >= (int)Poker::Character::length) { //�S�L�����I���ς݂̏ꍇ
		SequenceNextReset(actionRecord); //�A�N�V�������s�󋵂����V�[�������Ƀ��Z�b�g
		parent->dealer->SetActionChara((ChangeEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //change��allIn�����L�������A�N�V�����ΏۂȂ̂Ŏ���L�����̐ݒ�Ɋ܂߂�

		for (auto itr : parent->chara) { itr->SetSection(Chara::Section::change); } //�e�L�����̎��s�Z�N�V������ύX�Ashowdown�͐�p�̃Z�N�V�����������Ȃ��ׂ���ŗǂ�

		if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //�t�@�[�X�g�x�b�g�������ꍇ�����s����V�[�P���X�̓J�[�h����
		else { parent->run = parent->list[(int)Poker::Section::showdown]; } //�Z�J���h�x�b�g�Ȃ�V���[�_�E���ֈڍs����
	}
}
