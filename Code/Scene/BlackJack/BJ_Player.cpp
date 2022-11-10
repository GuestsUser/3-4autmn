﻿#include"BJ_Head.h"

  /*コンストラクタ*/
Player::Player() {
  /*変数の初期化*/
  hand_num = 0;   /*手札枚数を0で初期化*/
  score = 0;
  type = 0;
  data = 0;
  win_ct = los_ct = BJ_ct = dbl_ct = bst_ct = 0;

  spt_hand_num = 0;
  spt_score = 0;
  spt_type = 0;
  spt_data = 0;
  split = false;
  hit_num = 0;

  color = 0xffffff;
  color2 = 0xffffff;
  color3 = 0xffffff;
  color4 = 0xffffff;

  mouseX = mouseY = 0;
  btn_x = btn_y = btn_w = btn_h = 0;
  hit = std = dbl = spt = bet = false;
  win = los = bst = psh = BlackJack = game_flg = spt_a = false;
  D_BJ = D_bst = false;

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

  spt_hand_num = 0;
  spt_hand.erase(spt_hand.begin(),spt_hand.end());
  spt_score = 0;
  split = false;
  hit_num = 0;

  win_ct = los_ct = BJ_ct = dbl_ct = bst_ct = 0;
  type = 0;
  spt_type = 0;

  dealer_calc = 0;

  color = 0xffffff;
  color2 = 0xffffff;
  color3 = 0xffffff;
  color4 = 0xffffff;

  hit = std = dbl = spt = bet = false;
  win = los = bst = psh = BlackJack = spt_a = false;
  D_BJ = D_bst = false;
  game_flg = true;

}

/*カードの追加*/
void Player::Hit(Shoe* shoe) {    /*shoeオブジェクトポインタ*/

    if (split) {

      if (spt_hand_num < 2) {

        if (hand_num >= 2) {
          spt_hand.push_back(hand[1]);
          hand.pop_back();
          hand_num--;
        }
        spt_hand.push_back(shoe->Take_Card());
        spt_hand_num++;

      }
      else {

        if (hit_num < 1) {
          /*配列の最後にカードを追加*/
          hand.push_back(shoe->Take_Card());
          hand_num++;   /*手札枚数を増やす*/

        }
        else {
          /*配列の最後にカードを追加*/
          spt_hand.push_back(shoe->Take_Card());
          spt_hand_num++;   /*手札枚数を増やす*/
        }


      }

    }
    else {

      /*配列の最後にカードを追加*/
      hand.push_back(shoe->Take_Card());
      hand_num++;   /*手札枚数を増やす*/

    }

}

