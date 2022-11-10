#include"BJ_Head.h"

BlackJack::BlackJack() {

  shoe = new Shoe();
  player = new Player();
  dealer = new Dealer();

  game_endflg = false;
  next_flg = true;

  hit_flg = 0;

  end_img = LoadGraph("Resource/image/BJ_Image/BJ_Help.png");
  game_img = LoadGraph("Resource/image/BJ_Image/BJ_Game.png");
  title_img = LoadGraph("Resource/image/BJ_Image/BJ_Title.png");

  shoe->Inisialize();
  player->Initialize();
  dealer->Initialize();
}

BlackJack::~BlackJack() {

  delete shoe;
  delete player;
  delete dealer;

  BlackJack::Finalize();

}

void BlackJack::Initialize() {

  shoe->Inisialize();
  player->Initialize();
  dealer->Initialize();
  next_flg = true;

  hit_flg = 0;

}

void BlackJack::Update() {

  //player->Update();
    /*ゲームを開始 or 続けるか判定*/

  if (next_flg) {

    BlackJack::Initialize();
    next_flg = false;

  }
  if (hit_flg < 1) {
    dealer->Hit(shoe);
    hit_flg++;
  }
  if (player->Play(shoe)) {

    dealer->Play(shoe);
    player->Score(*player, *dealer);

  }
  else {
    player->Score(*player, *dealer);
  }
  if (!game_endflg) {

    if (player->ButtonHit(280,480,20,40)) {

      next_flg = true;

    }
    if (player->ButtonHit(340,480,20,40)) {

      game_endflg = true;

    }

  }

}
void BlackJack::Draw() {

  //DrawGraph(0,0,title_img,true);
  DrawGraph(0,0,game_img,true);
  //DrawGraph(0,0,end_img,true);

  player->Draw();
  dealer->Draw();

  DrawFormatString(550, 100, 0xffffff, "ゲーム画面");

  DrawFormatString(100, 80, 0xffffff, "ゲームを開始しますか？\n");
  DrawFormatString(100, 100, 0xffffff, "==============\n");
  DrawFormatString(100, 120, 0xffffff, "BLACK JACK\n");
  DrawFormatString(100, 140, 0xffffff, "==============\n");
  DrawFormatString(100, 160, 0xffffff, "player\n");
  //DrawFormatString(100, 180, 0xffffff, "==============\n");
  DrawFormatString(100, 200, 0xffffff, "==============\n");
  DrawFormatString(100, 220, 0xffffff, "dealer\n");
  DrawFormatString(100, 240, 0xffffff, "==============\n");
  DrawFormatString(100, 260, 0xffffff, "==============\n");
  if (!next_flg) {
    DrawFormatString(100, 480, 0xffffff, "ゲームを続けますか？ yes or no\n");
  }
  if (game_endflg) {
    DrawFormatString(100, 500, 0xffffff, "ゲームを終了します\n");
  }


}

void BlackJack::Finalize() {

  DeleteGraph(title_img);
  DeleteGraph(game_img);
  DeleteGraph(end_img);

}
