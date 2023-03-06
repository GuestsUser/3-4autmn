#pragma once
#include "../Code/Component/Component.h"

#include <deque>

class Cmp_BetActionRecord :public Component {
public:
	enum class Action { check, call, raise, allIn, change, fold, length, noAction }; //キャラクターの行えるアクション、noActionはアクションを行ってない事を示す
private:
	std::deque<bool> actionRecord; //actionの列挙型に対応した添え字にそのアクションを行ったか否か記録する、trueでアクション済み、falseで未実行
	Action finalAction; //このキャラが最後に行ったアクション
	bool isAction; //アクション終了済みでtrue、他にraiseしてきたキャラがいたらfalseに直す
	bool isLose; //所持金0状態で負けた場合、trueにしてこのキャラをゲームから除外する
	int raiseRunCount; //レイズした回数(実際に何回レイズを行ったか)を記録

public:
	Cmp_BetActionRecord() :actionRecord(std::deque<bool>((int)Action::length)), finalAction(Action::noAction), raiseRunCount(0), isAction(false), isLose(false) {}
	void Update() {}

	void FullReset() { //完全リセットはisLooseも戻す
		isLose = false;
		Reset();
	}

	void Reset() { //ラウンド開始時や新しいフェーズに移った際に実行、変数をfalseに戻してくれる
		for (int i = 0; i < actionRecord.size(); ++i) { actionRecord[i] = false; } //全アクションを行ってない状態に戻す
		isAction = false;
		raiseRunCount = 0;
	}

	bool GetActionRecord(Action get) const { return actionRecord[(int)get]; } //Action列挙型を添え字に指定する事で該当アクションを行ったかどうかをboolで受け取れる、trueでアクション済み
	Action GetFinalAction() const { return finalAction; } //最終アクションを取得
	bool GetIsAction() const { return isAction; } //trueでアクション終わってる
	bool GetIsLose() const { return isLose; } //trueで敗北済み
	int GetRaiseRunCount() const { return raiseRunCount; } //このフェーズ中のレイズした回数を返す

	void SetActionRecord(Action get, bool result) { actionRecord[(int)get] = result; } //該当アクションの実行済みか否かを設定する
	void SetFinalAction(Action action) { finalAction = action; } //最終アクションを設定
	void SetIsAction(bool set) { isAction = set; } //アクション終わらせたか設定
	void SetIsLose(bool set) { isLose = set; } //敗北したか否かの設定
	void SetRaiseRunCount(int set) { raiseRunCount = set; } //このフェーズ中のレイズした回数を設定
};