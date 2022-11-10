#pragma once

/*プレイヤークラス*/
class Player : public Dealer {

private:

  int mouseX, mouseY;   /*マウス座標*/
  int btn_x, btn_y, btn_w, btn_h;
  int hit_x, hit_y, hit_w, hit_h;
  int std_x, std_y, std_w, std_h;
  int spt_x, spt_y, spt_w, spt_h;
  int dbl_x, dbl_y, dbl_w, dbl_h;

  int spt_type;
  int hit_num;
  int win_ct , BJ_ct;
  int dbl_ct;
  int bst_ct;
  int los_ct;

  /*デバッグ用*/
  int color, color2, color3, color4;
  int c, c2, c3, c4;
  /*デバッグ用*/

  int dealer_calc;

  bool D_BJ;
  bool D_bst;

  bool hit, std, bet, spt, dbl;
  bool win, los, bst, psh, BlackJack, game_flg;
  bool spt_a;

  std::string str;          /*文字列型*/

public:

  Player();                    /*コンストラクタ*/
  ~Player();                   /*デストラクタ*/

  void Initialize();           /*変数初期化*/
  void Update();
  void Draw();

  bool ButtonHit(int, int, int, int);

  void Show_Hand();
  void Spt_Show_Hand();

  virtual void Hit(Shoe* shoe);        /*カードの追加*/
  virtual bool Play(Shoe* shoe);       /*ゲーム実行*/
  virtual void Score(Player player, Dealer dealer);

};
