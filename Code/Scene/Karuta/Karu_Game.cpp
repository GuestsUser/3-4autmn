#include"DxLib.h"
#include"./../Code/GetKey.h"
#include"Karu_Game.h"
#include "./../Title/Scene_Select.h"

#include <random>

/*************************
** 変数 **
*************************/

int ix = 0, iy = 0;
int reset = 0;
bool AllSet = false;

bool Yomiset = false;

bool Otetuki = false;
int Otetuki_AnimTime = 0;

int Click_check = 0;
int Click_AnimTime = 0;

bool Touch_once = false;

bool Cpu_Set = false;
bool now_voice = false;
bool old_voice = false;
int voice = 0;

int Rank_All = 0;

bool now_pause = false;
bool now_push = false;
bool on_ContinueButton = false;
bool on_MenuButton = false;
bool now_GoSe = false;

float Go_Angle1 = 0.0f;
float Go_Angle2 = 0.0f;
float Go_Angle3 = 0.0f;

bool once_bgm = false;
bool once_SelectContinueSE = false;
bool once_SelectMenuSE = false;

/*************************
** 構造体 **
*************************/

struct EFUDA Efuda[KARU_MAX_Y][KARU_MAX_X];
struct YOMIFUDA Yomifuda[KARU_MAX_Y][KARU_MAX_X];
struct FUDA Fuda[100];
struct KARU_PLAYER Karu_player;
struct KARU_CPU cpu_1;
struct KARU_CPU cpu_2;
struct KARU_CPU cpu_3;

