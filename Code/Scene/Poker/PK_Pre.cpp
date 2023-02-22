#include "PK_Pre.h"
#include "PK_Main.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "CardDealer.h"

#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/ComponentArray.h"
#include "Cmp_CPUBetLogic.h"


Poker::Pre::Pre(Poker& set) :parent(&set), actionRecord(std::deque<Cmp_BetActionRecord*>(4)) {
	playerGage = parent->chara[(int)Poker::Character::player]->EditAppendCmp()->EditCmp<Gage>(); //�Q�[�W���o��
	playerGageBorder = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_Border>(); //�Q�[�W����e��@�\�����o��
	playerGageUpper = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_UpperBorder>(); //�v���C���[�Q�[�W�������ݒ�@�\�̎��o��
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //�x�b�g�L�^�̃R���|�[�l���g�����o��
}

void Poker::Pre::Update() {
	BBSBLevy(parent->dealer->ReadBtn()->GetBtnPos(), parent->chara, actionRecord, *playerGageBorder, *playerGageUpper, *parent->pot, *parent->dealer); //BB�ASB�̒���
	playerGage->SetVol(0); //�v���C���[�̃x�b�g�Q�[�W������

	for (auto itr : parent->chara) {

		//�f�o�b�O�p
		//for (auto card : *itr->EditCard()) { card->SetDrawMode(PK_Card::DrawMode::front); } //�J�[�h���������Ă��� 

		for (auto card : *itr->EditCard()) { card->SetCard(parent->cardDealer->DeckDraw()); } //�R�D��������Ă����J�[�h����D�ɐݒ�
		if (typeid(*itr) == typeid(CPU)) { //���̃L������cpu�������ꍇ
			(itr->EditAppendCmp()->EditCmp<Cmp_CPUBetLogic>())->RaiseVolDecision(*itr, true); //���ݎ�D���烌�C�Y���ƕ����A���僌�C�Y���邩�ǂ��������肷��
		}
		else { //�v���C���[�������ꍇ
			for (auto card : *itr->EditCard()) { card->SetDrawMode(PK_Card::DrawMode::front); } //�J�[�h���������Ă��� 
		}
	}

	if (EnableCharaSearch(actionRecord, parent->dealer->ReadBtn()->GetBtnPos()) <= -1) { //���̒i�K�őS�L�����A�N�V�������I�����Ă����ꍇ
		SequenceNextReset(actionRecord); //�A�N�V�������s�L���̏�����
		parent->run = parent->list[(int)Poker::Section::change]; //�����V�[���Ɉڍs
		return; //�I���
	}
	parent->run = parent->list[(int)Poker::Section::main];
	((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(0); //�_�E���L���X�g�������g���n�b�L�����Ă邩�狖���āc�c

	//�f�o�b�O�p
	//parent->run = parent->list[(int)Poker::Section::change];
}
