#include"BJ_Head.h"

/*コンストラクタ*/
Dealer::Dealer() {

  hand_num = 0;   /*手札枚数を0で初期化*/
  score = 0;      /*スコアを0で初期化*/
  type = 0;       /*トランプのマーク*/

  spt_hand_num = 0;
  spt_score = 0;

  data = 0;
  spt_data = 0;

  split = false;

  D_BlackJakc = false;


}
Dealer::~Dealer() {};
/*変数初期化*/
void Dealer::Initialize() {

  hand_num = 0;                           /*手札枚数を0で初期化*/
  hand.erase(hand.begin(), hand.end());   /*手札をクリア*/
  score = 0;                              /*スコアを初期化*/
  type = 0;                               /*トランプのマーク*/

  D_BlackJakc = false;

}
/*スコアの計算*/
int Dealer::Calc() {
  /*メモリの動的確保*/
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
  score = 0;
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

/*カードの追加*/
void Dealer::Hit(Shoe* shoe) {    /*shoeオブジェクトポインタ*/
  /*配列の最後にカードを追加する*/
  hand.push_back(shoe->Take_Card());
  hand_num++;   /*手札枚数を増やす*/

}
/*手札を表示*/
void Dealer::Show_Hand() {
  /*標準出力*/

  //DrawFormatString(100,620,0xffffff,"hand:");
  /*配列の最初から最後までを順に表示*/
  for (int i = 0; i < hand_num; i++) {
    /*カードの種類（スペード、ハート、ダイヤ、クラブ）を探索*/
    type = (hand[i] % 52) / 13;   /*デッキごとに分けた後、13で割った数（0-3）で4種類を分割*/
    char a = '\0';
    /*分岐条件にtypeをそのまま利用*/
    switch (type) {

    case 0:   /*0であればスペードのs*/
      std::cout << 's';
      a = 's';
      break;

    case 1:   /*1であればハートのh*/
      std::cout << 'h';
      a = 'h';
      break;

    case 2:   /*2であればダイヤのd*/
      std::cout << 'd';
      a = 'd';
      break;

    case 3:   /*3であればクラブのc*/
      std::cout << 'c';
      a = 'c';
      break;

    default:    /*0-3でない場合はエラー処理*/
      /*標準出力*/

      DrawFormatString(0,0,0xffffff, "DefTypeError\nshow_hand");
      break;

    }
    /*標準出力*/

    DrawFormatString(160+i*50, 220,0xffffff," :%c %d",a,hand[i]%13+1);

  }

    DrawFormatString(100, 420, 0xffffff, "Dealer score: %d\n", Dealer::Calc());

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

void Dealer::Update() {


}

void Dealer::Draw() {

  DrawFormatString(100, 720, 0xffffff, "hit\n");
  /*手札の表示*/
  DrawFormatString(100, 740, 0xffffff, "==============\n");
  DrawFormatString(100, 760, 0xffffff, "dealer\n");
  Dealer::Show_Hand();

  DrawFormatString(100, 780, 0xffffff, "==============\n");

}