/*************************
** 初期化 **
*************************/
void Karu_Game::Karu_Game_Initialize(Scene* scene) {

	parent = scene;

	Karu_Bg = LoadGraph("Resource/image/Karu_Image/Karu_Tatami.png");		//背景画像をKaru_Bgに格納
	Karu_SideBg = LoadGraph("Resource/image/Karu_Image/Karu_Side_Bg.png");	//サイド背景画像をKaru_SideBgに格納
	Karu_getText = LoadGraph("Resource/image/Karu_Image/GetCountText.png");	//テキスト画像をKaru_getTextに格納
	Karu_PlayerText = LoadGraph("Resource/image/Karu_Image/Player.png");	//テキスト画像をKaru_PlayerTextに格納
	Karu_CPU1_Text = LoadGraph("Resource/image/Karu_Image/CPU_1.png");	//テキスト画像をKaru_CPU1_Textに格納
	Karu_CPU2_Text = LoadGraph("Resource/image/Karu_Image/CPU_2.png");	//テキスト画像をKaru_CPU2_Textに格納
	Karu_CPU3_Text = LoadGraph("Resource/image/Karu_Image/CPU_3.png");	//テキスト画像をKaru_CPU3_Textに格納
	PauseIcon = LoadGraph("Resource/image/Karu_Image/Karu_PauseIcon.png");//ポーズボタン画像をPauseIconに格納
	PauseBackImg = LoadGraph("Resource/image/Karu_Image/Karu_PauseBack.png");//ポーズボタン画像をPauseIconに格納
	ResultBackImg = LoadGraph("Resource/image/Karu_Image/Karu_ResultBack.png");//リザルト背景画像をResultBackImgに格納
	ResultRank1 = LoadGraph("Resource/image/Karu_Image/Karu_Rank_1.png");//順位画像をResultRank1に格納
	ResultRank2 = LoadGraph("Resource/image/Karu_Image/Karu_Rank_2.png");//順位画像をResultRank2に格納
	ResultRank3 = LoadGraph("Resource/image/Karu_Image/Karu_Rank_3.png");//順位画像をResultRank3に格納
	GameOverBackImg = LoadGraph("Resource/image/Karu_Image/Karu_GameOverBack.png");//ゲームオーバー画像をGameOverBackImgに格納
	GameOverImg = LoadGraph("Resource/image/Karu_Image/Karu_Guruguru.png");//ゲームオーバー画像をGameOverImgに格納

	LoadDivGraph("Resource/image/Karu_Image/number.png", 10, 10, 1, 30, 50, Karu_numImg, TRUE);	//数字画像をKaru_numImgに格納
	LoadDivGraph("Resource/image/Karu_Image/HandIcon.png", 2, 2, 1, 150, 150, Player_HandIcon, TRUE);	//マウスカーソル画像をHandIconに格納
	LoadDivGraph("Resource/image/Karu_Image/CpuHand_1.png", 2, 2, 1, 150, 150, Enemy1_HandIcon, TRUE);	//マウスカーソル画像をEnemy1_HandIconに格納
	LoadDivGraph("Resource/image/Karu_Image/CpuHand_2.png", 2, 2, 1, 150, 150, Enemy2_HandIcon, TRUE);	//マウスカーソル画像をEnemy2_HandIconに格納
	LoadDivGraph("Resource/image/Karu_Image/CpuHand_3.png", 2, 2, 1, 150, 150, Enemy3_HandIcon, TRUE);	//マウスカーソル画像をEnemy3_HandIconに格納
	LoadDivGraph("Resource/image/Karu_Image/Karu_Otetuki.png", 2, 2, 1, 100, 100, Karu_Otetuki_img, TRUE);	//お手付きの画像をKaru_Otetuki_imgに格納
	LoadDivGraph("Resource/image/Karu_Image/Karu_Fuda.png", 100, 10, 10, Karu_imgX, Karu_imgY, *Karu_fuda, TRUE);//絵札画像を分割してKaru_fudaに格納
	LoadDivGraph("Resource/image/Karu_Image/Karu_ContinueButton.png", 2, 2, 1, 400, 120, PauseContinueButton, TRUE);//ボタン画像を分割してPauseContinueButtonに格納
	LoadDivGraph("Resource/image/Karu_Image/Karu_MenuButton.png", 2, 2, 1, 400, 120, PauseMenuButton, TRUE);//ボタン画像を分割してPauseMenuButtonに格納
	LoadDivGraph("Resource/image/Karu_Image/Karu_EndContinue.png", 2, 2, 1, 400, 120, EndContinueButton, TRUE);//ボタン画像を分割してEndContinueButtonに格納
	LoadDivGraph("Resource/image/Karu_Image/Karu_EndMenu.png", 2, 2, 1, 400, 120, EndMenuButton, TRUE);//ボタン画像を分割してEndMenuButtonに格納
	LoadDivGraph("Resource/image/Karu_Image/Karu_ContinueButton.png", 2, 2, 1, 400, 120, GO_ContinueButton, TRUE);//ボタン画像を分割してGO_ContinueButtonに格納
	LoadDivGraph("Resource/image/Karu_Image/Karu_MenuButton.png", 2, 2, 1, 400, 120, GO_MenuButton, TRUE);//ボタン画像を分割してGO_MenuButtonに格納

	//EfudaとYomifudaの構造体を初期化
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
				Efuda[i][j] = { 0,0,0,0,0,true };
				Yomifuda[i][j] = { 0,0,0,true };
		}
	}

	//札の初期化(これによって同じ札が再び選出されなくなる)
	for (int z = 0; z < 100; z++) {
		Fuda[z].get = false;
	}

	Yomifuda[0][0].kara = true;
	Yomiset = false;
	reset = 0;
	end = false;
	Gameover = false;

	Click_check = 0;
	Click_AnimTime = 0;
	Touch_once = false;
	Cpu_Set = false;
	now_voice = false;
	old_voice = false;
	voice = 0;
	Rank_All = 0;
	once_bgm = false;
	now_pause = false;
	now_push = false;
	on_ContinueButton = false;
	on_MenuButton = false;


	//Karu_playerとcpu_1の初期化
	Karu_player = {0,0,0};
	cpu_1 = { 0.0f,0.0f, 0,0,0,0,0,false };
	cpu_2 = { 0.0f,0.0f, 0,0,0,0,0,false };
	cpu_3 = { 0.0f,0.0f, 0,0,0,0,0,false };

	//読み上げ音声を格納
	Voice_Storage();

	//SE格納
	Touch_Sound = LoadSoundMem("Resource/se/Karu_SE/Touch.wav");
	ChangeVolumeSoundMem(255 * 80 / 100, Touch_Sound);
	Suka_Sound = LoadSoundMem("Resource/se/Karu_SE/suka.wav");
	ChangeVolumeSoundMem(255 * 80 / 100, Suka_Sound);
	Otetuki_Sound = LoadSoundMem("Resource/se/Karu_SE/Buzzer.wav");
	ChangeVolumeSoundMem(255 * 80 / 100, Otetuki_Sound);
	Se_Cursor = LoadSoundMem("Resource/se/Karu_SE/Karu_Cursor.wav");
	Se_Select = LoadSoundMem("Resource/se/Karu_SE/Karu_Select.wav");
	Se_GameOver = LoadSoundMem("Resource/se/Karu_SE/Karu_GameOver.wav");
	ChangeVolumeSoundMem(255 * 80 / 100, Se_GameOver);
	Se_Result = LoadSoundMem("Resource/se/Karu_SE/Karu_Result.wav");
	ChangeVolumeSoundMem(255 * 80 / 100, Se_Result);

	//BGM格納
	Karu_Bgm = LoadSoundMem("Resource/bgm/Karu_BGM/Karuta_Bgm.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, Karu_Bgm);

	//順位初期化
	for (int i = 0;i < 4;i++) {
		End_Rank[i] = 0;
	}
}

/*************************
** 終了処理 **
*************************/
void Karu_Game::Karu_Game_Finalize() {
	DeleteGraph(Karu_Bg);
	DeleteGraph(Karu_SideBg);
	DeleteGraph(Karu_getText);
	DeleteGraph(Karu_PlayerText);
	for (int a = 0;a < 10;a++) {
		DeleteGraph(Karu_numImg[a]);
	}
	for (int b = 0; b < 2; b++) {
		DeleteGraph(Player_HandIcon[b]);
		DeleteGraph(Karu_Otetuki_img[b]);
		DeleteGraph(Enemy1_HandIcon[b]);
		DeleteGraph(Enemy2_HandIcon[b]);
		DeleteGraph(Enemy3_HandIcon[b]);
	}
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			DeleteGraph(Karu_fuda[i][j]);
		}
	}
}

