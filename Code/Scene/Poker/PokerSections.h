#pragma once
#include "../Scene.h"
#include "Poker.h"

#include "Btn.h"
#include "CPU.h"
#include "Pot.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"

#include <deque>

class Cmp_Image;
class Cmp_BetActionRecord;
class Cmp_CPUBetLogic;
class Cmp_Gage_Border;
class Cmp_Gage_MouseControl;
class Cmp_PlayerRaiseDraw;
class Button;
class Gage;
class CardDealer;
class Card;

class Poker::Ini :public Scene { //ラウンド開始時の処理を記したUpdateを持つ初期化クラス
	Poker* parent; //このクラスの実体を持つPokerへの参照
public:
	Ini(Poker& set) :parent(&set) {}
	void Update();
};

class Poker::Pre :public Scene { //カードを各キャラへ配るフェイズ
	Poker* parent; //このクラスの実体を持つPokerへの参照
public:
	Pre(Poker& set) :parent(&set) {}
	void Update();
};

class Poker::Main :public Scene { //メインベットフェイズ
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる
	std::deque<Cmp_CPUBetLogic*> betLogic;
	std::deque<Button*> playerButton; //プレイヤーが保持するボタンコンポーネント
	Cmp_PlayerRaiseDraw* playerGagePayDraw; //プレイヤーの現在ゲージ量に応じた支払額を表示するコンポーネント

	Button* actionButton; //playerButtonの中でも各種アクションを行うボタンを入れる
	Button* foldButton; //playerButtonの中でもfold専用のボタンを入れる
	Cmp_Image* actionButtonImage; //action用ボタンの画像コンポーネントを入れる変数

	Gage* playerGage; //プレイヤー保持のゲージ
	Cmp_Gage_Border* playerGageBorder; //プレイヤーのゲージ下限設定機能のコンポーネント
	Cmp_Gage_MouseControl* gageControl; //ゲージ操作を受け付けるコンポーネント

	Poker* parent; //このクラスの実体を持つPokerへの参照
	int phase; //これが何回目のベットフェイズか持っておく変数
	int count; //時間カウント

	int cpuWait; //cpuがアクションを行うまでの待機時間、フレーム数指定

public:
	Main(Poker& set);
	void Update();
	void SetPhase(int set) { phase = set; } //現在のベットフェイズをセット、runにMainを入れたらやっておくといい
};

class Poker::Change :public Scene { //カードを各キャラへ配るフェイズ
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる
	Button* actionButton; //playerButtonの中でも各種アクションを行うボタンを入れる
	std::deque<Button*> cardButton; //カードクリックを検知する為のボタン
	

	Poker* parent; //このクラスの実体を持つPokerへの参照
	CardDealer::CardPower border; //役になってない中で一番強いカードがこの強以上ならそれは保持する
	std::deque<bool> isClick; //カードをクリックして交換指定していればその要素がtrueになる
	int originalY; //カードをクリックした際、位置を前に出すので元に戻せるよう平常時のy記録用
	int moveY; //カードをクリックした時、カードが動くy量

	int count; //時間管理
	int cpuWait; //cpuがアクションを行うまでの待機時間、フレーム数指定
public:
	Change(Poker& set);
	void Update();
};