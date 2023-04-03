#include <DxLib.h>
#include "Cmp_Hand.h"

#include "PK_CardDealer.h"
#include "PK_Card.h"

#include <algorithm>
#include <deque>
#include <string>


Cmp_Hand::Cmp_Hand() :handPower(std::deque<int>()), handName(std::string()) {
	for (int i = 0; i < 5; ++i) { card.push_back(new PK_Card()); } //手札表示を新規作成
}
Cmp_Hand::~Cmp_Hand() {
	for (auto itr : card) { delete itr; } //手札の削除
	card.clear(); //配列のクリア
}

void Cmp_Hand::Update() { for (auto itr : card) { itr->Update(); } } //cardのUpdateを実行
void Cmp_Hand::Draw() { for (auto itr : card) { itr->Draw(); } } //cardのDrawを実行
void Cmp_Hand::FullReset() { for (auto itr : card) { itr->FullReset(); } } //所持するカードのFullResetを呼び出す
void Cmp_Hand::Reset() { for (auto itr : card) { itr->Reset(); } } //所持するカードのResetを呼び出す



std::string Hand2String(const std::deque<int>& hand) {
	switch ((Cmp_Hand::HandRank)(hand[0] / (int)Cmp_Hand::CardPower::max)) {
	case Cmp_Hand::HandRank::No: return "ハイカード"; break;
	case Cmp_Hand::HandRank::OnePair: return "ワンペア"; break;
	case Cmp_Hand::HandRank::TwoPair: return "ツーペア"; break;
	case Cmp_Hand::HandRank::ThreeCard: return "スリーカード"; break;
	case Cmp_Hand::HandRank::Straight: return "ストレート!"; break;
	case Cmp_Hand::HandRank::Flash: return "フラッシュ!"; break;
	case Cmp_Hand::HandRank::FullHause: return "フルハウス!"; break;
	case Cmp_Hand::HandRank::FourCard: return "フォーカード!!"; break;
	case Cmp_Hand::HandRank::StraightFlash: return "ストレートフラッシュ!!"; break;
	case Cmp_Hand::HandRank::RoyalStraightFlash: return "ロイヤルストレートフラッシュ!!!"; break;
	}
}

std::deque<int> CardNumExtract(std::deque<PK_Card*>& card) { //受け取ったcard配列から表示画像に利用する添え字だけ抜き出して配列に詰めて返す
	std::deque<int> set;
	for (auto itr : card) { set.push_back(itr->GetCard()); }
	return set;
}

PK_Card* Num2Card(int card, std::deque<PK_Card*>& originl) { //originalに入れられたCard配列からcardと同一の表示画像添え字のカード参照を返す関数
	for (auto itr : originl) {
		if (itr->GetCard() == card) { return itr; } //対応カードを見つけた場合それを返して終了、対応が複数あった場合最初に出た物が優先される
	}
	return nullptr; //見つからなかった場合nullptrを返す
}

PK_Card* CardPower2Card(int card, std::deque<PK_Card*>& originl) { //cardPowerの形式でoriginalから対応を探す、対応が複数あった場合スートが弱い物が優先される
	for (auto itr : originl) {
		for (int i = 0; i < 4; ++i) { //cardにはどのスートかの情報が入ってないので4つのスート全てを手札と比較して対応を探す
			if (itr->GetCard() == card + ((int)Cmp_Hand::CardPower::max) * i) { return itr; } //対応カードを見つけた場合それを返して終了
		}
	}
	return nullptr; //見つからなかった場合nullptrを返す
}

void HandComboCheck(std::deque<int> hand, Cmp_Hand::deque_map& get) { //handに現在手札を渡すとその手札で同じ強さのカードの個数をgetに入れてくれる
	for (int i = 0; i < hand.size(); ++i) {
		if (hand[i] == -1) { continue; } //チェック済みの-1札の場合飛ばす
		get.push_back(std::pair<int, int>(hand[i] % 13, 1)); //非チェックのカードなら追加しておく

		int sub = get.size() - 1; //今回の添え字
		for (int j = i + 1; j < hand.size(); ++j) {
			if (get[sub].first != hand[j] % (int)Cmp_Hand::CardPower::max) { continue; } //札が違う場合やり直し
			++get[sub].second; //その札の枚数カウントを増やす
			hand[j] = -1; //同じ札をチェックしないよう調べた札に-1入れる
		}
	}
	std::sort(get.begin(), get.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.second == b.second ? a.first > b.first:a.second > b.second; }); //getソート、同一カードが多い順、同一カード数が同じなら添え字が大きい順
}

int HandStraightCheck(const Cmp_Hand::deque_map& combo) { //ストレート(数値が1刻みで並んでる)をチェック、並んでる場合最も大きいカードパワーの返却、失敗の場合-1
	int old = combo.begin()->first; //前回の数値
	bool ato5 = false; //ace～fiveのストレートの場合trueにする
	for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) {
		if (old - itr->first == 1) { old = itr->first; continue; } //連番になっているなら次に行く
		if (old == (int)Cmp_Hand::CardPower::ace && itr->first == (int)Cmp_Hand::CardPower::five) { ato5 = true; old = itr->first; continue; } //前回がAで今回が5ならAを1として扱う為続ける
		return -1; //ここまで来た場合ストレートなし、失敗である-1を返し終了
	}
	return combo[ato5].first; //ace～fiveのストレートの場合先頭ではなく一つ小さい値を取る
}

