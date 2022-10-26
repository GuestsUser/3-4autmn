#pragma once

/*プレイヤークラス*/
class Player : public Dealer {

protected:
  ///*手札関連はprivateとする*/
  //std::vector<int> hand;    /*手札配列*/
  //int hand_num;             /*手札枚数*/
  //int score;                /*返り値用変数（計算結果）*/
  //int type;                 /*デッキごとに分けた後、13で割った数（0-3）で4種類を分割*/

  //int* data;                /*配列用ポインタ*/

  std::string str;          /*文字列型*/

public:

  Player();                    /*コンストラクタ*/
  ~Player();                   /*デストラクタ*/
  void Initialize();           /*変数初期化*/
  //int Calc();                  /*スコアの計算*/
  //void Hit(Shoe* shoe);        /*カードの追加*/
  //void Show_Hand();            /*手札を表示*/

  virtual void Hit(Shoe* shoe);        /*カードの追加*/
  virtual bool Play(Shoe* shoe);       /*ゲーム実行*/
  virtual void Score(Player player, Dealer dealer);

};
