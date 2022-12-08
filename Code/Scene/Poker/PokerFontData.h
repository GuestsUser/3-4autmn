#pragma once
#include <deque>

class PokerFontData { //Poker�Ŏg�p����t�H���g�f�[�^��GlovalLoading������o���ĕێ�����N���X
	static std::deque<int*> fontHandle; //�t�H���g�n���h�����l�߂��z��
	static std::deque<unsigned int*> fontColor; //�t�H���g�J���[���l�߂��z��
public:
	enum class type { normal, edge }; //fontHandle�ɂ��̒l��Y�����Ƃ��Ďg���ƖړI�̃n���h������鎖���ł���
	enum class color { normal, edgeNormal, edgeColor }; //��L��fontColor�p�AedgeNormal�̓G�b�W�t���t�H���g�̒ʏ핔���J���[�AedgeColor���G�b�W�̃J���[

	static void SetUp(); //�ŏ��ɂ�����Ăяo�����ŗ��p�\�ƂȂ�A�e��ϐ���static�Ȃ̂ŁuPokerFontData::�֐��v�̌`���ŐF�X�擾�\

	static const int* GetHandle(type get)  { return fontHandle[(int)get]; } //�ړI�̃n���h�������
	static const unsigned int* GetColor(color get)  { return fontColor[(int)get]; } //�ړI�̃J���[�����

	//���̐����֎~
	PokerFontData() = delete;
	PokerFontData(const PokerFontData&) = delete;
};