#include"PageOne.h"
#include"Scene_PageOne.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"
#include "./../Title/Scene_Select.h"
#include "./../Title/Cmp_SelectSelector.h"


void PageOne::PageOne_Initialize(Scene* scene) {

	//背景
	background = LoadGraph("Resource/image/CareerPoker.png");

	//カード画像
	card_img = LoadDivGraph("Resource/image/toranpu_all.png", 54, 13, 5, 200, 300, card_type);

	//リザルト画像
	PlayerCrown = LoadGraph("Resource/image/PageOne_Image/Player_Crown.png");
	NPC1_Icon = LoadGraph("Resource/image/PageOne_Image/NPC1_Crown.png");
	NPC2_Icon = LoadGraph("Resource/image/PageOne_Image/NPC2_Crown.png");
	NPC3_Icon = LoadGraph("Resource/image/PageOne_Image/NPC3_Crown.png");

	//パス画像
	Player_Pass_Icon = LoadGraph("Resource/image/PageOne_Image/Pass.png");
	NPC1_Pass_Icon = LoadGraph("Resource/image/PageOne_Image/NPC1_Pass.png");
	NPC2_Pass_Icon = LoadGraph("Resource/image/PageOne_Image/NPC2_Pass.png");
	NPC3_Pass_Icon = LoadGraph("Resource/image/PageOne_Image/NPC3_Pass.png");

	//ページワン宣言画像
	Player_PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One.png");
	NPC1_PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One_N1.png");
	NPC2_PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One_N2.png");
	NPC3_PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One_N3.png");

	//スートUI
	Spade = LoadGraph("Resource/image/PageOne_Image/Spade.png");
	Heart = LoadGraph("Resource/image/PageOne_Image/Heart.png");
	Diamond = LoadGraph("Resource/image/PageOne_Image/Diamond.png");
	Club = LoadGraph("Resource/image/PageOne_Image/Club.png");
	free = LoadGraph("Resource/image/PageOne_Image/Free.png");

	//ポーズ&リザルトUI
	Pause_Button = LoadGraph("Resource/image/PauseButton.png");
	Pause_Back = LoadGraph("Resource/image/PauseBack.png");
	Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
	Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);
	Pause_Flg = false;

	Result = LoadGraph("Resource/image/PageOne_Image/ResultBack.png");

	//SE&BGM
	pass_SE = LoadSoundMem("Resource/se/pageOne_SE/pass.wav");
	pageone_SE = LoadSoundMem("Resource/se/pageOne_SE/pageone.wav");
	card_SE_1 = LoadSoundMem("Resource/se/pageOne_SE/トランプ・引く02.wav");
	card_SE_2 = LoadSoundMem("Resource/se/pageOne_SE/カードを台の上に出す.wav");
	card_SE_3 = LoadSoundMem("Resource/se/pageOne_SE/カードをめくる.wav");
	win_SE = LoadSoundMem("Resource/se/pageOne_SE/Morning_Maze.wav");

	Select_SE = LoadSoundMem("Resource/se/Karu_SE/Karu_Select.wav");

	BGM = LoadSoundMem("Resource/se/pageOne_SE/フルハウス_2.wav");

	ChangeVolumeSoundMem(255 * 80 / 100, pass_SE);
	ChangeVolumeSoundMem(255 * 80 / 100, pageone_SE);
	ChangeVolumeSoundMem(255 * 80 / 100, card_SE_1);
	ChangeVolumeSoundMem(255 * 80 / 100, card_SE_2);
	ChangeVolumeSoundMem(255 * 80 / 100, card_SE_3);
	ChangeVolumeSoundMem(255 * 80 / 100, win_SE);

	ChangeVolumeSoundMem(255 * 80 / 100, Select_SE);

	ChangeVolumeSoundMem(255 * 80 / 100, BGM);

	OneShot = false;

	Deck_X = 130;
	Deck_Y = 550;

	Field_X = 500;
	Field_Y = 350;

	Player_X = 300;
	Player_Y = 575;

	NPC1_X = 125;
	NPC1_Y = 125;

	NPC2_X = 550;
	NPC2_Y = 75;

	NPC3_X = 975;
	NPC3_Y = 125;

	n = 0;

	flg_p = false;
	flg_1 = false;
	flg_2 = false;
	flg_3 = false;

	Player_setup = false;
	NPC1_setup = false;
	NPC2_setup = false;
	NPC3_setup = false;

	PageOne_flg = false;
	PageOne_player = false;
	PageOne_npc1 = false;
	PageOne_npc2 = false;
	PageOne_npc3 = false;

	Player_Pass_Flg = false;
	NPC1_Pass_Flg = false;
	NPC2_Pass_Flg = false;
	NPC3_Pass_Flg = false;

	lead = 0;
	pri = 1;
	draw = false;
	finish = false;
	reset = false;

	field = 0;
	player = 0;
	npc_1 = 0;
	npc_2 = 0;
	npc_3 = 0;

	priority = GetRand(MAX - 1);

	for (i = 0; i < 52; i++) {
		Card_obj.push_back(Card(card_type[i], i % 13, i / 13, Deck_X, Deck_Y));
	}

	Card_obj.push_back(Card(card_type[53], 99, 5, Deck_X, Deck_Y));	//ジョーカー

	Card_back = card_type[52];	//カードの裏面

	Old_key = KEY_FREE;
	select = scene;
}

