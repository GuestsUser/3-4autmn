#include <DxLib.h>

#include "../Scene.h"
#include "Poker.h"
#include "PokerFontData.h"

#include "PK_Ini.h"
#include "PK_Pre.h"
#include "PK_Main.h"
#include "PK_Change.h"
#include "PK_ShowDown.h"
#include "PK_NoContest.h"
#include "PK_GameOver.h"
#include "PK_GameClear.h"

#include "PK_Card.h"
#include "CPU.h"
#include "Pot.h"
#include "Chara.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"
#include "../Code/OriginMath.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Image.h"

#include <deque>

void Poker::Update() {
	run->Update(); //Update���s
	for (auto itr : chara) { if (itr->GetRunUpdate()) { itr->Update(); } } //�L�������̒ǉ��@�\�����s

	run = run->GetNext(); //���V�[���̎擾
	for (auto itr : list) { //���V�[����list���ɂ��镨���ǂ����`�F�b�N
		if (run == itr) { return; } //list���ɂ������ꍇDraw�ɏ������ڂ�
	}

	SetNext(run); //���V�[����Poker�Ǘ���Scene�ȊO�������ꍇ��������V�[���ɐݒ肵��Poker�͏I������
}

void Poker::Draw() {
	back->Draw(); //�w�i�`��
	pot->Draw(); //�|�b�g�`��
	dealer->Draw(); //�{�^���|�W�V�����̕`��
	for (auto itr : chara) { itr->Draw(); } //�e�L�����̎�D�Ƃ��������Ƃ��`��

	run->Draw();
}

Poker::Poker() :pot(new Pot()), dealer(new PK_Dealer()), cardDealer(new CardDealer()), back(nullptr), list(std::deque<Scene*>()) {
	PokerFontData::SetUp(); //�t�H���g�f�[�^�̎g�p����

	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_back.png")), 1); //�w�i�摜�쐬
	back->EditTranform()->EditPos().SetXYZ(1280 / 2, 720 / 2, 0); //��ʒ����ɔz�u

	for (int i = 0; i < (int)Character::length; ++i) { //�L�����N�^�[����
		Chara* current = nullptr;

		if (i == (int)Character::player) { current = new PK_Player(*pot, *dealer, *cardDealer); } //�v���C���[�̐���
		else { current = new CPU(i, *pot, *dealer, *cardDealer); } //cpu�̐���

		current->SetBBView(PK_Player::BBView::hide); //BB�\���͉B���Ă���
		

		chara.push_back(current);
	}
	cardDealer->Reset(); //�ŏ���Ini�����s���Ȃ��̂ŎR�D�����͏��������Ă���

	list.push_back(new Ini(*this));
	list.push_back(new Pre(*this));
	list.push_back(new Main(*this));
	list.push_back(new Change(*this));
	list.push_back(new ShowDown(*this));
	list.push_back(new NoContest(*this));
	list.push_back(new GameOver(*this));
	list.push_back(new GameClear(*this));



	run = list[(int)Section::pre]; //Pre����J�n
}

Poker::~Poker() {
	for (auto itr : list) { delete itr; } //Poker�ŊǗ����Ă����V�[���̍폜
	for (int i = 0; i < (int)Character::length; ++i) { delete chara[i]; }
	delete pot;
	delete dealer;
	delete cardDealer;
	delete back;
}



