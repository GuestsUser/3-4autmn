#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Map.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"
#include "SR_Result.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include<iostream>
#include "./../Title/Scene_Select.h"

using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;

int Player1sum;
int Player2sum;
int Player3sum;
int Player4sum;

SR_Saikoro::SR_Saikoro(Scene*scene) {
	parent = scene;
	LoadDivGraph("Resource/image/SR_Saikoro1.png", 6, 6, 1, 75, 75, SR_Saikoro1, true);	/*サイコロ画像読み込み*/
	LoadDivGraph("Resource/image/SR_Saikoro2.png", 6, 6, 1, 75, 75, SR_Saikoro2, true);	/*サイコロ画像読み込み*/
	SR_GOAL = LoadGraph("Resource//image/SR_GOAL.png");
	Pause_Button = LoadGraph("Resource/image/PauseButton.png");
	Pause_Back = LoadGraph("Resource/image/PauseBack.png");
	Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
	Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);

	y = 0, d = 0, i = 0;	/*各種変数初期化*/
	count = 0;
	countdiff = 0;
	countmi = 0;
	num = 1;
	Click = true;
	//SRand(count); // 乱数の初期値をcountに設定する
	srand((unsigned int)time(NULL));

	Player1sum = 0;
	Player2sum = 0;
	Player3sum = 0;
	Player4sum = 0;
	
}

