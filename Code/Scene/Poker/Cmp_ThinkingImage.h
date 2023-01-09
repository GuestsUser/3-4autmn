#pragma once
#include "../Code/Component/Component.h"
#include <deque>

class PK_Dealer;
class Chara;
class Cmp_Image;

class Vector3;

class Cmp_ThinkingImage :public Component {
	Cmp_Image* image; //考え中である事を示す為の画像を格納する為の変数
	Chara* parent; //このコンポーネントを持つキャラの参照
	PK_Dealer* dealer; //ディーラーの参照
	std::deque<Chara*>* chara; //キャラクターを詰めた配列の参照

	bool isPlayer; //parentがプレイヤーだった場合trueを記録する

public:

	Cmp_ThinkingImage(Chara& setParent, std::deque<Chara*>& setChara, PK_Dealer& setDealer, const Vector3& place);

	~Cmp_ThinkingImage() { delete image; }


	void Update();
	void Draw();
};