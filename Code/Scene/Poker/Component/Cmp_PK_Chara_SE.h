#pragma once
#include "Component.h"
#include "Cmp_Transform.h"

#include <deque>

class Cmp_Sound;
class PK_Dealer;

class Cmp_PK_Chara_SE :public Component { //charaが共通して持つseとサウンド位置変数を保持するクラス
public:
	enum class Request { call, fold, raise, cardChange, cardOpen, cardPlace, coinFew, coinMany };

private:
	Cmp_Transform soundPos; //サウンドの基準とするクラス
	std::deque<Cmp_Sound*> sound; //Charaの管理する共通サウンド
	static int fewBorder; //レイズ数がこの数値未満の場合コイン取得音にfewを使う

public:
	Cmp_PK_Chara_SE(const Cmp_Transform* const soundPos = nullptr);

	void Update() {}

	const Cmp_Sound* const ReadSE(Request request)const { return sound[(int)request]; } //requestで要求したseを編集禁止の形式で呼び出す
	const Cmp_Transform* const ReadTransform()const { return &soundPos; } //サウンドの鳴っている位置を読み出し専用形式で取得

	static Cmp_PK_Chara_SE::Request UseCoinSound(int pay, PK_Dealer& dealer); //pay金額がボーダー以上ならmanyを、未満ならfewをrequest形式で返す
};