bool HandFlashCheck(const std::deque<int>& hand) { //フラッシュ(全て同じスート)をチェック
	int suit = hand[0] / 13; //基準スート取り出し
	for (auto itr = ++hand.begin(); itr != hand.end(); ++itr) { if (suit != *itr / 13) { return false; } } //違うスートがあった場合フラッシュはなし
	return true; //ここまでこれれば成功、trueを返す
}

bool HandRoyalCheck(const Cmp_Hand::deque_map& combo) { //ロイヤル(並びがa～10)をチェック
	for (int i = 0; i < combo.size(); ++i) { if (combo[i].first != (int)Cmp_Hand::CardPower::ace - i) { return false; } } //comboは整列済みなので数列に例外的な値があれば失敗
	return true;
}
int HandFlashReachCheck(const std::deque<int>& hand) { //フラッシュリーチ(スート違いが1つだけ)チェック、返り値はスートの違うカード、リーチになってない場合-1
	int flash = -1;
	std::deque<std::deque<int>> suitVol = std::deque<std::deque<int>>(4); //[0]にスート、[0][0]にそのスートに属するカードを格納する
	for (auto itr : hand) { suitVol[(int)(itr / (int)Cmp_Hand::CardPower::max)].push_back(itr); }

	for (auto itr : suitVol) { //各スートに属するカード数をチェックする
		if (itr.size() > 1 && itr.size() < 4) { return -1; } //同種スートが2枚又は3枚あればフラッシュ不可
		if (itr.size() == 1) { //同種スートが1枚の場合
			if (flash != -1) { return -1; } //これが2回目の実行だった場合フラッシュ不可
			flash = itr[0]; //1枚のカードを格納
		}
	}
	return flash;
}
int HandStraightReachCheck(Cmp_Hand::deque_map combo, const std::deque<int>& hand) { //ストレートリーチ(スート違いが1つだけ)チェック、返り値はスートの違うカード、リーチになってない場合-1
	int straight = -1;
	if (combo[0].second > 2) { return -1; } //同種カードが2枚を超える場合ストレートは無理
	if (combo[1].second > 1) { return -1; } //ペアができてる場合ストレートは無理

	if (combo[0].second >= 2) { straight = combo[0].first; } //重複カードがある場合不要カードはそれ
	std::sort(combo.begin(), combo.end(), [](std::pair<int, int> a, std::pair<int, int> b) { return a.first > b.first; }); //同種カード保持枚数に関係なくカードの強さ順に並び替え

	if (combo[0].first == (int)Cmp_Hand::CardPower::ace && (combo[1].first == (int)Cmp_Hand::CardPower::five || combo[1].first == (int)Cmp_Hand::CardPower::four)) { //ace,twoの並びの場合aceをoneにして配列の最後へ格納する
		int copy = combo[0].second; //先頭のaceのカード枚数を記憶
		combo.erase(combo.begin()); //先頭を削除
		combo.push_back(std::pair<int, int>((int)Cmp_Hand::CardPower::one, copy)); //後ろに追加aceをoneに改めた物を追加
	}

	//oneの場合のストレートチェック未完成、aceを除き、2345の内3枚があればaceをoneとして扱う
	//if (combo[0].first == (int)CardDealer::CardPower::ace) {

	//}


	int start = combo[0].first - combo[1].first > 1; //一番強いカードと次のカードが繋がっている場合false、繋がっていなければtrueが返る、int型なので其々0、1に変換される
	int changeCount = 0; //繋がってないカードを検知した回数記録

	if (straight != -1 && combo[0].first - combo[1].first > 1) { return -1; } //重複カードがある且つ先頭と次のカードの差が2以上の場合重複カードと先頭カードを交換する必要があるのでストレートは無理
	if (straight == -1 && start) { straight = combo[0].first; } //先頭カードと次カードが繋がってなかった場合交換カードに先頭カードを指定、重複カードがあった場合そっちを優先
	if (straight == -1) { straight = combo[combo.size() - 1].first == (int)Cmp_Hand::CardPower::one ? (int)Cmp_Hand::CardPower::ace : combo[combo.size() - 1].first; } //交換指定がない場合一番弱いカードを交換する、oneの場合aceに直しておく

	int old = combo[start].first; //前回のカードの強さ入れ

	for (int i = start + 1; i < combo.size(); ++i) { //先頭以外に繋がってない部分がないかチェック
		if (old - 1 != combo[i].first) { //前回数値が今回数値と繋がらかかった場合
			if (changeCount > 0) { return -1; } //2回目の実行ならストレートは不可
			old = old - 2; //次に繋がるようoldを補完しておく、今回のfirstに合わせると2枚以上カードを飛び越える可能性があるので-2という形にする
			changeCount++; //繋がってないカードカウント
			continue; //やり直し
		}
		old = combo[i].first;
	}
	if (changeCount <= 0) { return -1; } //繋がってないカードを検知しなかった場合ストレートは無理というかもうできてる

	for (auto itr : hand) { //comboはカードをカードパワーで格納してるのでそれを通常カードに直す処理
		if (itr % (int)Cmp_Hand::CardPower::max == straight) { return itr; } //不要なカードとhand内の一致するカードパワーがあればそのカードを不要なカードとして返して終わり
	}
	return 99999; //多分ないと思うがエラー
}




