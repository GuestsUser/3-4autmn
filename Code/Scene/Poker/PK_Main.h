#pragma once
#include "../Scene.h"
#include "Poker.h"
#include "../Code/Component/Component.h"

#include <deque>

class Cmp_Image;
class Cmp_BetActionRecord;
class Cmp_CPUBetLogic;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;
class Cmp_Gage_MouseControl;
class Button;
class Gage;

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
	Cmp_Gage_UpperBorder* playerGageUpper; //�v���C���[�̃Q�[�W����ݒ�@�\�̃R���|�[�l���g
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
