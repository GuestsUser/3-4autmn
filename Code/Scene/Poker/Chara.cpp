#include "DxLib.h"

#include "Chara.h"
#include "PK_Card.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/Component/Cmp_Image.h"
#include "PokerFontData.h"

#include <string>

int Chara::coinIni = 5000; //所持金初期値設定

Chara::Chara() :coin(coinIni), card(std::deque<PK_Card*>()), coinBack(std::deque<Cmp_Image*>()), cmp(std::deque<Component*>()) {
	for (int i = 0; i < 5; ++i) { card.push_back(new PK_Card()); }

	coinBack.push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_score_back.png")), 1));
	int* handle = new int[2];
	LoadDivGraph("Resource/image/poker_pos_view.png", 2, 2, 1, 50, 30, handle);
	coinBack.push_back(new Cmp_Image(*handle, 2));
}

Chara::~Chara() {
	for (auto itr : card) { delete itr; }
	for (auto itr : coinBack) { delete itr; }
	ClearCmp();
}

void Chara::FullReset() {
	for (auto itr : cmp) { itr->FullReset(); } //追加機能の完全初期化
	for (auto itr : card) { itr->FullReset(); } //カードの完全初期化
	coin = coinIni; //所持金を初期値に合わせる
}
void Chara::Reset() {
	for (auto itr : cmp) { itr->Reset(); } //追加機能の初期化
	for (auto itr : card) { itr->Reset(); } //カードの初期化
}

void Chara::Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos) {
	for (int i = 0; i < card.size(); ++i) { card[i]->Place(cardPos[i].ReadPos().GetX(), cardPos[i].ReadPos().GetY()); } //カード配置

	coinBack[0]->EditTranform()->EditPos() = backPos.EditPos(); //コイン表示用UIの背景の位置を設定
	coinBack[1]->EditTranform()->EditPos() = backPos.EditPos(); //bb、sbを表す小見出しの位置設定、仮に背景と同じ位置に置いている


	int backX = 0; int backY = 0; //背景サイズ
	int bbX = 0; int bbY = 0; //小見出しサイズ
	GetGraphSize(*coinBack[0]->ReadImage(), &backX, &backY); //サイズ取得
	GetGraphSize(coinBack[1]->ReadImage()[1], &bbX, &bbY);
	coinBack[1]->EditTranform()->EditPos().SetXYZ(coinBack[1]->EditTranform()->EditPos().GetX() - backX / 2 + bbX / 2, coinBack[1]->EditTranform()->EditPos().GetY() - backY / 2 - bbY / 2, 0); //左上配置になるように再配置
}

void Chara::Update() {
	if (!GetRunUpdate()) { return; }
	for (auto itr : cmp) { if (itr->GetRunUpdate()) { itr->Update(); } }
}
void Chara::Draw() {
	if (!GetRunDraw()) { return; }
	for (auto itr : card) { itr->Draw(); } //カード描写
	for (auto itr : coinBack) { itr->Draw(); } //コイン描写用背景描写
	DrawStringToHandle(coinBack[0]->EditTranform()->ReadPos().GetX(), coinBack[0]->EditTranform()->ReadPos().GetY(), std::to_string(coin).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));

	for (auto itr : cmp) { 
		if (itr->GetRunDraw()) { itr->Draw(); } 
	}
}


void Chara::EraseCmp(Component* set) {
	for (auto itr : cmp) { if (itr == set) { delete set; return; } }
}
void Chara::ClearCmp() {
	for (auto itr : cmp) { delete itr; }
}

void Chara::GetHandNum(std::deque<int>& set) const {
	for (auto itr : card) { set.push_back(itr->GetCard()); } //手札から数値のみを取り出す処理
}
