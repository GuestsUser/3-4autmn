#pragma once

#define DECK 6          /*使用するデッキ数*/
#define CARD 52         /*トランプのカードの数（ジョーカーなし）*/
#define NUM DECK*CARD   /*カードの総数*/

/*カードシュー（デッキ管理をする機械）クラス*/
class Shoe {

protected:
  /*基本的にカードシューはprivate*/
  int card_shoe[NUM] = {};       /*カード配列*/
  int card_num;             /*カード枚数*/
  int place;                /*挿入位置*/
  int top;                  /*カード配列の先頭を格納*/

  std::random_device rnd;   /*乱数生成器*/

public:

  Shoe();                        /*コンストラクタ*/
  ~Shoe();                       /*デストラクタ*/
  void Inisialize();             /*変数初期化*/
  void Show_Shoe(bool type);     /*カードシューを表示(デバッグ用)*/

  virtual int Take_Card();               /*カードを1枚取り出す*/

};
