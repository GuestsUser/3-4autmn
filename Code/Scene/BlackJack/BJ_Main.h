#pragma once
#include"BJ_Head.h"


class BlackJack :public Scene {

private:

  int title_img,game_img,end_img;

  int hit_flg;

  bool game_endflg;
  bool next_flg;
  bool now_game_flg;

  std::string next;

  /*カードシューオブジェクトの生成*/
  Shoe* shoe;
  /*プレイヤーオブジェクトの生成*/
  Player* player;
  /*ディーラーオブジェクトの生成*/
  Dealer* dealer;

public:

  BlackJack();
  ~BlackJack();

  void Initialize();
  void Update();
  void Draw();
  void Finalize();

};