void SR_Saikoro::Update() {
	GetMousePoint(&MouseX, &MouseY);/*マウス座標取得（仮）*/
	if (PauseFlg == false) {
		count++;
		/*ゴールしたら*/
		if (Player1sum >= 62 || Player2sum >= 62 || Player3sum >= 62 || Player4sum >= 62) {
			if (Player1sum >= 62) { Player1sum = 62; }
			else if (Player2sum >= 62) { Player2sum = 62; }
			else if (Player3sum >= 62) { Player3sum = 62; }
			else if (Player4sum >= 62) { Player4sum = 62; }
			Goal();	/*まだ中身はない*/
		}
		/*プラス4マスに止まったら 12 48*/
		//if (Player1sum == 12 || Player2sum == 12 || Player3sum == 12 || Player4sum == 12 || Player1sum == 48 || Player2sum == 48 || Player3sum == 48 || Player4sum == 48) {
		//	Plus();	/*+4する*/
		//}
		/*マイナス5マスに止まったら 34*/
		if (Player1sum == 34 || Player2sum == 34 || Player3sum == 34 || Player4sum == 34) {
			Minus();	/*-4する*/
		}
		/*前のプレイヤーを戻す*/
		//if (Player1sum == 24 || Player2sum == 24 || Player3sum == 24 || Player4sum == 24) {
		//	Frontback();
		//	//if (array[3] == 24) { DrawString(500, 550, "何も起きない", GetColor(0, 0, 0)); }
		//	//DrawString(500, 550, "何も起きない", GetColor(0, 0, 0));
		//}
		array[0] = Player1sum; array[1] = Player2sum; array[2] = Player3sum; array[3] = Player4sum;
		switch (num) {
		case 1:	/*プレイヤーのターン*/
			current = 1;
			if (Click == true) {
				Replay = false;
				if (MouseX >= 1020 && MouseY >= 580 && MouseX <= 1250 && MouseY <= 700 && Whoisplay == true) {
					if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*もし左クリックしたら*/
						Shuffle = true;	/*シャッフルフラグをONに*/
					}
					else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true && Back == true && move == false) {	/*サイコロが出た分だけ戻るマス用（backフラグがある）*/
						Player1sum -= Sum;
						countdiff = count;
						Shuffle = false; Whoisplay = false; Replay = false; Back = false;	/*フラグ関連*/
					}
					else if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true && move == false) {
						/*for (o = 0; 0 > Sum;o++) {
							Player1sum += 1;
						}*/
						//Player1sum += Sum;
						countdiff = count;
						move = true; Shuffle = false; Whoisplay = false; Replay = false;	/*フラグ関連*/
					}
				}
				if (move == true) {
					if (o < Sum) {
						if ((count / 4) % 2 == 0) {
							Player1sum += 1;
							o += 1;
						}
					}
				}
				if (o - Sum == 0) {
					if (Player1sum == 22) { Restart(); }
					if (Player1sum == 12 || Player1sum == 48) { Plus(); }
					if (Player1sum == 8 || Player1sum == 27) { Replay = true; }
					if (Player1sum == 19) { Replay = true; Back = true; }
				}
			}
			if (Replay == true && count - countdiff == 100 && countdiff != 0) { num = 6; countdiff = count; Whoisplay = true;  move = false; o = 0; }
			else if (Replay == false && count - countdiff == 100 && countdiff != 0) { countdiff = count;  num = 2;  Whoisplay = true; move = false; o = 0; }	/*countが100進めば次のターン*/
			break;
		case 2:
			current = 2;
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;	/*テキストを被らせないようにする*/
				Shuffle = true;		/*サイコロをシャッフルする*/
				Sumflg = true;		/*サイコロの合計値を足す*/
			}
			else if (Back == true) {	/*Backフラグがtrueの時*/
				Shuffle = false;	/*シャッフルを止める*/
				if (Sumflg == true && p == 0) {
					p += 1;
					Player2sum -= Sum;		/*サイコロの合計値を足す*/
					Replay = false;Back = false;
				}
			}
			else {	/*cont300を超えたら*/
				Shuffle = false;	/*シャッフルを止める*/
				if (Sumflg == true && p == 0) {
					p += 1;
					Player2sum += Sum;		/*サイコロの合計値を足す*/
					Replay = false;
				}
			}
			if (Player2sum == 8 || Player2sum == 27) { Replay = true; }	/*もしリプレイますに乗ったら*/
			if (Player2sum == 12 || Player2sum == 48) { Plus(); }
			if (Player2sum == 22) { Restart(); }
			if (Player2sum == 19) { Replay = true; Back = true; }
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true; }		/**/
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = count;  num = 3; p = 0;  Sumflg = false; Whoisplay = true; }	/*countが100進めば次のターン*/
			break;
		case 3:
			current = 3;
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false; Shuffle = true; Sumflg = true;
			}
			else if (Back == true) {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player3sum -= Sum;
					Replay = false;Back = false;
				}
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player3sum += Sum;
					Replay = false;
				}
			}
			if (Player3sum == 8 || Player3sum == 27) {Replay = true;	}
			if (Player3sum == 12 || Player3sum == 48) { Plus(); }
			if (Player3sum == 22) { Restart(); }
			if (Player3sum == 19) { Replay = true; Back = true; }
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true; }
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = count;  num = 4; p = 0; Sumflg = false; Whoisplay = true; }	/*countが100進めば次のターン*/
			break;
		case 4:
			current = 4;
			if (count - countdiff >= 100 && count - countdiff <= 300) {
				Whoisplay = false;Shuffle = true;Sumflg = true;
			}
			else if (Back == true) {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player4sum -= Sum;
					Replay = false;Back = false;
				}
			}
			else {
				Shuffle = false;
				if (Sumflg == true && p == 0) {
					p += 1;
					Player4sum += Sum;
					Replay = false;
				}
			}
			if (Player4sum == 8 || Player4sum == 27) {Replay = true;}
			if (Player4sum == 12 || Player4sum == 48) { Plus(); }
			if (Player4sum == 22) { Restart(); }
			if (Player4sum == 19) { Replay = true; Back = true; }
			if (Replay == true && count - countdiff == 400 && countdiff != 0) { num = 6; countdiff = count;  p = 0;  Sumflg = false; Whoisplay = true; }
			else if (Replay == false && count - countdiff == 400 && countdiff != 0) { countdiff = 0;  num = 1; p = 0; Sumflg = false; Whoisplay = true; }	/*countが100進めば次のターン*/
			break;
		case 5:
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {	/*もし左クリックしたら*/
				parent->SetNext(new Scene_Select());
			}
			break;
		case 6:
			if (current == 1) { num = 1; }
			else if (current == 2) { num = 2; }
			else if (current == 3) { num = 3; }
			else if (current == 4) { num = 4; }
			break;
		}

		if ((count / 4) % 2 == 0 && Shuffle == true) {
			y = GetRand(5);
			d = GetRand(5);
		}

		/********************デバッグ用**************************/
		//if ((count / 4) % 2 == 0 && Shuffle == true) {
		//	y = GetRand(0);
		//	//d = GetRand(1);
		//}
		/********************************************************/

		/*if ((count / 4) % 2 == 0) {
			if (Player1sum <= Sum) {
				Player1sum += 1;
			}
			else if (Player2sum <= Sum) {
				Player2sum += 1;
			}
			else if (Player3sum <= Sum) {
				Player3sum += 1;
			}
			else if (Player4sum <= Sum) {
				Player4sum += 1;
			}
		}*/
		Sum = y + d + 2;	/*サイコロの合計値*/
		if ((20 <= MouseX && MouseX <= 200 && 25 <= MouseY && MouseY <= 105)) {
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PULL) {
				PauseFlg = true;
			}
		}

	}else {
		SR_Pose_Update();
	}
}

