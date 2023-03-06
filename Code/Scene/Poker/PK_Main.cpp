#include "PK_Main.h"

#include "../Scene.h"
#include "Poker.h"
#include "PK_SectionLibrary.h"
#include "../Code/ConstVal.h"

#include "CPU.h"
#include "Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"

#include "../Code/Component/ComponentArray.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "Cmp_BetActionRecord.h"


Poker::Main::Main(Poker& set) :parent(&set), phase(0), count(0), actionRecord(std::deque<Cmp_BetActionRecord*>((int)Poker::Character::length)), playerGage(nullptr), playerGageBorder(nullptr) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し

	playerGage = parent->chara[(int)Poker::Character::player]->EditAppendCmp()->EditCmp<Gage>(); //ゲージ取り出し
	playerGageBorder = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_Border>(); //ゲージから各種機能を取り出す
	playerGageUpper = playerGage->EditAppendCmp()->EditCmp<Cmp_Gage_UpperBorder>(); //プレイヤーゲージから上限設定機能の取り出し
}

void Poker::Main::Update() {
	int access = parent->dealer->GetActionCharaSub(); //今回アクションを行うキャラへの添え字を記録するアクセスショートカット

	parent->chara[access]->SectionUpdate(); //今回キャラのセクション用Updateを実行
	Cmp_BetActionRecord::Action result = actionRecord[access]->GetFinalAction(); //アクション結果を取得

	if (result == Cmp_BetActionRecord::Action::noAction) { return; } //アクションしてない場合以下処理は実行せず終わり
	if (result == Cmp_BetActionRecord::Action::raise) {
		for (auto itr : actionRecord) { if (!BetIgnore(itr)) { itr->SetIsAction(false); } } //fold,allInをしていない場合未アクション状態に更新する
		playerGageBorder->SetBorder((float)(parent->pot->GetCurrentMaxBet()) / (parent->dealer->GetBB() * parent->dealer->GetMaxBet())); //ゲージの最低値を更新
		actionRecord[access]->SetIsAction(true); //レイズしたキャラのアクションは終了済みに設定する
	}
	if (result == Cmp_BetActionRecord::Action::fold) { //フォールドした場合ラウンド中断チェックを行う
		for (auto itr : *parent->chara[access]->EditCard()) { itr->SetDrawMode(PK_Card::DrawMode::fold); } //手札をfold表示へ変更

		if (FoldCount(actionRecord, access) >= (int)Poker::Character::length - 1) { //1キャラ以外全てキャラが抜けた場合ノーコンテストへ
			SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
			parent->run = parent->list[(int)Poker::Section::nocontest]; //ノーコンテストへ移行
			return; //処理終わり
		}
	}

	int endCount = ActionEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
	parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す

	if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
		SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
		parent->dealer->SetActionChara((ChangeEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //changeはallInしたキャラもアクション対象なので次回キャラの設定に含める

		for (auto itr : parent->chara) { itr->SetSection(Chara::Section::change); } //各キャラの実行セクションを変更、showdownは専用のセクションを持たない為これで良し

		if (phase == 0) { parent->run = parent->list[(int)Poker::Section::change]; } //ファーストベットだった場合次実行するシーケンスはカード交換
		else { parent->run = parent->list[(int)Poker::Section::showdown]; } //セカンドベットならショーダウンへ移行する
	}
}
