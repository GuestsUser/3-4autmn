#pragma once
#include "../Scene.h"
#include "Poker.h"

#include "CardDealer.h"
#include "../Code/Component/Component.h"

#include <deque>

class Cmp_BetActionRecord;
class Button;
class Vector3;

class Poker::Change :public Scene { //�J�[�h���e�L�����֔z��t�F�C�Y
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������
	Button* actionButton; //playerButton�̒��ł��e��A�N�V�������s���{�^��������
	std::deque<Button*> cardButton; //�J�[�h�N���b�N�����m����ׂ̃{�^��
	Cmp_Image* actionButtonImage; //action�p�{�^���̉摜�R���|�[�l���g������ϐ�
	std::deque<Vector3*> cardPos; //�J�[�h�̈ʒu�ւ̃A�N�Z�X�V���[�g�J�b�g


	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	CardDealer::CardPower border; //���ɂȂ��ĂȂ����ň�ԋ����J�[�h�����̋��ȏ�Ȃ炻��͕ێ�����
	std::deque<bool> isClick; //�J�[�h���N���b�N���Č����w�肵�Ă���΂��̗v�f��true�ɂȂ�
	int originalY; //�J�[�h���N���b�N�����ہA�ʒu��O�ɏo���̂Ō��ɖ߂���悤���펞��y�L�^�p
	int moveY; //�J�[�h���N���b�N�������A�J�[�h������y��

	int count; //���ԊǗ�
	int cpuWait; //cpu���A�N�V�������s���܂ł̑ҋ@���ԁA�t���[�����w��
public:
	Change(Poker& set);
	void Update();
};