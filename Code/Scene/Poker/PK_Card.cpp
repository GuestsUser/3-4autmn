#include "DxLib.h"

#include "PK_Card.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/ComponentArray.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"

#include <deque>

PK_Card::PK_Card() :card(0), drawMode(DrawMode::front), cmp(ComponentArray()) {
	int* handle = new int[54];
	LoadDivGraph("Resource/image/poker_card.png", 54, 13, 5, 120, 150, handle); //カード画像読み込み
	image = new Cmp_Image(*handle, 53); //カード画像格納

	markingImage= new Cmp_Image(*new int(LoadGraph("Resource/image/poker_card_marking.png")), 1); //マーキング画像を格納

	Reset(); //見た目の初期化
}
PK_Card::~PK_Card() { //newした画像系は終了と共に削除
	delete image;
	delete markingImage;
}

void PK_Card::Reset() {
	SetDrawMode(DrawMode::back); //カードを裏側表示に
	SetMarking(false); //マーキングは非表示に
}

void PK_Card::Place(int x, int y) {
	image->EditTranform()->EditPos().SetXYZ(x, y, 0);
	markingImage->EditTranform()->EditPos().SetXYZ(x, y, 0);
}

void PK_Card::Update() {
	if (!GetRunUpdate()) { return; } //実行禁止命令があれば実行しない
	cmp.Update();
}


void PK_Card::Draw() {
	if (!GetRunDraw()) { return; } //実行禁止命令があれば実行しない

	switch (drawMode) {
	case PK_Card::DrawMode::back:image->SetAnimeSub(52); break; //裏指定ならカードの種類問わず添え字を裏の物に指定
	case PK_Card::DrawMode::front: image->SetAnimeSub(card); break; //表示モードが表指定の場合画像添え字を現在カードに設定
	case PK_Card::DrawMode::fold: image->SetAnimeSub(53); break; //fold表示の場合灰色カードを種類問わず表示する
	}
	
	image->Draw();
	markingImage->Draw();

	cmp.Draw();
}

void PK_Card::SetMarking(bool set) { markingImage->SetRunDraw(set); } //trueでマーキング表示を行うようにする

const Cmp_Transform* PK_Card::ReadTransform() const { return image->ReadTranform(); }
Cmp_Transform* PK_Card::EditTransform() { return image->EditTranform(); }