void PageOne::PageOne_Finalize() {

	//背景
	DeleteGraph(background);

	//カード画像
	DeleteGraph(card_img);

	//リザルト画像
	DeleteGraph(PlayerCrown);
	DeleteGraph(NPC1_Icon);
	DeleteGraph(NPC2_Icon);
	DeleteGraph(NPC3_Icon);

	//パス画像
	DeleteGraph(Player_Pass_Icon);
	DeleteGraph(NPC1_Pass_Icon);
	DeleteGraph(NPC2_Pass_Icon);
	DeleteGraph(NPC3_Pass_Icon);

	//ページワン画像
	DeleteGraph(Player_PageOne_Icon);
	DeleteGraph(NPC1_PageOne_Icon);
	DeleteGraph(NPC2_PageOne_Icon);
	DeleteGraph(NPC3_PageOne_Icon);

	//スート
	DeleteGraph(Spade);
	DeleteGraph(Heart);
	DeleteGraph(Diamond);
	DeleteGraph(Club);
	DeleteGraph(free);

	//ポーズ&リザルトUI
	DeleteGraph(Pause_Button);
	DeleteGraph(Pause_Back);
	DeleteGraph(Pause_Continue);
	DeleteGraph(Pause_Select);

	DeleteGraph(Result);

	//SE&BGM
	DeleteSoundMem(pass_SE);
	DeleteSoundMem(pageone_SE);
	DeleteSoundMem(card_SE_1);
	DeleteSoundMem(card_SE_2);
	DeleteSoundMem(card_SE_3);
	DeleteSoundMem(Select_SE);
	DeleteSoundMem(win_SE);
	DeleteSoundMem(BGM);

	//配列の初期化
	Card_obj.clear();
	Player_card.clear();
	Field_card.clear();
	Cemetery_card.clear();
	NPC_card_1.clear();
	NPC_card_2.clear();
	NPC_card_3.clear();
}

