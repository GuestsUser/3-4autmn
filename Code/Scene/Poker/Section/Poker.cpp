#include <DxLib.h>

#include "Scene.h"
#include "Poker.h"
#include "PokerFontData.h"
#include "Title/Title_Select.h"

#include "PK_Ini.h"
#include "PK_Pre.h"
#include "PK_Main.h"
#include "PK_Change.h"
#include "PK_ShowDown.h"
#include "PK_NoContest.h"
#include "PK_GameOver.h"
#include "PK_GameClear.h"
#include "PK_NewGameReset.h"
#include "Cmp_PK_Pause.h"

#include "PK_Chara.h"
#include "PK_CPU.h"
#include "PK_Player.h"

#include "PK_Card.h"
#include "PK_CardDealer.h"
#include "PK_Dealer.h"
#include "PK_Pot.h"
#include "OriginMath.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "Button.h"
#include "Gage.h"
#include "Cmp_Button_ClickCheck.h"
#include "Cmp_ButtonOverlapGroup.h"
#include "Cmp_Gage_MouseControl.h"
#include "Cmp_Gage_Border.h"
#include "Cmp_Gage_UpperBorder.h"
#include "Cmp_Image.h"

#include <deque>

void Poker::Update() {
	pauseButon->Update(); //�|�[�Y��ʂƃ{�^���̏������s
	if (pauseButon->GetRunUpdateClick()) { return; } //�N���b�N���ꂽ�ꍇ�|�[�Y��ʎ��s���Ȃ̂ŃQ�[���V�[���Ɋւ��鏈���͎��s���Ȃ�

	run->Update(); //�w��Z�N�V�����̏������s
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

	run->Draw(); //���s�Z�N�V������p�`��
	pauseButon->Draw(); //�|�[�Y��ʂƃ{�^���̕`��
}

Poker::Poker() :pot(new PK_Pot()), dealer(new PK_Dealer()), cardDealer(new PK_CardDealer()), back(nullptr), list(std::deque<Scene*>()) {
	PokerFontData::SetUp(); //�t�H���g�f�[�^�̎g�p����

	pauseButon = new Button(65, 53, 45, 37);
	pauseButon->EditAlways()->SetCmp(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pause.png")), 1, pauseButon->EditTransform())); //�|�[�Y�{�^���摜���쐬
	pauseButon->EditAlways()->SetCmp(new Cmp_ButtonOverlapGroup(*pauseButon)); //�|�[�Y�{�^���ɉ����ꂽ���d�Ȃ��Ă���{�^���̓��͂�؂�@�\�̒ǉ�
	//��L�d�Ȃ��Ă���{�^�����͎�t�֎~�R���|�[�l���g�̃O���[�v�͊Y���{�^���쐬�ӏ��Ŋe�O���[�v�֊i�[����
	pauseButon->EditClick()->SetCmp(new Cmp_PK_Pause(*pauseButon, *this)); //�N���b�N���ꂽ���N������|�[�Y��ʎ��s�@�\�ǉ�

	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_back.png")), 1); //�w�i�摜�쐬
	back->EditTranform()->EditPos().SetXYZ(1280 / 2, 720 / 2, 0); //��ʒ����ɔz�u

	for (int i = 0; i < (int)Character::length; ++i) { //�L�����N�^�[����
		PK_Chara* current = nullptr;

		if (i == (int)Character::player) { current = new PK_Player(*pot, *dealer, *cardDealer); } //�v���C���[�̐���
		else { current = new PK_CPU(i, *pot, *dealer, *cardDealer); } //cpu�̐���

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
	list.push_back(new NewGameReset(*this));


	run = list[(int)Section::pre]; //Pre����J�n
}

Poker::~Poker() {
	PokerFontData::Release(); //�t�H���g�f�[�^���i�[���Ă����z����N���[������
	for (auto itr : list) { delete itr; } //Poker�ŊǗ����Ă����V�[���̍폜
	for (int i = 0; i < (int)Character::length; ++i) { 
		delete chara[i]; 
	}
	delete pot;
	delete dealer;
	delete cardDealer;
	delete back;
	delete pauseButon;
}

void Poker::SetNextSection(Section section) {
	if (section == Section::titleback) { SetNext(new Title_Select()); } //titleback���w�肳�ꂽ��Q�[���Z���N�g��ʂ֖߂�
	else { run = list[(int)section]; } //����ȊO�Ȃ�Y���Z�N�V�����ֈڍs����
}


