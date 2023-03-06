#pragma once
#include "Chara.h"
#include <deque>

class Button;
class CardDealer;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;
class Cmp_Gage_MouseControl;
class Cmp_Image;
class Gage;
class PK_Dealer;
class Pot;

class PK_Player :public Chara {
	std::deque<Component*> sectionModule; //各セクションを保持
	Component* runSection; //SectionUpdateで使用するオブジェクトはこちらに移す

	Cmp_BetActionRecord* record; //アクション状況記録用変数
	Button* actionButton; //playerButtonの中でも各種アクションを行うボタンを入れる
	Button* foldButton; //playerButtonの中でもfold専用のボタンを入れる
	Cmp_Image* actionButtonImage; //action用ボタンの画像コンポーネントを入れる変数

	Gage* gage; //プレイヤー保持のゲージ
	Cmp_Gage_Border* gageBorder; //プレイヤーのゲージ下限設定機能のコンポーネント
	Cmp_Gage_UpperBorder* gageUpper; //プレイヤーのゲージ上限設定機能のコンポーネント
	Cmp_Gage_MouseControl* gageControl; //ゲージ操作を受け付けるコンポーネント

	Pot* pot;
	PK_Dealer* dealer;
	CardDealer* cardDealer;
public:
	PK_Player(Pot& pot, PK_Dealer& dealer, CardDealer& cardDealer);
	~PK_Player();

	void SectionUpdate();
	void SetSection(Section set) { runSection = sectionModule[(int)set]; }

private:
	class Main;
	class Change;
};