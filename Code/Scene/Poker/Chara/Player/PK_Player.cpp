#include "PK_Player.h"
#include "PK_Player_Main.h"
#include "PK_Player_Change.h"

#include "PK_CardDealer.h"
#include "PK_Chara.h"
#include "PK_Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"

#include "Cmp_PlayerRaiseDraw.h"
#include "Button.h"
#include "Gage.h"
#include "Cmp_Button_ClickCheck.h"
#include "Cmp_Gage_MouseControl.h"
#include "Cmp_Gage_Border.h"
#include "Cmp_Gage_UpperBorder.h"
#include "Cmp_Hand.h"
#include "Cmp_Image.h"

#include <deque>

PK_Player::PK_Player(PK_Pot& pot, PK_Dealer& dealer, PK_CardDealer& cardDealer) :pot(&pot), dealer(&dealer), cardDealer(&cardDealer), sectionModule(0) {
	int cardPlaceSpace = 134; //�J�[�h�z�u�Ԋu
	Vector3 firstCardPos = Vector3(360, 520, 0); //�J�[�h�̐擪�ʒu

	Vector3 monitorArea = Vector3(1.2, 2); //�Q�[�W���̉摜�T�C�Y�ɑ΂����̐��l���|�����l���N���b�N���m�͈͂Ƃ���
	Vector3 gagePlace = Vector3(442, 633); //�Q�[�W�̔z�u���W
	Vector3 actionPlace = Vector3(573, 663); //Call,Raise���e��A�N�V�����{�^���̔z�u���W
	Vector3 actionSize = Vector3(110, 90); //Call,Raise���e��A�N�V�����{�^���̉摜�T�C�Y
	Vector3 foldPlace = Vector3(772, 684); //foldButton�z�u���W
	Vector3 foldSize = Vector3(90, 45); //foldButton�摜�T�C�Y

	std::deque<Cmp_Transform> cardPos = std::deque<Cmp_Transform>(5); //�J�[�h�z�u�󂯓n���p�ϐ�
	Cmp_Transform backPos = Cmp_Transform(); //�R�C���\���w�i�z�u�󂯓n���p
	backPos.EditPos() = Vector3(418, 678, 0); //�\���w�i�����ʒu�ݒ�



	for (int j = 0; j < cardPos.size(); ++j) { //�J�[�h�z�u
		cardPos[j].EditPos() = firstCardPos; //���ݑ���ΏۃL�����ɍ��킹�Ĉʒu�̏����ݒ�
		cardPos[j].EditPos().SetX(firstCardPos.GetX() + cardPlaceSpace * j); //�z�u�񐔂ɍ��킹�Ĉʒu���炵���s��
	}

	actionButton = new Button(actionPlace.GetX(), actionPlace.GetY(), actionSize.GetX() / 2, actionSize.GetY() / 2, true); //�A�N�V�����{�^���̍쐬
	foldButton = new Button(foldPlace.GetX(), foldPlace.GetY(), foldSize.GetX() / 2, foldSize.GetY() / 2, true); //fold�{�^���̍쐬

	int* handle = new int[5]; //�����ǂݍ��݉摜�̕ۑ��p�̈�m��
	LoadDivGraph("Resource/image/poker_action_button.png", 5, 5, 1, 110, 90, handle); //�e��A�N�V�����p�{�^���̉摜�����ǂݍ���

	Cmp_Image* foldImage = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_fold.png")), 1, foldButton->EditTransform()); //fold�{�^���摜�쐬
	actionButtonImage = new Cmp_Image(*handle, 5, actionButton->EditTransform()); //�A�N�V�����{�^���摜�쐬

	actionButton->EditAlways()->SetCmp(actionButtonImage); //�{�^���ɉ摜��ǉ�
	foldButton->EditAlways()->SetCmp(foldImage);
	actionButton->EditClick()->SetCmp(new Cmp_Button_ClickCheck()); //�N���b�N�ɃN���b�N���m�p��R���|�[�l���g�̒ǉ�
	foldButton->EditClick()->SetCmp(new Cmp_Button_ClickCheck());

	actionButton->SetRunUpdate(false); //�{�^���n�͕K�v���ȊO���S�ɉB��
	foldButton->SetRunUpdate(false);
	actionButton->SetRunDraw(false);
	foldButton->SetRunDraw(false);


	Cmp_Image* base = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_gage_back.png")), 1); //�Q�[�W�摜�̍쐬
	Cmp_Image* full = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_gage_full.png")), 1);
	base->EditTranform()->EditPos().SetXYZ(gagePlace.GetX(), gagePlace.GetY(), 0); //�Q�[�W�ʒu�ݒ�
	full->EditTranform()->EditPos().SetXYZ(gagePlace.GetX(), gagePlace.GetY(), 0);

	gage = new Gage(*base, *full); //�Q�[�W�̍쐬
	gageBorder = new Cmp_Gage_Border(*gage);
	gageUpper = new Cmp_Gage_UpperBorder(*gage);
	int sizeX = -1; int sizeY = -1;
	GetGraphSize(*full->ReadImage(), &sizeX, &sizeY); //�Q�[�W�T�C�Y�擾

	gageControl = new Cmp_Gage_MouseControl(*gage, Vector3(sizeX * monitorArea.GetX(), sizeY * monitorArea.GetY()), dealer.GetMaxBet()); //�Q�[�W�̃}�E�X�R���g���[���󂯕t���R���|�[�l���g�쐬
	gageControl->SetRunUpdate(false); //�R���g���[���R���|�[�l���g�͒ʏ���s��؂��Ă���
	gage->EditAppendCmp()->SetCmp(gageControl); //�Q�[�W���}�E�X����R���g���[������@�\�̒ǉ�
	gage->EditAppendCmp()->SetCmp(gageBorder); //�Q�[�W�����ݒ�@�\�̒ǉ�
	gage->EditAppendCmp()->SetCmp(gageUpper); //�Q�[�W����ݒ�@�\�̒ǉ�


	std::deque<PK_Card*> card = *EditHand()->EditCard();
	for (int j = 0; j < card.size(); ++j) { //�J�[�h���擾
		Button* button = new Button(cardPos[j].ReadPos().GetX(), cardPos[j].ReadPos().GetY(), 60, 75, false); //�J�[�h�N���b�N����p�{�^���̍쐬
		button->EditClick()->SetCmp(new Cmp_Button_ClickCheck()); //�N���b�N���m�p��R���|�[�l���g�̒ǉ�

		card[j]->EditAppendCmp()->SetCmp(button); //�J�[�h�Ƀ{�^����ǉ�
	}
	record = new Cmp_BetActionRecord();

	EditAppendCmp()->SetCmp(gage); //�Q�[�W���v���C���[�ɒǉ�
	EditAppendCmp()->SetCmp(actionButton); //�A�N�V�����{�^�����v���C���[�ɒǉ�
	EditAppendCmp()->SetCmp(foldButton); //fold�{�^�����v���C���[�ɒǉ�
	EditAppendCmp()->SetCmp(new Cmp_PlayerRaiseDraw(*this, pot, dealer)); //�v���C���[�̌��݃Q�[�W�ł̎x���z�\���p�R���|�[�l���g��ǉ�
	EditAppendCmp()->SetCmp(record); //�A�N�V�����̏�Ԃ��L�^����ActionRecord�𓱓�

	Place(cardPos, backPos); //�J�[�h�ƃR�C���\���w�i�̔z�u

	sectionModule.push_back(new PK_Player::Main(*this));
	sectionModule.push_back(new PK_Player::Change(*this));

	runSection = sectionModule[(int)Section::main]; //main����X�^�[�g
}

PK_Player::~PK_Player() {
	for (auto itr : sectionModule) { delete itr; } //�e�Z�N�V�������폜
}

void PK_Player::SectionUpdate() {
	if (!runSection->GetRunUpdate()) { return; } //�Z�N�V���������s�֎~�Ȃ���s���Ȃ�
	runSection->Update(); //�w��Z�N�V������Update�����s
}
