#pragma once
#include "Component.h"

class Cmp_Transform;
class Cmp_BetActionRecord;
class Gage;
class PK_Chara;
class PK_Dealer;
class PK_Pot;

class Cmp_PlayerRaiseDraw :public Component {
	PK_Chara* parent; //プレイヤーへの参照
	Gage* gage; //ゲージへの参照

	PK_Pot* pot; //ポットへの参照
	PK_Dealer* dealer; //ディーラーへの参照を持つ
	Cmp_Transform* drawPos; //描写位置記録用
public:
	Cmp_PlayerRaiseDraw(PK_Chara& player, PK_Pot& setPot, PK_Dealer& setDealer);
	~Cmp_PlayerRaiseDraw();

	void Update() {}
	void Draw();
};