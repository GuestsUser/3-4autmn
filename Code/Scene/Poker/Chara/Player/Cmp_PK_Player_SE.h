#pragma once
#include "Component.h"
#include "Cmp_Transform.h"

#include <deque>

class Cmp_Sound;

class Cmp_PK_Player_SE :public Component { //chara�����ʂ��Ď���se�ƃT�E���h�ʒu�ϐ���ێ�����N���X
public:
	enum class Request { coinPlayer, gage };

private:
	Cmp_Transform soundPos; //�T�E���h�̊�Ƃ���N���X
	std::deque<Cmp_Sound*> sound; //Chara�̊Ǘ����鋤�ʃT�E���h

public:
	Cmp_PK_Player_SE(const Cmp_Transform* const soundPos = nullptr);

	void Update() {}

	const Cmp_Sound* const ReadSE(Request request)const { return sound[(int)request]; } //request�ŗv������se��ҏW�֎~�̌`���ŌĂяo��
	const Cmp_Transform* const ReadTransform()const { return &soundPos; } //�T�E���h�̖��Ă���ʒu��ǂݏo����p�`���Ŏ擾
};

