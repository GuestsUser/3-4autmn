#pragma once
#include"BJ_Head.h"


class BlackJack :public Scene {

private:

  int pose_img,game_img,pose_button_img;
  int select_img[4], continue_img[5];

  int hit_flg;
  int pose_x, pose_y, pose_h, pose_w;
  int select_x[2], select_y[2], select_w, select_h;

  int sct_pos_x, sct_pos_y, sct_w, sct_h;
  int ctn_pos_x;
  double sct_rate, ctn_rate;
  bool sct_flg,nx_flg;

  int bet_img;
  int bet_x, bet_y, bet_w, bet_h;
  float bet_r;
  bool bet;
  bool bet_flg;

  float wait_time;
  float time_count;

  bool game_endflg;
  bool next_flg;
  bool now_game_flg;
  bool pose_flg, ptn,ctn,scn;
  bool st;

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
  int Bottun_SE_;

  int BGM;	//BGM保存用変数
public:

  BlackJack();
  ~BlackJack();

  bool Wait_Time(float);

  void Initialize();
  void Update();
  void Draw();
  void Finalize();

};
