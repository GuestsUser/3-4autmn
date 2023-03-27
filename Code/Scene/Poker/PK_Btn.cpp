#include "DxLib.h"

#include "PK_Btn.h"
#include "Section/Poker.h"

#include "Component.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include <deque>

PK_Btn::PK_Btn() :posList(std::deque<Cmp_Transform>((int)Poker::Character::length)) {
	img = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_dealer.png")), 1); //�Q�[�W�摜�̍쐬

	posList[(int)Poker::Character::leftCom].EditPos().SetXYZ(87, 511, 0); //�e�L�������{�^���|�W�V�����ɂȂ����ہA�{�^����z�u������W��ݒ�
	posList[(int)Poker::Character::topLeftCom].EditPos().SetXYZ(437, 142, 0);
	posList[(int)Poker::Character::topRightCom].EditPos().SetXYZ(994, 142, 0);
	posList[(int)Poker::Character::rightCom].EditPos().SetXYZ(1015, 491, 0);
	posList[(int)Poker::Character::player].EditPos().SetXYZ(674, 671, 0);

	FullReset(); //�����{�^���|�W�V�����������_������
}

PK_Btn::~PK_Btn() { delete img; } //�V�������Y���Ă����摜�͏I���Ƌ��ɍ폜����

void PK_Btn::Reset() {
	usePos = (usePos + 1) % (int)Poker::Character::length; //�g�p�|�W�V�����̍X�V
	img->EditTranform()->EditPos() = posList[usePos].ReadPos(); //�V�����|�W�V�����ɍ��킹�ă{�^���̈ʒu���X�V����
}

void PK_Btn::FullReset() {
	usePos = GetRand((int)Poker::Character::length - 1); //�|�W�V�����������_������AGetRand�͊��ʓ��̐��l���܂ރ����_���Ȃ̂�-1����
	Reset(); //�{�^���ʒu�ݒ�ׂ̈̌Ăяo��
}

void PK_Btn::Draw() {
	img->Draw(); //�{�^���̕`��
}