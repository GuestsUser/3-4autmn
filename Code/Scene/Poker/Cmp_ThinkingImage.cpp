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

Cmp_ThinkingImage::Cmp_ThinkingImage(Poker::Character parent, PK_Dealer& setDealer, const Vector3& place) :parent(parent), dealer(&setDealer) {
	image = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_cpu_thinking.png")), 1); //画像作成
	image->EditTranform()->EditPos().SetXYZ(place.GetX(), place.GetY(), place.GetZ()); //xをspace分ずらした位置に配置する
}

void Cmp_ThinkingImage::Update() {
	if (!GetRunUpdate()) { return; } //禁止令が出てる場合実行しない
	image->Update();
}
void Cmp_ThinkingImage::Draw() {
	if (!GetRunDraw()) { return; } //禁止令が出てる場合実行しない
	if (dealer->GetActionCharaSub() != (int)parent) { return; } //現在アクション実行中キャラが自身を持つオブジェクトと違う場合実行しない

	image->Draw(); //描写
}