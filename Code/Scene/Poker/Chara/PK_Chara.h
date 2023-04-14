#pragma once
#include "Component.h"
#include "ComponentArray.h"
#include "Cmp_BetActionRecord.h"
#include "Cmp_Hand.h"
#include <deque>

#include <typeinfo>

class Cmp_Image;
class Cmp_Transform;
class PK_Card;

class PK_Chara :public Component {
public:
	enum class BBView { BB, SB, hide }; //BB�ASB�ł��鎖�������\�����ǂ��\�����邩�ׂ̗̈񋓌^�Ahide�͔�\���ABB,SB�͂����\������

private:
	static int coinIni; //�����������L�^�p�ϐ�
	int coin;
	std::deque<Cmp_Image*> coinBack;
	Cmp_Hand hand;
	BBView bbView;

	ComponentArray cmp; //�ǉ��@�\�W
public:
	enum class Section { main, change, wait }; //sectionModule����ړI�̃Z�N�V�������w�肷��ׂ̗񋓌^

	PK_Chara();
	virtual ~PK_Chara();
	virtual void FullReset();
	virtual void Reset();

	void Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos);
	void Update();
	void Draw();

	virtual void SectionUpdate() = 0; //�Q�[���̊e�Z�N�V��������Ăяo��Update�A�Z�N�V�����ɉ����ēK�؂ȏ��������s���Ă����
	virtual void SetSection(Section set) = 0; //�g�pSection�w��p�֐�

	int GetCoint() const { return coin; }
	void SetCoin(int set) { coin = set; }

	const Cmp_Hand* ReadHand() const { return &hand; } //��D��ǂݎ���p�ŕԂ�
	Cmp_Hand* EditHand() { return &hand; } //��D�𑀍�\�ȏ�ԂŕԂ�

	BBView GetBBView() const { return bbView; } //BB�\���̏�Ԃ𓾂�
	void SetBBView(BBView set); //BB�\����Ԃ�ݒ肷��

	const ComponentArray* const ReadAppendCmp() { return &cmp; } //�ǉ��@�\�W�ւ̃A�N�Z�X�A������͓ǂݏo����p
	ComponentArray* EditAppendCmp() { return &cmp; } //�ǉ��@�\�W�ւ̃A�N�Z�X��n��

};