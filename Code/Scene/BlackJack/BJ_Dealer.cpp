#include"BJ_Head.h"

/*コンストラクタ*/
Dealer::Dealer() {

  /*変数初期化*/
  hand_num = 0;   /*手札枚数を0で初期化*/
  score = 0;      /*スコアを0で初期化*/
  type = 0;       /*トランプのマーク*/

  spt_hand_num = 0;
  spt_score = 0;

  data = 0;
  spt_data = 0;
  /*変数初期化*/

  /*bool*/
  split = false;

  D_BlackJakc = false;
  /*bool*/

  /*初期位置*/
  cd_x = cd_y = cd_w = cd_h = 0;

  img_x = 600;
  img_y = 180;
  /*初期位置*/

  /*画像ハンドル*/
  LoadDivGraph("Resource/image/toranpu_all.png",54,13,5,200,300,card_hdl);

  btn_hdl[0] = LoadGraph("Resource/image/BJ_Image/Win.png");
  btn_hdl[1] = LoadGraph("Resource/image/BJ_Image/Los.png");
  btn_hdl[2] = LoadGraph("Resource/image/BJ_Image/Bust.png");
  btn_hdl[3] = LoadGraph("Resource/image/BJ_Image/Push.png");
  btn_hdl[4] = LoadGraph("Resource/image/BJ_Image/BlackJack.png");

  for (int i = 0; i < 5; i++) {

    for (int j = 0; j < 13; j++) {

      card_type[i][j] = card_hdl[j + (i * 13)];

    }

  }
  /*画像ハンドル*/

}

Dealer::~Dealer() {

}

/*変数初期化*/
void Dealer::Initialize() {

  hand_num = 0;                           /*手札枚数を0で初期化*/
  if (!hand.empty()) { hand.erase(hand.begin(), hand.end()); }   /*手札をクリア*/
  score = 0;                              /*スコアを初期化*/
  type = 0;                               /*トランプのマーク*/
  
  D_BlackJakc = false;
  D_ins = false;

}

void Dealer::Draw() {

  DrawRotaGraph(yama_x, yama_y, img_size, 0, card_hdl[52], 1);
  SetFontSize(24);
  DrawFormatString(10, 650, 0xffffff, "アクションを選択してください");
  SetFontSize(DEFAULT_FONT_SIZE);
  Dealer::Show_Hand();

  DrawRotaGraph(yama_x, yama_y, img_size, 0, card_hdl[52], 1);
  /*山札予定地*/

}
/*カードの追加*/
void Dealer::Hit(Shoe* shoe) {    /*shoeオブジェクトポインタ*/
  /*配列の最後にカードを追加する*/
  hand.push_back(shoe->Take_Card());
  hand_num++;   /*手札枚数を増やす*/

}