/*************************
** 更新処理 **
*************************/
void Karu_Game::Karu_Game_Update() {
	GetMousePoint(&Mouse_X, &Mouse_Y); //マウスの座標取得

	if (!once_bgm) {
		PlaySoundMem(Karu_Bgm, DX_PLAYTYPE_LOOP);
		once_bgm = true;
	}

	//デバッグ用
	//if (CheckHitKey(KEY_INPUT_0)) {
	//	if (!end) {
	//		PlaySoundMem(Se_Result, DX_PLAYTYPE_BACK);
	//		end = true;		//終了
	//	}
	//}

	//ゲームオーバーになるまで
	if (!end && !Gameover) {
		if (!now_pause) {
			if (!now_voice) {
				if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
					Click_check = 1;	//クリックしたことにする
					Mouse_HitBox();		//かるたに触れているか確認
				}

				Cpu_config();
			}

			if (reset < 44) {		//絵札が場に全部出されてなければ
				Efuda_Storage();	//絵札を場に出す
			}

			//読み札がセットされてない場合かつ自分の持ち札と相手の持ち札の合計が44以下だった場合
			if (!Yomiset && AllSet && (Karu_player.myFuda + cpu_1.myFuda + cpu_2.myFuda + cpu_3.myFuda) < 44) {
				Yomifuda_Storage();
			}
			else if ((Karu_player.myFuda + cpu_1.myFuda + cpu_2.myFuda + cpu_3.myFuda) > 43) {
				if (!end) {
					PlaySoundMem(Se_Result, DX_PLAYTYPE_BACK);
					end = true;		//終了
				}
			}

			if (CheckSoundMem(voice) == 1) {
				now_voice = true;
			}
			else {
				now_voice = false;
			}
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
				Pause();
			}
		}
		else {
			Pause_Controller();
		}
	}
	else if (Gameover) {
		if (CheckSoundMem(Se_GameOver) == 0) {
			now_GoSe = true;
		}
		Karu_GameOver();
		if (Go_Angle1 <= PI * 2) {
			Go_Angle1 += PI * 0.05f;
		}
		else {
			Go_Angle1 = 0.0f;
		}
		if (Go_Angle2 <= PI * 2) {
			Go_Angle2 += PI * 0.1f;
		}
		else {
			Go_Angle2 = 0.0f;
		}
		if (Go_Angle3 <= PI * 2) {
			Go_Angle3 += PI * 0.03f;
		}
		else {
			Go_Angle3 = 0.0f;
		}
	}
	else {
		Rank();

		Karu_End();
	}
	if (!Touch_once) {
		Click_Anim();
	}
	Otetuki_Anim();

	////デバッグ用
	//if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) { // 右クリックしたら
	//	//絵札総入れ替え
	//	for (int i = 0; i < KARU_MAX_Y; i++) {
	//		for (int j = 0; j < KARU_MAX_X; j++) {
	//			Efuda[i][j] = { 0,0,0,0,0,true };
	//		}
	//		for (int z = 0; z < 100; z++) {
	//			Fuda[z].get = false;
	//		}
	//	}
	//	Yomifuda[0][0].kara = true;
	//	Yomiset = false;
	//	reset = 0;
	//	end = false;
	//	Karu_player.Otetuki = 0;
	//	Karu_player.myFuda = 0;
	//	cpu_1 = { 0,0,0,0 };
	//	cpu_2 = { 0,0,0,0 };
	//	cpu_3 = { 0,0,0,0 };
	//}
}

