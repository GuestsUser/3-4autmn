#include <DxLib.h>

#include "../Scene.h"
#include "Poker.h"
#include "PokerSections.h" //Poker�Ǘ��̃V�[����`���s���Ă���
#include "PokerFontData.h"

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
#include "Cmp_ThinkingImage.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Image.h"

#include <deque>

void SetCardPlaceDate(Cmp_Transform* cardPos); //cardPos�z��Ɋe�L�������̃J�[�h�����ʒu��ݒ肷��
void SetCoinBackPlaceDate(Cmp_Transform* backPos); //backPos�z��Ɋe�L�������̃R�C���\���w�i�����ʒu��ݒ肷��

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
	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_back.png")), 1); //�w�i�摜�쐬
	back->EditTranform()->EditPos().SetXYZ(1280 / 2, 720 / 2, 0); //��ʒ����ɔz�u
	PokerFontData::SetUp(); //�t�H���g�f�[�^�Q�Ɨp�N���X�̃Z�b�g�A�b�v

	int cardPlaceSpace = 134; //�J�[�h�z�u�Ԋu
	int cardPlaceSpaceCpu = 33; //�J�[�h�z�u�Ԋu�Acpu�p
	Vector3 monitorArea = Vector3(1.2, 2); //�Q�[�W���̉摜�T�C�Y�ɑ΂����̐��l���|�����l���N���b�N���m�͈͂Ƃ���
	Vector3 gagePlace = Vector3(442, 633); //�Q�[�W�̔z�u���W
	Vector3 actionPlace = Vector3(573, 663); //Call,Raise���e��A�N�V�����{�^���̔z�u���W
	Vector3 actionSize = Vector3(110, 90); //Call,Raise���e��A�N�V�����{�^���̉摜�T�C�Y
	Vector3 foldPlace = Vector3(772, 684); //foldButton�z�u���W
	Vector3 foldSize = Vector3(90, 45); //foldButton�摜�T�C�Y

	std::deque<Cmp_Transform> cardPos = std::deque<Cmp_Transform>(5); //�J�[�h�z�u�󂯓n���p�ϐ�
	Cmp_Transform backPos = Cmp_Transform(); //�R�C���\���w�i�z�u�󂯓n���p
	Cmp_Transform cardPosFirst[] = { Cmp_Transform(), Cmp_Transform() ,Cmp_Transform() ,Cmp_Transform() }; //�J�[�h�z�u�̍ۂ̏����ʒu����
	Cmp_Transform backPosFirst[] = { Cmp_Transform(), Cmp_Transform() ,Cmp_Transform() ,Cmp_Transform() }; //�R�C���\���w�i�z�u�̍ۂ̏����ʒu����

	SetCardPlaceDate(cardPosFirst); //�����ʒu�W��ݒ�
	SetCoinBackPlaceDate(backPosFirst);

	
	for (int i = 0; i < (int)Character::length; ++i) { //�L�����N�^�[����
		bool isPlayer = i == (int)Character::player; //����̍쐬�L�������v���C���[���ۂ��Atrue�Ńv���C���[
		Chara* current = nullptr;
		int useSpace = isPlayer ? cardPlaceSpace : cardPlaceSpaceCpu; //�J�[�h�z�u�Ɏg���z�u�Ԋu
		cardPos[0] = cardPosFirst[i]; //�J�[�h�擪�����݃L�����ɉ������ʒu�ɕύX
		backPos = backPosFirst[i]; //���݃L�����ɉ������R�C���\���ʒu�ɐݒ�

		for (int j = 0; j < cardPos.size(); ++j) { //�J�[�h�z�u
			cardPos[j].EditPos() = cardPosFirst[i].ReadPos(); //���ݑ���ΏۃL�����ɍ��킹�Ĉʒu�̏����ݒ�
			cardPos[j].EditPos().SetX(cardPosFirst[i].ReadPos().GetX() + useSpace * j); //�z�u�񐔂ɍ��킹�Ĉʒu���炵���s��
		}


		if (isPlayer) { //�v���C���[�̐������w�肳�ꂽ�ꍇ
			useSpace = cardPlaceSpace; //�z�u�Ԋu���v���C���[�̕��ɕύX
			current = new PK_Player(); //�v���C���[�̐���


			Button* action = new Button(actionPlace.GetX(), actionPlace.GetY(), actionSize.GetX() / 2, actionSize.GetY() / 2, true); //�A�N�V�����{�^���̍쐬
			Button* fold = new Button(foldPlace.GetX(), foldPlace.GetY(), foldSize.GetX() / 2, foldSize.GetY() / 2, true); //fold�{�^���̍쐬

			int* handle = new int[5]; //�����ǂݍ��݉摜�̕ۑ��p�̈�m��
			LoadDivGraph("Resource/image/poker_action_button.png", 5, 5, 1, 110, 90, handle); //�e��A�N�V�����p�{�^���̉摜�����ǂݍ���

			Cmp_Image* foldImage = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_fold.png")), 1, fold->EditTransform()); //fold�{�^���摜�쐬
			Cmp_Image* actionImage = new Cmp_Image(*handle, 5, action->EditTransform()); //�A�N�V�����{�^���摜�쐬

			action->SetAlways(actionImage); //�{�^���ɉ摜��ǉ�
			fold->SetAlways(foldImage);
			action->SetClick(new Cmp_Button_ClickCheck()); //�N���b�N�ɃN���b�N���m�p��R���|�[�l���g�̒ǉ�
			fold->SetClick(new Cmp_Button_ClickCheck());

			action->SetRunUpdate(false); //�{�^���n�͕K�v���ȊO���S�ɉB��
			fold->SetRunUpdate(false);
			action->SetRunDraw(false);
			fold->SetRunDraw(false);


			Cmp_Image* base = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_gage_back.png")), 1); //�Q�[�W�摜�̍쐬
			Cmp_Image* full = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_gage_full.png")), 1);
			base->EditTranform()->EditPos().SetXYZ(gagePlace.GetX(), gagePlace.GetY(), 0); //�Q�[�W�ʒu�ݒ�
			full->EditTranform()->EditPos().SetXYZ(gagePlace.GetX(), gagePlace.GetY(), 0);

			Gage* gage = new Gage(*base, *full); //�Q�[�W�̍쐬
			int sizeX = -1; int sizeY = -1;
			GetGraphSize(*full->ReadImage(), &sizeX, &sizeY); //�Q�[�W�T�C�Y�擾

			Cmp_Gage_MouseControl* control = new Cmp_Gage_MouseControl(*gage, Vector3(sizeX * monitorArea.GetX(), sizeY * monitorArea.GetY()), dealer->GetMaxBet()); //�Q�[�W�̃}�E�X�R���g���[���󂯕t���R���|�[�l���g�쐬
			control->SetRunUpdate(false); //�R���g���[���R���|�[�l���g�͒ʏ���s��؂��Ă���
			gage->SetCmp(control); //�Q�[�W���}�E�X����R���g���[������@�\�̒ǉ�
			gage->SetCmp(new Cmp_Gage_Border(*gage)); //�Q�[�W�����ݒ�@�\�̒ǉ�
			gage->SetCmp(new Cmp_Gage_UpperBorder(*gage)); //�Q�[�W����ݒ�@�\�̒ǉ�


			

			std::deque<PK_Card*> card = *current->EditCard();
			for (int j = 0; j < card.size(); ++j) { //�J�[�h���擾
				Button* button = new Button(cardPos[j].ReadPos().GetX(), cardPos[j].ReadPos().GetY(), 60, 75, false); //�J�[�h�N���b�N����p�{�^���̍쐬
				button->SetClick(new Cmp_Button_ClickCheck()); //�N���b�N���m�p��R���|�[�l���g�̒ǉ�

				card[j]->SetCmp(button); //�J�[�h�Ƀ{�^����ǉ�
			}


			current->SetCmp(gage); //�Q�[�W���v���C���[�ɒǉ�
			current->SetCmp(action); //�A�N�V�����{�^�����v���C���[�ɒǉ�
			current->SetCmp(fold); //fold�{�^�����v���C���[�ɒǉ�
			current->SetCmp(new Cmp_PlayerRaiseDraw(*current, *pot, *dealer)); //�v���C���[�̌��݃Q�[�W�ł̎x���z�\���p�R���|�[�l���g��ǉ�
		}
		else { //cpu�̐������w�肳�ꂽ�ꍇ
			current = new CPU(); //cpu�̐���
			current->SetCmp(new Cmp_CPUBetLogic(*dealer)); //cpu�̃x�b�g�ɕK�v�ȃf�[�^��Z�߂�BetLogic�𓱓�
		}


		current->Place(cardPos, backPos); //�J�[�h�ƃR�C���\���w�i�̔z�u
		current->SetCmp(new Cmp_BetActionRecord()); //�A�N�V�����̏�Ԃ��L�^����ActionRecord�𓱓�
		current->SetCmp(new Cmp_ThinkingImage(*current, chara, *dealer, backPosFirst[i].ReadPos())); //�l���p�摜��\������R���|�[�l���g�̓���

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



	run = list[1];
}

