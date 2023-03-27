#pragma once
#include "Component.h"
#include "PK_Player.h"

#include <deque>

class Button;
class Vector3;

class PK_Player::Change :public Component {
	PK_Player* parent; //���g��ێ�����e
	std::deque<Button*> cardButton; //�J�[�h�N���b�N�����m����ׂ̃{�^��
	std::deque<Vector3*> cardPos; //�J�[�h�̈ʒu�ւ̃A�N�Z�X�V���[�g�J�b�g

	int count;
	int originalY; //�J�[�h���N���b�N�����ہA�ʒu��O�ɏo���̂Ō��ɖ߂���悤���펞��y�L�^�p
	int moveY; //�J�[�h���N���b�N�������A�J�[�h������y��
public:
	Change(PK_Player& parent);

	void Update();
};