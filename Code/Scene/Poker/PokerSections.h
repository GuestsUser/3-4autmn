#pragma once
#include "../Scene.h"
#include "Poker.h"

#include "Btn.h"
#include "CPU.h"
#include "Pot.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"

#include "../Code/Component/Component.h"
#include "../Code/Component/Button.h"

#include <deque>
#include <string>

class Cmp_Image;
class Cmp_BetActionRecord;
class Cmp_CPUBetLogic;
class Cmp_Gage_Border;
class Cmp_Gage_MouseControl;
class Cmp_PlayerRaiseDraw;
class Gage;
class CardDealer;
class Card;
class Vector3;

class Poker::Ini :public Scene { //���E���h�J�n���̏������L����Update�����������N���X
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������

public:
	Ini(Poker& set);
	void Update();
};

class Poker::Pre :public Scene { //�J�[�h���e�L�����֔z��t�F�C�Y
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������

public:
	Pre(Poker& set);
	void Update();
};

class Poker::Main :public Scene { //���C���x�b�g�t�F�C�Y
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������
	std::deque<Cmp_CPUBetLogic*> betLogic;
	std::deque<Button*> playerButton; //�v���C���[���ێ�����{�^���R���|�[�l���g

	Button* actionButton; //playerButton�̒��ł��e��A�N�V�������s���{�^��������
	Button* foldButton; //playerButton�̒��ł�fold��p�̃{�^��������
	Cmp_Image* actionButtonImage; //action�p�{�^���̉摜�R���|�[�l���g������ϐ�
	std::deque<Cmp_Image*> thinkingImage; //�l�����ł��鎖�������ׂ̉摜���i�[����z��


	Gage* playerGage; //�v���C���[�ێ��̃Q�[�W
	Cmp_Gage_Border* playerGageBorder; //�v���C���[�̃Q�[�W�����ݒ�@�\�̃R���|�[�l���g
	Cmp_Gage_MouseControl* gageControl; //�Q�[�W������󂯕t����R���|�[�l���g

	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	int phase; //���ꂪ����ڂ̃x�b�g�t�F�C�Y�������Ă����ϐ�
	int count; //���ԃJ�E���g

	int cpuWait; //cpu���A�N�V�������s���܂ł̑ҋ@���ԁA�t���[�����w��

public:
	Main(Poker& set);
	void Update();
	void SetPhase(int set) { phase = set; } //���݂̃x�b�g�t�F�C�Y���Z�b�g�Arun��Main����ꂽ�����Ă����Ƃ���
};

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

class Poker::ShowDown :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������
	
	std::deque<std::deque<int>> hand; //�e�L�����̃n���h�]����ێ�
	std::deque<Vector3> handPos; //�e�L�����̃n���h��\������ׂ̈ʒu�W�ߔz��
	std::deque<std::string> handString; //�e�L�����̃n���h��string�^�ŕێ�����z��

	int count;



	Vector3 titlePos; //�V���[�_�E���ł��鎖���������b�Z�[�W�̕\���ʒu

public:
	ShowDown(Poker& set);
	void Update();
	void Draw();
};

class Poker::NoContest :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	std::deque<Cmp_BetActionRecord*> actionRecord; //chara���甲���o�����R���|�[�l���g��ێ��A�z��̓Y�����̓L�����Ɠ��l�Ȃ̂œ����񋓌^�ł��̃L�����̃R���|�[�l���g������
	Button nextButton; //�N���b�N���鎖�Ŏ��V�[���ֈڍs����

	int count;
	int payOutTime; //���̃^�C�~���O�Ŏx�������s��
	int clickStartTime; //count�����̐��l�ɒB����ƃ{�^���N���b�N�̌��m���J�n����
	int blink; //���̎��ԊԊu�Ő�����_�ł�����

	Vector3 titlePos; //�m�[�R���e�X�g�ł��鎖���������b�Z�[�W�̕\���ʒu
	Vector3 explainPos; //�{�^�������̔z�u�ʒu
public:
	NoContest(Poker& set);
	void Update();
	void Draw();
};

class Poker::GameOver :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	Button nextButton; //�N���b�N���鎖�Ŏ��V�[���ֈڍs����

	int count;
	int clickStartTime; //count�����̐��l�ɒB����ƃ{�^���N���b�N�̌��m���J�n����
	int blink; //���̎��ԊԊu�Ő�����_�ł�����

	Vector3 titlePos; //�Q�[���I�[�o�[�ł��鎖���������b�Z�[�W�̕\���ʒu
	Vector3 explainPos; //�{�^�������̔z�u�ʒu
public:
	GameOver(Poker& set);
	void Update();
	void Draw();
};

class Poker::GameClear :public Scene {
	Poker* parent; //���̃N���X�̎��̂�����Poker�ւ̎Q��
	Vector3 titlePos; //�Q�[���N���A�ł��鎖���������b�Z�[�W�̕\���ʒu

public:
	GameClear(Poker& set) :parent(&set) {}
	void Update();
	void Draw();
};