void SR_Saikoro::Draw() {
	Sort();
	DrawGraph(1050, 600, SR_Saikoro1[y], true);
	DrawGraph(1140, 600, SR_Saikoro2[d], true);

	switch (num) {
	case 1:	/*プレイヤーの時*/
		if (Whoisplay == true && Shuffle == false) { DrawString(484, 620, "Player1のターン", GetColor(0, 0, 0)); }
		else if (Shuffle == false && Whoisplay == false) { DrawFormatString(484, 620, GetColor(0, 0, 0), "Player1は%d進んだ", Sum); }
		else if (Shuffle == true) { DrawString(484, 620, "サイコロコロコロ", GetColor(0, 0, 0)); }
		if (Player1sum) {

		}
		break;
	case 2:
		if (Whoisplay == true) { DrawString(484, 620, "Player2のターン", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(484, 620, GetColor(0, 0, 0), "Player2は%d進んだ", Sum); }
		else if (Shuffle == true) { DrawString(484, 620, "サイコロコロコロ", GetColor(0, 0, 0)); }
		break;
	case 3:
		if (Whoisplay == true) { DrawString(484, 620, "Player3のターン", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(484, 620, GetColor(0, 0, 0), "Player3は%d進んだ", Sum); }
		else if (Shuffle == true) { DrawString(484, 620, "サイコロコロコロ", GetColor(0, 0, 0)); }
		break;
	case 4:
		if (Whoisplay == true) { DrawString(484, 620, "Player4のターン", GetColor(0, 0, 0)); }
		if (Shuffle == false && Whoisplay == false) { DrawFormatString(484, 620, GetColor(0, 0, 0), "Player4は%d進んだ", Sum); }
		else if (Shuffle == true) { DrawString(484, 620, "サイコロコロコロ", GetColor(0, 0, 0)); }
		break;
	case 5:
		if (Goalflg == true) {
			DrawGraph(0, 0, SR_GOAL, true);
		}
		if (Player1sum == 64) { DrawString(500, 360, "Player1の勝利！！", GetColor(0, 0, 0)); }
		else if (Player2sum == 64) { DrawString(500, 360, "Player2の勝利！！", GetColor(0, 0, 0)); }
		else if (Player3sum == 64) { DrawString(500, 360, "Player3の勝利！！", GetColor(0, 0, 0)); }
		else if (Player4sum == 64) { DrawString(500, 360, "Player4の勝利！！", GetColor(0, 0, 0)); }
		break;
	}

	//ポーズボタン
	DrawRotaGraph(110, 65, 0.9, 0, Pause_Button, TRUE);
	if (PauseFlg == true) {
		DrawRotaGraph(650, 380, 1.15, 0, Pause_Back, TRUE);
		if (450 <= MouseX && MouseX <= 850 && 320 <= MouseY && MouseY <= 440) {
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
		if (450 <= MouseX && MouseX <= 850 && 470 <= MouseY && MouseY <= 590) {
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

void SR_Saikoro::SR_Enemy1() {	/*AI1*/
	Shuffle = true;
}
void SR_Saikoro::SR_Enemy2() {	/*AI2*/
	Shuffle = true;
}
void SR_Saikoro::SR_Enemy3() {	/*AI3*/
	Shuffle = true;
}

void SR_Saikoro::Plus() {
	DrawString(500, 600,"Playerは追加で４進む", GetColor(0, 0, 0));
	if (current == 1) { Player1sum += 4; }
	else if (current == 2) { Player2sum += 4; }
	else if (current == 3) { Player3sum += 4; }
	else if (current == 4) { Player4sum += 4; }
}

void SR_Saikoro::Minus() {
	if (current == 1) { Player1sum -= 5; }
	else if (current == 2) { Player2sum -= 5;}
	else if (current == 3) { Player3sum -= 5;}
	else if (current == 4) { Player4sum -= 5;}
}

void SR_Saikoro::ReDice() {
}

void SR_Saikoro::Restart() {
	if (current == 1 && Player1sum == 22) { Player1sum -= 22; }
	else if (current == 2 && Player2sum == 22) { Player2sum -= 22; }
	else if (current == 3 && Player3sum == 22) { Player3sum -= 22; }
	else if (current == 4 && Player4sum == 22) { Player4sum -= 22; }
}

void SR_Saikoro::Goal() {
	num = 5;
	Goalflg = true;
	//SetNext((new SR_Result));
}

void SR_Saikoro::Frontback() {
	//if (array[3] == 24) { /*何も起きない*/; }

	//if (array[2] == 24) {
	//	if (current == 1) {
	//		if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {	/*サイコロが出た分だけ戻るマス用（backフラグがある）*/
	//			array[3] -= Sum;
	//			Shuffle = false;
	//			countdiff = count;
	//			Whoisplay = false;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//	else {
	//		Shuffle = false;
	//		if (Sumflg == true && p == 0) {
	//			p += 1;
	//			array[3] -= Sum;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//}

	//if (array[1] == 24) { 
	//	if (current == 1) {
	//		if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {	/*サイコロが出た分だけ戻るマス用（backフラグがある）*/
	//			array[3] -= Sum;
	//			Shuffle = false;
	//			countdiff = count;
	//			Whoisplay = false;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//	else {
	//		Shuffle = false;
	//		if (Sumflg == true && p == 0) {
	//			p += 1;
	//			array[3] -= Sum;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//}

	//if (array[0] == 24) { 
	//	if (current == 1) {
	//		if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH && Shuffle == true) {	/*サイコロが出た分だけ戻るマス用（backフラグがある）*/
	//			array[3] -= Sum;
	//			Shuffle = false;
	//			countdiff = count;
	//			Whoisplay = false;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//	else {
	//		Shuffle = false;
	//		if (Sumflg == true && p == 0) {
	//			p += 1;
	//			array[3] -= Sum;
	//			Replay = false;
	//			Back = false;
	//		}
	//	}
	//}

	//if (array[3] == 24) { DrawString(500, 550, "何も起きない", GetColor(0, 0, 0)); }

	//if (array[2] == 24) {
	//	array[3] -= 5;
	//}

	//if (array[1] == 24) {
	//	array[2] -= 5;
	//}

	//if (array[0] == 24) {
	//	array[1] -= 5;
	//}

	/*for (v = 0; v < 4; v++) {}*/
}

void SR_Saikoro::Sort() {
	sort(array, array + 4);
}
void SR_Saikoro::SR_Pose_Update() {
	GetMousePoint(&MouseX, &MouseY);
	nowKey = key->GetKeyState(REQUEST_MOUSE_LEFT); //現在のマウス左ボタンの入力状態の取得
	// ポーズボタンを押したらポーズ画面を開くフラグをtrueにする /
		if ((20 <= MouseX && MouseX <= 200 && 25 <= MouseY && MouseY <= 105) || ((450 <= MouseX && MouseX <= 850 && 320 <= MouseY && MouseY <= 440) && PauseFlg)) {
			//PauseFlg = true;
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {
				//PauseFlg = true;
				PauseFlg = !PauseFlg;
				//pose = true;
			}
		}
	if (PauseFlg) {

		if (450 <= MouseX && MouseX <= 850 && 470 <= MouseY && MouseY <= 590) {
			if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //前の入力で左キーを話していなくて、今マウスの左キーを離した時
				//StopSoundMem(CF_GameBGM);
				parent->SetNext(new Scene_Select());
			}
		}
	}
	OldKey = nowKey; //前に入力していたキーを今入力していたキーに上書きする
}