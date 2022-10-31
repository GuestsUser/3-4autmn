#include"CF_Player.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"
#include<time.h>

//CF_Player cf_player;
void CF_Player::CF_Player_Initialize() {
	CF_Back = LoadGraph("Resource/image/CF_Back.png"); //背景
	CF_Panel = LoadGraph("Resource/image/CF_Panel.png"); //パネル
	CF_PCoin = LoadGraph("Resource/image/Player_Coin.png"); //プレイヤーコイン
	CF_CCoin = LoadGraph("Resource/image/CPU_Coin.png"); //CPUコイン
	Player_Y = 50; //プレイヤーのY座標の初期値
	k = 1;
	Yajirusi_Y = 100; //矢印の初期値
	Yajirusi_Move = 0.5f; //矢印のアニメーションの初期値
	yadd = 0.0f; //重力加速度の初期値
	FallCount = 0.0f; //コインが落ちるまでの時間の初期値;
	DlayCount = 0; //
	for (i = 0; i < Board_Ysize; i++) {
		for (j = 0; j < Board_Xsize; j++) {
			Coin_Exp[j][i] = 0.17f;
		}
	}
	Mouse_Push = false; //左クリックされたかのフラグの初期値
	CF_Clear = false; //クリアフラグの初期値
	CF_Draw = false; //ドローフラグの初期値
	CF_Start = false; //ゲームがスタートしたかのフラグの初期値
	for (i = 0; i < 7; i++) {
		Yajirusi_Col[i] = 0xff0000; //矢印の色の初期値
	}
	Board_Init();//パネル情報の初期化
	srand((unsigned int)time(NULL));
	PlayUser = rand() % 2 + 1; //プレイヤーの先攻後攻をランダムで取得
}
void CF_Player::CF_Player_Finalize() {
	DeleteGraph(CF_Back); //画像削除処理
	DeleteGraph(CF_Panel);
}
void CF_Player::CF_Player_Update() {
	if (CF_Start == false) {
		DlayCount++;
		if (DlayCount > 150) {
			DlayCount = 0;
			CF_Start = true;
		}
	}
	if (CF_Clear == false && CF_Draw == false && CF_Start == true) {
		if (Mouse_Push == false) {
			GetMousePoint(&Mouse_X, &Mouse_Y); //マウスの座標取得
		}
		Player_X = Mouse_X;
		if (Player_X <= 306) {
			Player_X = 306;
		}
		else if (Player_X >= 990) {
			Player_X = 990;
		}
		Yajirusi_Y += Yajirusi_Move;
		if (100 >= Yajirusi_Y) {
			Yajirusi_Y = 100;
			Yajirusi_Move = -Yajirusi_Move;
		}
		else if (Yajirusi_Y >= 115) {
			Yajirusi_Y = 115;
			Yajirusi_Move = -Yajirusi_Move;
		}
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (j * 114 + 306 - 48 < Player_X && Player_X < j * 114 + 306 + 48) { //矢印の範囲にコインが入ったら
					if (CF_Board[j][0] == Coin_Space) {
						if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
							Mouse_Push = true;
						}
						if (Mouse_Push == true) {
							Coin_Fall(); //コインを配置する
						}
					}
					Yajirusi_Col[j] = 0xffffff;
				}
				else {
					Yajirusi_Col[j] = 0xff0000;
				}
				if (CF_Board[j][i] == Coin_Space) {
					continue;
				}
				if (ClearCheck(CF_Board, j, i)) {
					CF_Clear = true;
				}
				if (DrawCheck(CF_Board)) {
					CF_Draw = true;
				}
			}
		}
	}
	else if (CF_Clear == true) {
	}
}
void CF_Player::CF_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, CF_Back, TRUE);
	if (CF_Start == false) {
		SetFontSize(160);
		if (DlayCount > 30){
			DrawFormatString(50, 200, 0xffffff, "あなた");
			DrawFormatString(50, 400, 0xffffff, "ＣＰＵ");
			DrawRotaGraph(700, 280, 0.45, 0, CF_PCoin, TRUE);
			DrawRotaGraph(700, 480, 0.45, 0, CF_CCoin, TRUE);
		}
		if (DlayCount > 60) {
			if (PlayUser == Coin_Player) {
				DrawFormatString(850, 200, 0xff0000, "先攻");
			}
			else if (PlayUser == Coin_CPU) {
				DrawFormatString(850, 400, 0xff0000, "先攻");
			}
		}
		if (DlayCount > 90) {
			if (PlayUser == Coin_Player) {
				DrawFormatString(850, 400, 0xffffff, "後攻");
			}
			else if (PlayUser == Coin_CPU) {
				DrawFormatString(850, 200, 0xffffff, "後攻");
			}
		}
	}
	else{
		SetFontSize(24);
		if (CF_Clear == false) {
			if (PlayUser == Coin_Player) {
				DrawFormatString(100, 50, 0x000000, "あなたの番です");
				DrawRotaGraph(Player_X, Player_Y, 0.17, 0, CF_PCoin, TRUE);
			}
			else {
				DrawFormatString(100, 50, 0x000000, "ＣＰＵの番です");
				DrawRotaGraph(Player_X, Player_Y, 0.17, 0, CF_CCoin, TRUE);
			}
		}
		SetFontSize(16);
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (CF_Board[j][0] == Coin_Space) {
					DrawFormatString(297 + j * 114.5, Yajirusi_Y, Yajirusi_Col[j], "▼");
				}
				if (CF_Board[j][i] == Coin_Player) {
					DrawRotaGraph(j * 114 + 306, i * 79 + 209, Coin_Exp[j][i], 0, CF_PCoin, TRUE);
				}
				else if (CF_Board[j][i] == Coin_CPU) {
					DrawRotaGraph(j * 114 + 306, i * 79 + 209, Coin_Exp[j][i], 0, CF_CCoin, TRUE);
				}
			}
		}
		DrawRotaGraph(640, 420, 0.8, 0, CF_Panel, TRUE);
	}
	if (CF_Clear == true) {
		SetFontSize(48);
		if (PlayUser != Coin_Player) {
			DrawFormatString(440, 300, 0x0000ff, "プレイヤーの勝ち！");
		}
		else {
			DrawFormatString(500, 300, 0x0000ff, "ＣＰＵの勝ち！");
		}
		SetFontSize(16);
	}
	if (CF_Draw == true) {
		SetFontSize(48);
		DrawFormatString(440, 300, 0x0000ff, "引 き 分 け");
		SetFontSize(16);
	}
}