/*ゲーム実行*/
bool Player::Play(Shoe* shoe) {

  /*ボタン処理（hit,stand,double,splite）*/
  hit = Player::ButtonHit(hit_x, hit_y, hit_w, hit_h);
  spt = Player::ButtonHit(spt_x, spt_y, spt_w, spt_h);

  if (Player::ButtonHit(std_x, std_y, std_w, std_h) || dbl) {
    std = true;
  }
  if (Player::ButtonHit(dbl_x, dbl_y, dbl_w, dbl_h)) {
    dbl = true;
  }

  /*バーストするまでループ処理*/
  if (game_flg) {

    if (!split) {

      if (Player::Calc() <= 21) {

        /*手札が二枚以下なら*/
        if (hand_num < 2) {
          /*一枚配る*/
          Player::Hit(shoe);

          /*ブラックジャックだったら*/
          if (Player::Calc() == 21) {

            /*勝負開始（stand自動実行）*/
            BlackJack = true;
            std = true;
            game_flg = false;

          }

        }

        if (Player::Calc() == 21) {

          std = true;

        }

        /*hitが入力された場合*/
        if (hit) {

          /*カードの配布*/
          Player::Hit(shoe);

          color = 0xff0000;
          c++;

        }
        /*standが入力された場合*/
        else if (std) {

          /*勝負開始して返り値をtrueとして終了*/
          game_flg = false;
          std = false;
          return true;

          color2 = 0x00ff00;
          c2++;

        }
        /*doubleが入力された場合*/
        else if (dbl && hand_num <= 2) {

          /*カードを引いて勝負開始*/
          Player::Hit(shoe);
          color3 = 0xff00ff;
          c3++;

        }
        /*spliteが入力された場合*/
        else if (spt && hand_num <= 2) {

          if ((hand[0] % 13) == (hand[1] % 13) || (hand[0] % 13 > 8 && hand[1] % 13 > 8)) {

            if (hand[0] % 13 == 0 && hand[1] % 13 == 0) {

              spt_a = true;

            }

            split = true;
            Player::Hit(shoe);

          }

          color4 = 0xffff00;
          c4++;

        }

      }
      /*バーストしていた場合*/
      if (Player::Calc() > 21) {

        bst = true;
        std = true;
        game_flg = false;
        return false;

      }
    }
    if (split) {

      if (Player::Calc() <= 21 || Player::Spt_Calc() <= 21) {

        /*手札が二枚以下なら*/
        if (hand_num < 2) {

          /*一枚配る*/
          Player::Hit(shoe);

          /*ブラックジャックだったら*/
          if (Player::Calc() == 21 && Player::Spt_Calc() == 21) {

            /*勝負開始（stand自動実行）*/
            BlackJack = true;
            game_flg = false;
            return true;

          }

          if (Player::Calc() == 21) {
            BJ_ct++;
            std = true;
          }

          if (Player::Spt_Calc() == 21 && BJ_ct <= 1) {
            BJ_ct++;
            std = true;
          }

        }

        if ((Player::Calc() == 21 && hit_num < 1)) {

          std = true;

        }

        /*hitが入力された場合*/
        if (hit) {
          color = 0xff0000;
          c++;

          /*カードの配布*/
          Player::Hit(shoe);
        }
        /*standが入力された場合*/
        else if (std) {
          if (hit_num < 1) {

            hit_num++;

          }
          else {

            /*勝負開始して返り値をtrueとして終了*/
            game_flg = false;
            return true;

          }

          std = false;

          color2 = 0x00ff00;
          c2++;

        }
        /*doubleが入力された場合*/
        else if (dbl && (hand_num <= 2 || spt_hand_num <= 2)) {

          /*カードを引いて勝負開始*/
          Player::Hit(shoe);
          dbl = false;
          dbl_ct++;
          std = true;

          color3 = 0xff00ff;
          c3++;

        }

        if (Player::Calc() > 21 && hit_num < 1) {

          bst_ct++;
          los_ct++;
          std = true;

        }
        else if (Player::Spt_Calc() > 21 && hit_num == 1) {

          bst_ct++;
          los_ct++;
          hit_num++;
          std = true;

        }

      }
      else {
        game_flg = false;
      }

    }
  }

  /*バーストしているのでfalseを返して終了*/
  return false;

}

void Player::Score(Player player, Dealer dealer) {   /*プレイヤーとディーラーのスコア勝負*/
  /*最終スコアがプレイヤーのほうが高い場合*/

  dealer_calc = dealer.Calc();
  D_BJ = dealer.BlackJack();
  if (!game_flg) {

    if (dealer.Calc() > 21) {
      D_bst = true;
      win = true;
    }

    if (player.Calc() > 21 || bst_ct >= 2) {
      bst = true;
      los = true;
    }

    if (!bst) {

      if (player.Calc() > dealer.Calc()) {
        /*プレイヤーの勝利*/
        win = true;

      }
      else if (player.Calc() < dealer.Calc()) {    /*ディーラーのほうが高い場合*/

        if (dealer.Calc() > 21) {
          /*プレイヤーの勝ち*/
          win = true;
          D_bst = true;

        }
        else {
          /*プレイヤーの負け*/

          los = true;

        }
      }
      else {    /*同点の場合*/
        /*引き分け*/
        if (!BlackJack || (D_BJ && BlackJack)) {

          psh = true;

        }

      }

    }
    else {


      los = true;

    }

  }

}


