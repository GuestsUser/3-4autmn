#pragma once
#include "Component.h"
#include "Cmp_Transform.h"

#include <deque>

class Cmp_Sound;

class Cmp_PK_Player_SE :public Component { //charaが共通して持つseとサウンド位置変数を保持するクラス
public:
	enum class Request { coinPlayer, gage };

private:
	Cmp_Transform soundPos; //サウンドの基準とするクラス
	std::deque<Cmp_Sound*> sound; //Charaの管理する共通サウンド

public:
	Cmp_PK_Player_SE(const Cmp_Transform* const soundPos = nullptr);

	void Update() {}

	const Cmp_Sound* const ReadSE(Request request)const { return sound[(int)request]; } //requestで要求したseを編集禁止の形式で呼び出す
	const Cmp_Transform* const ReadTransform()const { return &soundPos; } //サウンドの鳴っている位置を読み出し専用形式で取得
};

