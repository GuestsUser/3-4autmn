#pragma once
#include "../Code/Component/Component.h"

class Cmp_Transform;
class Cmp_BetActionRecord;
class PK_Dealer;
class Gage;
class Pot;
class Chara;

class Cmp_PlayerRaiseDraw :public Component {
	Chara* parent; //プレイヤーへの参照
	Gage* gage; //ゲージへの参照

	Pot* pot; //ポットへの参照
	PK_Dealer* dealer; //ディーラーへの参照を持つ
	Cmp_Transform* drawPos; //描写位置記録用
public:
	Cmp_PlayerRaiseDraw(Chara& player, Pot& setPot, PK_Dealer& setDealer);
	~Cmp_PlayerRaiseDraw();

	void Update() {}
	void Draw();
};