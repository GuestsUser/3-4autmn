#pragma once
#include "Component.h"
#include <deque>

class Button;
class Cmp_Image;
class Poker;

class Cmp_PK_Pause :public Component { //ポーズボタンから起動するポーズ画面、押された時起動したいのでclickに格納する事、pokerに処理を戻す際、親ボタンの他機能をリセットしたいのでこのコンポーネントは最後に付ける事
	Poker* poker; //親ボタンが所属するpokerシーン
	Button* parent; //このコンポーネントを持つ親ボタン

	Cmp_Image* back; //背景画像
	std::deque<Button*> button; //タイトル等へ遷移する為のUI構成ボタン入れ

	bool runClose; //trueになったらResetを実行してポーズ画面を終了する
	int count; //ポーズ画面開始からの経過時間記録
public:
	Cmp_PK_Pause(Button& set, Poker& poker);
	~Cmp_PK_Pause() { delete back; }

	void Update();
	void Draw();
private:
	void CloseOrder() { runClose = true; } //実行するとrunCloseをtrueにする、下記内部クラス向け機能

	class DataSetting; //buttonを正しい位置に設定する等のデータ設定クラス
	class PauseEnd; //ポーズ画面終了機能を持つクラス
	class NewGame; //ポーズ画面を閉じてゲームを最初から始める為の機能を持つクラス
	class GameEnd; //ポーズ画面を閉じてゲームセレクトへ戻る為の機能を持つクラス
};