#pragma once
#include "Cmp_Transform.h"

#include <map>
#include <unordered_map>

class Cmp_Image;
class PK_Chara;

class PK_Pot { //サイドポット計算、各キャラのポット受け取り資格の記録など支払計算に必要な色々を有するクラス
	Cmp_Image* back; //幾らポットに支払われてるか表示する為のエリアの背景画像
	std::map<int, int> pot; //ポット、first=ポットの要求額、second=そのポット内の合計金額
	std::unordered_map<const PK_Chara*, int> charaPayment; //どのキャラが幾ら支払ったか記録、どのポットを受け取る権利を持つか判断するのに使用、first=キャラ、second=支払額
	Cmp_Transform textPos; //ポット金額表示の座標

public:
	PK_Pot();
	~PK_Pot();

	void Reset(); //ラウンド終了時に呼び出す、ポットや支払状況をリセットする
	int PayOut(const PK_Chara& user); //キャラを渡すとそいつが受け取る権利のある全てのポットが支払われる、支払ったポットは空になる
	void SetSidePot(int pay, const PK_Chara& user); //AllInがあったら呼び出し、そいつの金額に合わせた新しいポットを作成し、再振り分けを行う
	void SetMainPot(int pay, const PK_Chara& user); //平常時ポットへの支払があれば呼び出し

	int Inquiry(const PK_Chara& user); //payOut同様だがこちらは払い出しは行わない自分が幾ら出したか照会する為の機能
	int TotalAmount(); //pot内の現在合計金額を返す
	int GetCurrentMaxBet() { return pot.size() > 0 ? (--pot.end())->first : 0; } //一度でも支払があった場合potの最後の要素の添え字が最大ベット額となる

	void Draw(); //ポット金額表示の背景を描写する
};
