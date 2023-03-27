#include "Poker.h"

#include "PK_CPU.h"
#include "PK_CPU_DataPlace.h"

#include "Cmp_ThinkingImage.h"
#include "Cmp_Transform.h"

#include "OriginMath.h"

void GetFirstCardPos(int sub, Vector3& edit) { //edit�ɓ��ꂽVector3�֓Y�����ɉ������J�[�h�擪���W��Ԃ�
	switch ((Poker::Character)sub) {
	case Poker::Character::leftCom: edit = Vector3(91, 301, 0); return; //leftCpu�̈�ԍŏ��ɔz�u����J�[�h�ʒu
	case Poker::Character::topLeftCom: edit = Vector3(199, 91, 0); return; //topLeftCpu�̈�ԍŏ��ɔz�u����J�[�h�ʒu
	case Poker::Character::topRightCom: edit = Vector3(756, 91, 0); return; //topRightCpu�̈�ԍŏ��ɔz�u����J�[�h�ʒu
	case Poker::Character::rightCom: edit = Vector3(1024, 296, 0); return; //rightCpu�̈�ԍŏ��ɔz�u����J�[�h�ʒu
	}
}

void GetCoinBackPos(int sub, Vector3& edit) { //edit�֓��ꂽVector3�֓Y�����ɉ������R�C���\���w�i�ʒu��Ԃ�
	switch ((Poker::Character)sub) {
	case Poker::Character::leftCom: edit = Vector3(151, 434, 0); return; //leftCpu�ʒu
	case Poker::Character::topLeftCom: edit = Vector3(502, 78, 0); return; //topLeftCpu�ʒu
	case Poker::Character::topRightCom: edit = Vector3(1059, 78, 0); return; //topRightCpu�ʒu
	case Poker::Character::rightCom: edit = Vector3(1082, 428, 0); return; //rightCpu�ʒu
	}
}

void GetThinkingPos(int sub, Vector3& edit) { //edit�֓��ꂽVector3�֓Y�����ɉ������R�C���\���w�i�ʒu��Ԃ�
	switch ((Poker::Character)sub) {
	case Poker::Character::leftCom: edit = Vector3(269, 434, 0); return; //leftCpu�ʒu
	case Poker::Character::topLeftCom: edit = Vector3(620, 78, 0); return; //topLeftCpu�ʒu
	case Poker::Character::topRightCom: edit = Vector3(1177, 78, 0); return; //topRightCpu�ʒu
	case Poker::Character::rightCom: edit = Vector3(1200, 428, 0); return; //rightCpu�ʒu
	}
}

void PK_CPU::DataPlace::Run(PK_CPU& parent, int sub) {
	int cardPlaceSpace = 33; //�J�[�h�z�u�Ԋu
	Vector3 firstCardPos; //�J�[�h�̐擪�ʒu
	GetFirstCardPos(sub, firstCardPos); //�擪�ʒu�̎擾

	std::deque<Cmp_Transform> cardPos = std::deque<Cmp_Transform>(5); //�J�[�h�z�u�󂯓n���p�ϐ�
	Cmp_Transform backPos = Cmp_Transform(); //�R�C���\���w�i�z�u�󂯓n���p
	GetCoinBackPos(sub, backPos.EditPos()); //�R�C���\���w�i�ʒu�擾

	for (int j = 0; j < cardPos.size(); ++j) { //�J�[�h�z�u
		cardPos[j].EditPos() = firstCardPos; //���ݑ���ΏۃL�����ɍ��킹�Ĉʒu�̏����ݒ�
		cardPos[j].EditPos().SetX(firstCardPos.GetX() + cardPlaceSpace * j); //�z�u�񐔂ɍ��킹�Ĉʒu���炵���s��
	}
	parent.Place(cardPos, backPos); //�J�[�h�ƃR�C���\���w�i�̔z�u

	Vector3 pos;
	GetThinkingPos(sub, pos);
	parent.EditAppendCmp()->SetCmp(new Cmp_ThinkingImage((Poker::Character)sub, *parent.dealer, pos)); //�l���p�摜��\������R���|�[�l���g�̓���
}