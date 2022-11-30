#pragma once
#include"BJ_Head.h"


class BlackJack :public Scene {

private:

  int pose_img,game_img,pose_button_img;
  int select_img[2], continue_img[2];

  int hit_flg;
  int pose_x, pose_y, pose_h, pose_w;
  int select_x[2], select_y[2], select_w, select_h;

  /*苦し紛れのベット*/
  int bet_x, bet_y, bet_w, bet_h;
  bool bet_flg;
//  if (Player::ButtonHit(bet_x, bet_y, bet_w, bet_h)) {
//  bet_flg = true;
//}
//  bet_w = 60;
//  bet_h = 60;  bet_x = 420;  bet_y = 650;
  /*苦し紛れのベット*/

  float wait_time;
  float time_count;

  bool game_endflg;
  bool next_flg;
  bool now_game_flg;
  bool pose_flg, ptn,ctn,scn;

  std::string next;

  /*カードシューオブジェクトの生成*/
  Shoe* shoe;
  /*プレイヤーオブジェクトの生成*/
  Player* player;
  /*ディーラーオブジェクトの生成*/
  Dealer* dealer;

  /*slider*/
  class Slider* slider;
  bool isClick;
  int mousePosX;
  int mousePosY;
  /*slider*/

public:

  BlackJack();
  ~BlackJack();

  bool Wait_Time(float);

  void Initialize();
  void Update();
  void Draw();
  void Finalize();

};
