#pragma once
#include "Chara.h"
#include <deque>

class Button;
class CardDealer;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;
class Cmp_Gage_MouseControl;
class Cmp_Image;
class Gage;
class PK_Dealer;
class Pot;

class PK_Player :public Chara {
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

	Pot* pot;
	PK_Dealer* dealer;
	CardDealer* cardDealer;
public:
	PK_Player(Pot& pot, PK_Dealer& dealer, CardDealer& cardDealer);
	~PK_Player();

	void SectionUpdate();
	void SetSection(Section set) { runSection = sectionModule[(int)set]; }

private:
	class Main;
	class Change;
};