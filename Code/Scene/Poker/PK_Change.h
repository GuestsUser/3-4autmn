#pragma once
#include "../Scene.h"
#include "Poker.h"

#include "CardDealer.h"
#include "../Code/Component/Component.h"

#include <deque>

class Cmp_BetActionRecord;
class Button;
class Vector3;

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