/*************************
** 描画処理 **
*************************/
void Karu_Game::Karu_Game_Draw() {
	DrawRotaGraph(640, 360, 1.0, 0, Karu_Bg, TRUE);
	DrawRotaGraph(1100, 360, 1.0, 0, Karu_SideBg, TRUE);
	if (!now_voice) {
		DrawRotaGraph(1080, 520, 1.7, 0, Yomifuda[0][0].img, TRUE);
	}
	for (int o = 0; o < 3;o++) {
		if (Karu_player.Otetuki > o ) {
			DrawRotaGraph(1000 + (100 * o), 290, 1.0, 0, Karu_Otetuki_img[1], TRUE);
		}
		else {
			DrawRotaGraph(1000 + (100 * o), 290, 1.0, 0, Karu_Otetuki_img[0], TRUE);
		}
	}

	DrawRotaGraph(1080, 60, 1.0, 0, Karu_getText, TRUE);

	//プレイヤー
	DrawRotaGraph(950, 150, 1.0, 0, Karu_PlayerText, TRUE);
	DrawRotaGraph(1020, 150, 1.0, 0, Karu_numImg[Karu_player.myFuda / 10], TRUE);
	DrawRotaGraph(1050, 150, 1.0, 0, Karu_numImg[Karu_player.myFuda % 10], TRUE);

	//CPU1
	DrawRotaGraph(950, 200, 1.0, 0, Karu_CPU1_Text, TRUE);
	DrawRotaGraph(1020, 200, 1.0, 0, Karu_numImg[cpu_1.myFuda / 10], TRUE);
	DrawRotaGraph(1050, 200, 1.0, 0, Karu_numImg[cpu_1.myFuda % 10], TRUE);

	//CPU2
	DrawRotaGraph(1150, 150, 1.0, 0, Karu_CPU2_Text, TRUE);
	DrawRotaGraph(1220, 150, 1.0, 0, Karu_numImg[cpu_2.myFuda / 10], TRUE);
	DrawRotaGraph(1250, 150, 1.0, 0, Karu_numImg[cpu_2.myFuda % 10], TRUE);

	//CPU3
	DrawRotaGraph(1150, 200, 1.0, 0, Karu_CPU3_Text, TRUE);
	DrawRotaGraph(1220, 200, 1.0, 0, Karu_numImg[cpu_3.myFuda / 10], TRUE);
	DrawRotaGraph(1250, 200, 1.0, 0, Karu_numImg[cpu_3.myFuda % 10], TRUE);

	DrawRotaGraph(40, 17, 1.0, 0, PauseIcon, TRUE);

	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			if (!Efuda[i][j].kara) {
				DrawRotaGraph((Efuda[i][j].x), (Efuda[i][j].y), 1.0, 0, Efuda[i][j].img, TRUE);
			}
		}
	}
	AllSet = true;

	if (cpu_1.onClick) {
		DrawRotaGraph(cpu_1.x, cpu_1.y, 1.0, 0, Enemy1_HandIcon[1], TRUE);
	}
	if (cpu_2.onClick) {
		DrawRotaGraph(cpu_2.x, cpu_2.y, 1.0, 0, Enemy2_HandIcon[1], TRUE);
	}
	if (cpu_3.onClick) {
		DrawRotaGraph(cpu_3.x, cpu_3.y, 1.0, 0, Enemy3_HandIcon[1], TRUE);
	}
	if (!now_pause && !end && !Gameover) {
		DrawRotaGraph(Mouse_X, Mouse_Y, 1.0, 0, Player_HandIcon[Click_check], TRUE);
	}

	if (Otetuki) {
		DrawRotaGraph(Mouse_X, Mouse_Y, 1.0, 0, Karu_Otetuki_img[1], TRUE);
	}

	if (end) {
		DrawFormatString(800, 400, 0xFF0000, "END");
		DrawRotaGraph(640, 360, 1.0, 0, ResultBackImg, TRUE);
		DrawRotaGraph(640, 280, 1.0, 0, ResultRank1, TRUE);
		DrawRotaGraph(640, 280, 2.0, 0, End_Rank[0], TRUE);
		DrawRotaGraph(640, 360, 1.0, 0, ResultRank2, TRUE);
		DrawRotaGraph(640, 360, 2.0, 0, End_Rank[1], TRUE);
		DrawRotaGraph(640, 440, 1.0, 0, ResultRank3, TRUE);
		DrawRotaGraph(640, 440, 2.0, 0, End_Rank[2], TRUE);

		DrawRotaGraph(340, 640, 1.0, 0, EndContinueButton[on_ContinueButton], TRUE);
		DrawRotaGraph(940, 640, 1.0, 0, EndMenuButton[on_MenuButton], TRUE);
	}

	if (Gameover) {
		DrawRotaGraph(640, 360, 1.0, 0, GameOverBackImg, TRUE);
		DrawRotaGraph(320, 150, 1.0, Go_Angle1, GameOverImg, TRUE);
		DrawRotaGraph(1020, 220, 0.7, Go_Angle2, GameOverImg, TRUE);
		DrawRotaGraph(970, 200, 1.0, Go_Angle3, GameOverImg, TRUE);
		if (now_GoSe) {
			DrawRotaGraph(640, 310, 1.0, 0, GO_ContinueButton[on_ContinueButton], TRUE);
			DrawRotaGraph(640, 460, 1.0, 0, GO_MenuButton[on_MenuButton], TRUE);
		}
	}

	if (now_pause) {
		DrawRotaGraph(640, 360, 1.0, 0, PauseBackImg, TRUE);
		DrawRotaGraph(640, 360, 1.0, 0, PauseContinueButton[on_ContinueButton], TRUE);
		DrawRotaGraph(640, 510, 1.0, 0, PauseMenuButton[on_MenuButton], TRUE);
		DrawRotaGraph(Mouse_X, Mouse_Y, 1.0, 0, Player_HandIcon[Click_check], TRUE);
	}
}

/*****************
** 絵札の格納 **
* 引数  :なし
* 戻り値:なし
******************/
void Karu_Game::Efuda_Storage() {
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			if (Efuda[i][j].kara) {
				AllSet = false;
				int X = 0, Y = 0;
				do {
					Y = GetRand(9);
					X = GetRand(4) * 2;
				} while ((Y == 7 && X == 2) || (Y == 7 && X == 6) ||
					(Y == 9 && X == 2) || (Y == 9 && X == 4) ||
					(Y == 9 && X == 6) || (Y == 9 && X == 8) || Fuda[(Y * 10) + X].get == true);

				Efuda[i][j] = { (j * Karu_imgX) + (Karu_imgX / 2) + (Karu_Space * (j + 1)) + Karu_StartPosX,
								(i * Karu_imgY) + (Karu_imgY / 2) + (Karu_Space * (i + 1)) + Karu_StartPosY,
								Karu_fuda[Y][X],X,Y,false };
				Fuda[(Y * 10) + X].get = true;
				reset++;
			}
		}
	}
}

/*****************
** 読み札の格納 **
* 引数  :なし
* 戻り値:なし
******************/
void Karu_Game::Yomifuda_Storage() {
	int x, y;
	do {
		x = GetRand(KARU_MAX_X - 1);
		y = GetRand(KARU_MAX_Y - 1);
	} while (Efuda[y][x].kara);

	if (Yomifuda[0][0].kara) {
		Yomifuda[0][0].img = Karu_fuda[Efuda[y][x].numY][(Efuda[y][x].numX) + 1];
		Yomifuda[0][0].kara = false;
		Yomiset = true;
		voice = Fuda_voice[Efuda[y][x].numY][Efuda[y][x].numX];
		PlaySoundMem(voice, DX_PLAYTYPE_BACK);
	}
}