/*手札を表示*/
void Dealer::Show_Hand() {

  /*配列の最初から最後までを順に表示*/
  for (int i = 0; i < hand_num; i++) {
    /*カードの種類（スペード、ハート、ダイヤ、クラブ）を探索*/
    type = (hand[i] % 52) / 13;   /*デッキごとに分けた後、13で割った数（0-3）で4種類を分割*/

    DrawRotaGraph(600 + i * 30, 140, img_size, 0, card_type[type][hand[i] % 13], 1);

  }

  if (hand_num < 2)DrawRotaGraph(630, 140, img_size, 0, card_type[4][0], 1);
  SetFontSize(60);
  DrawFormatString(580, 200, 0, "%d\n", Dealer::Calc());
  SetFontSize(DEFAULT_FONT_SIZE);
  Dealer::Set_Ins();

}
/*スコアの計算*/
int Dealer::Calc() {
  /*メモリの動的確保*/
  score = 0;
  data = 0;
  data = new int[hand_num];   /*手札枚数確保*/
  /*手札配列からデータを取得、1-10の値として格納*/
  for (int i = 0; i < hand_num; i++) {
    /*配列の値が10以下（0-9）であれば1を加えて格納*/
    if (hand[i] % 13 < 10) {
      /*1-13のカードとして扱うために1加えている*/
      data[i] = hand[i] % 13 + 1;

    }
    else {    /*配列の値が10以上（10-12）であれば10を格納*/
      /*ここで10を格納しているのは、11-13のカードのことである*/
      data[i] = 10;

    }

  }
  /*ソート*/
  std::sort(data, data + hand_num);
  /*返り値用変数（計算結果*/
  /*2番目から順にスコアを足していく（1番目は判定が必要）*/
  for (int i = 1; i < hand_num; i++) {
    /*スコアにデータを加える*/
    score += data[i];

  }
  if (data[0] == 1) {     /*先頭が1であるか判定*/
    /*1をどう扱うか判定する*/
    if (score + 11 < 22) {    /*11として扱ってもバーストしない場合*/
      /*11を加える*/
      score += 11;

    }
    else {    /*11として扱うとバーストする場合*/
      /*スコアに1を加える*/
      score += 1;

    }

  }
  else {    /*先頭が1でないなら、スコアにデータをそのまま加える*/
    /*スコアにデータを加える*/
    score += data[0];

  }

  if (hand[0] % 13 == 0 && hand.size() <= 1) {

    D_ins = true;

  }
  else {
    D_ins = false;
  }

  delete[] data;    /*メモリの開放*/
  return score;     /*計算結果を返す*/

}

int Dealer::Spt_Calc() {
  /*メモリの動的確保*/
  spt_data = new int[spt_hand_num];   /*手札枚数確保*/
  /*手札配列からデータを取得、1-10の値として格納*/
  for (int i = 0; i < spt_hand_num; i++) {
    /*配列の値が10以下（0-9）であれば1を加えて格納*/
    if (spt_hand[i] % 13 < 10) {
      /*1-13のカードとして扱うために1加えている*/
      spt_data[i] = spt_hand[i] % 13 + 1;

    }
    else {    /*配列の値が10以上（10-12）であれば10を格納*/
      /*ここで10を格納しているのは、11-13のカードのことである*/
      spt_data[i] = 10;

    }

  }
  /*ソート*/
  std::sort(spt_data, spt_data + spt_hand_num);
  /*返り値用変数（計算結果*/
  spt_score = 0;
  /*2番目から順にスコアを足していく（1番目は判定が必要）*/
  for (int i = 1; i < spt_hand_num; i++) {
    /*スコアにデータを加える*/
    spt_score += spt_data[i];

  }
  if (spt_data[0] == 1) {     /*先頭が1であるか判定*/
    /*1をどう扱うか判定する*/
    if (spt_score + 11 < 22) {    /*11として扱ってもバーストしない場合*/
      /*11を加える*/
      spt_score += 11;

    }
    else {    /*11として扱うとバーストする場合*/
      /*スコアに1を加える*/
      spt_score += 1;

    }

  }
  else {    /*先頭が1でないなら、スコアにデータをそのまま加える*/
    /*スコアにデータを加える*/
    spt_score += spt_data[0];

  }

  delete[] spt_data;    /*メモリの開放*/
  return spt_score;     /*計算結果を返す*/

}
/*ゲーム実行*/
bool Dealer::Play(Shoe* shoe) {   /*shoeオブジェクトポインタ*/

  if (hand_num < 2) {
    Dealer::Hit(shoe);
    if (Dealer::Calc() == 21) {
      D_BlackJakc = true;
    }
  }
  /*スコアが16以下の場合hitを続ける*/
  while (Dealer::Calc() < 17 && Dealer::Calc() > 0) {
    /*ヒットする*/
    Dealer::Hit(shoe);

  }
  return true;
}

bool Dealer::BlackJack(){

  return D_BlackJakc;

}

int Dealer::Set_Magnification(float setrate, int getcoin) {

  return setrate*getcoin;
}

bool Dealer::Set_Ins() {

  return D_ins;

}