Poker::~Poker() {
	for (auto itr : list) { delete itr; } //Poker�ŊǗ����Ă����V�[���̍폜
	for (int i = 0; i < (int)Character::length; ++i) { delete chara[i]; }
	delete pot;
	delete dealer;
	delete cardDealer;
	delete back;
}



void SetCardPlaceDate(Cmp_Transform* cardPos) {
	cardPos[(int)Poker::Character::leftCom].EditPos().SetXYZ(91, 301, 0); //leftCpu�̈�ԍŏ��ɔz�u����J�[�h�ʒu
	cardPos[(int)Poker::Character::topCom].EditPos().SetXYZ(517, 95, 0); //topCpu�̈�ԍŏ��ɔz�u����J�[�h�ʒu
	cardPos[(int)Poker::Character::rightCom].EditPos().SetXYZ(1024, 296, 0); //rightCpu�̈�ԍŏ��ɔz�u����J�[�h�ʒu
	cardPos[(int)Poker::Character::player].EditPos().SetXYZ(360, 520, 0); //player�̈�ԍŏ��ɔz�u����J�[�h�ʒu
}
void SetCoinBackPlaceDate(Cmp_Transform* backPos) {
	backPos[(int)Poker::Character::leftCom].EditPos().SetXYZ(151, 434, 0); //leftCpu�̈�ԍŏ��ɔz�u����ʒu
	backPos[(int)Poker::Character::topCom].EditPos().SetXYZ(819, 82, 0); //topCpu�̈�ԍŏ��ɔz�u����ʒu
	backPos[(int)Poker::Character::rightCom].EditPos().SetXYZ(1082, 428, 0); //rightCpu�̈�ԍŏ��ɔz�u����ʒu
	backPos[(int)Poker::Character::player].EditPos().SetXYZ(418, 678, 0); //player�̈�ԍŏ��ɔz�u����ʒu
}