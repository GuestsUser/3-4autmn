#pragma once
#include <deque>
#include <random>
#include <utility>

class PK_Chara;

class PK_CardDealer {
private:
	std::mt19937 gen; //�����_���l�����@
	std::deque<int> deck; //�R�D
	int top; //�R�D�̈�ԏ�������Y����
public:
	PK_CardDealer();
	void Reset(); //���E���h�I�����ɌĂяo���A�R�D�̏����������s���Ă����

	int DeckDraw(); //�R�D����1�����������ʎ�ɓ������J�[�h��Ԃ��A���s����ƎR�D������
};