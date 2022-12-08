#pragma once
#include "../Code/Component/Cmp_Transform.h"

#include <map>
#include <unordered_map>

class Cmp_Image;
class Chara;

class Pot { //�T�C�h�|�b�g�v�Z�A�e�L�����̃|�b�g�󂯎�莑�i�̋L�^�Ȃǎx���v�Z�ɕK�v�ȐF�X��L����N���X
	Cmp_Image* back; //���|�b�g�Ɏx�����Ă邩�\������ׂ̃G���A�̔w�i�摜
	std::map<int, int> pot; //�|�b�g�Afirst=�|�b�g�̗v���z�Asecond=���̃|�b�g���̍��v���z
	std::unordered_map<const Chara*, int> charaPayment; //�ǂ̃L���������x���������L�^�A�ǂ̃|�b�g���󂯎�錠�����������f����̂Ɏg�p�Afirst=�L�����Asecond=�x���z
	Cmp_Transform textPos; //�|�b�g���z�\���̍��W

public:
	Pot();
	~Pot();

	void Reset(); //���E���h�I�����ɌĂяo���A�|�b�g��x���󋵂����Z�b�g����
	int PayOut(const Chara& user); //�L������n���Ƃ������󂯎�錠���̂���S�Ẵ|�b�g���x������A�x�������|�b�g�͋�ɂȂ�
	void SetSidePot(int pay, const Chara& user); //AllIn����������Ăяo���A�����̋��z�ɍ��킹���V�����|�b�g���쐬���A�ĐU�蕪�����s��
	void SetMainPot(int pay, const Chara& user); //���펞�|�b�g�ւ̎x��������ΌĂяo��

	int Inquiry(const Chara& user); //payOut���l����������͕����o���͍s��Ȃ����������o�������Ɖ��ׂ̋@�\

	void Draw(); //�|�b�g���z�\���̔w�i��`�ʂ���
};
