#pragma once
#include "Component.h"
#include "Cmp_Transform.h"

#include <deque>

class Cmp_Sound;
class PK_Dealer;

class Cmp_PK_Chara_SE :public Component { //chara�����ʂ��Ď���se�ƃT�E���h�ʒu�ϐ���ێ�����N���X
public:
	enum class Request { call, fold, raise, cardChange, cardOpen, cardPlace, coinFew, coinMany };

private:
	Cmp_Transform soundPos; //�T�E���h�̊�Ƃ���N���X
	std::deque<Cmp_Sound*> sound; //Chara�̊Ǘ����鋤�ʃT�E���h
	static int fewBorder; //���C�Y�������̐��l�����̏ꍇ�R�C���擾����few���g��

public:
	Cmp_PK_Chara_SE(const Cmp_Transform* const soundPos = nullptr);

	void Update() {}

	const Cmp_Sound* const ReadSE(Request request)const { return sound[(int)request]; } //request�ŗv������se��ҏW�֎~�̌`���ŌĂяo��
	const Cmp_Transform* const ReadTransform()const { return &soundPos; } //�T�E���h�̖��Ă���ʒu��ǂݏo����p�`���Ŏ擾

	static Cmp_PK_Chara_SE::Request UseCoinSound(int pay, PK_Dealer& dealer); //pay���z���{�[�_�[�ȏ�Ȃ�many���A�����Ȃ�few��request�`���ŕԂ�
};

