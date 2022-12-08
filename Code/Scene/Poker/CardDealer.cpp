#include <DxLib.h>

#include "CardDealer.h"
#include "PK_Card.h"
#include "Chara.h"

#include <algorithm>
#include <deque>
#include <numeric>
#include <random>
#include <unordered_map>
#include <utility>

CardDealer::CardDealer() :deck(std::deque<int>(52)), gen(std::mt19937()), top(0) { gen.seed((std::random_device())()); }

void CardDealer::Reset() {
	top = 0; //山札の上を0に戻す
	std::iota(deck.begin(), deck.end(), 0); //0～52の値を各要素に格納
	std::shuffle(deck.begin(), deck.end(), gen); //代入されている値をランダム交換
}

int CardDealer::DeckDraw() {
	++top; //山札を引くので1つ増やして次の添え字へ
	return deck[top - 1]; //今回の山札の数値を返す
}




void HandComboCheck(std::deque<int> hand, CardDealer::deque_map& get) { //handに現在手札を渡すとその手札で同じ強さのカードの個数をgetに入れてくれる
	for (int i = 0; i < hand.size(); ++i) {
		if (hand[i] = -1) { continue; } //チェック済みの-1札の場合飛ばす
		++get[hand[i] % 13].second; //非チェックのカードなら個数加算しておく

		for (int j = i; j < hand.size(); ++j) {
			if (hand[i] % (int)CardDealer::CardPower::max != hand[j] % (int)CardDealer::CardPower::max) { continue; } //札が違う場合やり直し
			++get[hand[j] % 13].second; //その札の枚数カウントを増やす
			hand[j] = -1; //同じ札をチェックしないよう調べた札に-1入れる
		}
	}
	std::sort(get.begin(), get.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.second == b.second ? a.first > b.first:a.second > b.second; }); //getソート、同一カードが多い順、同一カード数が同じなら添え字が大きい順
}

int HandStraightCheck(const CardDealer::deque_map& combo) { //ストレート(数値が1刻みで並んでる)をチェック、並んでる場合最も大きいカードパワーの返却、失敗の場合-1
	int old = combo.begin()->first; //前回の数値
	bool ato5 = false; //ace～fiveのストレートの場合trueにする
	for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) {
		if (old - itr->first == 1) { old = itr->first; continue; } //連番になっているなら次に行く
		if (old == (int)CardDealer::CardPower::ace && itr->first == (int)CardDealer::CardPower::five) { ato5 = true; old = itr->first; continue; } //前回がAで今回が5ならAを1として扱う為続ける
		return -1; //ここまで来た場合ストレートなし、失敗である-1を返し終了
	}
	return combo[ato5].first; //ace～fiveのストレートの場合先頭ではなく一つ小さい値を取る
}

bool HandFlashCheck(const std::deque<int>& hand) { //フラッシュ(全て同じスート)をチェック
	int suit = hand[0] / 13; //基準スート取り出し
	for (auto itr = ++hand.begin(); itr != hand.end(); ++itr) { if (suit != *itr / 13) { return false; } } //違うスートがあった場合フラッシュはなし
	return true; //ここまでこれれば成功、trueを返す
}

