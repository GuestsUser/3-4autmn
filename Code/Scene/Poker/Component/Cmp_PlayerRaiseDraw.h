#pragma once
#include "Component.h"

class Cmp_Transform;
class Cmp_BetActionRecord;
class Gage;
class PK_Chara;
class PK_Dealer;
class PK_Pot;

class Cmp_PlayerRaiseDraw :public Component {
	PK_Chara* parent; //�v���C���[�ւ̎Q��
	Gage* gage; //�Q�[�W�ւ̎Q��

	PK_Pot* pot; //�|�b�g�ւ̎Q��
	PK_Dealer* dealer; //�f�B�[���[�ւ̎Q�Ƃ�����
	Cmp_Transform* drawPos; //�`�ʈʒu�L�^�p
public:
	Cmp_PlayerRaiseDraw(PK_Chara& player, PK_Pot& setPot, PK_Dealer& setDealer);
	~Cmp_PlayerRaiseDraw();

	void Update() {}
	void Draw();
};