#pragma once
#include "Scene.h"
#include <deque>

class Btn;
class Button;
class Cmp_Image;
class PK_BGM;
class PK_Chara;
class PK_CardDealer;
class PK_Dealer;
class PK_Player;
class PK_Pot;

class Poker :public Scene { //ポーカーのゲームシーン
	Button* pauseButton; //ポーズ画面に移行する為のボタン
	PK_BGM* bgm;
	PK_Pot* pot;
	PK_Dealer* dealer;
	PK_CardDealer* cardDealer;
	std::deque<PK_Chara*> chara;
	Cmp_Image* back; //背景

	std::deque<Scene*> list; //ポーカーを行う為の処理を行うシーンの実体保持用配列
	Scene* run; //これに入ってるシーンを実行する
public:
	enum class Character { leftCom, topLeftCom, topRightCom, rightCom, player, length }; //charaから狙ったキャラを取り出す為の要素指定用列挙型、lengthを参照すればキャラ数を取得できるライフハック
	enum class Section { ini, pre, main, change, showdown, nocontest, gameover, gameclear, newgamereset, titleback }; //list配列から望んだシーンを取り出す為の要素指定用列挙型

	Poker();
	~Poker();
	void Update();
	void Draw();

	void SetNextSection(Section section); //次実行に移すセクションの設定
	PK_BGM* const ControlBGM() { return bgm; } //bgmを置き換え不可の形で返す

private: //ポーカーを行う為のデータを操作する処理を定義したPoker管理シーン前方宣言
	class Ini;
	class Pre;
	class Main;
	class Change;
	class ShowDown;
	class NoContest;
	class GameOver;
	class GameClear;

	class NewGameReset;
};