/*****************
** 読み上げ音声の格納 **
* 引数  :なし
* 戻り値:なし
******************/
void Karu_Game::Voice_Storage() {
	Fuda_voice[0][0] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Atama.wav");
	Fuda_voice[0][2] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Inu.wav");
	Fuda_voice[0][4] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Uma.wav");
	Fuda_voice[0][6] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Ebi.wav");
	Fuda_voice[0][8] = LoadSoundMem("Resource/se/Karu_SE/AGroup/Oni.wav");
	Fuda_voice[1][0] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Kapa.wav");
	Fuda_voice[1][2] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Kyusi.wav");
	Fuda_voice[1][4] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Kusai.wav");
	Fuda_voice[1][6] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Kega.wav");
	Fuda_voice[1][8] = LoadSoundMem("Resource/se/Karu_SE/KaGroup/Koi.wav");
	Fuda_voice[2][0] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Saru.wav");
	Fuda_voice[2][2] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Siranu.wav");
	Fuda_voice[2][4] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Sumeba.wav");
	Fuda_voice[2][6] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Senri.wav");
	Fuda_voice[2][8] = LoadSoundMem("Resource/se/Karu_SE/SaGroup/Sonae.wav");
	Fuda_voice[3][0] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Tanuki.wav");
	Fuda_voice[3][2] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Tiritumo.wav");
	Fuda_voice[3][4] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Tuki.wav");
	Fuda_voice[3][6] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Teki.wav");
	Fuda_voice[3][8] = LoadSoundMem("Resource/se/Karu_SE/TaGroup/Touhu.wav");
	Fuda_voice[4][0] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Naki.wav");
	Fuda_voice[4][2] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Nikai.wav");
	Fuda_voice[4][4] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Nureginu.wav");
	Fuda_voice[4][6] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Neko.wav");
	Fuda_voice[4][8] = LoadSoundMem("Resource/se/Karu_SE/NaGroup/Noren.wav");
	Fuda_voice[5][0] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/Hana.wav");
	Fuda_voice[5][2] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/HIni.wav");
	Fuda_voice[5][4] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/Hundari.wav");
	Fuda_voice[5][6] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/Hebi.wav");
	Fuda_voice[5][8] = LoadSoundMem("Resource/se/Karu_SE/HaGroup/Hotoke.wav");
	Fuda_voice[6][0] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Manaita.wav");
	Fuda_voice[6][2] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Mizu.wav");
	Fuda_voice[6][4] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Mukasi.wav");
	Fuda_voice[6][6] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Mekara.wav");
	Fuda_voice[6][8] = LoadSoundMem("Resource/se/Karu_SE/MaGroup/Moroha.wav");
	Fuda_voice[7][0] = LoadSoundMem("Resource/se/Karu_SE/YaGroup/Yake.wav");
	Fuda_voice[7][4] = LoadSoundMem("Resource/se/Karu_SE/YaGroup/Yudan.wav");
	Fuda_voice[7][8] = LoadSoundMem("Resource/se/Karu_SE/YaGroup/Yorime.wav");
	Fuda_voice[8][0] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Rati.wav");
	Fuda_voice[8][2] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Ryouyaku.wav");
	Fuda_voice[8][4] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Ruitomo.wav");
	Fuda_voice[8][6] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Reiniyotte.wav");
	Fuda_voice[8][8] = LoadSoundMem("Resource/se/Karu_SE/RaGroup/Ronyori.wav");
	Fuda_voice[9][0] = LoadSoundMem("Resource/se/Karu_SE/WaGroup/Wara.wav");
}

/*****************
** 絵札の当たり判定 **
* 引数  :なし
* 戻り値:なし
******************/
void Karu_Game::Mouse_HitBox() {
	for (int i = 0; i < KARU_MAX_Y; i++) {
		for (int j = 0; j < KARU_MAX_X; j++) {
			if (Mouse_X > (Efuda[i][j].x - (Karu_imgX / 2)) && Mouse_X < (Efuda[i][j].x + (Karu_imgX / 2)) &&
				Mouse_Y >(Efuda[i][j].y - (Karu_imgY / 2)) && Mouse_Y < (Efuda[i][j].y + (Karu_imgY / 2))) {
				ix = j;
				iy = i;
				if (Yomifuda[0][0].img == Karu_fuda[Efuda[i][j].numY][(Efuda[i][j].numX) + 1]) {
					PlaySoundMem(Touch_Sound, DX_PLAYTYPE_BACK);
					if (!Touch_once) {
						Rank_All++;
						Karu_player.Rank = Rank_All;
						Touch_once = true;
					}
					if (Rank_All >= TOTAL_PLAYER) {
						Cpu_reset();
						
						Efuda[i][j].kara = true;
						Player_Reset();
					}
				}
				else if(!Efuda[i][j].kara && !Touch_once){
					Otetuki = true;
					PlaySoundMem(Otetuki_Sound, DX_PLAYTYPE_BACK);
					if (Karu_player.Otetuki < KARU_OTETUKI_MAX) {
						Karu_player.Otetuki++;
					}
					else {
						Karu_player.Otetuki++;
						Karu_GameOver();
					}
				}
			}
		}
	}
}

/***********************************
** クリック時のアニメーション **
* 引数  :なし
* 戻り値:なし
************************************/
void Karu_Game::Click_Anim() {
	if (Click_check == 1) {
		if (Click_AnimTime < 60) {
			Click_AnimTime++;
		}
		else {
			Click_check = 0;
		}
	}
	else {
		Click_AnimTime = 0;
	}
}

