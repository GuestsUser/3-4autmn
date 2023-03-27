#include "PK_Change.h"
#include "PK_Main.h"

#include "Scene.h"
#include "Poker.h"
#include "ConstVal.h"

#include "PK_CPU.h"
#include "PK_Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "PK_SectionLibrary.h"

#include "Button.h"
#include "ComponentArray.h"
#include "Cmp_Image.h"
#include "Cmp_CPUBetLogic.h"

Poker::Change::Change(Poker& set) :parent(&set),actionRecord(std::deque<Cmp_BetActionRecord*>((int)Poker::Character::length)) {
	for (int i = 0; i < parent->chara.size(); ++i) { actionRecord[i] = parent->chara[i]->EditAppendCmp()->EditCmp<Cmp_BetActionRecord>(); } //ベット記録のコンポーネントを取り出し
}

void Poker::Change::Update() {
	int access = parent->dealer->GetActionCharaSub(); //今回アクションを行うキャラへの添え字を記録するアクセスショートカット
	
	parent->chara[access]->SectionUpdate(); //今回キャラのセクション用Updateを実行
	if(actionRecord[access]->GetFinalAction() == Cmp_BetActionRecord::Action::noAction) { return; } //今回キャラがアクションしてない場合以下処理は実行せず終わり


	int endCount = ChangeEndCount(actionRecord, access); //アクション終了済みキャラのチェックを行う
	parent->dealer->SetActionChara((endCount + access) % (int)Poker::Character::length); //終了済みキャラを飛ばし次のキャラへアクション順を回す

	if (endCount >= (int)Poker::Character::length) { //全キャラ終了済みの場合
		SequenceNextReset(actionRecord); //アクション実行状況を次シーン向けにリセット
		parent->dealer->SetActionChara((ActionEndCount(actionRecord, access) + access) % (int)Poker::Character::length); //mainではallInキャラのアクションは不能なのでそれを取り除いた値に応じてとなる
		
		for (auto itr : parent->chara) { itr->SetSection(PK_Chara::Section::main); } //各キャラの実行セクションを変更、showdownは専用のセクションを持たない為これで良し
		parent->run = parent->list[(int)Poker::Section::main]; //セカンドベットへ
		((Poker::Main*)parent->list[(int)Poker::Section::main])->SetPhase(1);


		int endCount = 1; //アクション不能なキャラの数を取得
		for (endCount; endCount < actionRecord.size(); ++endCount) {
			if (!BetIgnore(actionRecord[(access + endCount) % actionRecord.size()])) { break; } //チェックキャラが終了条件の1つにも引っかからなかった場合中断
		}
		if (endCount >= actionRecord.size()) { parent->run = parent->list[(int)Poker::Section::showdown]; } //どのキャラもベット不能の場合ショーダウン直行
	}
}
