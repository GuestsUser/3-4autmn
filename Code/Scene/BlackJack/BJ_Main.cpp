#include"BJ_Head.h"

BlackJack::BlackJack() {

  shoe = new Shoe();
  dealer = new Dealer();
  player = new Player();
  slider = new Slider();

  game_endflg = false;
  next_flg = true;
  now_game_flg = false;

  hit_flg = 0;
  time_count = 0.0f;

  end_img = LoadGraph("Resource/image/BJ_Image/BJ_Help.png");
  game_img = LoadGraph("Resource/image/BJ_Image/BJ_Game.png");
  title_img = LoadGraph("Resource/image/BJ_Image/BJ_Title.png");

  shoe->Inisialize();
  dealer->Initialize();
  player->Initialize();
}

BlackJack::~BlackJack() {

  delete shoe;
  delete dealer;
  delete player;
  delete slider;

  BlackJack::Finalize();

}

void BlackJack::Initialize() {

  shoe->Inisialize();
  dealer->Initialize();
  player->Initialize();
  slider->Inisialize();
  slider->SetMaxValue(player->P_MaxCoin());
  next_flg = true;
  now_game_flg = true;
  time_count = 0;

  hit_flg = 0;

}

void BlackJack::Update() {

  GetMousePoint(&mousePosX, &mousePosY);
  isClick = GetMouseInput() == MOUSE_INPUT_LEFT;
  slider->Update(mousePosX, mousePosY, isClick);
  if (player->P_MaxCoin() < 1) {

    game_endflg = true;
    next_flg = false;

  }
    /*ゲームを開始 or 続けるか判定*/
  if (next_flg) {

    if (player->Bet_Flg()) {
      player->Set_Bet(slider->GetValue());
    }
    //player->Set_Bet(slider->GetValue());
    BlackJack::Initialize();
    next_flg = false;

  }
  if (!game_endflg) {

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
    if (player->ButtonHit(700,340,60,40)) {

      next_flg = true;

    }
    if (player->ButtonHit(760,340,60,40)) {

      game_endflg = true;
      //SetNext(nullptr);
      SetNext(new Scene_Select());

    }

  }

}
void BlackJack::Draw() {
  
  //DrawGraph(0,0,title_img,true);
  DrawGraph(0,0,game_img,true);
  //DrawGraph(0,0,end_img,true);
  SetFontSize(24);
  if (game_endflg) {
    if (BlackJack::Wait_Time(0.5f)) {
      //exit(0);
      SetNext(new Scene_Select());
    }
    else {

      DrawFormatString(450, 340, 0xffffff, "セレクト画面に戻ります\n");

    }
  }
  else {

    if (!player->Now_Game()) {
      DrawFormatString(450, 340, 0xffffff, "ゲームを続けますか？ yes or no\n");
      SetFontSize(DEFAULT_FONT_SIZE);
    }
    /*slider*/
    slider->Draw();
    /*slider*/
    player->Draw();
    dealer->Draw();

    SetFontSize(32);
    DrawFormatString(500, 630, 0xffffff, "掛金：%d", (int)slider->GetValue());
  }
  SetFontSize(DEFAULT_FONT_SIZE);

}

void BlackJack::Finalize() {

  DeleteGraph(title_img);
  DeleteGraph(game_img);
  DeleteGraph(end_img);

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

  //return this;

}
