#include"BJ_Head.h"

/*コンストラクタ*/
Shoe::Shoe() {

  card_num = NUM; /*カード枚数の設定*/
  place = 0;
  top = 0;

  for (auto& raw :  card_trans) {

    for (auto& i:raw) {
      i = 5;
    }

  }

  /*配列をすべて-1で初期化*/
  for (auto& i : card_shoe) {

    i = -1;   /*-1の代入*/

  }
  /*配列にカードを順番に格納(iのカードをどこに挿入するか決める)*/
  for (int i = 0; i < NUM; i++) {
    /*iのカードが挿入されるまでループ*/
    while (1) {
      /*乱数によって挿入位置を選定*/
      place = rnd() % (NUM);    /*挿入位置*/
      /*乱数で決めた挿入位置が空であるか確認*/
      if (card_shoe[place] == -1) {
        /*カードの格納*/
        card_shoe[place] = i;
        break;    /*ループを抜ける*/

      }

    }

  }

}
Shoe::~Shoe() {};   /*デストラクタ*/
/*初期化*/
void Shoe::Inisialize() {
  /*配列をすべて-1で初期化*/
  for (auto& i : card_shoe) {

    i = -1;   /*-1の代入*/

  }
  /*配列にカードを順番に格納(iのカードをどこに挿入するか決める)*/
  for (int i = 0; i < NUM; i++) {
    /*iのカードが挿入されるまでループ*/
    while (1) {
      /*乱数によって挿入位置を選定*/
      place = rnd() % (NUM);    /*挿入位置*/
      /*乱数で決めた挿入位置が空であるか確認*/
      if (card_shoe[place] == -1) {
        /*カードの格納*/
        card_shoe[place] = i;
        break;    /*ループを抜ける*/

      }

    }

  }

  card_num = NUM; /*カード枚数の設定*/

}

/*カードシューを表示(デバッグ用)*/
void Shoe::Show_Shoe(bool type) {
  /*typeで表示範囲を操作（trueならカード枚数分表示）*/
  if (type) {
    /*カード配列を先頭から表示する*/
    for (int i = 0; i < card_num; i++) {

      DrawFormatString(0,0,0xffffff," ");

    }

  }
  else {    /*falseなら配列全体*/
    /*カード配列を先頭から表示する*/
    for (auto i : card_shoe) {

      DrawFormatString(0,0,0xffffff," ");

    }

  }

}
/*カードを1枚取り出す*/
int Shoe::Take_Card() {
  /*カード枚数が0だった場合、エラーとして出力*/
  if (card_num == 0) {
    /*標準出力*/
    DrawFormatString(0,0,0xffffff, "NoStackError\nShoe_card_num");

    return -1;
  }
  /*カード配列の先頭を格納*/
  top = card_shoe[0];
  /*カード配列を先頭から順に変更*/
  for (int i = 0; i < card_num - 1; i++) {
    /*要素を1つずつずらす*/
    card_shoe[i] = card_shoe[i + 1];

  }
  /*必要なくなった範囲には-1を代入*/
  card_shoe[card_num - 1] = -1;
  card_num--;   /*カード枚数を1減らす*/

  return top;   /*先頭にある要素を返り値とする*/
}
