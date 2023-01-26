#include "DxLib.h"

#include "PK_Card.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"

#include <deque>

PK_Card::PK_Card() :card(0), cmp(std::deque<Component*>()) {
	int* handle = new int[53];
	LoadDivGraph("Resource/image/poker_card.png", 53, 13, 5, 120, 150, handle); //カード画像読み込み
	image = new Cmp_Image(*handle, 53); //カード画像格納

	markingImage= new Cmp_Image(*new int(LoadGraph("Resource/image/poker_card.png")), 1); //マーキング画像を格納

	Reset(); //見た目の初期化
}
PK_Card::~PK_Card() { //newした画像系は終了と共に削除
	delete image;
	delete markingImage;
	for (auto itr : cmp) { delete itr; }
}

void PK_Card::Reset() {
	SetVisible(false); //カードを裏側表示に
	SetMarking(false); //マーキングは非表示に
}

void PK_Card::Place(int x, int y) {
	image->EditTranform()->EditPos().SetXYZ(x, y, 0);
	markingImage->EditTranform()->EditPos().SetXYZ(x, y, 0);
}

void PK_Card::Draw() {
	if (!GetRunDraw()) { return; } //実行禁止命令があれば実行しない
	image->Draw();
	markingImage->Draw();
}

void PK_Card::SetVisible(bool set) {
	if (set) { image->SetAnimeSub(card); } //trueなら表示画像を表の物に変更
	else { image->SetAnimeSub(52); } //falseなら裏側に
}
void PK_Card::SetMarking(bool set) { markingImage->SetRunDraw(set); } //trueでマーキング表示を行うようにする

const Cmp_Transform* PK_Card::ReadTransform() const { return image->ReadTranform(); }