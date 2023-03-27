#pragma once
#include "Cmp_Transform.h"

#include <map>
#include <unordered_map>

class Cmp_Image;
class PK_Chara;

class PK_Pot { //�T�C�h�|�b�g�v�Z�A�e�L�����̃|�b�g�󂯎�莑�i�̋L�^�Ȃǎx���v�Z�ɕK�v�ȐF�X��L����N���X
	Cmp_Image* back; //���|�b�g�Ɏx�����Ă邩�\������ׂ̃G���A�̔w�i�摜
	std::map<int, int> pot; //�|�b�g�Afirst=�|�b�g�̗v���z�Asecond=���̃|�b�g���̍��v���z
	std::unordered_map<const PK_Chara*, int> charaPayment; //�ǂ̃L���������x���������L�^�A�ǂ̃|�b�g���󂯎�錠�����������f����̂Ɏg�p�Afirst=�L�����Asecond=�x���z
	Cmp_Transform textPos; //�|�b�g���z�\���̍��W

public:
	PK_Pot();
	~PK_Pot();

	void Reset(); //���E���h�I�����ɌĂяo���A�|�b�g��x���󋵂����Z�b�g����
	int PayOut(const PK_Chara& user); //�L������n���Ƃ������󂯎�錠���̂���S�Ẵ|�b�g���x������A�x�������|�b�g�͋�ɂȂ�
	void SetSidePot(int pay, const PK_Chara& user); //AllIn����������Ăяo���A�����̋��z�ɍ��킹���V�����|�b�g���쐬���A�ĐU�蕪�����s��
	void SetMainPot(int pay, const PK_Chara& user); //���펞�|�b�g�ւ̎x��������ΌĂяo��

	int Inquiry(const PK_Chara& user); //payOut���l����������͕����o���͍s��Ȃ����������o�������Ɖ��ׂ̋@�\
	int TotalAmount(); //pot���̌��ݍ��v���z��Ԃ�
	int GetCurrentMaxBet() { return pot.size() > 0 ? (--pot.end())->first : 0; } //��x�ł��x�����������ꍇpot�̍Ō�̗v�f�̓Y�������ő�x�b�g�z�ƂȂ�

	void Draw(); //�|�b�g���z�\���̔w�i��`�ʂ���
};
