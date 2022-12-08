#include "DxLib.h"

#include "Btn.h"
#include "Poker.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/Component/Cmp_Image.h"

#include <deque>

Btn::Btn() :posList(std::deque<Cmp_Transform>((int)Poker::Character::length)) {
	img = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_dealer.png")), 1); //�Q�[�W�摜�̍쐬

	posList[(int)Poker::Character::leftCom].EditPos().SetXYZ(87, 511, 0); //�e�L�������{�^���|�W�V�����ɂȂ����ہA�{�^����z�u������W��ݒ�
	posList[(int)Poker::Character::topCom].EditPos().SetXYZ(754, 146, 0);
	posList[(int)Poker::Character::rightCom].EditPos().SetXYZ(1015, 491, 0);
	posList[(int)Poker::Character::player].EditPos().SetXYZ(677, 699, 0);

	FullReset(); //�����{�^���|�W�V�����������_������
}

Btn::~Btn() { delete img; } //�V�������Y���Ă����摜�͏I���Ƌ��ɍ폜����

void Btn::Reset() {
	usePos = (usePos + 1) % (int)Poker::Character::length; //�g�p�|�W�V�����̍X�V
	img->EditTranform()->EditPos() = posList[usePos].ReadPos(); //�V�����|�W�V�����ɍ��킹�ă{�^���̈ʒu���X�V����
}

void Btn::FullReset() {
	usePos = GetRand((int)Poker::Character::length - 1); //�|�W�V�����������_������AGetRand�͊��ʓ��̐��l���܂ރ����_���Ȃ̂�-1����
	Reset(); //�{�^���ʒu�ݒ�ׂ̈̌Ăяo��
}

void Btn::Draw() {
	img->Draw(); //�{�^���̕`��
}