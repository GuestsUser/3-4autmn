#pragma once
#include "Poker.h"
#include "../Code/Component/Component.h"
#include <deque>

class PK_Dealer;
class Chara;
class Cmp_Image;

class Vector3;

class Cmp_ThinkingImage :public Component {
	Cmp_Image* image; //考え中である事を示す為の画像を格納する為の変数
	PK_Dealer* dealer; //ディーラーの参照
	Poker::Character parent; //このコンポーネントを持つキャラクター番号

public:
	Cmp_ThinkingImage(Poker::Character parent, PK_Dealer& setDealer, const Vector3& place);

	~Cmp_ThinkingImage() { delete image; }


	void Update();
	void Draw();
};