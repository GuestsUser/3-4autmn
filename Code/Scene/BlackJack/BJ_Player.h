﻿#pragma once


/*プレイヤークラス*/
class Player : public Dealer {

private:

  int mouseX, mouseY;   /*マウス座標*/
  int btn_x, btn_y, btn_w, btn_h;
  int hit_x, hit_y, hit_w, hit_h;
  int std_x, std_y, std_w, std_h;
  int spt_x, spt_y, spt_w, spt_h;
  int dbl_x, dbl_y, dbl_w, dbl_h;
  float hit_r, std_r, spt_r, dbl_r;

  int hit_img, std_img, spt_img, dbl_img;
  

  int spt_type;
  int hit_num;


  int p_coin = 1000;

  int Bottun_SE_;

  /*bool*/
  bool now_game_flg;

  bool bet_flg = false;

  bool D_BJ;
  bool D_bst;

  bool spt_flg;
  bool hit, std, bet, spt, dbl;
  bool spt_hit;
  bool win, los, bst, psh, BlackJack, game_flg;
  bool spt_win, spt_los, spt_bst, spt_psh, spt_BJ;
  bool spt_a;
  /*bool*/

public:

  Player();                    /*コンストラクタ*/
  ~Player();                   /*デストラクタ*/

  void Initialize();           /*変数初期化*/
  void Draw();
  void Debug_Draw(bool);

  int P_MaxCoin();

  bool ButtonHit(int, int, int, int);
  bool Now_Game();
  bool P_BJ();
  void Bet_Flg(bool);

  void Show_Hand();
  void Spt_Show_Hand();
  void Show_Play();

  virtual void Set_Bet(int getbet);
  virtual void Hit(Shoe* shoe);        /*カードの追加*/
  virtual bool Play(Shoe* shoe);       /*ゲーム実行*/
  virtual void Score(Player player, Dealer dealer);

};