/***********************************
** お手付き時のアニメーション **
* 引数  :なし
* 戻り値:なし
************************************/
void Karu_Game::Otetuki_Anim() {
	if (Otetuki) {
		if (Otetuki_AnimTime < 60) {
			Otetuki_AnimTime++;
		}
		else {
			Otetuki = false;
			Otetuki_AnimTime = 0;
		}
	}
}

/**************
** CPUの設定 **
* 引数  :なし
* 戻り値:なし
***************/
void Karu_Game::Cpu_config() {
	cpu_1.Time++;
	cpu_2.Time++;
	cpu_3.Time++;
	if (!Cpu_Set) {
		cpu_1.setTime = GetRand(60) + 30;
		cpu_2.setTime = GetRand(60) + 20;
		cpu_3.setTime = GetRand(60) + 60;
		Cpu_Set = true;
	}
	if (cpu_1.Time > cpu_1.setTime) {
		for (int i = 0; i < KARU_MAX_Y; i++) {
			for (int j = 0; j < KARU_MAX_X; j++) {
				if (Yomifuda[0][0].img == Karu_fuda[Efuda[i][j].numY][(Efuda[i][j].numX) + 1]) {
					if (!cpu_1.onClick) {
						cpu_1.x = Efuda[i][j].x;
						cpu_1.y = Efuda[i][j].y;
						Rank_All++;
						PlaySoundMem(Touch_Sound, DX_PLAYTYPE_BACK);
						cpu_1.Rank = Rank_All;
						cpu_1.onClick = true;
					}
					if (Rank_All >= TOTAL_PLAYER) {
						Cpu_reset();
						Efuda[i][j].kara = true;
						Player_Reset();
					}
				}
			}
		}
	}

	if (cpu_2.Time > cpu_2.setTime) {
		for (int i = 0; i < KARU_MAX_Y; i++) {
			for (int j = 0; j < KARU_MAX_X; j++) {
				if (Yomifuda[0][0].img == Karu_fuda[Efuda[i][j].numY][(Efuda[i][j].numX) + 1]) {
					if (!cpu_2.onClick) {
						cpu_2.x = Efuda[i][j].x;
						cpu_2.y = Efuda[i][j].y;
						Rank_All++;
						PlaySoundMem(Touch_Sound, DX_PLAYTYPE_BACK);
						cpu_2.Rank = Rank_All;
						cpu_2.onClick = true;
					}
					if (Rank_All >= TOTAL_PLAYER) {
						Cpu_reset();
						Efuda[i][j].kara = true;
						Player_Reset();
					}
				}
			}
		}
	}

	if (cpu_3.Time > cpu_3.setTime) {
		for (int i = 0; i < KARU_MAX_Y; i++) {
			for (int j = 0; j < KARU_MAX_X; j++) {
				if (Yomifuda[0][0].img == Karu_fuda[Efuda[i][j].numY][(Efuda[i][j].numX) + 1]) {
					if (!cpu_3.onClick) {
						cpu_3.x = Efuda[i][j].x;
						cpu_3.y = Efuda[i][j].y;
						Rank_All++;
						PlaySoundMem(Touch_Sound, DX_PLAYTYPE_BACK);
						cpu_3.Rank = Rank_All;
						cpu_3.onClick = true;
					}
					if (Rank_All >= TOTAL_PLAYER) {
						Cpu_reset();
						Efuda[i][j].kara = true;
						Player_Reset();
					}
				}
			}
		}
	}
}

/**************
** CPUのリセット **
* 引数  :なし
* 戻り値:なし
***************/
void Karu_Game::Cpu_reset() {
	cpu_1.Time = 0;
	cpu_2.Time = 0;
	cpu_3.Time = 0;
	Cpu_Set = false;
}

/**************
** 全プレイヤーのリセット **
* 引数  :なし
* 戻り値:なし
***************/
void Karu_Game::Player_Reset() {

	if (Karu_player.Rank == 1) {
		Karu_player.myFuda++;
	}
	if (cpu_1.Rank == 1) {
		cpu_1.myFuda++;
	}
	if (cpu_2.Rank == 1) {
		cpu_2.myFuda++;
	}
	if (cpu_3.Rank == 1) {
		cpu_3.myFuda++;
	}
	AllSet = false;
	Touch_once = false;
	Click_check = 0;
	Click_AnimTime = 0;
	Otetuki = false;
	Otetuki_AnimTime = 0;
	cpu_1.onClick = false;
	cpu_2.onClick = false;
	cpu_3.onClick = false;
	Yomifuda[0][0].kara = true;
	Yomiset = false;
	Rank_All = 0;
}

/**************
** ポーズボタン押したら **
* 引数  :なし
* 戻り値:なし
***************/
void Karu_Game::Pause() {
	if (Mouse_X > 0 && Mouse_X < 80 && Mouse_Y > 0 && Mouse_Y < 40) {
		old_voice = now_voice;
		now_pause = true;
		now_push = true;
		StopSoundMem(Touch_Sound);
		StopSoundMem(Otetuki_Sound);
		StopSoundMem(Karu_Bgm);
		StopSoundMem(voice);
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PULL) { // 左クリックしたら
			now_push = false;
		}
	}
}

