﻿#include"BJ_Head.h"

BlackJack::BlackJack() {

  shoe = new Shoe();
  dealer = new Dealer();
  player = new Player();
  slider = new Slider();

  game_endflg = false;
  next_flg = true;
  now_game_flg = false;
  pose_flg = ptn = scn = ctn = false;

  bet_r = 1;
  bet_w = 105;
  bet_h = 42;
  bet_x = 380;
  bet_y = 650;
  bet_flg = false;


  hit_flg = 0;
  time_count = 0.0f;

  pose_x = 0;
  pose_y = 0;
  pose_w = 180;
  pose_h = 80;
  select_x[0] = 220;
  select_y[0] = 480;
  select_x[1] = 630;
  select_y[1] = 480;
  select_w = 400;
  select_h = 120;

  sct_pos_x = 940;
  sct_pos_y = 350;
  sct_w = 150;
  sct_h = 60;
  ctn_pos_x = 780;
  sct_rate = ctn_rate = 1;
  sct_flg = false;
  //DrawRotaGraph(780, 350, 1, 0, continue_img[2], true);
  //DrawRotaGraph(940, 350, 1.2, 0, select_img[2], true);

  game_img = LoadGraph("Resource/image/BJ_Image/BJ_Game.png");
  pose_img = LoadGraph("Resource/image/BJ_Image/BJ_PauseBack.png");
  pose_button_img = LoadGraph("Resource/image/BJ_Image/BJ_PauseButton.png");
  LoadDivGraph("Resource/image/BJ_Image/BJ_MenuButton.png",2,2,1,400,120,select_img);
  LoadDivGraph("Resource/image/BJ_Image/BJ_Continue_Button.png",2,2,1,400,120,continue_img);
  select_img[2] = LoadGraph("Resource/image/BJ_Image/End_Button.png");
  continue_img[2] = LoadGraph("Resource/image/BJ_Image/Continue_Button.png");
  select_img[3] = LoadGraph("Resource/image/BJ_Image/End_Button_2.png");
  continue_img[3] = LoadGraph("Resource/image/BJ_Image/Continue_Button_2.png");
  continue_img[4] = LoadGraph("Resource/image/BJ_Image/Continue.png");
  bet_img = LoadGraph("Resource/image/BJ_Image/Bet_105.png");

  shoe->Inisialize();
  dealer->Initialize();
  player->Initialize();
  Pose_Initialize();
}

BlackJack::~BlackJack() {

  delete shoe;
  delete dealer;
  delete player;
  delete slider;

  BlackJack::Finalize();

}

void BlackJack::Initialize() {

  Pose_Initialize();
  shoe->Inisialize();
  dealer->Initialize();
  player->Initialize();
  slider->Inisialize();
  slider->SetMaxValue(player->P_MaxCoin());
  next_flg = true;
  nx_flg = false;
  now_game_flg = true;
  time_count = 0;
  bet = false;
  hit_flg = 0;

}

