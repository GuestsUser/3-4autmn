#include"BJ_Head.h"

  /*コンストラクタ*/
Player::Player() {
  /*変数の初期化*/
  hand_num = 0;   /*手札枚数を0で初期化*/
  score = 0;
  type = 0;
  data = 0;

  color = 0xffffff;
  color2 = 0xffffff;
  color3 = 0xffffff;
  color4 = 0xffffff;

  mouseX = mouseY = 0;
  btn_x = btn_y = btn_w = btn_h = 0;
  hit = std = dbl = spt = bet = false;
  win = los = bst = psh = BlackJack = game_flg = false;

  dealer_calc = 0;

  hit_x = 800;
  hit_y = std_y = dbl_y = spt_y = 600;

  std_x = hit_x + 80;
  dbl_x = hit_x + 200;
  spt_x = hit_x + 320;

  hit_w = 60;
  std_w = 95;
  dbl_w = spt_w = 110;
  hit_h = std_h = dbl_h = spt_h = 60;

  c = c2 = c3 = c4 = 0;
}
Player::~Player() {};
void Player::Initialize() {

  hand_num = 0;
  hand.erase(hand.begin(), hand.end());
  score = 0;
  type = 0;

  dealer_calc = 0;

  hit = std = dbl = spt = bet = false;
  win = los = bst = psh = BlackJack = false;
  game_flg = true;

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
  hit = Player::ButtonHit(hit_x, hit_y, hit_w, hit_h);
  std = Player::ButtonHit(std_x, std_y, std_w, std_h);
  dbl = Player::ButtonHit(dbl_x, dbl_y, dbl_w, dbl_h);
  spt = Player::ButtonHit(spt_x, spt_y, spt_w, spt_h);

  if (Player::Calc() <= 21 && game_flg) {
    /*選択肢を聞く（ヒット、スタンド）*/

    if (hand_num < 2) {
      Player::Hit(shoe);
      if (Player::Calc() == 21) {

        BlackJack = true;
        std = true;
        game_flg = false;
      }
    }
    /*hitが入力された場合*/
    if (hit) {
      color = 0xff0000;
      c++;
      /*カードの配布*/
      Player::Hit(shoe);

    }
    else if (std || Player::Calc() == 21) {    /*standが入力された場合*/
      color2 = 0x00ff00;
      c2++;
      /*返り値としてtrueとして終了*/
      game_flg = false;
      return true;
    }
    else if (dbl && hand_num <= 2) {
      color3 = 0xff00ff;
      c3++;
      Player::Hit(shoe);
      game_flg = false;
      return true;
    }
    else if (spt) {
      color4 = 0xffff00;
      c4++;
    }

  }
  else {
    if (Player::Calc() > 21) {
      bst = true;
      los = true;
      win = false;
    }

    game_flg = false;
    return true;
  }
  /*バーストしているのでfalseを返して終了*/
  return false;

}

void Player::Score(Player player, Dealer dealer) {   /*プレイヤーとディーラーのスコア勝負*/
  /*最終スコアがプレイヤーのほうが高い場合*/

  dealer_calc = dealer.Calc();

  if (std || dbl) {

    if (player.Calc() > dealer.Calc()) {
      /*プレイヤーの勝利*/

      if (!bst) {
        win = true;
      }

    }
    else if (player.Calc() < dealer.Calc()) {    /*ディーラーのほうが高い場合*/

      if (dealer.Calc() > 21) {
        /*プレイヤーの勝ち*/

        if (!bst) {
          win = true;
        }

      }
      else {
        /*プレイヤーの負け*/

        los = true;

      }
    }
    else {    /*同点の場合*/
      /*引き分け*/
      if (!BlackJack ||  (dealer.BlackJack() && BlackJack)) {

        if (!bst) {
          psh = true;
        }

      }

    }
  }

}


/*手札を表示*/
void Player::Show_Hand() {
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

      DrawFormatString(0, 0, 0xffffff, "DefTypeError\nshow_hand");
      break;

    }
    /*標準出力*/

    DrawFormatString(160 + i * 50, 160,0xffffff," :%c %d",a,hand[i] % 13);

  }

  //if (Player::Calc() <= 21) {


    DrawFormatString(100, 380, 0xffffff, "Player score: %d\n", Player::Calc());

  //}

}

bool Player::ButtonHit(int x,int y,int w,int h) {

  GetMousePoint(&mouseX, &mouseY);

  if (mouseX >= x && mouseX < (x + w) && mouseY >= y && mouseY < (y + h)) {

    if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {

      return true;

    }
    else {

      return false;

    }

  }
  else {
    return false;
  }

}

void Player::Update() {



}

void Player::Draw() {

  Player::Show_Hand();

  SetFontSize(32);
  DrawFormatString(hit_x, hit_y, color, "Hit");
  DrawFormatString(std_x, std_y, color2, "Stand");
  DrawFormatString(dbl_x, dbl_y, color3, "Double");
  DrawFormatString(spt_x, spt_y, color4, "Splite");
  SetFontSize(DEFAULT_FONT_SIZE);
  DrawFormatString(spt_x, spt_y+40, color, "%d",hit+c);
  DrawFormatString(spt_x, spt_y+60, color2, "%d",std+c2);
  DrawFormatString(spt_x, spt_y+80, color3, "%d",dbl+c3);
  DrawFormatString(spt_x, spt_y+100, color4, "%d",spt+c4);

  DrawFormatString(spt_x+40, spt_y+100, color4, "%d",dealer_calc);

  DrawFormatString(spt_x-80, spt_y+80, color4, "%Win %d",win);
  DrawFormatString(spt_x-80, spt_y+100, color4, "Los %d",los);

  DrawFormatString(100, 460, 0xffffff, "選択してください");

  if (win && !bst) {
    /*プレイヤーの勝利*/
    if (dealer_calc > 21 && !BlackJack) {

      DrawFormatString(100, 500, 0xffffff, "DealerBurst あなたの勝ちです !!\n");

    }
    else {

      DrawFormatString(100, 520, 0xffffff, "あなたの勝ちです !!\n");

    }

  }
  if (BlackJack) {

    DrawFormatString(100,540,0xffffff,"BlackJack あなたの勝ちです");

  }
  if (los && !bst) {    /*ディーラーのほうが高い場合*/

      DrawFormatString(100, 560, 0xffffff, "あなたの負けです\n");

  }
  if(psh && !BlackJack) {    /*同点の場合*/
    /*引き分け*/
    DrawFormatString(100, 580, 0xffffff, "引き分けです\n");

  }
  if (bst) {

    DrawFormatString(100, 600, 0xffffff, "Burst あなたの負けです\n");

  }
}