/**************
** ポーズ関連 **
* 引数  :なし
* 戻り値:なし
***************/
void Karu_Game::Pause_Controller() {
	if (Mouse_X > 440 && Mouse_X < 840 && Mouse_Y > 300 && Mouse_Y < 420) {
		if (!once_SelectContinueSE) {
			PlaySoundMem(Se_Cursor, DX_PLAYTYPE_BACK);
			once_SelectContinueSE = true;
		}
		on_ContinueButton = true;
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
			PlaySoundMem(Se_Select, DX_PLAYTYPE_BACK);
			now_pause = false;
			//PlaySoundMem(Otetuki_Sound,DX_PLAYTYPE_BACK,FALSE);	//お手付きじゃなくてもなる
			PlaySoundMem(Karu_Bgm, DX_PLAYTYPE_LOOP, FALSE);
			if (old_voice) {
				PlaySoundMem(voice, DX_PLAYTYPE_BACK, FALSE);
			}
			old_voice = false;
		}
	}
	else {
		on_ContinueButton = false;
		once_SelectContinueSE = false;
	}

	if (Mouse_X > 440 && Mouse_X < 840 && Mouse_Y > 450 && Mouse_Y < 570) {
		if (!once_SelectMenuSE) {
			PlaySoundMem(Se_Cursor, DX_PLAYTYPE_BACK);
			once_SelectMenuSE = true;
		}
		on_MenuButton = true;
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
			PlaySoundMem(Se_Select, DX_PLAYTYPE_BACK);
			parent->SetNext(new Scene_Select());
		}	
	}
	else {
		on_MenuButton = false;
		once_SelectMenuSE = false;
	}
	if (Mouse_X > 0 && Mouse_X < 80 && Mouse_Y > 0 && Mouse_Y < 40) {
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH && !now_push) { // 左クリックしたら
			PlaySoundMem(Se_Select, DX_PLAYTYPE_BACK);
			now_pause = false;
			//PlaySoundMem(Otetuki_Sound,DX_PLAYTYPE_BACK,FALSE);	//お手付きじゃなくてもなる
			PlaySoundMem(Karu_Bgm, DX_PLAYTYPE_LOOP, FALSE);
			if (old_voice) {
				PlaySoundMem(voice, DX_PLAYTYPE_BACK, FALSE);
			}
			old_voice = false;
		}
	}
}

/*******************
** 順位計算 **
* 引数  :なし
* 戻り値:なし
********************/
void Karu_Game::Rank() {
	if (Karu_player.myFuda >= cpu_1.myFuda) {
		End_Rank[0] = Karu_PlayerText;
		End_Rank[1] = Karu_CPU1_Text;
	}
	else {
		End_Rank[0] = Karu_CPU1_Text;
		End_Rank[1] = Karu_PlayerText;
	}

	if((End_Rank[0] == Karu_PlayerText && Karu_player.myFuda >= cpu_2.myFuda && cpu_1.myFuda <= cpu_2.myFuda) ||
	   (End_Rank[0] == Karu_CPU1_Text && cpu_1.myFuda >= cpu_2.myFuda && Karu_player.myFuda <= cpu_2.myFuda)){
		End_Rank[2] = End_Rank[1];
		End_Rank[1] = Karu_CPU2_Text;
	}
	else if ((End_Rank[1] == Karu_PlayerText && Karu_player.myFuda >= cpu_2.myFuda) ||
			 (End_Rank[1] == Karu_CPU1_Text && cpu_1.myFuda >= cpu_2.myFuda)) {
		End_Rank[2] = Karu_CPU2_Text;
	}
	else {
		End_Rank[2] = End_Rank[1];
		End_Rank[1] = End_Rank[0];
		End_Rank[0] = Karu_CPU2_Text;
	}

	if ((End_Rank[0] == Karu_PlayerText && Karu_player.myFuda >= cpu_3.myFuda && (cpu_1.myFuda <= cpu_3.myFuda || cpu_2.myFuda <= cpu_3.myFuda)) ||
		(End_Rank[0] == Karu_CPU1_Text && cpu_1.myFuda >= cpu_3.myFuda && (Karu_player.myFuda <= cpu_3.myFuda || cpu_2.myFuda <= cpu_3.myFuda)) ||
		(End_Rank[0] == Karu_CPU2_Text && cpu_2.myFuda >= cpu_3.myFuda && (Karu_player.myFuda <= cpu_3.myFuda || cpu_1.myFuda <= cpu_3.myFuda))) {
		End_Rank[3] = End_Rank[2];
		End_Rank[2] = End_Rank[1];
		End_Rank[1] = Karu_CPU3_Text;
	}
	else if ((End_Rank[1] == Karu_PlayerText && Karu_player.myFuda >= cpu_3.myFuda && (cpu_1.myFuda <= cpu_3.myFuda || cpu_2.myFuda <= cpu_3.myFuda)) ||
			 (End_Rank[1] == Karu_CPU1_Text && cpu_1.myFuda >= cpu_3.myFuda && (Karu_player.myFuda <= cpu_3.myFuda || cpu_2.myFuda <= cpu_3.myFuda)) || 
			 (End_Rank[1] == Karu_CPU2_Text && cpu_2.myFuda >= cpu_3.myFuda && (Karu_player.myFuda <= cpu_3.myFuda || cpu_1.myFuda <= cpu_3.myFuda))) {
		End_Rank[3] = End_Rank[2];
		End_Rank[2] = Karu_CPU3_Text;
	}
	else if ((End_Rank[2] == Karu_PlayerText && Karu_player.myFuda >= cpu_3.myFuda) ||
			 (End_Rank[2] == Karu_CPU1_Text && cpu_1.myFuda >= cpu_3.myFuda) ||
			 (End_Rank[2] == Karu_CPU2_Text && cpu_2.myFuda >= cpu_3.myFuda)) {
		End_Rank[3] = Karu_CPU3_Text;
	}
	else {
		End_Rank[3] = End_Rank[2];
		End_Rank[2] = End_Rank[1];
		End_Rank[1] = End_Rank[0];
		End_Rank[0] = Karu_CPU3_Text;
	}
}