void BlackJack::Update() {
  Pose_Update();
  GetMousePoint(&mousePosX, &mousePosY);
  isClick = GetMouseInput() == MOUSE_INPUT_LEFT;
  slider->Update(mousePosX, mousePosY, isClick);
  pose_flg = pose;

  player->Update();

  /*旧ポーズボタン*/
  //ptn = player->ButtonHit(pose_x, pose_y, pose_w, pose_h);
  //scn = player->ButtonHit(select_x[0], select_y[0], select_w, select_h);
  //ctn = player->ButtonHit(select_x[1], select_y[1], select_w, select_h);
  //if (ptn) {
  //  pose_flg = !pose_flg;
  //}
  //if (ctn && pose_flg) {
  //  pose_flg = false;
  //}
  /*旧ポーズボタン*/

  if (player->ButtonHit(bet_x, bet_y, bet_w, bet_h) && !bet) {

    bet = true;
    bet_r = 1.2;
  }
  else {
    bet_r = 1;
  }
  if (bet && !bet_flg) {
    if (BlackJack::Wait_Time(0.5)) {
      player->Bet_Flg(bet_flg);
      player->Set_Bet(slider->GetValue());
      bet_flg = true;
    }
  }

  if (player->P_MaxCoin() < 0 || end) {

    game_endflg = true;
    next_flg = false;

  }
    /*ゲームを開始 or 続けるか判定*/
  if (!pose_flg) {


    if (next_flg) {

      BlackJack::Initialize();
      next_flg = false;
      bet_flg = false;

    }
    if (!game_endflg && bet_flg) {

      if (hit_flg < 1) {
        player->Hit(shoe);
        dealer->Hit(shoe);
        hit_flg++;
      }
      if (player->Play(shoe)) {

        hit_flg = 2;
        dealer->Play(shoe);
        player->Score(*player, *dealer);
      }
      else {
        player->Score(*player, *dealer);
        if (hit_flg == 1 && !player->Now_Game()) {
          hit_flg++;
          dealer->Hit(shoe);
        }
      }

      if (player->ButtonHit(700, 320, sct_w, sct_h)) {
        ctn_rate = 1.2;
        nx_flg = true;

      }
      else ctn_rate = 1;
      if (nx_flg) {
        if (BlackJack::Wait_Time(0.1))next_flg = true;
      }
      if (player->ButtonHit(860, 320, sct_w, sct_h)) {

        sct_rate = 1.2;
        sct_flg = true;

      }
      else sct_rate = 1;
      if (sct_flg) {
        if (BlackJack::Wait_Time(0.1f)) {
          game_endflg = true;
        }
      }

    }
  }
}
void BlackJack::Draw() {
  DrawGraph(0, 0, game_img, true);

  /*旧ポーズ画面*/
  //if (pose_flg) {
  //  //DrawGraph(200, 150, pose_img, true);
  //  //DrawGraph(220, 480, select_img[0], true);
  //  //DrawGraph(630, 480, continue_img[0], true);
  //}
  //DrawGraph(0,0,pose_button_img,true);
  /*旧ポーズ画面*/

  Pose_Draw();
  SetFontSize(24);
  if (game_endflg || end) {
    if (BlackJack::Wait_Time(0.5f)) {
      //exit(0);
      SetNext(new Scene_Select());
    }
    else {

      if(!pose_flg)DrawFormatString(450, 340, 0xffffff, "セレクト画面に戻ります\n");
        sct_rate = 1.2;

    }
  }
  else if(!pose_flg) {
    dealer->Update();
    SetFontSize(32);
    DrawFormatString(500, 680, 0xffffff, "所持金：%d", player->P_MaxCoin());
    SetFontSize(DEFAULT_FONT_SIZE);
    if (!player->Now_Game()) {
      //SetFontSize(24);
      //DrawFormatString(450, 340, 0xffffff, "ゲームを続けますか？ yes or no\n");
      //SetFontSize(DEFAULT_FONT_SIZE);
      DrawGraph(240, 320, continue_img[4], true);

      DrawRotaGraph(ctn_pos_x, sct_pos_y,ctn_rate,0, continue_img[2], true);
      DrawRotaGraph(sct_pos_x, sct_pos_y,sct_rate,0, select_img[2], true);
    }
    /*slider*/
    if (!bet_flg) {
      SetFontSize(32);
      slider->Draw();
      //DrawFormatString(420, 650, 0xffffff, "Bet");
      DrawRotaGraph(bet_x + bet_w / 2, bet_y + bet_h / 2 , bet_r, 0, bet_img, true);
      SetFontSize(DEFAULT_FONT_SIZE);
    }
    else {
      /*slider*/
      player->Draw();
      dealer->Draw();
    }
    
    SetFontSize(32);

  }

  SetFontSize(DEFAULT_FONT_SIZE);
  //DrawFormatString(80, 280, 0xffffff, "pose %d", pose);

}

void BlackJack::Finalize() {

  DeleteGraph(pose_img);
  DeleteGraph(game_img);
  DeleteGraph(pose_button_img);

}

bool BlackJack::Wait_Time(float time) {
  wait_time = time * FPS;

  while (1) {
    if (time_count < wait_time) {

      time_count++;
      return false;
    }
    else
    {
      return true;
      break;
    }
  }

}
