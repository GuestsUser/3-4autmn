#include"BJ_Head.h"

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
  Bottun_SE_ = LoadSoundMem("Resource/se/pageOne_SE/トランプ・引く02.wav");
  ChangeVolumeSoundMem(150, Bottun_SE_);
  BGM = LoadSoundMem("Resource/se/pageOne_SE/フルハウス_2.wav");

  ChangeVolumeSoundMem(255 * 80 / 100, BGM);
  shoe->Inisialize();
  dealer->Initialize();
  player->Initialize();
  Pose_Initialize();
}

BlackJack::~BlackJack() {

  DeleteGraph(game_img);
  DeleteGraph(pose_img);
  DeleteGraph(pose_button_img);
  DeleteGraph(bet_img);
  DeleteSoundMem(BGM);

  for (auto &i: select_img) {

    DeleteGraph(i);

  }
  for (auto &i: continue_img) {

    DeleteGraph(i);

  }

  delete shoe;
  delete dealer;
  delete player;
  delete slider;

}

void BlackJack::Initialize() {

  Pose_Initialize();
  shoe->Inisialize();
  dealer->Initialize();
  player->Initialize();
  slider->Inisialize();
  //slider->SetMaxValue(player->P_MaxCoin());
  next_flg = true;
  nx_flg = false;
  now_game_flg = true;
  time_count = 0;
  bet = false;
  hit_flg = 0;
  st = false;

}

void BlackJack::Update() {
  if (CheckSoundMem(BGM) == false) {
    PlaySoundMem(BGM, DX_PLAYTYPE_BACK, TRUE);
  }
  Pose_Update();
  GetMousePoint(&mousePosX, &mousePosY);
  isClick = GetMouseInput() == MOUSE_INPUT_LEFT;
  slider->Update(mousePosX, mousePosY, isClick);
  pose_flg = pose;


  if (player->ButtonHit(bet_x, bet_y, bet_w, bet_h) && !bet) {

    PlaySoundMem(Bottun_SE_, DX_PLAYTYPE_BACK, TRUE);
    bet = true;
    bet_r = 1.2;
  }
  else {
    bet_r = 1;
  }
  if (bet && !bet_flg) {
    if (BlackJack::Wait_Time(0.5)) {
      bet_flg = true;
      player->Bet_Flg(bet_flg);
      player->Set_Bet(slider->GetValue());
    }
  }

  if ((player->P_MaxCoin() <= 0 && !player->Now_Game() && next_flg) || end) {

    game_endflg = true;
    next_flg = false;

  }
  //if (player->P_MaxCoin() < slider->GetValue()) {

  //  slider->SetValue(player->P_MaxCoin());

  //}
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
      if (player->Play(shoe,dealer) && !player->P_BJ()) {

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

      if (player->ButtonHit(700, 320, sct_w, sct_h) && !nx_flg && !player->Now_Game()) {
        ctn_rate = 1.2;
        nx_flg = true;

      }
      else ctn_rate = 1;
      if (nx_flg) {
        if (BlackJack::Wait_Time(1))next_flg = true;
      }
      if (player->ButtonHit(860, 320, sct_w, sct_h) && !st && !player->Now_Game()) {

        sct_rate = 1.2;
        st = true;

      }
      else sct_rate = 1;
      if (st) {
        if (BlackJack::Wait_Time(1)) {

          sct_flg = true;
        }
      }
      if (sct_flg) {

          game_endflg = true;
      }

    }
  }
}
void BlackJack::Draw() {

  DrawGraph(0, 0, game_img, true);

  Pose_Draw();
  SetFontSize(24);
  if (game_endflg || end) {
    pose_flg = false;
    if (BlackJack::Wait_Time(3.0f)) {
      SetNext(new Scene_Select());
    }
    else {

        SetFontSize(100);
        if (!pose_flg) {
          if (player->P_MaxCoin() <= 0) {
            DrawFormatString(60, 250, 0xff00ff, "所持金がなくなりました\nセレクト画面に戻ります\n");
          }
          else {
            DrawFormatString(60, 250, 0xff00ff, "セレクト画面に戻ります\n");
          }
        }
        sct_rate = 1.2;
        SetFontSize(DEFAULT_FONT_SIZE);

    }
  }
  else if(!pose_flg) {
    SetFontSize(32);
    DrawFormatString(500, 680, 0xffffff, "所持金：%d", player->P_MaxCoin());
    SetFontSize(DEFAULT_FONT_SIZE);
    if (!player->Now_Game()) {
      if (player->P_MaxCoin() <= 0) {
        if (BlackJack::Wait_Time(1))game_endflg = true;
      }
      else {
        DrawGraph(240, 320, continue_img[4], true);
        DrawRotaGraph(ctn_pos_x, sct_pos_y, ctn_rate, 0, continue_img[2], true);
        DrawRotaGraph(sct_pos_x, sct_pos_y, sct_rate, 0, select_img[2], true);
      }

    }
    /*slider*/
    if (!bet_flg) {
      SetFontSize(32);
      slider->Draw();
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
