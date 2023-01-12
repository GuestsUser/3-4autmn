#pragma once
#include "../Scene.h"
#include "Poker.h"

#include "Btn.h"
#include "CPU.h"
#include "Pot.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"

#include "../Code/Component/Component.h"
#include "../Code/Component/Button.h"

#include <deque>
#include <string>

class Cmp_Image;
class Cmp_BetActionRecord;
class Cmp_CPUBetLogic;
class Cmp_Gage_Border;
class Cmp_Gage_MouseControl;
class Cmp_PlayerRaiseDraw;
class Gage;
class CardDealer;
class Card;
class Vector3;

class Poker::Ini :public Scene { //ラウンド開始時の処理を記したUpdateを持つ初期化クラス
	Poker* parent; //このクラスの実体を持つPokerへの参照
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる

public:
	Ini(Poker& set);
	void Update();
};

class Poker::Pre :public Scene { //カードを各キャラへ配るフェイズ
	Poker* parent; //このクラスの実体を持つPokerへの参照
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる

public:
	Pre(Poker& set);
	void Update();
};

class Poker::Main :public Scene { //メインベットフェイズ
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる
	std::deque<Cmp_CPUBetLogic*> betLogic;
	std::deque<Button*> playerButton; //プレイヤーが保持するボタンコンポーネント

	Button* actionButton; //playerButtonの中でも各種アクションを行うボタンを入れる
	Button* foldButton; //playerButtonの中でもfold専用のボタンを入れる
	Cmp_Image* actionButtonImage; //action用ボタンの画像コンポーネントを入れる変数
	std::deque<Cmp_Image*> thinkingImage; //考え中である事を示す為の画像を格納する配列


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
	Cmp_Image* actionButtonImage; //action用ボタンの画像コンポーネントを入れる変数
	std::deque<Vector3*> cardPos; //カードの位置へのアクセスショートカット


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

class Poker::ShowDown :public Scene {
	Poker* parent; //このクラスの実体を持つPokerへの参照
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる
	
	std::deque<std::deque<int>> hand; //各キャラのハンド評価を保持
	std::deque<Vector3> handPos; //各キャラのハンドを表示する為の位置集め配列
	std::deque<std::string> handString; //各キャラのハンドをstring型で保持する配列

	int count;



	Vector3 titlePos; //ショーダウンである事を示すメッセージの表示位置

public:
	ShowDown(Poker& set);
	void Update();
	void Draw();
};

class Poker::NoContest :public Scene {
	Poker* parent; //このクラスの実体を持つPokerへの参照
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる
	Button nextButton; //クリックする事で次シーンへ移行する

	int count;
	int payOutTime; //このタイミングで支払いを行う
	int clickStartTime; //countがこの数値に達するとボタンクリックの検知を開始する
	int blink; //この時間間隔で説明を点滅させる

	Vector3 titlePos; //ノーコンテストである事を示すメッセージの表示位置
	Vector3 explainPos; //ボタン説明の配置位置
public:
	NoContest(Poker& set);
	void Update();
	void Draw();
};

class Poker::GameOver :public Scene {
	Poker* parent; //このクラスの実体を持つPokerへの参照
	Button nextButton; //クリックする事で次シーンへ移行する

	int count;
	int clickStartTime; //countがこの数値に達するとボタンクリックの検知を開始する
	int blink; //この時間間隔で説明を点滅させる

	Vector3 titlePos; //ゲームオーバーである事を示すメッセージの表示位置
	Vector3 explainPos; //ボタン説明の配置位置
public:
	GameOver(Poker& set);
	void Update();
	void Draw();
};

class Poker::GameClear :public Scene {
	Poker* parent; //このクラスの実体を持つPokerへの参照
	Vector3 titlePos; //ゲームクリアである事を示すメッセージの表示位置

public:
	GameClear(Poker& set) :parent(&set) {}
	void Update();
	void Draw();
};