void Cmp_Hand::HandPowerUpdate() {
	handPower.clear(); //中身のリセット
	deque_map combo = deque_map(); //first=カードの強さ second=そのカードの枚数 で構成されたカード格納配列
	std::deque<int> hand = CardNumExtract(card); //手札を数値化した物を格納

	HandComboCheck(hand, combo); //同一カードを格納する

	while (true) { //breakを使って処理の流れをコントロールしたいのでwhileを採用、ループの意図はない
		if (combo.begin()->second == 1) { //同じカードが1枚もなかった場合
			int max = HandStraightCheck(combo); //役を構成するカードの中で最大カードパワー、ストレートの有効チェックも兼ねている
			bool straight = max > 0; //maxに0以上が入っていればストレート有効
			bool flash = HandFlashCheck(hand); //フラッシュ評価結果を入れておく

			handPower.push_back(combo.begin()->first); //comboから最大カードパワーを取っておく
			for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { handPower.push_back(itr->first); } //カード格納

			if (straight && flash) { //ストレートとフラッシュが有効な場合に限りロイヤルチェックを行う
				if (HandRoyalCheck(combo)) { handPower[0] = ((int)HandRank::RoyalStraightFlash) * (int)CardPower::max + max; } //ロイヤルが有効だった場合ロイヤルストレートフラッシュ
				else { handPower[0] = ((int)HandRank::StraightFlash) * (int)CardPower::max + max; } //無効化であればストレートフラッシュ
				break; //ポイント計算終わり
			}
			if (straight) { handPower[0] = ((int)HandRank::Straight) * (int)CardPower::max + max; break; } //ストレートを返す
			if (flash) { handPower[0] = ((int)HandRank::Flash) * (int)CardPower::max + handPower[0]; break; } //フラッシュを返す

			break; //ポイント計算終わり
		}

		if ((combo.begin() + 1)->second == 1) { //カードがペア(aaa33のように同じカードの組ができてる、ワンペアは対象外)ではない場合
			HandRank rank = HandRank::OnePair; //同じカードの枚数に応じてランクを決定、取り敢えずワンペア
			if (combo.begin()->second == 3) { rank = HandRank::ThreeCard; } //3枚あればスリーカード
			if (combo.begin()->second == 4) { rank = HandRank::FourCard; } //4枚ならばフォーカード

			handPower.push_back(((int)rank) * (int)CardPower::max + combo.begin()->first); //ランクに応じた得点入れ
			for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { handPower.push_back(itr->first); } //余ったカードを入れる
			break; //ポイント計算終わり
		}

		//残りはペアの場合の点計算のみ
		handPower.push_back(((int)(combo.begin()->second == 3 ? HandRank::FullHause : HandRank::TwoPair)) * (int)CardPower::max + combo.begin()->first); //同じカードが3枚あった場合フルハウス、そうでないならツーペア
		for (auto itr = ++combo.begin(); itr != combo.end(); ++itr) { handPower.push_back(itr->first); } //余ったカードを入れる
		break; //ポイント計算終わり
	}
	handName = Hand2String(handPower); //完成役名を更新
}

PK_Card* Cmp_Hand::ReachCheck() {
	deque_map combo = deque_map(); //first=カードの強さ second=そのカードの枚数 で構成されたカード格納配列
	std::deque<int> hand = CardNumExtract(card); //手札を数値化した物を格納
	HandComboCheck(hand, combo); //同一カードを格納する

	PK_Card* flash = Num2Card(HandFlashReachCheck(hand), card); //フラッシュ完成に不要なカード
	PK_Card* straight = Num2Card(HandStraightReachCheck(combo, hand), card); //ストレート完成に不要なカード

	if (flash != nullptr && straight != nullptr) { //ストレート、フラッシュ両方可能だった場合
		if (flash->GetCard() % (int)Cmp_Hand::CardPower::max == straight->GetCard() % (int)Cmp_Hand::CardPower::max) { straight = flash; } //ストレートの変更カードに重複カードがあった場合2つのカードの内hand要素の若い方を返すのだが、flashと要求カードパワーが一緒だったならflashのカードに合わせる
		return GetRand(1) ? flash : straight; //両方ヒットした場合どちらを返すかはGetRandでランダム決定する
	}

	return flash == nullptr ? straight : flash; //空じゃない方を返す、両方空の場合straightを返すが中身はどっちも一緒だから関係ない
}