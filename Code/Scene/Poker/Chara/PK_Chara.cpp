#include "DxLib.h"

#include "PK_Chara.h"
#include "PK_Card.h"
#include "PokerFontData.h"

#include "Component.h"
#include "Cmp_Hand.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include <string>

int PK_Chara::coinIni = 5000; //所持金初期値設定

PK_Chara::PK_Chara() :coin(coinIni), hand(Cmp_Hand()), bbView(BBView::hide), coinBack(std::deque<Cmp_Image*>()), cmp(ComponentArray()){
	coinBack.push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/poker_score_back.png")), 1));
	int* handle = new int[2];
	LoadDivGraph("Resource/image/poker_pos_view.png", 2, 2, 1, 50, 30, handle);
	coinBack.push_back(new Cmp_Image(*handle, 2));
}

PK_Chara::~PK_Chara() {
	for (auto itr : coinBack) { delete itr; }
}

void PK_Chara::FullReset() {
	cmp.FullReset(); //追加機能の完全初期化
	hand.FullReset(); //手札のFullReset実行

	coin = coinIni; //所持金を初期値に合わせる
	SetBBView(BBView::hide); //BB、SB表示を隠す
}
void PK_Chara::Reset() {
	cmp.Reset(); //追加機能の初期化
	hand.Reset(); //手札のReset実行

	SetBBView(BBView::hide); //BB、SB表示を隠す
}

void PK_Chara::Place(std::deque<Cmp_Transform>& cardPos, Cmp_Transform& backPos) {
	std::deque<PK_Card*> card = *hand.EditCard(); //カード配列取得
	for (int i = 0; i < card.size(); ++i) { card[i]->Place(cardPos[i].ReadPos().GetX(), cardPos[i].ReadPos().GetY()); } //カード配置

	coinBack[0]->EditTranform()->EditPos() = backPos.EditPos(); //コイン表示用UIの背景の位置を設定
	coinBack[1]->EditTranform()->EditPos() = backPos.EditPos(); //bb、sbを表す小見出しの位置設定、仮に背景と同じ位置に置いている


	int backX = 0; int backY = 0; //背景サイズ
	int bbX = 0; int bbY = 0; //小見出しサイズ
	GetGraphSize(*coinBack[0]->ReadImage(), &backX, &backY); //サイズ取得
	GetGraphSize(coinBack[1]->ReadImage()[1], &bbX, &bbY);
	coinBack[1]->EditTranform()->EditPos().SetXYZ(coinBack[1]->EditTranform()->EditPos().GetX() - backX / 2 + bbX / 2, coinBack[1]->EditTranform()->EditPos().GetY() - backY / 2 - bbY / 2, 0); //左上配置になるように再配置
}

void PK_Chara::Update() {
	if (!GetRunUpdate()) { return; }
	hand.Update(); //手札のUpdateを実行
	cmp.Update(); //追加機能実行
}
void PK_Chara::Draw() {
	if (!GetRunDraw()) { return; }
	for (auto itr : coinBack) { itr->Draw(); } //コイン描写用背景描写
	DrawStringToHandle(coinBack[0]->EditTranform()->ReadPos().GetX(), coinBack[0]->EditTranform()->ReadPos().GetY(), std::to_string(coin).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));

	hand.Draw(); //手札のDrawを実行
	cmp.Draw(); //追加機能実行
}

void PK_Chara::SetBBView(BBView set) {
	bbView = set; //表示を新しい物に入れ替え
	coinBack[1]->SetRunDraw(true); //表示を付ける
	if (bbView == BBView::hide) { coinBack[1]->SetRunDraw(false); } //隠し指定だった場合描写を切る
	else { coinBack[1]->SetAnimeSub((int)bbView); } //新しい表示に切り替える
}