#include"PageOne.h"
#include"Scene_PageOne.h"
#include"DxLib.h"
#include"./../Code/GetKey.h"
#include "./../Title/Scene_Select.h"
#include "./../Title/Cmp_SelectSelector.h"


void PageOne::PageOne_Initialize(Scene* scene) {

	//�w�i
	background = LoadGraph("Resource/image/CareerPoker.png");

	//�J�[�h�摜
	LoadDivGraph("Resource/image/toranpu_all.png", 54, 13, 5, 200, 300, card_type);

	//���U���g�摜
	PlayerCrown = LoadGraph("Resource/image/PageOne_Image/Player_Crown.png");
	NPC1_Icon = LoadGraph("Resource/image/PageOne_Image/NPC1_Crown.png");
	NPC2_Icon = LoadGraph("Resource/image/PageOne_Image/NPC2_Crown.png");
	NPC3_Icon = LoadGraph("Resource/image/PageOne_Image/NPC3_Crown.png");
	
	//�p�X�摜
	Player_Pass_Icon = LoadGraph("Resource/image/PageOne_Image/Pass.png");
	NPC1_Pass_Icon = LoadGraph("Resource/image/PageOne_Image/NPC1_Pass.png");
	NPC2_Pass_Icon = LoadGraph("Resource/image/PageOne_Image/NPC2_Pass.png");
	NPC3_Pass_Icon = LoadGraph("Resource/image/PageOne_Image/NPC3_Pass.png");
	
	//�y�[�W�����錾�摜
	Player_PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One.png");
	NPC1_PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One_N1.png");
	NPC2_PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One_N2.png");
	NPC3_PageOne_Icon = LoadGraph("Resource/image/PageOne_Image/Page_One_N3.png");

	//�X�[�gUI
	Spade = LoadGraph("Resource/image/PageOne_Image/Spade.png");
	Heart = LoadGraph("Resource/image/PageOne_Image/Heart.png");
	Diamond = LoadGraph("Resource/image/PageOne_Image/Diamond.png");
	Club = LoadGraph("Resource/image/PageOne_Image/Club.png");
	free = LoadGraph("Resource/image/PageOne_Image/Free.png");

	//�|�[�Y&���U���gUI
	Pause_Button = LoadGraph("Resource/image/PauseButton.png");
	Pause_Back = LoadGraph("Resource/image/PauseBack.png");
	Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
	Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);
	Pause_Flg = false;

	Result = LoadGraph("Resource/image/PageOne_Image/ResultBack.png");

	//SE
	pass_SE = LoadSoundMem("Resource/se/pageOne_SE/pass.wav");
	pageone_SE = LoadSoundMem("Resource/se/pageOne_SE/pageone.wav");
	card_SE_1 = LoadSoundMem("Resource/se/pageOne_SE/�g�����v�E����02.wav");
	card_SE_2 = LoadSoundMem("Resource/se/pageOne_SE/�J�[�h���̏�ɏo��.wav");
	card_SE_3 = LoadSoundMem("Resource/se/pageOne_SE/�J�[�h���߂���.wav");

	ChangeVolumeSoundMem(150, pass_SE);
	ChangeVolumeSoundMem(150, pageone_SE);
	ChangeVolumeSoundMem(150, card_SE_1);
	ChangeVolumeSoundMem(150, card_SE_2);
	ChangeVolumeSoundMem(150, card_SE_3);

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
	
	cemetery = 0;

	priority = GetRand(MAX - 1);

	for (i = 0; i < 52; i++) {
		Card_obj.push_back(Card(card_type[i], i % 13, i / 13, Deck_X, Deck_Y));
	}

	Card_obj.push_back(Card(card_type[53], 99, 5, Deck_X, Deck_Y));	//�W���[�J�[

	Card_back = card_type[52];	//�J�[�h�̗���

	Old_key = KEY_FREE;
	select = scene;
}

void PageOne::PageOne_Finalize() {
	for (i = 0; i < 54; i++) {
		DeleteGraph(card_type[i]);
	}
}

