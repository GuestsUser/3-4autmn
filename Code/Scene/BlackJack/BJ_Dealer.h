#pragma once

/*ディーラークラス*/
class Dealer {

protected:
  /*手札関連はprivateとする*/
  std::vector<int> hand;    /*手札配列*/
  int hand_num;             /*手札枚数*/
  int score;                /*返り値用変数（計算結果)*/
  int type;                 /*カードの種類（スペード、ハート、ダイヤ、クラブ）を探索*/

  int* data;                /*配列用ポインタ*/

public:

  Dealer();                /*コンストラクタ*/
  ~Dealer();               /*デストラクタ*/
  void Initialize();       /*変数の初期化*/
  int Calc();              /*スコアの計算*/
  //void Hit(Shoe* shoe);    /*カードの追加*/
  void Show_Hand();        /*手札を表示*/
  virtual void Hit(Shoe* shoe);    /*カードの追加*/
  virtual bool Play(Shoe* shoe);   /*ゲーム実行*/

};
