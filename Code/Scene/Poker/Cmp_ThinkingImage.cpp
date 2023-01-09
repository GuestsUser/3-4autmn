#include "DxLib.h"

#include "../Code/Component/Component.h"
#include "Chara.h"
#include "PK_Player.h"
#include "CPU.h"

#include "PK_Dealer.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/OriginMath.h"

#include <typeinfo>
#include <deque>

#include "Cmp_ThinkingImage.h"

Cmp_ThinkingImage::Cmp_ThinkingImage(Chara& setParent, std::deque<Chara*>& setChara, PK_Dealer& setDealer, const Vector3& place) : parent(&setParent), chara(&setChara), dealer(&setDealer) {
	int space = 118; //placeにこの数値分だけxをずらした位置に配置する

	image = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_cpu_thinking.png")), 1); //画像作成
	image->EditTranform()->EditPos().SetXYZ(place.GetX() + space, place.GetY(), place.GetZ()); //xをspace分ずらした位置に配置する

	isPlayer = typeid(*parent) == typeid(PK_Player);
}


void Cmp_ThinkingImage::Update() {
	if (!GetRunUpdate()) { return; } //禁止令が出てる場合実行しない
	image->Update();
}
void Cmp_ThinkingImage::Draw() {
	if (!GetRunDraw()) { return; } //禁止令が出てる場合実行しない
	if (isPlayer) { return; } //プレイヤーの場合表示しない
	if ((*chara)[dealer->GetActionCharaSub()] != parent) { return; } //現在アクション実行中キャラが親ではない場合実行しない

	image->Draw(); //描写
}