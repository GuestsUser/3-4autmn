#include <DxLib.h>
#include "PK_ShowDown.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Player.h"
#include "CardDealer.h"
#include "PokerFontData.h"

#include "Cmp_BetActionRecord.h"
#include "../Code/Component/ComponentArray.h"

Poker::ShowDown::ShowDown(Poker& set) :parent(&set), count(0), actionRecord(std::deque<Cmp_BetActionRecord*>((int)Poker::Character::length)), hand(std::deque<std::deque<int>>((int)Poker::Character::length, std::deque<int>(5))), handPos(std::deque<Vector3>((int)Poker::Character::length)), handString(std::deque<std::string>((int)Poker::Character::length)) {
	titlePos.SetXYZ(513, 189, 0); //ショーダウンである事を示すメッセージの位置設定

	//手札役を表示する為の位置設定
	handPos[0].SetXYZ(108, 382, 0);
	handPos[1].SetXYZ(455, 28, 0);
	handPos[2].SetXYZ(1012, 28, 0);
	handPos[3].SetXYZ(1039, 377, 0);
	handPos[4].SetXYZ(497, 400, 0);

	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}

void Poker::ShowDown::Update() {

	if (count == 60) {
		for (int i = 0; i < actionRecord.size(); ++i) { //各キャラをチェックし持ち札を公開する処理
			if (IsFold(*actionRecord[i])) { continue; } //ゲームから除外されていた場合以下処理は実行しない
			for (auto itr : *parent->chara[i]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::front); } //ここまでこれたキャラはカードを表側表示化
		}
	}

	if (count == 120) {
		for (int i = 0; i < parent->chara.size(); ++i) { //ハンド評価を行う
			hand[i] = CardDealer::HandCheck(*parent->chara[i]); //各キャラの手札評価を入れる
			handString[i] = Hand2String(hand[i]); //各キャラの完成役を文字列化した物を格納
		}
	}

	if (count == 180) {
		std::deque<Chara*> enableChara = std::deque<Chara*>(); //勝負を行うキャラ纏め
		std::deque<Chara*> foldChara = std::deque<Chara*>(); //フォールドしたキャラ纏め(敗北済みは除く)

		std::deque<std::deque<int>> enableHand = std::deque<std::deque<int>>(); //勝負を行うキャラのハンド評価纏め

		for (int i = 0; i < parent->chara.size(); ++i) { //キャラを勝負をするキャラ、foldキャラ、除外キャラに仕分ける
			if (actionRecord[i]->GetIsLose()) { continue; } //敗北済みの場合何もせず次キャラへ移行
			if (actionRecord[i]->GetActionRecord(Cmp_BetActionRecord::Action::fold)) { foldChara.push_back(parent->chara[i]); continue; } //foldしてる場合foldCaraへ格納し次キャラへ移行
			enableChara.push_back(parent->chara[i]); //現在キャラをenableCharaへ格納
			enableHand.push_back(hand[i]); //現在キャラのハンド評価格納
		}


		while (enableChara.size() > 0) { //enableChara全てに支払い終えるまで実行
			std::deque<int> max = std::deque<int>(1, 0); //今回支払を行うキャラの添え字集、取り敢えず要素数1で格納値は0

			for (int i = 1; i < enableChara.size(); ++i) { //一番強い役を持つキャラを決定する
				if (enableHand[max[0]][0] > enableHand[i][0]) { continue; } //最強キャラが変わらず最高である場合やり直し
				if (enableHand[max[0]][0] < enableHand[i][0]) { max = std::deque<int>(1, i); continue; } //今回の役の方が強い場合支払を行うキャラを今回の物に変更

				//ここまで来た場合役の強さは同じなので役をなさないカードの強さで強弱をチェックする
				int sameCount; //現在最強キャラと今回キャラの同じ強さのカード枚数
				for (sameCount = 1; sameCount < enableHand[max[0]].size(); ++sameCount) { //構成カード全てをチェック
					if (enableHand[max[0]][sameCount] % (int)CardDealer::CardPower::max != enableHand[i][sameCount] % (int)CardDealer::CardPower::max) { break; } //強さの違うカードに当たったら中断
				}
				if (sameCount >= enableHand[max[0]].size()) { max.push_back(i); continue; } //全てのカードが同じ強さなら今回キャラも支払い対象として配列に追加する
				if (enableHand[max[0]][sameCount] % (int)CardDealer::CardPower::max < enableHand[i][sameCount] % (int)CardDealer::CardPower::max) { max = std::deque<int>(1, i); continue; } //今回キャラの構成カードの方が強ければ最強キャラを今回の物に交換
			}

			//デバッグ用
			//std::deque<int> max = std::deque<int>(); //今回支払を行うキャラの添え字集、取り敢えず要素数1で格納値は0
			//for (int i = 0; i < enableChara.size(); ++i) { max.push_back(i); }

			std::deque<int> copy = max; //maxを編集する為のコピー
			if (copy.size() == 1) { //要素が1つしかない場合
				enableChara[copy[0]]->SetCoin(enableChara[copy[0]]->GetCoint() + parent->pot->PayOut(*enableChara[copy[0]])); //受取金額総取り
				copy.erase(copy.begin()); //要素消し
			}
			else { std::sort(copy.begin(), copy.end(), [=](int a, int b) { return parent->pot->Inquiry(*enableChara[copy[a]]) < parent->pot->Inquiry(*enableChara[copy[b]]); }); } //支払額の昇順ソート

			while (copy.size() > 0) { //copyが空になるまで続ける
				std::deque<Chara*> same = std::deque<Chara*>(1, enableChara[copy[0]]); //支払額同一のキャラまとめ
				int pay = parent->pot->Inquiry(*same[0]); //今回の支払額
				for (int i = 1; i < copy.size(); ++i) { //今回支払額と同一のキャラ探し
					if (pay == parent->pot->Inquiry(*enableChara[copy[i]])) { same.push_back(enableChara[copy[i]]); } //同一なら配列へ格納
				}

				pay = parent->pot->PayOut(*same[0]) / same.size(); //支払いを実行、同一支払額キャラの数だけ金額総を等分
				for (int i = 0; i < same.size(); ++i) { //同一支払額の各キャラへ支払い
					same[i]->SetCoin(same[i]->GetCoint() + pay); //同一支払額のキャラへ配分
					for (int j = 0; j < copy.size(); ++j) { //支払ったキャラをcopyから除外する為のループ
						if (enableChara[copy[j]] == same[i]) { copy.erase(copy.cbegin() + j); break; } //今回支払ったキャラをcopyから除外
					}
				}

			}

			if (parent->pot->TotalAmount() <= 0) { ++count; return; } //支払いの結果ポット内金額が0になった場合その時点で終わり

			std::deque<Chara*> maxChara = std::deque<Chara*>(); //maxを基にenableCharaから取り出した物を保持する配列
			for (int i = 0; i < max.size(); ++i) { maxChara.push_back(enableChara[max[i]]); } //maxCharaへ対応Chara参照を格納


			for (int i = 0; i < maxChara.size(); ++i) { //同一支払額の各キャラへ支払い
				for (int j = 0; j < enableChara.size(); ++j) { //支払ったキャラをcopyから除外する為のループ
					if (enableChara[j] == maxChara[i]) { //enableChara内のどの要素を使ったか特定する
						enableChara.erase(enableChara.begin() + j); //対応要素をenableから除外
						enableHand.erase(enableHand.begin() + j); //handの方も消しておく
						break;
					}
				}
			}
		}
		FoldMemberPayOut(foldChara, *parent->pot); //余ったpotはfoldキャラへ分配

	}

	if (count == 240) {
		parent->run = parent->list[(int)Poker::Section::ini]; //最初の状態に戻る
		count = -1; //カウントリセット

		LoseSet(parent->chara, actionRecord); //敗北状況の設定
		Poker::Section next = GameEndCheck(parent->chara, actionRecord); //敗北状況から次向かうべきシーンを取得

		if (next != Poker::Section::ini) { //ini(続行すべき)以外が入った場合
			parent->run = parent->list[(int)next]; //そのシーンに移行
			count = -1; //カウントリセット
			return; //終わり
		}

	}

	++count;
}

void Poker::ShowDown::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "ショーダウン!!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));

	if (count >= 120) {
		for (int i = 0; i < actionRecord.size(); ++i) { //勝負に挑んだキャラのハンドを表示する
			if (IsFold(*actionRecord[i])) { continue; } //ゲームから除外されていた場合以下処理は実行しない
			DrawStringToHandle(handPos[i].GetX(), handPos[i].GetY(), handString[i].c_str(), *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal)); //ハンド表示
		}
	}


}