/*******************
** ゲームオーバー **
* 引数  :なし
* 戻り値:なし
********************/
void Karu_Game::Karu_GameOver() {
	StopSoundMem(Touch_Sound);
	StopSoundMem(Karu_Bgm);
	StopSoundMem(voice);
	if (!Gameover) {
		PlaySoundMem(Se_GameOver, DX_PLAYTYPE_BACK);
		Gameover = true;
	}
	if (now_GoSe) {
		if (Mouse_X > 440 && Mouse_X < 840 && Mouse_Y > 250 && Mouse_Y < 370) {
			if (!once_SelectContinueSE) {
				PlaySoundMem(Se_Cursor, DX_PLAYTYPE_BACK);
				once_SelectContinueSE = true;
			}
			on_ContinueButton = true;
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
				now_GoSe = false;
				PlaySoundMem(Se_Select, DX_PLAYTYPE_BACK);

				PlaySoundMem(Karu_Bgm, DX_PLAYTYPE_LOOP, FALSE);
				if (old_voice) {
					PlaySoundMem(voice, DX_PLAYTYPE_BACK, FALSE);
				}
				old_voice = false;

				//絵札総入れ替え
				for (int i = 0; i < KARU_MAX_Y; i++) {
					for (int j = 0; j < KARU_MAX_X; j++) {
						Efuda[i][j] = { 0,0,0,0,0,true };
					}
					for (int z = 0; z < 100; z++) {
						Fuda[z].get = false;
					}
				}
				Yomifuda[0][0].kara = true;
				Yomiset = false;
				reset = 0;
				end = false;
				Gameover = false;
				Karu_player.Otetuki = 0;
				Karu_player.myFuda = 0;
				cpu_1 = { 0,0,0,0 };
				cpu_2 = { 0,0,0,0 };
				cpu_3 = { 0,0,0,0 };
			}
		}
		else {
			on_ContinueButton = false;
			once_SelectContinueSE = false;
		}

		if (Mouse_X > 440 && Mouse_X < 840 && Mouse_Y > 400 && Mouse_Y < 520) {
			if (!once_SelectMenuSE) {
				PlaySoundMem(Se_Cursor, DX_PLAYTYPE_BACK);
				once_SelectMenuSE = true;
			}
			on_MenuButton = true;
			if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
				now_GoSe = false;
				PlaySoundMem(Se_Select, DX_PLAYTYPE_BACK);
				parent->SetNext(new Scene_Select());
			}
		}
		else {
			on_MenuButton = false;
			once_SelectMenuSE = false;
		}
	}
}

/*******************
** 終了時の画面 **
* 引数  :なし
* 戻り値:なし
********************/
void Karu_Game::Karu_End() {

	StopSoundMem(Karu_Bgm);
	StopSoundMem(voice);

	if (Mouse_X > 140 && Mouse_X < 540 && Mouse_Y > 580 && Mouse_Y < 700) {
		if (!once_SelectContinueSE) {
			PlaySoundMem(Se_Cursor, DX_PLAYTYPE_BACK);
			once_SelectContinueSE = true;
		}
		on_ContinueButton = true;
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
			PlaySoundMem(Se_Select, DX_PLAYTYPE_BACK);

			PlaySoundMem(Karu_Bgm, DX_PLAYTYPE_LOOP, FALSE);
			if (old_voice) {
				PlaySoundMem(voice, DX_PLAYTYPE_BACK, FALSE);
			}
			old_voice = false;

			//絵札総入れ替え
			for (int i = 0; i < KARU_MAX_Y; i++) {
				for (int j = 0; j < KARU_MAX_X; j++) {
					Efuda[i][j] = { 0,0,0,0,0,true };
				}
				for (int z = 0; z < 100; z++) {
					Fuda[z].get = false;
				}
			}
			Yomifuda[0][0].kara = true;
			Yomiset = false;
			reset = 0;
			end = false;
			Gameover = false;
			Karu_player.Otetuki = 0;
			Karu_player.myFuda = 0;
			cpu_1 = { 0,0,0,0 };
			cpu_2 = { 0,0,0,0 };
			cpu_3 = { 0,0,0,0 };
		}
	}
	else {
		on_ContinueButton = false;
		once_SelectContinueSE = false;
	}

	if (Mouse_X > 740 && Mouse_X < 1140 && Mouse_Y > 580 && Mouse_Y < 700) {
		if (!once_SelectMenuSE) {
			PlaySoundMem(Se_Cursor, DX_PLAYTYPE_BACK);
			once_SelectMenuSE = true;
		}
		on_MenuButton = true;
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
			PlaySoundMem(Se_Select, DX_PLAYTYPE_BACK);
			parent->SetNext(new Scene_Select());
		}
	}
	else {
		on_MenuButton = false;
		once_SelectMenuSE = false;
	}
}