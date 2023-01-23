#include "DxLib.h"

#include "Pot.h"
#include "DxLib.h"
#include "PokerFontData.h"

#include "Chara.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_Transform.h"

#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>

Pot::Pot() :pot(std::map<int, int>()), charaPayment(std::unordered_map<const Chara*, int>()), textPos(Cmp_Transform()) {
	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_pot.png")), 1); //ポット金額表示背景画像生成
	back->EditTranform()->EditPos().SetXYZ(604, 295, 0); //位置設定
	textPos.EditPos().SetXYZ(567, 324, 0); //テキスト位置設定
}

Pot::~Pot() { delete back; } //画像は終了と同時に削除

void Pot::Draw() {
	back->Draw(); //ポット金額の背景表示

	int potSum = 0; //ポット内金額合計
	for (auto itr : pot) { potSum += itr.second; } //ポットの要素全てをチェックし合計金額を出す
	DrawStringToHandle(textPos.ReadPos().GetX(), textPos.ReadPos().GetY(), std::to_string(potSum).c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
}

void Pot::Reset() {
	charaPayment = std::unordered_map<const Chara*, int>(); //各キャラの支払い情報のリセット、即ち空にする
	pot = std::map<int, int>(); //サイドポット、メインポットをリセット
}

int Pot::PayOut(const Chara& user) {
	int payOut = 0; //支払合計額

	for (auto itr = pot.find(charaPayment[&user]); true; --itr) { //mapは昇順なので自身以下のポットを得る為前に進める
		payOut += itr->second; //今回のポットを支払額に加える
		itr->second = 0; //今回のポットをリセット
		if (itr == pot.begin()) { break; } //前方だとend()のような物がないので終了条件をこっちに持ってくる
	}

	return payOut; //支払額を返す
}

int Pot::Inquiry(const Chara& user) {
	if (charaPayment.count(&user) == 0) { return 0; } //支払いがない場合0を返して終わり
	return charaPayment[&user]; //支払額を返す
}

int Pot::TotalAmount() {
	int sum = 0;
	for (auto itr = pot.begin(); itr != pot.end(); ++itr) { sum += itr->second; } //各ポット内金額をsumへ合計してゆく
	return sum;
}

void Pot::SetSidePot(int pay, const Chara& user) {
	charaPayment[&user] = charaPayment[&user] + pay; //取り敢えずサイドポット用支払額を記録しておく

	std::deque<std::pair<int, const Chara*>> copy = std::deque<std::pair<int, const Chara*>>(); //支払状況をコピーする
	for (auto itr : charaPayment) { copy.push_back(std::make_pair(itr.second, itr.first)); } //mapもunordered_mapも余計な機能のせいでソートできないからpairを使う
	std::sort(copy.begin(), copy.end(), [](std::pair<int, const Chara*> a, std::pair<int, const Chara*> b) { return a.first < b.first; }); //支払額を昇順にソート

	Reset(); //元データの消去

	for (auto itr : copy) { SetMainPot(itr.first, *itr.second); } //割り込んだサイドポットを元からある物として扱う為昇順に再振り分けを行う
}

void Pot::SetMainPot(int pay, const Chara& user) {
	auto itr = pot.begin(); //for開始位置
	int paid = 0; //今回payからpotへ支払った分の金額
	int old = 0; //前回までの支払額

	if (charaPayment.count(&user)) { //一度支払った事がある場合
		itr = pot.find(charaPayment[&user]); //前回支払位置に設定
		old = itr->first; //前回支払分記憶
		itr++; //開始位置を前回支払位置の次に変更する
	}

	for (itr; itr != pot.end(); ++itr) { //開始位置から現在最大ポットまでイテレーターを回し振り分けを行う
		int currentPay = itr->first - paid - old; //今回のポットへの支払要求額
		if (pay < paid + currentPay) { break; } //今回支払った分が支払額を超えたら終了
		itr->second += currentPay; //ポットに要求額を支払う
		paid += currentPay; //今回要求額を支払済みとする
	}

	pot[pay + old] += pay - paid; //各ポットへ支払った額を取り除いて今回額のポットへ支払う
	charaPayment[&user] += pay; //今回の支払額を記録

}