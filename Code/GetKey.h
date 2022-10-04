#pragma once
#include "DxLib.h"

//このファイルをインクルードするとkeyという変数が使用可能になる、そこからキー入力に関する様々な情報を受け取れる

constexpr short SHORT_SIZE = 32767; //short最大値、スティックの傾きはshortの値で返ってくるらしいのでこれに小数点を掛ければ
constexpr double X_TILT_MIN = SHORT_SIZE * 0.4; //スティックの傾きがこれ未満の場合入力判定にはならない、これはx軸用
constexpr double Y_TILT_MIN = SHORT_SIZE * 0.4; //上記のy軸用

//GetKeyStateで返ってくる値、Aボタン(緑ボタン)を今押したかどうかで条件分岐したい場合 if (GetKeyState(A_KEY) == KEY_PUSH) { 押した瞬間の処理 } のような具合になる
extern constexpr int KEY_PUSH = 0; //押した瞬間
extern constexpr int KEY_HOLD = 1; //押しっぱなし
extern constexpr int KEY_PULL = 2; //離した瞬間
extern constexpr int KEY_FREE = 3; //離しっぱなし

//GetKeyState等で引数に渡す変数、Aボタン(緑ボタン)の状態が知りたかったらGetKeyState(A_KEY)で取得できる
//このリストに載ってないように現在LT、RTボタンの状態は受け取れない
extern int A_KEY;
extern int B_KEY;
extern int X_KEY;
extern int Y_KEY;
extern int L_KEY;
extern int R_KEY;
extern int POUSE_KEY; //start
extern int SELECT_KEY; //back

//KeySystem各関数のrequestにスティックをリクエストする為のconst値、その他ボタンとの重複を避ける為100を基準に打っている
//
extern constexpr int L_STICK_UP = 100;
extern constexpr int L_STICK_DOWN = 101;
extern constexpr int L_STICK_LEFT = 102;
extern constexpr int L_STICK_RIGHT = 103;
extern constexpr int R_STICK_UP = 104;
extern constexpr int R_STICK_DOWN = 105;
extern constexpr int R_STICK_LEFT = 106;
extern constexpr int R_STICK_RIGHT = 107;

//GetTiltに指定するスティック傾き方向
extern constexpr int LX_TILT = 0; //左スティックのx軸の動きをチェックする、-なら左、+なら右に傾いている
extern constexpr int LY_TILT = 1; //左スティックy軸の動きを見る、-なら下、+なら上に傾いている
extern constexpr int RX_TILT = 2; //上記の右スティック用
extern constexpr int RY_TILT = 3;

//Xinputでは上方向、右方向がプラスらしいので押しっぱなし配列等はdulr(下、上、左、右)の順番で並んでいる

class KeySystem {
private:
	const int key_vol = 12;
	int key_state[20];
	int hold_time[20];
	double tilt[4];
	XINPUT_STATE input;
public:
	KeySystem();
	//~KeySystem();
	void KeyInput(); //キー入力受付関数、これを毎フレーム1回呼び出す事でキーの状態を更新する
	int GetKeyState(int request); //指定キーが押されてるかどうかを取得できる、引数には取得したいキーを指定する
	int GetKeyHoldTime(int request); //指定キーが押しっぱなし、離しっぱなしならそのフレーム数を取得できる
	double GetTilt(int request) { return tilt[request]; } //指定スティックの傾きの値が取得できる
};

extern KeySystem* key; //グローバル変数宣言、ヘッダーに宣言を載せる事で他ファイルからも呼び出し可能になる