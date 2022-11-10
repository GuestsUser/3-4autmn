#pragma once

/*ディーラークラス*/
class Dealer {

protected:
  /*手札関連はprivateとする*/
  std::vector<int> hand;    /*手札配列*/
  std::vector<int> spt_hand;    /*手札配列*/
  int hand_num;             /*手札枚数*/
  int score;                /*返り値用変数（計算結果)*/

  int spt_hand_num;         /*スプリット時の手札枚数*/
  int spt_score;            /*スプリット時の返り値用変数（計算結果)*/

  int type;                 /*カードの種類（スペード、ハート、ダイヤ、クラブ）を探索*/

  int* data;                /*配列用ポインタ*/
  int* spt_data;            /*スプリット時の配列用ポインタ*/

  bool D_BlackJakc;
  bool split;

public:

  Dealer();                /*コンストラクタ*/
  ~Dealer();               /*デストラクタ*/

  void Initialize();       /*変数の初期化*/
  void Update();
  void Draw();


  int Calc();              /*スコアの計算*/
  int Spt_Calc();          /*スプリット時のスコアの計算*/

  bool BlackJack();

  virtual void Show_Hand();        /*手札を表示*/
  virtual void Hit(Shoe* shoe);    /*カードの追加*/
  virtual bool Play(Shoe* shoe);   /*ゲーム実行*/

};