void PageOne::PageOne_Update() {

	GetMousePoint(&Mouse_X, &Mouse_Y);

	Now_key = key->GetKeyState(REQUEST_MOUSE_LEFT); //現在のマウス左ボタンの入力状態の取得

	if (CheckSoundMem(BGM) == false) {
		PlaySoundMem(BGM, DX_PLAYTYPE_BACK, TRUE);
	}

	//ポーズボタンを押したらポーズ画面を開くフラグをtrueにする
	if ((20 <= Mouse_X && Mouse_X <= 175 && 5 <= Mouse_Y && Mouse_Y <= 70) || ((450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) && Pause_Flg == true)) {
		if (Old_key != KEY_FREE && Now_key == KEY_PULL) {
			PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK);
			Pause_Flg = !Pause_Flg;
		}
	}

	//セレクト画面へ移動
	if (Pause_Flg == true) {
		if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
			if (Old_key != KEY_FREE && Now_key == KEY_PULL) {  //前の入力で左キーを話していなくて、今マウスの左キーを離した時
				PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK);
				StopSoundMem(BGM);
				PageOne_Finalize();
				select->SetNext(new Scene_Select());
			}
		}
	}

	if (finish == true) {
		//最初からプレイ
		if (175 <= Mouse_X && Mouse_X <= 575 && 565 <= Mouse_Y && Mouse_Y <= 685) {
			if (Old_key != KEY_FREE && Now_key == KEY_PULL) {  //前の入力で左キーを話していなくて、今マウスの左キーを離した時
				PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK);
				StopSoundMem(BGM);
				PageOne_Finalize();
				select->SetNext(new Scene_PageOne());
			}
		}

		//セレクト画面へ移動
		if (625 <= Mouse_X && Mouse_X <= 1025 && 565 <= Mouse_Y && Mouse_Y <= 685) {
			if (Old_key != KEY_FREE && Now_key == KEY_PULL) {  //前の入力で左キーを話していなくて、今マウスの左キーを離した時
				PlaySoundMem(Select_SE, DX_PLAYTYPE_BACK);
				StopSoundMem(BGM);
				PageOne_Finalize();
				select->SetNext(new Scene_Select());
			}
		}
	}

	n++;	//山札からカード引くときのクールタイム（早すぎると違和感があるから）

	if (finish == false && Pause_Flg == false) {
		switch (priority) {
		case 0:	// player
			if (Player_setup == false) {
				if (n > 15) {
					itr = Card_obj.begin();
					r = GetRand(Card_obj.size() -1);
					for (int i = 0; i < r; i++) {
						itr++;
					}
					(*itr).card_x = Player_X;
					(*itr).card_y = Player_Y;
					PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
					Player_card.push_back(*itr);

					if (Player_card.size() >= MAX) {
						Player_setup = true;
					}
					priority++;
					n = 0;
					Card_obj.erase(itr);
				}
				break;
			}
			else {
				if (flg_p == false) {

					f_itr = Field_card.begin();

					if (Field_card.empty() == false && (*f_itr).suit == 5) {
						lead = 1;
					}
					else {
						lead = 0;
					}

					reset = false;

					if (Field_card.empty()) {
						draw = false;
					}
					else {

						if (lead == 1) {
							f_itr++;
						}

						for (p_itr = Player_card.begin(); p_itr != Player_card.end(); p_itr++) {
							if ((*p_itr).suit == 5) {
								draw = false;
							}
							else if ((*f_itr).suit == (*p_itr).suit) {
								draw = false;
							}
						}
					}

					//プレイヤーがカード引く用
					if (draw == true) {
						if (n > 30) {
							if ((Mouse_X > Deck_X - (card_w * 0.7) / 2) && (Mouse_X < Deck_X + (card_w * 0.7) / 2) && (Mouse_Y > Deck_Y - (card_h * 0.7) / 2) && (Mouse_Y < Deck_Y + (card_h * 0.7) / 2)) {
								if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
									itr = Card_obj.begin();

									PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
									r = GetRand(Card_obj.size() - 1);

									for (int i = 0; i < r; i++) {
										itr++;
									}
									
									(*itr).card_x = Player_X;
									(*itr).card_y = Player_Y;
									
									Player_card.push_back(*itr);
									Card_obj.erase(itr);
									
									n = 0;
									break;
								}
							}
						}
					}

					for (p_itr = Player_card.begin(); p_itr != Player_card.end(); p_itr++) {
						//山札0枚＆手札に出せるカードがない場合パスをする
						if (Card_obj.empty() == true && (*f_itr).suit != (*p_itr).suit && (*p_itr).suit != 5) {
							Player_Pass_Flg = true;
							if ((Mouse_X > 890) && (Mouse_X < 1040) && (Mouse_Y > 440) && (Mouse_Y < 515)) {
								if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
									PlaySoundMem(pass_SE, DX_PLAYTYPE_BACK, TRUE);
									flg_p = true;
									priority++;
									n = 0;
									break;
								}
							}
						}
						else {
							Player_Pass_Flg = false;
						}
					}

					player = Player_card.size();
					p_itr = Player_card.begin();
					f_itr = Field_card.begin();

					//プレイヤーの手札からカードだす
					for (i = 0; i < player; i++) {
						if (Field_card.empty() || Field_card.front().suit == 5 || (*f_itr).suit == (*p_itr).suit || (*p_itr).suit == 5) {
							//手札が残り二枚だとページワン宣言できる
							if (Player_card.size() == 2 && PageOne_flg == false) {
								PageOne_player = true;
							}
							else {
								PageOne_player = false;
							}

							//ページワン宣言ボタン
							if (PageOne_player == true) {
								if ((Mouse_X > 500) && (Mouse_X < 800) && (Mouse_Y > 400) && (Mouse_Y < 500)) {
									if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
										PlaySoundMem(pageone_SE, DX_PLAYTYPE_BACK, TRUE);
										PageOne_player = false;
										PageOne_flg = true;
									}
								}
							}
							if (PageOne_player == false) {
								if (Card::Hit(Mouse_X, Mouse_Y, Player_X + (card_w * 0.5) * (i % 10), Player_Y + (card_h * pow(0.5, 2)) * (i / 10), card_w, card_h, 0.5)) {
									(*p_itr).card_y = Player_Y - 50;
									if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
										PlaySoundMem(card_SE_2, DX_PLAYTYPE_BACK, TRUE);

										Field_card.push_back(*p_itr);

										if ((*p_itr).num == 99) {
											pri = 99;
										}
										else if ((*p_itr).num == 0) {
											if (pri != 99) {
												pri = 0;
											}
											else {
												pri = 99;
											}
										}
										else if (pri != 0 && pri < (*p_itr).num) {
											pri = (*p_itr).num;
										}

										p_pow = (*p_itr).num;
										priority++;
										draw = true;
										flg_p = true;
										n = 0;
										PageOne_flg = false;
										Player_card.erase(p_itr);
										break;
									}
								}
								else {
									(*p_itr).card_y = Player_Y;
								}
							}
						}
						++p_itr;
					}
				}
				else {
					priority++;
				}
				break;
			}

		case 1:	// NPC1
			if (NPC1_setup == false) {
				if (n > 15) {
					itr = Card_obj.begin();
					r = GetRand(Card_obj.size() - 1);
					for (int i = 0; i < r; i++) {
						itr++;
					}
					(*itr).card_x = NPC1_X;
					(*itr).card_y = NPC1_Y;
					PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
					NPC_card_1.push_back(*itr);

					if (NPC_card_1.size() >= MAX) {
						NPC1_setup = true;
					}
					priority++;
					n = 0;
					Card_obj.erase(itr);
				}
				break;
			}
			else {
				if (flg_1 == false) {

					f_itr = Field_card.begin();

					if (Field_card.empty() == false && (*f_itr).suit == 5) {
						lead = 1;
					}
					else {
						lead = 0;
					}

					reset = false;

					if (Field_card.empty()) {
						draw = false;
					}
					else {
						npc_1 = NPC_card_1.size();
						n1_itr = NPC_card_1.begin();

						if (lead == 1) {
							f_itr++;
						}

						for (i = 0; i < npc_1; i++) {
							if ((*n1_itr).suit == 5) {
								draw = false;
							}
							else if ((*f_itr).suit == (*n1_itr).suit) {
								draw = false;
							}
							n1_itr++;
						}
					}
		
					//NPCがカード引く用
					if (draw == true && Card_obj.empty() == false) {
						if (n > 30) {
							itr = Card_obj.begin();

							PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
							r = GetRand(Card_obj.size() - 1);

							for (int i = 0; i < r; i++) {
								itr++;
							}

							(*itr).card_x = NPC1_X;
							(*itr).card_y = NPC1_X;

							NPC_card_1.push_back(*itr);
							Card_obj.erase(itr);

							n = 0;
							break;
						}
					}
		
					//手札が残り二枚だとページワン宣言できる
					if (NPC_card_1.size() == 2 && PageOne_flg == false) {
						if (50 < n && n <= 90) {
							if (OneShot == false) {
								PlaySoundMem(pageone_SE, DX_PLAYTYPE_BACK, TRUE);
								OneShot = true;
							}
							PageOne_npc1 = true;
						}
						if (n > 90) {
							n = 0;
							PageOne_npc1 = false;
							PageOne_flg = true;
							OneShot = false;
						}
					}
					else {
						PageOne_npc1 = false;
					}

					f_itr = Field_card.begin();

					//場のスートの判定基準を決めている
					if (Field_card.empty() == false && (*f_itr).suit == 5) {
						f_itr++;
					}
					else {
						f_itr = Field_card.begin();
					}
		
					//NPCの手札からカードだす
					for (n1_itr = NPC_card_1.begin(); n1_itr != NPC_card_1.end(); n1_itr++) {
		
						//山札0枚＆手札に出せるカードがない場合パスをする
						if (Card_obj.empty() == true && Field_card.empty() == false && (*f_itr).suit != (*n1_itr).suit && (*n1_itr).suit != 5) {
		
							if (50 < n && n <= 90) {
								if (OneShot == false) {
									PlaySoundMem(pass_SE, DX_PLAYTYPE_BACK, TRUE);
									OneShot = true;
								}
		
								NPC1_Pass_Flg = true;
							}
		
							if (n > 90) {
								flg_1 = true;
								priority++;
								n = 0;
							}
						}
						else {
							if (n > 90) {
		
								if (Field_card.empty() || Field_card.front().suit == 5 || (*f_itr).suit == (*n1_itr).suit || (*n1_itr).suit == 5) {
		
									if (PageOne_npc1 == false) {
										PlaySoundMem(card_SE_2, DX_PLAYTYPE_BACK, TRUE);
										Field_card.push_back(*n1_itr);
		
										if ((*n1_itr).num == 99) {
											pri = 99;
										}
										else if ((*n1_itr).num == 0) {
											if (pri != 99) {
												pri = 0;
											}
											else {
												pri = 99;
											}
										}
										else if (pri != 0 && pri < (*n1_itr).num) {
											pri = (*n1_itr).num;
										}

										n1_pow = (*n1_itr).num;
										priority++;
										draw = true;
										flg_1 = true;
										n = 0;
										PageOne_flg = false;
										NPC_card_1.erase(n1_itr);
										break;
									}
								}
							}
						}
					}
				}
				else {
					priority++;
				}
				break;
			}
		
		case 2:	// NPC2
			if (NPC2_setup == false) {
				if (n > 15) {
					itr = Card_obj.begin();
					r = GetRand(Card_obj.size() - 1);
					for (int i = 0; i < r; i++) {
						itr++;
					}
					(*itr).card_x = NPC2_X;
					(*itr).card_y = NPC2_Y;
					PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
					NPC_card_2.push_back(*itr);
					
					if (NPC_card_2.size() >= MAX) {
						NPC2_setup = true;
					}
					priority++;
					n = 0;
					Card_obj.erase(itr);
				}
				break;
			}
			else {
				if (flg_2 == false) {

					f_itr = Field_card.begin();

					if (Field_card.empty() == false && (*f_itr).suit == 5) {
						lead = 1;
					}
					else {
						lead = 0;
					}

					reset = false;

					if (Field_card.empty()) {
						draw = false;
					}
					else {
						npc_2 = NPC_card_2.size();
						n2_itr = NPC_card_2.begin();

						if (lead == 1) {
							f_itr++;
						}

						for (i = 0; i < npc_2; i++) {
							if ((*n2_itr).suit == 5) {
								draw = false;
							}
							else if ((*f_itr).suit == (*n2_itr).suit) {
								draw = false;
							}
							n2_itr++;
						}
					}

					//NPCがカード引く用
					if (draw == true && Card_obj.empty() == false) {
						if (n > 30) {
							itr = Card_obj.begin();

							PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
							r = GetRand(Card_obj.size() - 1);

							for (int i = 0; i < r; i++) {
								itr++;
							}

							(*itr).card_x = NPC2_X;
							(*itr).card_y = NPC2_X;

							NPC_card_2.push_back(*itr);
							Card_obj.erase(itr);

							n = 0;
							break;
						}
					}

					//手札が残り二枚だとページワン宣言できる
					if (NPC_card_2.size() == 2 && PageOne_flg == false) {
						if (50 < n && n <= 90) {
							if (OneShot == false) {
								PlaySoundMem(pageone_SE, DX_PLAYTYPE_BACK, TRUE);
								OneShot = true;
							}
							PageOne_npc2 = true;
						}
						if (n > 90) {
							n = 0;
							PageOne_npc2 = false;
							PageOne_flg = true;
							OneShot = false;
						}
					}
					else {
						PageOne_npc2 = false;
					}

					f_itr = Field_card.begin();

					//場のスートの判定基準を決めている
					if (Field_card.empty() == false && (*f_itr).suit == 5) {
						f_itr++;
					}
					else {
						f_itr = Field_card.begin();
					}

					//NPCの手札からカードだす
					for (n2_itr = NPC_card_2.begin(); n2_itr != NPC_card_2.end(); n2_itr++) {

						//山札0枚＆手札に出せるカードがない場合パスをする
						if (Card_obj.empty() == true && Field_card.empty() == false && (*f_itr).suit != (*n2_itr).suit && (*n2_itr).suit != 5) {

							if (50 < n && n <= 90) {
								if (OneShot == false) {
									PlaySoundMem(pass_SE, DX_PLAYTYPE_BACK, TRUE);
									OneShot = true;
								}

								NPC2_Pass_Flg = true;
							}

							if (n > 90) {
								flg_2 = true;
								priority++;
								n = 0;
							}
						}
						else {
							if (n > 90) {

								if (Field_card.empty() || Field_card.front().suit == 5 || (*f_itr).suit == (*n2_itr).suit || (*n2_itr).suit == 5) {

									if (PageOne_npc2 == false) {
										PlaySoundMem(card_SE_2, DX_PLAYTYPE_BACK, TRUE);
										Field_card.push_back(*n2_itr);

										if ((*n2_itr).num == 99) {
											pri = 99;
										}
										else if ((*n2_itr).num == 0) {
											if (pri != 99) {
												pri = 0;
											}
											else {
												pri = 99;
											}
										}
										else if (pri != 0 && pri < (*n2_itr).num) {
											pri = (*n2_itr).num;
										}

										n2_pow = (*n2_itr).num;
										priority++;
										draw = true;
										flg_2 = true;
										n = 0;
										PageOne_flg = false;
										NPC_card_2.erase(n2_itr);
										break;
									}
								}
							}
						}
					}
				}
				else {
					priority++;
				}
				break;
			}
		case 3:	// NPC3
			if (NPC3_setup == false) {
				if (n > 15) {
					itr = Card_obj.begin();
					r = GetRand(Card_obj.size() - 1);
					for (int i = 0; i < r; i++) {
						itr++;
					}
					(*itr).card_x = NPC3_X;
					(*itr).card_y = NPC3_Y;
					PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
					NPC_card_3.push_back(*itr);
					if (NPC_card_3.size() >= MAX) {
						NPC3_setup = true;
					}
					priority++;
					n = 0;
					Card_obj.erase(itr);
				}
				break;
			}
			else {
				if (flg_3 == false) {

					f_itr = Field_card.begin();

					if (Field_card.empty() == false && (*f_itr).suit == 5) {
						lead = 1;
					}
					else {
						lead = 0;
					}

					reset = false;

					if (Field_card.empty()) {
						draw = false;
					}
					else {
						npc_3 = NPC_card_3.size();
						n3_itr = NPC_card_3.begin();

						if (lead == 1) {
							f_itr++;
						}

						for (i = 0; i < npc_3; i++) {
							if ((*n3_itr).suit == 5) {
								draw = false;
							}
							else if ((*f_itr).suit == (*n3_itr).suit) {
								draw = false;
							}
							n3_itr++;
						}
					}

					//NPCがカード引く用
					if (draw == true && Card_obj.empty() == false) {
						if (n > 30) {
							itr = Card_obj.begin();

							PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
							r = GetRand(Card_obj.size() - 1);

							for (int i = 0; i < r; i++) {
								itr++;
							}

							(*itr).card_x = NPC3_X;
							(*itr).card_y = NPC3_X;

							NPC_card_3.push_back(*itr);
							Card_obj.erase(itr);

							n = 0;
							break;
						}
					}

					//手札が残り二枚だとページワン宣言できる
					if (NPC_card_3.size() == 2 && PageOne_flg == false) {
						if (50 < n && n <= 90) {
							if (OneShot == false) {
								PlaySoundMem(pageone_SE, DX_PLAYTYPE_BACK, TRUE);
								OneShot = true;
							}
							PageOne_npc3 = true;
						}
						if (n > 90) {
							n = 0;
							PageOne_npc3 = false;
							PageOne_flg = true;
							OneShot = false;
						}
					}
					else {
						PageOne_npc3 = false;
					}

					f_itr = Field_card.begin();

					//場のスートの判定基準を決めている
					if (Field_card.empty() == false && (*f_itr).suit == 5) {
						f_itr++;
					}
					else {
						f_itr = Field_card.begin();
					}

					//NPCの手札からカードだす
					for (n3_itr = NPC_card_3.begin(); n3_itr != NPC_card_3.end(); n3_itr++) {

						//山札0枚＆手札に出せるカードがない場合パスをする（手動）
						if (Card_obj.empty() == true && Field_card.empty() == false && (*f_itr).suit != (*n3_itr).suit && (*n3_itr).suit != 5) {

							if (50 < n && n <= 90) {
								if (OneShot == false) {
									PlaySoundMem(pass_SE, DX_PLAYTYPE_BACK, TRUE);
									OneShot = true;
								}

								NPC3_Pass_Flg = true;
							}

							if (n > 90) {
								flg_3 = true;
								priority++;
								n = 0;
							}
						}
						else {
							if (n > 90) {

								if (Field_card.empty() || Field_card.front().suit == 5 || (*f_itr).suit == (*n3_itr).suit || (*n3_itr).suit == 5) {

									if (PageOne_npc3 == false) {
										PlaySoundMem(card_SE_3, DX_PLAYTYPE_BACK, TRUE);

										if ((*n3_itr).num == 99) {
											pri = 99;
										}
										else if ((*n3_itr).num == 0) {
											if (pri != 99) {
												pri = 0;
											}
											else {
												pri = 99;
											}
										}
										else if (pri != 0 && pri < (*n3_itr).num) {
											pri = (*n3_itr).num;
										}

										n3_pow = (*n3_itr).num;
										priority++;
										draw = true;
										flg_3 = true;
										n = 0;
										PageOne_flg = false;

										Field_card.push_back(*n3_itr);

										NPC_card_3.erase(n3_itr);
										break;
									}
								}
							}
						}
					}
				}
				else {
					priority++;
				}
				break;
			}

		case 4:
		default:
			// 全員の手番がおわってるか？
			if (flg_p == false || flg_1 == false || flg_2 == false || flg_3 == false) {
				priority = 0;
			}
			else {
				reset = true;
				if (90 <= n && n < 180) {
					if (OneShot == false) {
						PlaySoundMem(card_SE_3, DX_PLAYTYPE_BACK, TRUE);
						OneShot = true;
					}
					Field_X += 20;
					n++;
				}
				else if (180 <= n) {
					Player_Pass_Flg = false;
					NPC1_Pass_Flg = false;
					NPC2_Pass_Flg = false;
					NPC3_Pass_Flg = false;

					if (pri == p_pow) {
						priority = 0;
					}
					if (pri == n1_pow) {
						priority = 1;
					}
					if (pri == n2_pow) {
						priority = 2;
					}
					if (pri == n3_pow) {
						priority = 3;
					}

					pri = 1;

					flg_p = false;
					flg_1 = false;
					flg_2 = false;
					flg_3 = false;

					cemetery = Field_card.size();
					f_itr = Field_card.begin();

					for (i = 0; i < cemetery; i++) {
						Cemetery_card.push_back((*f_itr));
						f_itr++;
					}

					Field_card.clear();
					Field_X = 500;
					if (Card_obj.empty() == true) {
						Card_obj = Cemetery_card;
						Cemetery_card.clear();
					}
					OneShot = false;
					n = 0;
				}
			}
			break;
		}
	}

	Old_key = Now_key;
}

