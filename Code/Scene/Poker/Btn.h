#pragma once
#include "../Code/Component/Cmp_Transform.h"
#include <deque>

class Cmp_Image;

class Btn { //ボタン画像とボタンの位置を保有したクラス
	Cmp_Image* img; //ボタン画像
	std::deque<Cmp_Transform> posList; //ボタンを表示する位置集、この配列の並びはキャラ配列と対応している
	int usePos; //posList内のどの位置を表示に使うか決定する添え字変数、この数値がボタンポジションという事になる

public:
	Btn();
	~Btn();
	void Reset(); //新しいラウンド開始時に呼び出す、ポジション位置の更新を行う
	void FullReset(); //ゲーム完全初期化を行いたい時呼び出す、ボタン初期位置をランダム決定したりする

	int GetBtnPos() { return usePos; } //ボタン現在位置を添え字で取得、取得した添え字はキャラを格納する配列に使えばそのキャラを呼び出せる
	void SetBtnPos(int set) { usePos = set % posList.size(); } //ボタン位置を新しく設定、キャラ数を超える値を入れても範囲内に修正してくれる

	void Draw();
};