void CF_Player:: Coin_Fall() { //コインを配置する処理
	Player_X = j * 114 + 306;
	if (FallCount++ > 90) {
		if(CF_Board[j][Board_Ysize - k] != Coin_Space && Board_Ysize - k >= 0) { //空白じゃないなら、一つ上に置く
			while (CF_Board[j][Board_Ysize - k] != Coin_Space && Board_Ysize - k >= 0) {
				k += 1;
			}
		}
		else if (CF_Board[j][Board_Ysize - k + 1] == Coin_Space && Board_Ysize - k + 1 < Board_Ysize) { //下が空白なら、おけるところまで下に下げる
			while (CF_Board[j][Board_Ysize - k + 1] == Coin_Space && Board_Ysize - k + 1 < Board_Ysize) {
				k -= 1;
			}
		}
		else { //それ以外ならその場に置く
			k = k;
		}
		if (Player_Y < (Board_Ysize - k) * 79 + 209) {
			Player_Y += yadd;
			yadd += 0.04f;
		}
		else {
			yadd = 0;
			if (DlayCount++ > 90) {
				FallCount = 0;
				if (CF_Board[j][Board_Ysize - k] == Coin_Space) {
					if (PlayUser == Coin_Player) {
						CF_Board[j][Board_Ysize - k] = Coin_Player;
					}
					else {
						CF_Board[j][Board_Ysize - k] = Coin_CPU;
					}
				}
				ChangeTurn(&PlayUser);
				Mouse_Push = false;
				Player_Y = 50;
				DlayCount = 0;
			}
		}
	}
}
void CF_Player::Board_Init() { //パネル情報の初期化
	for (i = 0; i < Board_Ysize; i++) {
		for (j = 0; j < Board_Xsize; j++) {
			CF_Board[j][i] = Coin_Space;
		}
	}
}
int CF_Player::ClearCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {//クリア判定処理
	int a, b, ClearFlg;
	int dx[] = { 0,1,1 ,-1};
	int dy[] = { 1,0,1 ,1};
	for (a = 0; a < 4; a++) { //0の時は上、1の時は右、2の時は右上,3の時は左上の盤面を見る
		for (b = 1, ClearFlg = 1; b <= 3; b++) { //指定した座標から4マス見る
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] ||(( 0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize) || (0 >(y - b * dy[a])|| (y - b * dy[a]) >= Board_Ysize)) || board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) {
				ClearFlg = 0;
			}
		}
		if (ClearFlg == 1) { //4マスとも同じものであったらクリアを返す
			DlayCount++;
			if (DlayCount < 30) {
				Coin_Exp[x][y] = 0.25f;
				Coin_Exp[x + b * dx[a]][y - b * dy[a]] = 0.25f;
			}
			else if (DlayCount < 60) {
				Coin_Exp[x][y] = 0.17f; 
				Coin_Exp[x + b * dx[a]][y - b * dy[a]] = 0.17f;
			}
			else {
				DlayCount = 0;
			}
			return 1;
		}
	}
	
	return 0;
}

void CF_Player::ChangeTurn(int *PlayUser) {
	if (*PlayUser == Coin_Player) {
		*PlayUser = Coin_CPU;
	}
	else {
		*PlayUser = Coin_Player;
	}
}
int CF_Player::DrawCheck(int board[Board_Xsize][Board_Ysize]) {
	int a, b, DrawFlg;
	for (a = Board_Ysize; a >= 0; a--) {
		for (b = Board_Xsize, DrawFlg = 1; b >= 0; b--) {
			if (board[b][a] == Coin_Space) {
				DrawFlg = 0;
			}
		}
	}
	if (DrawFlg == 1) {
		return 1;
	}
	else {
		return 0;
	}
}