void PageOne::PageOne_Draw() {
	field = Field_card.size();
	player = Player_card.size();
	npc_1 = NPC_card_1.size();
	npc_2 = NPC_card_2.size();
	npc_3 = NPC_card_3.size();

	f_itr = Field_card.begin();
	p_itr = Player_card.begin();

	DrawRotaGraph(640, 360, 1.0, 0, background, TRUE);

	if (reset == false && Player_setup == true && NPC1_setup == true && NPC2_setup == true && NPC3_setup == true) {

		switch (priority) {
		case 0:
			DrawFormatString(50, 350, GetColor(255, 255, 255), "手番：プレイヤー");
			if (draw == true) {
				DrawFormatString(250, 450, GetColor(100, 100, 255), "カードを引いてください");
			}
			else if (Player_Pass_Flg == true) {
				DrawFormatString(250, 450, GetColor(100, 100, 255), "パスをしてください");
			}
			else {
				DrawFormatString(250, 450, GetColor(100, 100, 255), "");
			}

			break;
		case 1:
			DrawFormatString(50, 350, GetColor(255, 255, 255), "手番：NPC１号");
			break;
		case 2:
			DrawFormatString(50, 350, GetColor(255, 255, 255), "手番：NPC２号");
			break;
		case 3:
			DrawFormatString(50, 350, GetColor(255, 255, 255), "手番：NPC３号");
			break;
		}

		DrawFormatString(1000, 375, GetColor(255, 255, 255), "現在のスート");
		if (Field_card.empty() == false) {
			switch (Field_card.front().suit) {
			case 0:
				DrawRotaGraph(1100, 450, 0.8, 0, Spade, TRUE);
				break;
			case 1:
				DrawRotaGraph(1100, 450, 0.8, 0, Heart, TRUE);
				break;
			case 2:
				DrawRotaGraph(1100, 450, 0.8, 0, Diamond, TRUE);
				break;
			case 3:
				DrawRotaGraph(1100, 450, 0.8, 0, Club, TRUE);
				break;
			default:
				DrawRotaGraph(1100, 450, 0.8, 0, free, TRUE);
				break;
			}
		}
		else {
			DrawRotaGraph(1100, 450, 0.8, 0, free, TRUE);
		}
	}

	//山札の描画
	if (Card_obj.empty() == false) {
		DrawRotaGraph(Deck_X, Deck_Y, 0.7, 0, Card_back, TRUE);
	}

	//場に出ているカードの描画
	for (i = 0; i < field; i++) {
		DrawRotaGraph(Field_X + i * 100, Field_Y, 0.5, 0, (*f_itr).img, TRUE);
		f_itr++;
	}

	//プレイヤーの手札描画
	for (i = 0; i < player; i++) {
		DrawRotaGraph((*p_itr).card_x + (i % 10) * (card_w * 0.5), (*p_itr).card_y + (i / 10) * (card_h * pow(0.5, 2)), 0.5, 0, (*p_itr).img, TRUE);
		p_itr++;
	}

	//NPC１号の手札描画
	for (i = 0; i < npc_1; i++) {
		DrawRotaGraph(NPC1_X + (i % 5) * (card_w * 0.3), NPC1_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, Card_back, TRUE);
		//DrawRotaGraph(NPC1_X + (i % 5) * (card_w * 0.3), NPC1_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_1[i].img, TRUE);
	}

	//NPC２号の手札描画
	for (i = 0; i < npc_2; i++) {
		DrawRotaGraph(NPC2_X + (i % 5) * (card_w * 0.3), NPC2_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, Card_back, TRUE);
		//DrawRotaGraph(NPC2_X + (i % 5) * (card_w * 0.3), NPC2_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_2[i].img, TRUE);
	}

	//NPC３号の手札描画
	for (i = 0; i < npc_3; i++) {
		DrawRotaGraph(NPC3_X + (i % 5) * (card_w * 0.3), NPC3_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, Card_back, TRUE);
		//DrawRotaGraph(NPC3_X + (i % 5) * (card_w * 0.3), NPC3_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_3[i].img, TRUE);
	}

	if (finish == false) {
		DrawFormatString(25, 100, GetColor(255, 255, 255), "NPC");
		DrawFormatString(25, 125, GetColor(255, 255, 255), "１号");

		DrawFormatString(450, 50, GetColor(255, 255, 255), "NPC");
		DrawFormatString(450, 75, GetColor(255, 255, 255), "２号");

		DrawFormatString(875, 100, GetColor(255, 255, 255), "NPC");
		DrawFormatString(875, 125, GetColor(255, 255, 255), "３号");

		DrawFormatString(0, 665, GetColor(255, 255, 255), "山札:残り%d枚", Card_obj.size());
	}

	//パスのUI
	if (Player_Pass_Flg == true) {
		DrawGraph(890, 440, Player_Pass_Icon, true);
	}
	if (NPC1_Pass_Flg == true) {
		DrawGraph(0, 175, NPC1_Pass_Icon, true);
	}
	if (NPC2_Pass_Flg == true) {
		DrawGraph(400, 105, NPC2_Pass_Icon, true);
	}
	if (NPC3_Pass_Flg == true) {
		DrawGraph(800, 175, NPC3_Pass_Icon, true);
	}

	//ページワンボタン
	if (PageOne_player == true) {
		DrawGraph(500, 400, Player_PageOne_Icon, true);
	}
	if (PageOne_npc1 == true) {
		DrawGraph(0, 175, NPC1_PageOne_Icon, true);
	}
	if (PageOne_npc2 == true) {
		DrawGraph(400, 105, NPC2_PageOne_Icon, true);
	}
	if (PageOne_npc3 == true) {
		DrawGraph(800, 175, NPC3_PageOne_Icon, true);
	}

	//勝利時のUI
	if (Player_setup == true && Player_card.size() == 0 && n >= 30) {
		PlaySoundMem(win_SE, DX_PLAYTYPE_BACK, TRUE);
		DrawRotaGraph(600, 300, 1.0, 0, Result, TRUE);
		DrawRotaGraph(600, 300, 1.3, 0, PlayerCrown, TRUE);
		finish = true;
	}
	if (NPC1_setup == true && NPC_card_1.size() == 0 && n >= 30) {
		PlaySoundMem(win_SE, DX_PLAYTYPE_BACK, TRUE);
		DrawRotaGraph(600, 300, 1.0, 0, Result, TRUE);
		DrawRotaGraph(600, 300, 1.3, 0, NPC1_Icon, TRUE);
		finish = true;
	}
	if (NPC2_setup == true && NPC_card_2.size() == 0 && n >= 30) {
		PlaySoundMem(win_SE, DX_PLAYTYPE_BACK, TRUE);
		DrawRotaGraph(600, 300, 1.0, 0, Result, TRUE);
		DrawRotaGraph(600, 300, 1.3, 0, NPC2_Icon, TRUE);
		finish = true;
	}
	if (NPC3_setup == true && NPC_card_3.size() == 0 && n >= 30) {
		PlaySoundMem(win_SE, DX_PLAYTYPE_BACK, TRUE);
		DrawRotaGraph(600, 300, 1.0, 0, Result, TRUE);
		DrawRotaGraph(600, 300, 1.3, 0, NPC3_Icon, TRUE);
		finish = true;
	}

	//ポーズボタン
	DrawRotaGraph(100, 40, 0.8, 0, Pause_Button, TRUE);
	if (Pause_Flg == true) {
		DrawRotaGraph(650, 380, 1.15, 0, Pause_Back, TRUE);
		if (450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) {
			if (Now_key == KEY_HOLD) {
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
			if (Now_key == KEY_HOLD) {
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

	if (finish == true) {
		if (175 <= Mouse_X && Mouse_X <= 575 && 565 <= Mouse_Y && Mouse_Y <= 685) {
			if (Now_key == KEY_HOLD) {
				DrawRotaGraph(375, 625, 0.9, 0, pause_continue[1], TRUE);
			}
			else {
				DrawRotaGraph(375, 625, 1.0, 0, pause_continue[1], TRUE);
			}
		}
		else {
			DrawRotaGraph(375, 625, 1.0, 0, pause_continue[0], TRUE);
		}
		if (625 <= Mouse_X && Mouse_X <= 1025 && 565 <= Mouse_Y && Mouse_Y <= 685) {
			if (Now_key == KEY_HOLD) {
				DrawRotaGraph(825, 625, 0.9, 0, pause_select[1], TRUE);
			}
			else {
				DrawRotaGraph(825, 625, 1.0, 0, pause_select[1], TRUE);
			}
		}
		else {
			DrawRotaGraph(825, 625, 1.0, 0, pause_select[0], TRUE);
		}

	}

	//デバッグ用
	//DrawBox(890, 440,980, 500, color, TRUE);
	//DrawFormatString(900, 450, GetColor(255, 0, 0), "パス");
	//DrawFormatString(900, 450, GetColor(255, 0, 0), "list:%d", Field_card.size());
	//if (Field_card.empty() == true) {
	//	DrawFormatString(900, 450, GetColor(255, 0, 0), "空っぽだよ");
	//}
	//else if (Field_card.empty() == false) {
	//	DrawFormatString(900, 450, GetColor(255, 0, 0), "入ってるよ");
	//}
	//else {
	//	DrawFormatString(900, 450, GetColor(255, 0, 0), "そもそもないよ");
	//}
	//DrawGraph(0, 175, NPC_Pass_Icon, true);
	//DrawGraph(500, 400, NPC_PageOne_Icon, true);
}
