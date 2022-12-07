#include"CF_Player.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"
#include<time.h>
#include "../../SceneManager.h"
#include "../Title/Scene_GameTitle.h"
#include"Scene_ConnectFour.h"
#include "./../Scene.h"
#include "./../Title/Scene_Select.h"


//CF_Player cf_player;
void CF_Player::CF_Player_Initialize(Scene* scene){
	parent = scene;

	CF_Back = LoadGraph("Resource/image/CF_Back.png"); //背景
	CF_Panel = LoadGraph("Resource/image/CF_Panel.png"); //パネル
	CF_PCoin = LoadGraph("Resource/image/Player_Coin.png"); //プレイヤーコイン
	CF_CCoin = LoadGraph("Resource/image/CPU_Coin.png"); //CPUコイン
	Pause_Button = LoadGraph("Resource/image/PauseButton.png");
	Pause_Back = LoadGraph("Resource/image/PauseBack.png");
	Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
	Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);
	CF_GameBGM = LoadSoundMem("Resource/bgm/CF_BGM.wav"); //ゲーム中のBGM
	CF_StartSE = LoadSoundMem("Resource/se/CF_SoundofCollision.wav"); //先攻後攻の文字を表示する時のSE
	CF_CoinFallSE = LoadSoundMem("Resource/se/CF_CoinFallSound.wav"); //コインがぶつかったときのSE
	CF_ClickSE = LoadSoundMem("Resource/se/CF_ClickSound.wav"); //マウスをクリックしたときのSE
	Pause_Cursol = LoadSoundMem("Resource/se/Pause_Cursor.wav");
	Pause_Click = LoadSoundMem("Resource/se/Pause_Click.wav");
	Player_Y = 50; //コインのY座標の初期値
	k = 1;
	Yajirusi_Y = 100; //矢印の初期値
	Yajirusi_Move = 0.5f; //矢印のアニメーションの初期値
	yadd = 0.0f; //重力加速度の初期値
	FallCount = 0.0f; //コインが落ちるまでの時間の初期値;
	DlayCount = 0; //
	Mouse_Push = false; //左クリックされたかのフラグの初期値
	CF_Clear = false; //クリアフラグの初期値
	CF_Draw = false; //ドローフラグの初期値
	CF_Start = false; //ゲームがスタートしたかのフラグの初期値
	FallSEflg = false; //CoinFallSEが鳴ったかどうかのフラグ
	PauseFlg = false; //ポーズ画面を表示するかどうかのフラグ
	Board_Init();//パネル情報の初期化
	srand((unsigned int)time(NULL)); //乱数を現在時刻の情報で初期化
	PlayUser = rand() % 2 + 1; //プレイヤーの先攻後攻をランダムで取得
	CPU_j = rand() % 7;
	OldKey = KEY_FREE;

	Pause_OneClick = false;
	Pause_OneCursol = false;

	Circle_Exp = 0.5f;
	Circle_Radius = 32.0f;
}
void CF_Player::CF_Player_Finalize() {
	DeleteGraph(CF_Back); //画像削除処理
	DeleteGraph(CF_Panel);
}
void CF_Player::CF_Player_Update() {
	nowKey = key->GetKeyState(REQUEST_MOUSE_LEFT); //現在のマウス左ボタンの入力状態の取得
	if (CF_Start == false) {
		DlayCount++;
		if (DlayCount % 40 == 0 && DlayCount <= 120) {
			PlaySoundMem(CF_StartSE, DX_PLAYTYPE_BACK);
		}
		if (DlayCount > 240) {
			DlayCount = 0;
			CF_Start = true;
		}
	}
	if (Mouse_Push == false) {
		GetMousePoint(&Mouse_X, &Mouse_Y); //マウスの座標取得
	}
	if (CF_Clear == false && CF_Draw == false && CF_Start == true && PauseFlg == false) {
		if (CheckSoundMem(CF_GameBGM) == 0) {
			ChangeVolumeSoundMem(110, CF_GameBGM);
			PlaySoundMem(CF_GameBGM, DX_PLAYTYPE_LOOP);
		}
		
		if (PlayUser == Coin_Player) {
			Player_X = Mouse_X;
		}
		else if (PlayUser == Coin_CPU) {
			CPU_X = CPU_j * 114 + 306;
		}
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
		/*ポーズボタンを押したらポーズ画面を開くフラグをtrueにする*/
		if (20 <= Mouse_X && Mouse_X <= 200 && 25 <= Mouse_Y && Mouse_Y <= 105) {
			if(OldKey != KEY_FREE && nowKey == KEY_PULL) {
				PauseFlg = true;
			}
		}
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (PlayUser == Coin_CPU) {
					CPU_CoinCheck(CF_Board, j, i);
					if (j * 114 + 306 - 48 < CPU_X && CPU_X < j * 114 + 306 + 48) {
						if (CF_Board[j][0] == Coin_Space) {
							Coin_Fall();
						}
						else {
							while (CPU_j == j)
							{
								CPU_RandomFall();
								if (CPU_j != j) {
									Coin_Fall();
									break;
								}
							}
						}
					}
				}
				else if (PlayUser == Coin_Player) {
					if (30 > Mouse_X || Mouse_X > 147 || 35 > Mouse_Y || Mouse_Y > 89) {
						if (j * 114 + 306 - 48 < Player_X && Player_X < j * 114 + 306 + 48) { //矢印の範囲にコインが入ったら
							if (CF_Board[j][0] == Coin_Space) {
								if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
									if (CheckSoundMem(CF_ClickSE) == 0 && Mouse_Push == false) {
										ChangeVolumeSoundMem(200, CF_ClickSE);
										PlaySoundMem(CF_ClickSE, DX_PLAYTYPE_BACK);
									}
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
					}
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
		Circle_Radius += Circle_Exp;
		if (32 >= Circle_Radius) {
			Circle_Radius = 32;
			Circle_Exp = -Circle_Exp;
		}
		else if (Circle_Radius >= 39) {
			Circle_Radius = 39;
			Circle_Exp = -Circle_Exp;
		}
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (ClearCheck(CF_Board, j, i)) {
				}
			}
		}
		DlayCount++;
		if (DlayCount > 90) {
			CF_ClearText = true;
		}
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
			StopSoundMem(CF_GameBGM);
			parent->SetNext(new Scene_Select());
		}
		/*ポーズ画面の内容*/
	}else if (PauseFlg == true) {
		if ((450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) ||(20 <= Mouse_X && Mouse_X <= 200 && 25 <= Mouse_Y && Mouse_Y <= 105)) {
			if (Pause_OneCursol == false) {
				PlaySoundMem(Pause_Cursol, DX_PLAYTYPE_BACK);
				Pause_OneCursol = true;
			}
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //マウスの左キーを離した時
				PlaySoundMem(Pause_Click, DX_PLAYTYPE_BACK);
				PauseFlg = false;
			}
		}
		else {
			Pause_OneCursol = false;
		}
		if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
			if (Pause_OneClick == false) {
				PlaySoundMem(Pause_Cursol, DX_PLAYTYPE_BACK);
				Pause_OneClick = true;
			}
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //マウスの左キーを離した時
				PlaySoundMem(Pause_Click, DX_PLAYTYPE_BACK);
				StopSoundMem(CF_GameBGM);
				parent->SetNext(new Scene_Select());
			}
		}
		else {
			Pause_OneClick = false;
		}
	}
	OldKey = nowKey; //前に入力していたキーを今入力していたキーに上書きする
}
void CF_Player::CF_Player_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, CF_Back, TRUE);
	if (CF_Start == false) {
		SetFontSize(160);
		if (DlayCount > 40){
			DrawFormatString(50, 200, 0xffffff, "あなた");
			DrawFormatString(50, 400, 0xffffff, "ＣＰＵ");
			DrawRotaGraph(700, 280, 0.45, 0, CF_PCoin, TRUE);
			DrawRotaGraph(700, 480, 0.45, 0, CF_CCoin, TRUE);
		}
		if (DlayCount > 80) {
			if (PlayUser == Coin_Player) {
				DrawFormatString(850, 200, 0xff0000, "先攻");
			}
			else if (PlayUser == Coin_CPU) {
				DrawFormatString(850, 400, 0xff0000, "先攻");
			}
		}
		if (DlayCount > 120) {
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
			//ポーズボタン
			DrawRotaGraph(110, 65, 0.9, 0, Pause_Button, TRUE);
			if (PlayUser == Coin_Player) {
				DrawFormatString(1080, 50, 0x000000, "あなたの番です");
				DrawRotaGraph(Player_X, Player_Y, 0.17, 0, CF_PCoin, TRUE);
			}
			else {
				DrawFormatString(1080, 50, 0x000000, "ＣＰＵの番です");
				DrawRotaGraph(CPU_X, Player_Y, 0.17, 0, CF_CCoin, TRUE);
			}
		}
		SetFontSize(16);
		for (i = 0; i < Board_Ysize; i++) {
			for (j = 0; j < Board_Xsize; j++) {
				if (CF_Board[j][0] == Coin_Space && PlayUser == Coin_Player) {
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
		if (CF_Clear == true) {
			for (i = 0; i < Board_Ysize; i++) {
				for (j = 0; j < Board_Xsize; j++) {
					if (CF_CircleBoard[j][i] == 1) {
						DrawCircle(j * 114 + 306, i * 79 + 209, Circle_Radius, 0xffffff, FALSE);
					}
				}
			}
		}
		/*ポーズ画面の画像*/
		if (PauseFlg == true) {
			DrawRotaGraph(650, 380, 1.15, 0, Pause_Back, TRUE);
			if (450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) {
				if (nowKey == KEY_HOLD) {
					DrawRotaGraph(650, 380, 0.9, 0, pause_continue[1], TRUE);
				}
				else {
					DrawRotaGraph(650, 380, 1.0, 0, pause_continue[1], TRUE);
				}
			}
			else {
				DrawRotaGraph(650, 380, 1.0, 0, pause_continue[0], TRUE);
			}
			if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
				if (nowKey == KEY_HOLD) {
					DrawRotaGraph(650, 530, 0.9, 0, pause_select[1], TRUE);
				}
				else {
					DrawRotaGraph(650, 530, 1.0, 0, pause_select[1], TRUE);
				}
			}
			else {
				DrawRotaGraph(650, 530, 1.0, 0, pause_select[0], TRUE);
			}
		}
	}
	if (CF_ClearText == true) {
		SetFontSize(48);
		if (PlayUser != Coin_Player) {
			DrawFormatString(440, 300, 0x0000ff, "プレイヤーの勝ち！");
		}
		else {
			DrawFormatString(500, 300, 0x0000ff, "ＣＰＵの勝ち！");
		}
		SetFontSize(24);
		DrawBox(475, 495, 855, 529, 0xffffff, TRUE);
		DrawFormatString(480, 500, 0x000000, "左クリックでセレクト画面に戻る");
	}
	if (CF_Draw == true) {
		SetFontSize(48);
		DrawFormatString(440, 300, 0x0000ff, "引 き 分 け");
		SetFontSize(16);
	}
	SetFontSize(16);

}

void CF_Player:: Coin_Fall() { //コインを配置する処理
	if (PlayUser == Coin_Player) {
		Player_X = j * 114 + 306;
	}
	else if (PlayUser == Coin_CPU) {
		j = CPU_j;
		CPU_X = j * 114 + 306;
	}
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
			Player_Y = (Board_Ysize - k) * 79 + 209;
			yadd = 0;
			if (CheckSoundMem(CF_CoinFallSE) == 0 && FallSEflg == false) {
				PlaySoundMem(CF_CoinFallSE, DX_PLAYTYPE_BACK);
				FallSEflg = true;
			}
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
				Mouse_Push = false;
				FallSEflg = false;

				Player_Y = 50;
				DlayCount = 0;
				ChangeTurn(&PlayUser);
			}
		}
	}
}
void CF_Player::Board_Init() { //パネル情報の初期化
	for (i = 0; i < Board_Ysize; i++) {
		for (j = 0; j < Board_Xsize; j++) {
			if (i == 6) {
				CF_Board[j][i] = 99;
			}
			else {
				CF_Board[j][i] = Coin_Space;
			}
			Coin_Exp[j][i] = 0.17f;
			CF_CircleBoard[j][i] = 0;
		}
	}
}
int CF_Player::ClearCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {//クリア判定処理
	int a, b, ClearFlg;
	int dx[] = { 0,1,1 ,-1};
	int dy[] = { 1,0,1 ,1};
	for (a = 0; a < 4; a++) { //0の時は上、1の時は右、2の時は右上,3の時は左上の盤面を見る
		for (b = 1, ClearFlg = 1; b <= 3; b++) { //指定した座標から4マス見る
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] ||( 0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize || 0 >(y - b * dy[a])|| (y - b * dy[a]) >= Board_Ysize) || board[x + b * dx[a]][y - b * dy[a]] == Coin_Space || board[x + b * dx[a]][y - b * dy[a]] == 99) {
				ClearFlg = 0;
			}
		}
		if (ClearFlg == 1) { //4マスとも同じものであったらクリアを返す
			for (b = 1; b <= 3; b++) {
				CF_CircleBoard[x][y] = 1;
				CF_CircleBoard[x + b * dx[a]][y - b * dy[a]] = 1;
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
void CF_Player::CPU_CoinCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {
	int a, b, CoinCheck, DoubleCheck;
	int dx[] = { 0,1,1 ,-1 };
	int dy[] = { 1,0,1 ,1 };
	for (a = 0; a < 4; a++) { //0の時は上、1の時は右、2の時は右上,3の時は左上の盤面を見る
		for (b = 1, CoinCheck = 1,DoubleCheck = 1; b <= 2; b++) { //指定した座標から3マス見る
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] || ((0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize) || (0 > (y - b * dy[a]) || (y - b * dy[a]) >= Board_Ysize)) || board[x][y] == Coin_Space || board[x][y] == 99) {
				if (b == 1) {
					DoubleCheck = 0;
					CoinCheck = 0;
				}
				else {
					CoinCheck = 0;
				}
			}
		}
		if (DoubleCheck == 1 && CoinCheck == 0) { //2個続いていて、3個続いているものがない時
			if (board[x][y] == Coin_CPU) {
				//上に2つ続いていて、その上に何もないなら
				if (a == 0 && board[x + b * dx[a]][(y - (b * dy[a]) + 1)] == Coin_Space && 0 <= (y - (b * dy[a]) + 1)) {
					CPU_j = x;
				}
				//横2つ続いていて右端の一つ右に何もない時か、右斜めに2つ続いていてその右上に何もない時
				else if (((a == 1 && board[x + (b * dx[a]) - 1][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a] - 1][y - b * dy[a] + 1] != Coin_Space) || ((a == 2 && board[x + b * dx[a] - 1][y - b * dy[a] + 1] == Coin_Space) && board[x + b * dx[a] - 1][y - b * dy[a] + 2] != Coin_Space)) {
					CPU_j = x + (b * dx[a]) - 1;
				}
				//横に2つ続いていてその左に何もない時か、右斜めに2つ続いていてその左下に何もない時
				else if (((a == 1 && board[x - 1][y] == Coin_Space) && board[x - 1][y + 1] != Coin_Space && 0 <= (x - 1)) || ((a == 2 && board[x - 1][y + 1] == Coin_Space) && board[x - 1][y + 2] != Coin_Space && 0 <= (x - 1) && (y + 2) < Board_Ysize)) {
					CPU_j = x - 1;
				}
				//左斜めに2つ続いていて、その左上に何もない時
				else if (a == 3 && board[x + b * dx[a] + 1][y - b * dy[a] + 1] == Coin_Space && board[x + b * dx[a] + 1][y - b * dy[a] + 2] != Coin_Space) {
					CPU_j = x + (b * dx[a]) + 1;
				}
				//左斜めに2つ続いていて、その右下に何もない時
				else if (a == 3 && board[x + 1][y + 1] == Coin_Space && board[x + 1][y + 2] != Coin_Space && x + 1 < Board_Xsize && y + 2 < Board_Ysize) {
					CPU_j = x + 1;
				}
				else {
					CPU_RandomFall();
				}
			}
			else if (board[x][y] == Coin_Player) {
				//横2つ続いていて右端の一つ右に何もない時か、右斜めに2つ続いていてその右上に何もない時
				if (((a == 1 && board[x + (b * dx[a]) - 1][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a] - 1][y - b * dy[a] + 1] != Coin_Space) || ((a == 2 && board[x + b * dx[a] - 1][y - b * dy[a] + 1] == Coin_Space) && board[x + b * dx[a] - 1][y - b * dy[a] + 2] != Coin_Space)) {
					CPU_j = x + (b * dx[a]) - 1;
				}
				//横に2つ続いていてその左に何もない時か、右斜めに2つ続いていてその左下に何もない時
				else if (((a == 1 && board[x - 1][y] == Coin_Space) && board[x - 1][y + 1] != Coin_Space && 0 <= (x - 1)) || ((a == 2 && board[x - 1][y + 1] == Coin_Space) && board[x - 1][y + 2] != Coin_Space && 0 <= (x - 1) && (y + 2) < Board_Ysize)) {
					CPU_j = x - 1;
				}
				//左斜めに2つ続いていて、その左上に何もない時
				else if (a == 3 && board[x + b * dx[a] + 1][y - b * dy[a] + 1] == Coin_Space && board[x + b * dx[a] + 1][y - b * dy[a] + 2] != Coin_Space) {
					CPU_j = x + (b * dx[a]) + 1;
				}
				//左斜めに2つ続いていて、その右下に何もない時
				else if (a == 3 && board[x + 1][y + 1] == Coin_Space && board[x + 1][y + 2] != Coin_Space && x + 1 < Board_Xsize && y + 2 < Board_Ysize) {
					CPU_j = x + 1;
				}
				else {
					CPU_RandomFall();
				}
			}
			SpaceDoubleCheck(board, x, y);
		}
		if (CoinCheck == 1) { //3マスとも同じものがあったら
			if (board[x][y] == Coin_CPU) {
				if (a == 0 && board[x + b * dx[a]][(y - b * dy[a])] == Coin_Space && 0 <= (y - (b * dy[a]))) { //上に3つ続いていて、その上に何もないなら
					CPU_j = x;
				}
				//横3つ続いていて右端の一つ右に何もない時か、右斜めに3つ続いていてその右上に何もない時
				else if (((a == 1 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) || ((a == 2 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space)) {
					CPU_j = x + (b * dx[a]);
				}
				//横に3つ続いていてその左に何もない時か、右斜めに3つ続いていてその左下に何もない時
				else if (((a == 1 && board[x - 1][y] == Coin_Space) && board[x - 1][y + 1] != Coin_Space && 0 <= (x - 1)) || ((a == 2 && board[x - 1][y + 1] == Coin_Space) && board[x - 1][y + 2] != Coin_Space && 0 <= (x - 1) && (y + 2) < Board_Ysize)) {
					CPU_j = x - 1;
				}
				//左斜めに3つ続いていて、その左上に何もない時
				else if (a == 3 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) {
					CPU_j = x + (b * dx[a]);
				}
				//左斜めに3つ続いていて、その右下に何もない時
				else if (a == 3 && board[x + 1][y + 1] == Coin_Space && board[x + 1][y + 2] != Coin_Space && x + 1 < Board_Xsize && y + 2 < Board_Ysize) {
					CPU_j = x + 1;
				}
				else {
					CPU_RandomFall();
				}
			}
			else if (board[x][y] == Coin_Player) {
				if (a == 0 && board[x + b * dx[a]][(y - b * dy[a])] == Coin_Space && 0 <= (y - (b * dy[a]))) { //上に3つ続いていて、その上に何もないなら
					CPU_j = x;
				}
				//横3つ続いていて右端の一つ右に何もない時か、右斜めに3つ続いていてその右上に何もない時
				else if (((a == 1 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) || ((a == 2 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space)) {
					CPU_j = x + (b * dx[a]);
				}
				//横に3つ続いていてその左に何もない時か、右斜めに3つ続いていてその左下に何もない時
				else if (((a == 1 && board[x - 1][y] == Coin_Space) && board[x - 1][y + 1] != Coin_Space && 0 <= (x - 1)) || ((a == 2 && board[x - 1][y + 1] == Coin_Space) && board[x - 1][y + 2] != Coin_Space && 0 <= (x - 1) && (y + 2) < Board_Ysize)) {
					CPU_j = x - 1;
				}
				//左斜めに3つ続いていて、その左上に何もない時
				else if (a == 3 && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space && board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) {
					CPU_j = x + (b * dx[a]);
				}
				//左斜めに3つ続いていて、その右下に何もない時
				else if (a == 3 && board[x + 1][y + 1] == Coin_Space && board[x + 1][y + 2] != Coin_Space && x + 1 < Board_Xsize && y + 2 < Board_Ysize) {
					CPU_j = x + 1;
				}
				else {
					CPU_RandomFall();
				}
			}
			SpaceCheck(board, x, y);
		}
		
	}
}
void CF_Player::SpaceCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {
	int a, b;
	int dx[] = {1,1 ,-1 };
	int dy[] = {0,1 ,1 };
	for (a = 0; a < 3; a++) { //0の時は右、1の時は右上,2の時は左上の盤面を見る
		for (b = 1; b <= 3; b++) { //指定した座標から4マス見る
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) {
				if (((0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize) || (0 > (y - b * dy[a]) || (y - b * dy[a]) >= Board_Ysize)) || board[x + b * dx[a]][y - b * dy[a]] == 99) {
					
				}else{
					if (board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) {
						if (board[x][y] == Coin_CPU) {
							if (a == 0) { //右を見ているとき
								//1個右が空いているか2個右が空いているとき
								if ((b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]] && board[x][y] == board[x + b * dx[a] + 2][y - b * dy[a]])|| (b == 2 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]])) {
									CPU_j = x + b * dx[a]; 
								}
							}
							else if (a == 1) { //右上を見ているとき
								//1個右上が空いているか2個右上が空いているとき
								if ((b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1] && board[x][y] == board[x + b * dx[a] + 2][y - b * dy[a] - 1])|| (b == 2 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1])) {
									CPU_j = x + b * dx[a];
								}
							}
							else if (a == 2) { //左上を見ているとき
								//1個左上が空いているか2個左上が空いているとき
								if ((b == 1 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1] && board[x][y] == board[x + b * dx[a] - 2][y - b * dy[a] - 1]) || (b == 2 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1])) {
									CPU_j = x + b * dx[a];
								}
							}
						}else if (board[x][y] == Coin_Player) {
							if (a == 0) { //右を見ているとき
								//1個右が空いているか2個右が空いているとき
								if ((b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]] && board[x][y] == board[x + b * dx[a] + 2][y - b * dy[a]]) || (b == 2 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]])) {
									CPU_j = x + b * dx[a];
								}
							}
							else if (a == 1) { //右上を見ているとき
								//1個右上が空いているか2個右上が空いているとき
								if ((b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1] && board[x][y] == board[x + b * dx[a] + 2][y - b * dy[a] - 1]) || (b == 2 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1])) {
									CPU_j = x + b * dx[a];
								}
							}
							else if (a == 2) { //左上を見ているとき
								//1個左上が空いているか2個左上が空いているとき
								if ((b == 1 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1] && board[x][y] == board[x + b * dx[a] - 2][y - b * dy[a] - 1]) || (b == 2 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1])) {
									CPU_j = x + b * dx[a];
								}
							}
						}
					}
				}
			}
		}
	}
}
void CF_Player::SpaceDoubleCheck(int board[Board_Xsize][Board_Ysize], int x, int y) {
	int a, b;
	int dx[] = { 1,1 ,-1 };
	int dy[] = { 0,1 ,1 };
	for (a = 0; a < 3; a++) { //0の時は右、1の時は右上,2の時は左上の盤面を見る
		for (b = 1; b <= 2; b++) { //指定した座標から3マス見る
			if (board[x][y] != board[x + b * dx[a]][y - b * dy[a]] && board[x + b * dx[a]][y - b * dy[a]] == Coin_Space) {
				if (((0 > (x + b * dx[a]) || (x + b * dx[a]) >= Board_Xsize) || (0 > (y - b * dy[a]) || (y - b * dy[a]) >= Board_Ysize)) || board[x + b * dx[a]][y - b * dy[a]] == 99) {

				}
				else {
					if (board[x + b * dx[a]][y - b * dy[a] + 1] != Coin_Space) {
						if (board[x][y] == Coin_CPU) {
							if (a == 0) { //右を見ているとき
								//1個右が空いているか2個右が空いているとき
								if (b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]]) {
									CPU_j = x + b * dx[a];
									break;
								}
							}
							else if (a == 1) { //右上を見ているとき
								//1個右上が空いているか2個右上が空いているとき
								if (b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1]) {
									CPU_j = x + b * dx[a];
									break;
								}
							}
							else if (a == 2) { //左上を見ているとき
								//1個左上が空いているか2個左上が空いているとき
								if (b == 1 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1]) {
									CPU_j = x + b * dx[a];
									break;
								}
							}
						}
						else if (board[x][y] == Coin_Player) {
							if (a == 0) { //右を見ているとき
								//1個右が空いているか2個右が空いているとき
								if (b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a]]) {
									CPU_j = x + b * dx[a];
								}
							}
							else if (a == 1) { //右上を見ているとき
								//1個右上が空いているか2個右上が空いているとき
								if (b == 1 && board[x][y] == board[x + b * dx[a] + 1][y - b * dy[a] - 1]) {
									CPU_j = x + b * dx[a];
								}
							}
							else if (a == 2) { //左上を見ているとき
								//1個左上が空いているか2個左上が空いているとき
								if (b == 1 && board[x][y] == board[x + b * dx[a] - 1][y - b * dy[a] - 1]) {
									CPU_j = x + b * dx[a];
								}
							}
						}
					}
				}
			}
		}
	}
}
void CF_Player::CPU_RandomFall() {
	if (DlayCount == 0) {
		CPU_j = rand() % 7;
		DlayCount = 1;
	}
}
