#pragma once
#include "../Code/Component/Component.h"

class Cmp_Transform;
class Cmp_BetActionRecord;
class PK_Dealer;
class Gage;
class Pot;
class Chara;

class Cmp_PlayerRaiseDraw :public Component {
	Chara* parent; //�v���C���[�ւ̎Q��
	Gage* gage; //�Q�[�W�ւ̎Q��

	Pot* pot; //�|�b�g�ւ̎Q��
	PK_Dealer* dealer; //�f�B�[���[�ւ̎Q�Ƃ�����
	Cmp_Transform* drawPos; //�`�ʈʒu�L�^�p
public:
	Cmp_PlayerRaiseDraw(Chara& player, Pot& setPot, PK_Dealer& setDealer);
	~Cmp_PlayerRaiseDraw();

	void Update() {}
	void Draw();
};