/*手札を表示*/
void Player::Show_Hand() {
  /*標準出力*/

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
      DrawFormatString(160 + i * 50, 160, 0xffffff, " :%c %d", a, hand[i] % 13 + 1);

  }

    DrawFormatString(100, 380, 0xffffff, "Player score: %d\n", Player::Calc());

}
/*手札を表示*/
void Player::Spt_Show_Hand() {
  /*標準出力*/

  /*配列の最初から最後までを順に表示*/
  for (int i = 0; i < spt_hand_num; i++) {
    /*カードの種類（スペード、ハート、ダイヤ、クラブ）を探索*/
    spt_type = (spt_hand[i] % 52) / 13;   /*デッキごとに分けた後、13で割った数（0-3）で4種類を分割*/
    char a = '\0';
    /*分岐条件にtypeをそのまま利用*/
    switch (spt_type) {

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

      DrawFormatString(160 + i * 50, 180, 0xffffff, " :%c %d", a, spt_hand[i] % 13 + 1);

  }

    DrawFormatString(100, 400, 0xffffff, "Player_Splite score: %d\n", Player::Spt_Calc());

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
  if (split) {
    Player::Spt_Show_Hand();
  }

  SetFontSize(32);
  DrawFormatString(hit_x, hit_y, color, "Hit");
  DrawFormatString(std_x, std_y, color2, "Stand");
  DrawFormatString(dbl_x, dbl_y, color3, "Double");
  DrawFormatString(spt_x, spt_y, color4, "Splite");
  SetFontSize(DEFAULT_FONT_SIZE);

  /*デバッグ用*/
  DrawFormatString(spt_x, spt_y+40, color, "%d",hit+c);
  DrawFormatString(spt_x, spt_y+60, color2, "%d",std+c2);
  DrawFormatString(spt_x, spt_y+80, color3, "%d",dbl+c3);
  DrawFormatString(spt_x, spt_y+100, color4, "%d",spt+c4);
  DrawFormatString(spt_x+40, spt_y+40, color4, "hand_num：%d",hand_num);
  DrawFormatString(spt_x+40, spt_y+80, color4, "spt_num：%d",spt_hand_num);
  DrawFormatString(spt_x+40, spt_y+60, color4, "spt_a：%d",spt_a);

  DrawFormatString(spt_x+40, spt_y+100, color4, "%d",dealer_calc);

  DrawFormatString(spt_x-80, spt_y+40, color4, "%Win %d",win);
  DrawFormatString(spt_x-80, spt_y+60, color4, "Los %d",los);
  DrawFormatString(spt_x-80, spt_y+80, color4, "psh %d",psh);
  DrawFormatString(spt_x-80, spt_y+100, color4, "BlJ %d",BlackJack);
  DrawFormatString(spt_x-140, spt_y+100, color4, "bst %d",bst);
  DrawFormatString(spt_x-140, spt_y+80, color4, "spt %d",split);
  /*デバッグ用*/

  DrawFormatString(100, 460, 0xffffff, "選択してください");

  /*勝ち負け出力*/
  if (win) {
    /*プレイヤーの勝利*/
    if (dealer_calc > 21 && !BlackJack) {

      DrawFormatString(100, 500, 0xffffff, "DealerBurst あなたの勝ちです !!\n");

    }

      DrawFormatString(100, 520, 0xffffff, "あなたの勝ちです !!\n");


      if (BlackJack) {

        DrawFormatString(100, 540, 0xffffff, "BlackJack あなたの勝ちです");

      }

  }
  if (los) {    /*ディーラーのほうが高い場合*/

      DrawFormatString(100, 560, 0xffffff, "あなたの負けです\n");

      if (bst) {

        DrawFormatString(100, 600, 0xffffff, "Burst あなたの負けです\n");

      }

  }
  if(psh) {    /*同点の場合*/
    /*引き分け*/
    DrawFormatString(100, 580, 0xffffff, "引き分けです\n");

  }
  /*勝ち負け出力*/

  ///*勝ち負け出力*/
  //if (win && !bst) {
  //  /*プレイヤーの勝利*/
  //  if (dealer_calc > 21 && !BlackJack) {

  //    DrawFormatString(100, 500, 0xffffff, "DealerBurst あなたの勝ちです !!\n");

  //  }
  //  else {

  //    DrawFormatString(100, 520, 0xffffff, "あなたの勝ちです !!\n");

  //  }

  //}
  //if (BlackJack) {

  //  DrawFormatString(100,540,0xffffff,"BlackJack あなたの勝ちです");

  //}
  //if (los && !bst) {    /*ディーラーのほうが高い場合*/

  //    DrawFormatString(100, 560, 0xffffff, "あなたの負けです\n");

  //}
  //if(psh && !BlackJack) {    /*同点の場合*/
  //  /*引き分け*/
  //  DrawFormatString(100, 580, 0xffffff, "引き分けです\n");

  //}
  //if (bst) {

  //  DrawFormatString(100, 600, 0xffffff, "Burst あなたの負けです\n");

  //}
  ///*勝ち負け出力*/

}

