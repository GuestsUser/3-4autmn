#pragma once
#include "../Code/Component/Component.h"
#include "../Code/Component/ComponentArray.h"
#include "Cmp_BetActionRecord.h"
#include <deque>

#include <typeinfo>

class Cmp_Image;
class Cmp_Transform;
class PK_Card;

class Chara :public Component {
public:
	enum class BBView { BB, SB, hide }; //BB�ASB�ł��鎖�������\�����ǂ��\�����邩�ׂ̗̈񋓌^�Ahide�͔�\���ABB,SB�͂����\������

private:
	static int coinIni; //�����������L�^�p�ϐ�
	int coin;
	std::deque<PK_Card*> card;
	std::deque<Cmp_Image*> coinBack;
	BBView bbView;

	ComponentArray cmp; //�ǉ��@�\�W
public:
	enum class Section { main, change }; //sectionModule����ړI�̃Z�N�V�������w�肷��ׂ̗񋓌^

	Chara();
	virtual ~Chara();
	void FullReset();
	void Reset();

	void Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos);
	void Update();
	void Draw();

	virtual void SectionUpdate() = 0; //�Q�[���̊e�Z�N�V��������Ăяo��Update�A�Z�N�V�����ɉ����ēK�؂ȏ��������s���Ă����
	virtual void SetSection(Section set) = 0; //�g�pSection�w��p�֐�

	int GetCoint() const { return coin; }
	const std::deque<PK_Card*>* ReadCard() const { return &card; }
	void GetHandNum(std::deque<int>& set) const; //�n���h�𐔒l�����������擾�Aset�z����Ɋi�[���ĕԂ�

	void SetCoin(int set) { coin = set; }
	std::deque<PK_Card*>* EditCard() { return &card; }

	BBView GetBBView() const { return bbView; } //BB�\���̏�Ԃ𓾂�
	void SetBBView(BBView set); //BB�\����Ԃ�ݒ肷��

	ComponentArray* EditAppendCmp() { return &cmp; } //�ǉ��@�\�W�ւ̃A�N�Z�X��n��
	const ComponentArray* const ReadAppendCmp() { return &cmp; } //�ǉ��@�\�W�ւ̃A�N�Z�X�A������͓ǂݏo����p
};