void PageOne::PageOne_Update() {

	GetMousePoint(&Mouse_X, &Mouse_Y);

	Now_key = key->GetKeyState(REQUEST_MOUSE_LEFT); //���݂̃}�E�X���{�^���̓��͏�Ԃ̎擾

	//�|�[�Y�{�^������������|�[�Y��ʂ��J���t���O��true�ɂ���
	if ((20 <= Mouse_X && Mouse_X <= 175 && 5 <= Mouse_Y && Mouse_Y <= 70) || ((450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) && Pause_Flg == true)) {
		if (Old_key != KEY_FREE && Now_key == KEY_PULL) {
			Pause_Flg = !Pause_Flg;
		}
	}

	//�Z���N�g��ʂֈړ�
	if (Pause_Flg == true) {
		if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
			if (Old_key != KEY_FREE && Now_key == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
				select->SetNext(new Scene_Select());
			}
		}
	}

	if (finish == true) {
		//�ŏ�����v���C
		if (175 <= Mouse_X && Mouse_X <= 575 && 565 <= Mouse_Y && Mouse_Y <= 685) {
			if (Old_key != KEY_FREE && Now_key == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
				select->SetNext(new Scene_PageOne());
			}
		}

		//�Z���N�g��ʂֈړ�
		if (625 <= Mouse_X && Mouse_X <= 1025 && 565 <= Mouse_Y && Mouse_Y <= 685) {
			if (Old_key != KEY_FREE && Now_key == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
				select->SetNext(new Scene_Select());
			}
		}
	}

	n++;	//�R�D����J�[�h�����Ƃ��̃N�[���^�C���i��������ƈ�a�������邩��j

	if (finish == false && Pause_Flg == false) {
		switch (priority) {
		case 0:	// player
			if (Player_setup == false) {
				if (n > 15) {
					r = GetRand(Card_obj.size());
					Card_obj[r].card_x = Player_X;
					Card_obj[r].card_y = Player_Y;
					PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
					Player_card.push_back(Card_obj[r]);
					Cemetery_card.push_back(Card_obj[r]);
					Card_obj.erase(Card_obj.begin() + r);
					if (Player_card.size() >= MAX) {
						Player_setup = true;
					}
					priority++;
					n = 0;
				}
				break;
			}
			else {
				if (flg_p == false) {
					reset = false;

					if (Field_card.empty()) {
						draw = false;
					}
					else {
						player = Player_card.size();
						for (i = 0; i < player; i++) {
							if (Player_card[i].suit == 5) {
								draw = false;
							}else if (Field_card[lead].suit == Player_card[i].suit) {
								draw = false;
							}
						}
					}

					//�v���C���[���J�[�h�����p
					if (draw == true && Card_obj.empty() == false) {
						if (n > 30) {
							if ((Mouse_X > Deck_X - (card_w * 0.7) / 2) && (Mouse_X < Deck_X + (card_w * 0.7) / 2) && (Mouse_Y > Deck_Y - (card_h * 0.7) / 2) && (Mouse_Y < Deck_Y + (card_h * 0.7) / 2)) {
								if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
									PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
									r = GetRand(Card_obj.size());
									Card_obj[r].card_x = Player_X;
									Card_obj[r].card_y = Player_Y;
									Player_card.push_back(Card_obj[r]);
									Card_obj.erase(Card_obj.begin() + r);
									n = 0;
									break;
								}

								//�f�o�b�O�p
								//color = GetColor(255, 0, 0);
							}
						}
					}

					if (Field_card.empty() == false && Field_card[0].suit == 5) {
						lead = 1;
					}
					else {
						lead = 0;
					}

					player = Player_card.size();

					//�v���C���[�̎�D����J�[�h����
					for (i = 0; i < player; i++) {

						//�R�D0������D�ɏo����J�[�h���Ȃ��ꍇ�p�X������
						if (Card_obj.empty() == true && Field_card.empty() == false && Field_card[lead].suit != Player_card[i].suit && Player_card[i].suit != 5) {
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
							if (Field_card.empty() || Field_card[0].suit == 5 || Field_card[lead].suit == Player_card[i].suit || Player_card[i].suit == 5) {
								//��D���c��񖇂��ƃy�[�W�����錾�ł���
								if (Player_card.size() == 2 && PageOne_flg == false) {
									PageOne_player = true;
								}
								else {
									PageOne_player = false;
								}

								//�y�[�W�����錾�{�^��
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
										Player_card[i].card_y = Player_Y - 50;
										if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
											PlaySoundMem(card_SE_2, DX_PLAYTYPE_BACK, TRUE);
											Field_card.push_back(Player_card[i]);

											if (Player_card[i].num == 99) {
												pri = 99;
											}

											if (Player_card[i].num == 0) {
												pri = 0;
											}

											if (pri != 0 && pri < Player_card[i].num) {
												pri = Player_card[i].num;
											}

											if (pri == 0 && Player_card[i].num != 99) {
												pri = 0;
											}

											p_pow = Player_card[i].num;
											p = i;
											priority++;
											draw = true;
											flg_p = true;
											n = 0;
											PageOne_flg = false;
											break;
										}
									}
									else {
										Player_card[i].card_y = Player_Y;
									}
								}
							}
						}
					}
					if (flg_p == true && Player_Pass_Flg != true) {
						Player_card.erase(Player_card.begin() + p);
					}
					Player_Pass_Flg = false;
				}
				else {
					priority++;
				}

				if (Player_card.empty()) {
					break;
				}
				break;
			}

		case 1:	// NPC1
			if (NPC1_setup == false) {
				if (n > 15) {
					r = GetRand(sizeof(Card_obj));
					Card_obj[r].card_x = NPC1_X;
					Card_obj[r].card_y = NPC1_Y;
					PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
					NPC_card_1.push_back(Card_obj[r]);
					Cemetery_card.push_back(Card_obj[r]);
					Card_obj.erase(Card_obj.begin() + r);
					if (NPC_card_1.size() >= MAX) {
						NPC1_setup = true;
					}
					priority++;
					n = 0;
				}
				break;
			}
			else {
				if (flg_1 == false) {
					reset = false;

					if (Field_card.empty()) {
						draw = false;
					}
					else {
						npc_1 = NPC_card_1.size();
						for (i = 0; i < npc_1; i++) {
							if (NPC_card_1[i].suit == 5) {
								draw = false;
							}
							if (Field_card[lead].suit == NPC_card_1[i].suit) {
								draw = false;
							}
						}
					}

					//NPC���J�[�h�����p
					if (draw == true && Card_obj.empty() == false) {
						if (n > 30) {
							r = GetRand(Card_obj.size());
							PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
							NPC_card_1.push_back(Card_obj[r]);
							Card_obj.erase(Card_obj.begin() + r);
							n = 0;
							break;
						}
					}

					//��D���c��񖇂��ƃy�[�W�����錾�ł���
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

					//��̃X�[�g�̔��������߂Ă���
					if (Field_card.empty() == false && Field_card[0].suit == 5) {
						lead = 1;
					}
					else {
						lead = 0;
					}

					npc_1 = NPC_card_1.size();

					//NPC�̎�D����J�[�h����
					for (i = 0; i < npc_1; i++) {

						//�R�D0������D�ɏo����J�[�h���Ȃ��ꍇ�p�X������i�蓮�j
						if (Card_obj.empty() == true && Field_card.empty() == false && Field_card[lead].suit != NPC_card_1[i].suit && NPC_card_1[i].suit != 5) {

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
								NPC1_Pass_Flg = false;
							}
						}
						else {
							if (n > 90) {

								if (Field_card.empty() || Field_card[0].suit == 5 || Field_card[lead].suit == NPC_card_1[i].suit || NPC_card_1[i].suit == 5) {

									if (PageOne_npc1 == false) {
										PlaySoundMem(card_SE_2, DX_PLAYTYPE_BACK, TRUE);
										Field_card.push_back(NPC_card_1[i]);

										if (NPC_card_1[i].num == 99) {
											pri = 99;
										}

										if (NPC_card_1[i].num == 0) {
											pri = 0;
										}

										if (pri != 0 && pri < NPC_card_1[i].num) {
											pri = NPC_card_1[i].num;
										}

										if (pri == 0 && NPC_card_1[i].num != 99) {
											pri = 0;
										}

										n1_pow = NPC_card_1[i].num;
										n1 = i;
										priority++;
										draw = true;
										flg_1 = true;
										n = 0;
										PageOne_flg = false;
									}
								}
							}
						}
					}
					if (flg_1 == true) {
						NPC_card_1.erase(NPC_card_1.begin() + n1);
					}
				}
				else {
					priority++;
				}

				if (NPC_card_1.empty()) {
					break;
				}
				break;
			}

		case 2:	// NPC2
			if (NPC2_setup == false) {
				if (n > 15) {
					r = GetRand(Card_obj.size());
					Card_obj[r].card_x = NPC2_X;
					Card_obj[r].card_y = NPC2_Y;
					PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
					NPC_card_2.push_back(Card_obj[r]);
					Cemetery_card.push_back(Card_obj[r]);
					Card_obj.erase(Card_obj.begin() + r);
					if (NPC_card_2.size() >= MAX) {
						NPC2_setup = true;
					}
					priority++;
					n = 0;
				}
				break;
			}
			else {

				if (flg_2 == false) {
					reset = false;

					if (Field_card.empty()) {
						draw = false;
					}
					else {
						npc_2 = NPC_card_2.size();
						for (i = 0; i < npc_2; i++) {
							if (NPC_card_2[i].suit == 5) {
								draw = false;
							}
							if (Field_card[lead].suit == NPC_card_2[i].suit) {
								draw = false;
							}
						}
					}

					//NPC���J�[�h�����p
					if (draw == true && Card_obj.empty() == false) {
						if (n > 30) {
							r = GetRand(Card_obj.size());
							PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
							NPC_card_2.push_back(Card_obj[r]);
							Card_obj.erase(Card_obj.begin() + r);
							n = 0;
							break;
						}
					}

					//��D���c��񖇂��ƃy�[�W�����錾�ł���
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

					//��̃X�[�g�̔��������߂Ă���
					if (Field_card.empty() == false && Field_card[0].suit == 5) {
						lead = 1;
					}
					else {
						lead = 0;
					}

					npc_2 = NPC_card_2.size();

					//NPC�̎�D����J�[�h����
					for (i = 0; i < npc_2; i++) {

						//�R�D0������D�ɏo����J�[�h���Ȃ��ꍇ�p�X������i�蓮�j
						if (Card_obj.empty() == true && Field_card.empty() == false && Field_card[lead].suit != NPC_card_2[i].suit && NPC_card_2[i].suit != 5) {
							if (50 < n && n <= 90) {
								NPC2_Pass_Flg = true;
							}

							if (n > 90) {
								PlaySoundMem(pass_SE, DX_PLAYTYPE_BACK, TRUE);
								flg_2 = true;
								priority++;
								n = 0;
								NPC2_Pass_Flg = false;
							}
						}
						else {
							if (n > 90) {
								if (Field_card.empty() || Field_card[0].suit == 5 || Field_card[lead].suit == NPC_card_2[i].suit || NPC_card_2[i].suit == 5) {
									if (PageOne_npc2 == false) {
										PlaySoundMem(card_SE_2, DX_PLAYTYPE_BACK, TRUE);
										Field_card.push_back(NPC_card_2[i]);

										if (NPC_card_2[i].num == 99) {
											pri = 99;
										}

										if (NPC_card_2[i].num == 0) {
											pri = 0;
										}

										if (pri != 0 && pri < NPC_card_2[i].num) {
											pri = NPC_card_2[i].num;
										}

										if (pri == 0 && NPC_card_2[i].num != 99) {
											pri = 0;
										}

										n2_pow = NPC_card_2[i].num;
										n2 = i;
										priority++;
										draw = true;
										flg_2 = true;
										n = 0;
										PageOne_flg = false;
									}
								}
							}
						}
					}
					if (flg_2 == true) {
						NPC_card_2.erase(NPC_card_2.begin() + n2);
					}
				}
				else {
					priority++;
				}

				if (NPC_card_2.empty()) {
					break;
				}
				break;
			}

		case 3:	// NPC3
			if (NPC3_setup == false) {
				if (n > 15) {
					r = GetRand(Card_obj.size());
					Card_obj[r].card_x = NPC3_X;
					Card_obj[r].card_y = NPC3_Y;
					PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
					NPC_card_3.push_back(Card_obj[r]);
					Cemetery_card.push_back(Card_obj[r]);
					Card_obj.erase(Card_obj.begin() + r);
					if (NPC_card_3.size() >= MAX) {
						NPC3_setup = true;
					}
					priority++;
					n = 0;
				}
				break;
			}
			else {
				if (flg_3 == false) {
					reset = false;

					if (Field_card.empty()) {
						draw = false;
					}
					else {
						npc_3 = NPC_card_3.size();
						for (i = 0; i < npc_3; i++) {
							if (NPC_card_3[i].suit == 5) {
								draw = false;
							}
							if (Field_card[lead].suit == NPC_card_3[i].suit) {
								draw = false;
							}
						}
					}

					//NPC���J�[�h�����p
					if (draw == true && Card_obj.empty() == false) {
						if (n > 30) {
							r = GetRand(Card_obj.size());
							PlaySoundMem(card_SE_1, DX_PLAYTYPE_BACK, TRUE);
							NPC_card_3.push_back(Card_obj[r]);
							Card_obj.erase(Card_obj.begin() + r);
							n = 0;
							break;
						}
					}

					//��D���c��񖇂��ƃy�[�W�����錾�ł���
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

					//��̃X�[�g�̔��������߂Ă���
					if (Field_card.empty() == false && Field_card[0].suit == 5) {
						lead = 1;
					}
					else {
						lead = 0;
					}

					npc_3 = NPC_card_3.size();

					//NPC�̎�D����J�[�h����
					for (i = 0; i < npc_3; i++) {

						//�R�D0������D�ɏo����J�[�h���Ȃ��ꍇ�p�X������i�蓮�j
						if (Card_obj.empty() == true && Field_card.empty() == false && Field_card[lead].suit != NPC_card_3[i].suit && NPC_card_3[i].suit != 5) {
							if (50 < n && n <= 90) {
								NPC3_Pass_Flg = true;
							}

							if (n > 90) {
								PlaySoundMem(pass_SE, DX_PLAYTYPE_NORMAL, TRUE);
								flg_3 = true;
								priority++;
								n = 0;
								NPC3_Pass_Flg = false;
							}
						}
						else {
							if (n > 90) {
								if (Field_card.empty() || Field_card[0].suit == 5 || Field_card[lead].suit == NPC_card_3[i].suit || NPC_card_3[i].suit == 5) {

									if (PageOne_npc3 == false) {
										PlaySoundMem(card_SE_2, DX_PLAYTYPE_BACK, TRUE);
										Field_card.push_back(NPC_card_3[i]);

										if (NPC_card_3[i].num == 99) {
											pri = 99;
										}

										if (NPC_card_3[i].num == 0) {
											pri = 0;
										}

										if (pri != 0 && pri < NPC_card_3[i].num) {
											pri = NPC_card_3[i].num;
										}

										if (pri == 0 && NPC_card_3[i].num != 99) {
											pri = 0;
										}

										n3_pow = NPC_card_3[i].num;

										n3 = i;
										priority++;
										draw = true;
										flg_3 = true;
										n = 0;
										PageOne_flg = false;
									}
								}
							}
						}
					}
					if (flg_3 == true) {
						NPC_card_3.erase(NPC_card_3.begin() + n3);
					}
				}
				else {
					priority++;
				}

				if (NPC_card_3.empty()) {
					break;
				}
				break;
			}

		case 4:
		default:
			// �S���̎�Ԃ�������Ă邩�H
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
				else if(180 <= n) {

					if (pri == p_pow) {
						priority = 0;
						pri = 1;
					}
					if (pri == n1_pow) {
						priority = 1;
						pri = 1;
					}
					if (pri == n2_pow) {
						priority = 2;
						pri = 1;
					}
					if (pri == n3_pow) {
						priority = 3;
						pri = 1;
					}

					flg_p = false;
					flg_1 = false;
					flg_2 = false;
					flg_3 = false;

					cemetery = Field_card.size();
					
					for (i = 0; i < cemetery; i++) {
						Cemetery_card.push_back(Field_card[i]);
					}

					Field_card.erase(Field_card.begin(), Field_card.end());
					Field_X = 500;
					if (Card_obj.empty() == true) {
						Card_obj = Cemetery_card;
						Cemetery_card.erase(Cemetery_card.begin(), Cemetery_card.end());
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

	DrawRotaGraph(640, 360, 1.0, 0, background, TRUE);

	if (reset == false && Player_setup == true && NPC1_setup == true && NPC2_setup == true && NPC3_setup == true) {

		switch (priority) {
		case 0:
			DrawFormatString(50, 350, GetColor(255, 255, 255), "��ԁF�v���C���[");
			if (Card_obj.empty() == false && draw == true) {
				DrawFormatString(250, 450, GetColor(100, 100, 255), "�J�[�h�������Ă�������");
			}
			else if (Player_Pass_Flg == true) {
				DrawFormatString(250, 450, GetColor(100, 100, 255), "�p�X�����Ă�������");
			}
			break;
		case 1:
			DrawFormatString(50, 350, GetColor(255, 255, 255), "��ԁFNPC�P��");
			break;
		case 2:
			DrawFormatString(50, 350, GetColor(255, 255, 255), "��ԁFNPC�Q��");
			break;
		case 3:
			DrawFormatString(50, 350, GetColor(255, 255, 255), "��ԁFNPC�R��");
			break;
		}

		DrawFormatString(1000, 375, GetColor(255, 255, 255), "���݂̃X�[�g");
		if (Field_card.empty() == false) {
			switch (Field_card[0].suit) {
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


	//�R�D�̕`��
	if (Card_obj.empty() == false) {
		DrawRotaGraph(Deck_X, Deck_Y, 0.7, 0, Card_back, TRUE);
	}

	//��ɏo�Ă���J�[�h�̕`��
	for (i = 0; i < field; i++) {
		DrawRotaGraph(Field_X + i * 100, Field_Y, 0.5, 0, Field_card[i].img, TRUE);
	}

	//�v���C���[�̎�D�`��
	for (i = 0; i < player; i++) {
		DrawRotaGraph(Player_card[i].card_x + (i % 10) * (card_w * 0.5), Player_card[i].card_y + (i / 10) * (card_h * pow(0.5, 2)), 0.5, 0, Player_card[i].img, TRUE);
	}

	//�p�X��UI
	if (Player_Pass_Flg == true) {
		DrawGraph(890, 440, Player_Pass_Icon, true);
	}

	//�y�[�W�����{�^��
	if (PageOne_player == true) {
		DrawGraph(500, 400, Player_PageOne_Icon, true);
	}
	//��������UI
	if (Player_setup == true && Player_card.size() == 0 && n >= 30) {
		DrawRotaGraph(600, 300, 1.0, 0, Result, TRUE);
		DrawRotaGraph(600, 300, 1.3, 0, PlayerCrown, TRUE);
		finish = true;
	}


	//NPC�P���̎�D�`��
	for (i = 0; i < npc_1; i++) {
		DrawRotaGraph(NPC1_X + (i % 5) * (card_w * 0.3), NPC1_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, Card_back, TRUE);
		//DrawRotaGraph(NPC1_X + (i % 5) * (card_w * 0.3), NPC1_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_1[i].img, TRUE);
	}
	//�p�X��UI
	if (NPC1_Pass_Flg == true) {
		DrawGraph(0, 175, NPC1_Pass_Icon, true);
	}
	//�y�[�W�����錾����UI
	if (PageOne_npc1 == true) {
		DrawGraph(0, 175, NPC1_PageOne_Icon, true);
	}
	//��������UI
	if (NPC1_setup == true && NPC_card_1.size() == 0 && n >= 30) {
		DrawRotaGraph(600, 300, 1.0, 0, Result, TRUE);
		DrawRotaGraph(600, 300, 1.3, 0, NPC1_Icon, TRUE);
		finish = true;
	}

	//NPC�Q���̎�D�`��
	for (i = 0; i < npc_2; i++) {
		DrawRotaGraph(NPC2_X + (i % 5) * (card_w * 0.3), NPC2_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, Card_back, TRUE);
		//DrawRotaGraph(NPC2_X + (i % 5) * (card_w * 0.3), NPC2_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_2[i].img, TRUE);
	}
	//�p�X��UI
	if (NPC2_Pass_Flg == true) {
		DrawGraph(400, 105, NPC2_Pass_Icon, true);
	}
	//�y�[�W�����錾����UI
	if (PageOne_npc2 == true) {
		DrawGraph(400, 105, NPC2_PageOne_Icon, true);
	}
	//��������UI
	if (NPC2_setup == true && NPC_card_2.size() == 0 && n >= 30) {
		DrawRotaGraph(600, 300, 1.0, 0, Result, TRUE);
		DrawRotaGraph(600, 300, 1.3, 0, NPC2_Icon, TRUE);
		finish = true;
	}

	//NPC�R���̎�D�`��
	for (i = 0; i < npc_3; i++) {
		DrawRotaGraph(NPC3_X + (i % 5) * (card_w * 0.3), NPC3_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, Card_back, TRUE);
		//DrawRotaGraph(NPC3_X + (i % 5) * (card_w * 0.3), NPC3_Y + (i / 5) * (card_h * pow(0.3, 2)), 0.3, 0, NPC_card_3[i].img, TRUE);
	}
	//�p�X��UI
	if (NPC3_Pass_Flg == true) {
		DrawGraph(800, 175, NPC3_Pass_Icon, true);
	}
	//�y�[�W�����錾����UI
	if (PageOne_npc3 == true) {
		DrawGraph(800, 175, NPC3_PageOne_Icon, true);
	}
	//��������UI
	if (NPC3_setup == true && NPC_card_3.size() == 0 && n >= 30) {
		DrawRotaGraph(600, 300, 1.0, 0, Result, TRUE);
		DrawRotaGraph(600, 300, 1.3, 0, NPC3_Icon, TRUE);
		finish = true;
	}

	if (finish == false) {
		DrawFormatString(25, 100, GetColor(255, 255, 255), "NPC");
		DrawFormatString(25, 125, GetColor(255, 255, 255), "�P��");

		DrawFormatString(450, 50, GetColor(255, 255, 255), "NPC");
		DrawFormatString(450, 75, GetColor(255, 255, 255), "�Q��");

		DrawFormatString(875, 100, GetColor(255, 255, 255), "NPC");
		DrawFormatString(875, 125, GetColor(255, 255, 255), "�R��");

		DrawFormatString(0, 665, GetColor(255, 255, 255), "�R�D:�c��%d��", Card_obj.size());
	}

	//�|�[�Y�{�^��
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

	//�f�o�b�O�p
	//DrawBox(890, 440,980, 500, color, TRUE);
	//DrawFormatString(900, 450, GetColor(255, 0, 0), "�p�X");
	//DrawGraph(0, 175, NPC_Pass_Icon, true);
	//DrawGraph(500, 400, NPC_PageOne_Icon, true);
}