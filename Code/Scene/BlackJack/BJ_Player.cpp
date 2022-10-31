#include"BJ_Head.h"

  /*コンストラクタ*/
Player::Player() {
  /*変数の初期化*/
  hand_num = 0;   /*手札枚数を0で初期化*/
  score = 0;
  type = 0;

  data = 0;

}
Player::~Player() {};
void Player::Initialize() {

  hand_num = 0;
  hand.erase(hand.begin(), hand.end());
  score = 0;
  type = 0;

}

/*カードの追加*/
void Player::Hit(Shoe* shoe) {    /*shoeオブジェクトポインタ*/
  /*配列の最後にカードを追加*/
  hand.push_back(shoe->Take_Card());
  hand_num++;   /*手札枚数を増やす*/

}

/*ゲーム実行*/
bool Player::Play(Shoe* shoe) {
  /*バーストするまでループ処理*/
  char buf[10];
  
  while (Player::Calc() <= 21) {
    /*選択肢を聞く（ヒット、スタンド）*/
    //DrawFormatString(100,460,0xffffff,"選択してください");
    //str = KeyInputSingleCharString(100, 100, 10, buf, TRUE);
    str = "stand";
    /*hitが入力された場合*/
    if (str == "hit") {
      /*カードの配布*/
      Player::Hit(shoe);
      /*手札の表示*/

      DrawFormatString(100, 480, 0xffffff, "==============");

      DrawFormatString(100,500,0xffffff,"player");
      Player::Show_Hand();
      DrawFormatString(100, 520, 0xffffff, "==============");

    }
    else if (str == "stand") {    /*standが入力された場合*/
      /*返り値としてtrueとして終了*/
      return true;

    }

  }
  /*バーストしているのでfalseを返して終了*/
  return false;

}

void Player::Score(Player player, Dealer dealer) {   /*プレイヤーとディーラーのスコア勝負*/
  /*最終スコアがプレイヤーのほうが高い場合*/
  if (player.Calc() > dealer.Calc()) {
    /*プレイヤーの勝利*/

    DrawFormatString(100, 420,0xffffff,"Player win !!\n");

  }
  else if (player.Calc() < dealer.Calc()) {    /*ディーラーのほうが高い場合*/

    if (dealer.Calc() > 21) {
      /*プレイヤーの勝ち*/

      DrawFormatString(100, 420,0xffffff,"Plaeyr Win !!\n");
    }
    else {
      /*プレイヤーの負け*/

      DrawFormatString(100, 420,0xffffff,"Player Lose\n");
    }

  }
  else {    /*同点の場合*/
    /*引き分け*/

    DrawFormatString(100, 420,0xffffff,"Push\n");

  }

}
