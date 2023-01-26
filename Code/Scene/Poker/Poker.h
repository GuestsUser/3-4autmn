#pragma once
#include "../Scene.h"
#include <deque>

class Btn;
class CardDealer;
class Cmp_Image;
class Chara;
class PK_Dealer;
class PK_Player;
class Pot;

class Poker :public Scene { //ポーカーのゲームシーン
	Pot* pot;
	PK_Dealer* dealer;
	CardDealer* cardDealer;
	std::deque<Chara*> chara;
	Cmp_Image* back; //背景

	std::deque<Scene*> list; //ポーカーを行う為の処理を行うシーンの実体保持用配列
	Scene* run; //これに入ってるシーンを実行する
public:
	enum class Character { leftCom, topCom, rightCom, player, length }; //charaから狙ったキャラを取り出す為の要素指定用列挙型、lengthを参照すればキャラ数を取得できるライフハック

	Poker();
	~Poker();
	void Update();
	void Draw();

private: //ポーカーを行う為のデータを操作する処理を定義したPoker管理シーン前方宣言
	enum class Section { ini, pre, main, change, showdown, nocontest, gameover, gameclear }; //list配列から望んだシーンを取り出す為の要素指定用列挙型
	class Ini;
	class Pre;
	class Main;
	class Change;
	class ShowDown;
	class NoContest;
	class GameOver;
	class GameClear;
};