bool HandRoyalCheck(const CardDealer::deque_map& combo) { //ロイヤル(並びがa～10)をチェック
	for (int i = 0; i < combo.size(); ++i) { if (combo[i].first != (int)CardDealer::CardPower::ace - i) { return false; } } //comboは整列済みなので数列に例外的な値があれば失敗
	return true;
}
int HandFlashReachCheck(const std::deque<int>& hand) { //フラッシュリーチ(スート違いが1つだけ)チェック、返り値はスートの違うカード、リーチになってない場合-1
	int flash = -1;
	std::deque<std::deque<int>> suitVol = std::deque<std::deque<int>>(4); //[0]にスート、[0][0]にそのスートに属するカードを格納する
	for (auto itr : hand) { suitVol[(int)(itr / (int)CardDealer::CardPower::max)].push_back(itr); }

	for (auto itr : suitVol) { //各スートに属するカード数をチェックする
		if (itr.size() > 1 && itr.size() < 4) { return -1; } //同種スートが2枚又は3枚あればフラッシュ不可
		if (itr.size() == 1) { //同種スートが1枚の場合
			if (flash != -1) { return -1; } //これが2回目の実行だった場合フラッシュ不可
			flash = itr[0]; //1枚のカードを格納
		}
	}
	return flash;
}
int HandStraightReachCheck(CardDealer::deque_map combo, const std::deque<int>& hand) { //ストレートリーチ(スート違いが1つだけ)チェック、返り値はスートの違うカード、リーチになってない場合-1
	int straight = -1;
	if (combo[0].second > 2) { return -1; } //同種カードが2枚を超える場合ストレートは無理
	if (combo[1].second > 1) { return -1; } //ペアができてる場合ストレートは無理

	if (combo[0].second >= 2) { straight = combo[0].first; } //重複カードがある場合不要カードはそれ
	std::sort(combo.begin(), combo.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.first > b.first; }); //同種カード保持枚数に関係なくカードの強さ順に並び替え
	
	if (combo[0].first == (int)CardDealer::CardPower::ace && (combo[1].first == (int)CardDealer::CardPower::five || combo[1].first == (int)CardDealer::CardPower::four)) { //ace,twoの並びの場合aceをoneにして配列の最後へ格納する
		int copy = combo[0].second; //先頭のaceのカード枚数を記憶
		combo.erase(combo.begin()); //先頭を削除
		combo.push_back(std::pair<int, int>((int)CardDealer::CardPower::one, copy)); //後ろに追加aceをoneに改めた物を追加
	}
	
	int start = combo[0].first - combo[1].first > 0; //一番強いカードと次のカードが繋がっている場合false、繋がっていなければtrueが返る、int型なので其々0、1に変換される
	int changeCount = start; //繋がってないカードを検知した回数記録、startが1なら先頭と次が繋がってないからこちらも1開始

	if (straight != -1 && combo[0].first - combo[1].first > 1) { return -1; } //重複カードがある且つ先頭と次のカードの差が2以上の場合重複カードと先頭カードを交換する必要があるのでストレートは無理
	if (straight == -1 && start) { straight = combo[0].first; } //先頭カードと次カードが繋がってなかった場合交換カードに先頭カードを指定、重複カードがあった場合そっちを優先
	if (straight == -1) { straight = combo[combo.size() - 1].first == (int)CardDealer::CardPower::one ? (int)CardDealer::CardPower::ace : combo[combo.size() - 1].first; } //交換指定がない場合一番弱いカードを交換する、oneの場合aceに直しておく

	int old = combo[start].first; //前回のカードの強さ入れ
	
	for (int i = start + 1; i < combo.size(); ++i) { //先頭以外に繋がってない部分がないかチェック
		if (old - 1 != combo[i].first) { //前回数値が今回数値と繋がらかかった場合
			if (changeCount > 0) { return -1; } //2回目の実行ならストレートは不可
			old = old - 1; //次に繋がるようoldを補完しておく
			changeCount++; //繋がってないカードカウント
			continue; //やり直し
		}
		old = combo[i].first;
	}
	if (changeCount <= 0) { return -1; } //繋がってないカードを検知しなかった場合ストレートは無理というかもうできてる

	for (auto itr : hand) { //comboはカードをカードパワーで格納してるのでそれを通常カードに直す処理
		if (itr % (int)CardDealer::CardPower::max == straight) { return itr; } //不要なカードとhand内の一致するカードパワーがあればそのカードを不要なカードとして返して終わり
	}
	return 99999; //多分ないと思うがエラー
}




