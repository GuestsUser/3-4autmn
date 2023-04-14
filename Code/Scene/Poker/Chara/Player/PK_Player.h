#pragma once
#include "PK_Chara.h"
#include <deque>

class Button;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;
class Cmp_Gage_MouseControl;
class Cmp_Image;
class Gage;
class PK_CardDealer;
class PK_Dealer;
class PK_Pot;

class PK_Player :public PK_Chara {
	std::deque<Component*> sectionModule; //�e�Z�N�V������ێ�
	Component* runSection; //SectionUpdate�Ŏg�p����I�u�W�F�N�g�͂�����Ɉڂ�

	Cmp_BetActionRecord* record; //�A�N�V�����󋵋L�^�p�ϐ�
	Button* actionButton; //playerButton�̒��ł��e��A�N�V�������s���{�^��������
	Button* foldButton; //playerButton�̒��ł�fold��p�̃{�^��������
	Cmp_Image* actionButtonImage; //action�p�{�^���̉摜�R���|�[�l���g������ϐ�

	Gage* gage; //�v���C���[�ێ��̃Q�[�W
	Cmp_Gage_Border* gageBorder; //�v���C���[�̃Q�[�W�����ݒ�@�\�̃R���|�[�l���g
	Cmp_Gage_UpperBorder* gageUpper; //�v���C���[�̃Q�[�W����ݒ�@�\�̃R���|�[�l���g
	Cmp_Gage_MouseControl* gageControl; //�Q�[�W������󂯕t����R���|�[�l���g

	PK_Pot* pot;
	PK_Dealer* dealer;
	PK_CardDealer* cardDealer;
public:
	PK_Player(PK_Pot& pot, PK_Dealer& dealer, PK_CardDealer& cardDealer);
	~PK_Player();

	void FullReset();
	void Reset();

	void SectionUpdate();
	void SetSection(Section set) { runSection = sectionModule[(int)set]; }

private:
	class Main;
	class Change;
};