std::deque<int> CardDealer::HandCheck(const Chara& chara) {
	std::deque<int> point = std::deque<int>();
	deque_map combo = deque_map(); //first=カードの強さ second=そのカードの枚数 で構成されたカード格納配列
	std::deque<int> hand; //手札を数値化した物を格納
	chara.GetHandNum(hand); //キャラから手札配列を取得

	HandComboCheck(hand, combo); //同一カードを格納する


	if (combo.begin()->second == 1) { //同じカードが1枚もなかった場合
		int max = HandStraightCheck(combo); //役を構成するカードの中で最大カードパワー、ストレートの有効チェックも兼ねている
		bool straight = max > 0; //maxに0以上が入っていればストレート有効
		bool flash = HandFlashCheck(hand); //フラッシュ評価結果を入れておく

		point.push_back(combo.begin()->first); //comboから最大カードパワーを取っておく
		for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { point.push_back(itr->first); } //カード格納

		if (straight && flash) { //ストレートとフラッシュが有効な場合に限りロイヤルチェックを行う
			if (HandRoyalCheck(combo)) { point[0] = ((int)HandRank::RoyalStraightFlash) * (int)CardPower::max + max; } //ロイヤルが有効だった場合ロイヤルストレートフラッシュ
			else { point[0] = ((int)HandRank::StraightFlash) * (int)CardPower::max + max; } //無効化であればストレートフラッシュ
			return point; //ポイント計算終わり
		}
		if (straight) { point[0] = ((int)HandRank::Straight) * (int)CardPower::max + max; return point; } //ストレートを返す
		if (flash) { point[0] = ((int)HandRank::Flash) * (int)CardPower::max + point[0]; return point; } //フラッシュを返す

		return point; //ポイント計算終わり
	}


	if (++combo.begin()->second == 1) { //カードがペア(aaa33のように同じカードの組ができてる、ワンペアは対象外)ではない場合
		HandRank rank = HandRank::OnePair; //同じカードの枚数に応じてランクを決定、取り敢えずワンペア
		if (combo.begin()->second == 3) { rank = HandRank::ThreeCard; } //3枚あればスリーカード
		if (combo.begin()->second == 4) { rank = HandRank::FourCard; } //4枚ならばフォーカード

		point.push_back(((int)rank) * (int)CardPower::max + combo.begin()->first); //ランクに応じた得点入れ
		for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { point.push_back(itr->first); } //余ったカードを入れる
		return point; //ポイント計算終わり
	}
	

	//残りはペアの場合の点計算のみ
	point.push_back(((int)(combo.begin()->second == 3 ? HandRank::FullHause : HandRank::TwoPair)) * (int)CardPower::max + combo.begin()->first); //同じカードが3枚あった場合フルハウス、そうでないならツーペア
	for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { point.push_back(itr->first); } //余ったカードを入れる
	return point; //ポイント計算終わり
}

int CardDealer::ReachCheck(const Chara& chara) {
	deque_map combo = deque_map(); //first=カードの強さ second=そのカードの枚数 で構成されたカード格納配列
	std::deque<int> hand; //手札を数値化した物を格納
	chara.GetHandNum(hand); //キャラから手札配列を取得
	HandComboCheck(hand, combo); //同一カードを格納する

	int flash = HandFlashReachCheck(hand); //フラッシュ完成に不要なカード
	int straight = HandStraightReachCheck(combo, hand); //ストレート完成に不要なカード

	if (flash > -1 && straight > -1) { //ストレート、フラッシュ両方可能だった場合
		if (flash % (int)CardDealer::CardPower::max == straight % (int)CardDealer::CardPower::max) { straight = flash; } //ストレートの変更カードに重複カードがあった場合2つのカードの内hand要素の若い方を返すのだが、flashと要求カードパワーが一緒だったならflashのカードに合わせる
		return GetRand(1) ? flash : straight; //両方ヒットした場合どちらを返すかはGetRandでランダム決定する
	}

	return flash == -1 ? straight : flash; //-1じゃない方を返す、両方-1の場合straightを返すが中身はどっちも一緒だから関係ない
}