#include"BJ_Head.h"
BlackJack BJ;
//Dealer Dr;
/*
  WorldVal::Set("test",new int(4)); こんな感じ、new intの方の型は好きな型が使える
  int get=WorldVal::Get<int>("test"); こんな風に取り出す、<int>の部分は取り出す型に合わせて変える
  WorldVal::Del("test"); これで"test"の値を削除できる
  WorldVal::Set("test",new int (1000));
*/
/*コンストラクタ*/
Player::Player() {
  /*変数の初期化*/
  hand_num = 0;   /*手札枚数を0で初期化*/
  score = 0;
  type = 0;
  data = 0;
  p_coin = 100000;

  spt_hand_num = 0;
  spt_score = 0;
  spt_type = 0;
  spt_data = 0;
  hit_num = 0;
  /*変数の初期化*/

  /*bool*/
  spt_flg = false;
  split = false;
  hit = std = dbl = spt = bet = ins_btn = false;
  ins_flg = insurance = false;
  win = los = bst = psh = BlackJack = game_flg = spt_a = false;
  D_BJ = D_bst = false;
  spt_win = spt_los = spt_bst = spt_psh = spt_BJ = false;
  bet_flg = false;
  now_game_flg = true;
  /*bool*/

  /*初期位置*/
  mouseX = mouseY = 0;
  img_x = 600;
  img_y = 560;

  hit_x = 755;
  hit_y = std_y = dbl_y = spt_y = 650;
  ins_y = hit_y - 62;

  std_x = hit_x + 125;
  dbl_x = hit_x + 245;
  spt_x = hit_x + 365;
  ins_x = hit_x + 365;

  hit_w = std_w = dbl_w = spt_w = ins_w = 105;
  hit_h = std_h = dbl_h = spt_h = ins_h = 42;
  hit_r = std_r = spt_r = dbl_r = ins_r = 1;
  /*初期位置*/

  /*画像ハンドル*/
  for (int i = 0; i < 5; i++) {

    for (int j = 0; j < 13; j++) {

      card_type[i][j] = card_hdl[j + (i * 13)];

    }

  }

  hit_img = LoadGraph("Resource/image/BJ_Image/Hit_105.png");
  std_img = LoadGraph("Resource/image/BJ_Image/Stand_105.png");
  dbl_img = LoadGraph("Resource/image/BJ_Image/Double_105.png");
  spt_img = LoadGraph("Resource/image/BJ_Image/Split_105.png");
  ins_img = LoadGraph("Resource/image/BJ_Image/Insurance.png");
  /*画像ハンドル*/

  /*SE*/
  Bottun_SE_ = LoadSoundMem("Resource/se/pageOne_SE/トランプ・引く02.wav");
  ChangeVolumeSoundMem(150, Bottun_SE_);
  /*SE*/

}

Player::~Player() {

}

void Player::Initialize() {

  /*変数初期化*/
  hand_num = 0;
  if (!hand.empty()) { hand.erase(hand.begin(), hand.end()); }
  score = 0;

  spt_hand_num = 0;
  if (!spt_hand.empty()) { spt_hand.erase(spt_hand.begin(), spt_hand.end()); }
  spt_score = 0;
  hit_num = 0;

  type = 0;
  spt_type = 0;
  ins_coin = 0;
  /*変数初期化*/

  /*bool*/
  split = false;
  spt_flg = false;
  D_spt_dbl = false;
  D_dbl = false;

  hit = std = dbl = spt = bet = false;
  win = los = bst = psh = BlackJack = spt_a = false;
  spt_win = spt_los = spt_bst = spt_psh = spt_BJ = spt_std = false;
  D_BJ = D_bst = false;
  game_flg = true;
  now_game_flg = true;
  insurance = ins_btn = ins_flg = false;
  /*bool*/


}


/*ゲーム実行*/
bool Player::Play(Shoe* shoe ,Dealer* Dr) {
  if (hit) {
    hit_r = 1.2;
    hit = false;
    PlaySoundMem(Bottun_SE_, DX_PLAYTYPE_BACK, TRUE);
  }
  else hit_r = 1;

  if (!std)std_r = 1;
  if (!dbl)dbl_r = 1;

  if (ins_btn) {

    ins_r = 1.2;
    ins_btn = false;
    ins_coin = bet_coin / 2;
    p_coin -= ins_coin;
    PlaySoundMem(Bottun_SE_, DX_PLAYTYPE_BACK, TRUE);
  }
  else {
    ins_r = 1;
  }

  if (game_flg) {
    /*ボタン処理（hit,stand,double,splite）*/

    hit = Player::ButtonHit(hit_x, hit_y, hit_w, hit_h);

    if (ins_flg && Player::ButtonHit(ins_x, ins_y, ins_w, ins_h)) {
      ins_btn = true;
      insurance = true;
    }

    if (Player::ButtonHit(spt_x, spt_y, spt_w, spt_h) && !spt) {
      spt = true;
      spt_r = 1.2;
      PlaySoundMem(Bottun_SE_, DX_PLAYTYPE_BACK, TRUE);
    }
    else spt_r = 1;
    if (spt && spt_flg) {
      if (BJ.Wait_Time(0.2)) {
        spt_flg = false;
      }

    }
    if (Player::ButtonHit(std_x, std_y, std_w, std_h) || dbl) {
      std = true;
      PlaySoundMem(Bottun_SE_, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Player::ButtonHit(dbl_x, dbl_y, dbl_w, dbl_h) && (hand_num == 2 || spt_hand_num == 2) && (p_coin > bet_coin || p_coin > spt_bet_coin)) {

      PlaySoundMem(Bottun_SE_, DX_PLAYTYPE_BACK, TRUE);
      if (p_coin < bet_coin || p_coin < spt_bet_coin) {
        std = true;
      }
      else {
        dbl = true;
      }
    }

    /*ボタン処理（hit,stand,double,splite）*/
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
          if (Player::Calc() == 21 && now_game_flg) {

            /*勝負開始（stand自動実行）*/
            BlackJack = true;
            std = true;
            game_flg = false;
            now_game_flg = false;

          }

        }

        if (Player::Calc() == 21) {

          std = true;

        }

        if (Dr->Set_Ins() && !insurance) {
          ins_flg = true;
        }
        if (insurance) {
          if(BJ.Wait_Time(0.2))ins_flg = false;
        }

        /*hitが入力された場合*/
        if (hit) {
          ins_flg = false;
          /*カードの配布*/
          Player::Hit(shoe);

        }
        /*standが入力された場合*/
        else if (std) {
          std_r = 1.2;
          /*勝負開始して返り値をtrueとして終了*/
          game_flg = false;
          std = false;
          ins_flg = false;
          now_game_flg = false;
          return true;

        }
        /*doubleが入力された場合*/
        else if (dbl && hand_num <= 2) {
          dbl_r = 1.2;
          /*カードを引いて勝負開始*/
          Player::Hit(shoe);
          Player::Set_Bet(bet_coin);
          D_dbl = true;

        }
        /*splitが入力された場合*/
        else if (hand_num == 2) {

          if ((hand[0] % 13) == (hand[1] % 13) || (hand[0] % 13 > 8 && hand[1] % 13 > 8)) {
            spt_flg = true;
            if (spt) {

              if (hand[0] % 13 == 0 && hand[1] % 13 == 0) {

                spt_a = true;

              }
              ins_flg = false;
              spt_bet_coin = bet_coin;
              Player::Set_Bet(spt_bet_coin);
              split = true;
              spt_hit = false;
              Player::Hit(shoe);
            }

          }


        }

      }
      /*バーストしていた場合*/
      if (Player::Calc() > 21) {

        bst = true;
        std = true;
        game_flg = false;
        now_game_flg = false;
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
          if (Player::Calc() == 21 && Player::Spt_Calc() == 21 && now_game_flg) {

            /*勝負開始（stand自動実行）*/
            BlackJack = true;
            spt_BJ = true;
            game_flg = false;
            now_game_flg = false;
            return true;

          }

          if (Player::Calc() == 21 && now_game_flg) {
            BlackJack = true;
            std = true;
          }

          if (Player::Spt_Calc() == 21 && now_game_flg && !spt_std) {
            spt_BJ = true;
            spt_std = true;
          }

        }

        if ((Player::Calc() == 21 && hit_num < 1)) {

          std = true;

        }
        if (Player::Spt_Calc() == 21) {
          if (hit_num >= 1) {
            std = true;
            spt_std = true;
          }
          else {
            spt_std = true;
          }

        }

        /*hitが入力された場合*/
        if (hit) {

          /*カードの配布*/
          Player::Hit(shoe);

        }
        /*standが入力された場合*/
        else if (std && !spt_std) {
          std_r = 1.2;
          if (hit_num < 1) {

            hit_num++;

          }
          else {
            hit_num = 2;
            /*勝負開始して返り値をtrueとして終了*/
            game_flg = false;
            now_game_flg = false;
            return true;

          }

          std = false;

        }
        else if (spt_std && std) {

          std_r = 1.2;
          hit_num = 2;
          /*勝負開始して返り値をtrueとして終了*/
          game_flg = false;
          now_game_flg = false;
          return true;

          std = false;

        
        }
        /*doubleが入力された場合*/
        else if (dbl && (hand_num <= 2 || spt_hand_num <= 2)) {
          dbl_r = 1.2;
          /*カードを引いて勝負開始*/
          if (hand_num <= 2 && hit_num < 1) {
            Set_Bet(bet_coin);
            bet_coin *= 2;
            D_dbl = true;
          }
          if (spt_hand_num <= 2 && hit_num >= 1) {
            Set_Bet(spt_bet_coin);
            if (D_dbl)bet_coin *= 2;
            spt_bet_coin *= 2;
            D_spt_dbl = true;
          }
          Player::Hit(shoe);
          dbl = false;
          std = true;

        }

        if (Player::Calc() > 21 && hit_num < 1) {

          bst = true;
          los = true;
          std = true;

        }
        else if (Player::Spt_Calc() > 21 && hit_num == 1) {

          spt_bst = true;
          spt_los = true;
          hit_num = 2;
          std = true;

        }

      }
      else {
        game_flg = false;
        now_game_flg = false;
      }

    }
  }
  else {
    now_game_flg = false;
    std_r = 1;
  }

  /*バーストしているのでfalseを返して終了*/
  return false;

}

void Player::Draw() {

  SetFontSize(32);
  if(ins_flg)DrawRotaGraph(ins_x + ins_w / 2, ins_y + ins_h / 2, ins_r, 0, ins_img, true);
  if (insurance)DrawFormatString(520, 0, 0xff00ff, "Insurance：%d", ins_coin);
  /*ボタン表示*/

  DrawRotaGraph(hit_x + hit_w / 2, hit_y + hit_h / 2, hit_r, 0, hit_img, true);
  DrawRotaGraph(std_x + std_w / 2, std_y + std_h / 2, std_r, 0, std_img, true);
  if ((hand_num == 2 || spt_hand_num == 2) && game_flg) {
    if (p_coin < bet_coin || p_coin < spt_bet_coin); else DrawRotaGraph(dbl_x + dbl_w / 2, dbl_y + dbl_h / 2, dbl_r, 0, dbl_img, true);
  }

  if (spt_flg && game_flg) {

    DrawRotaGraph(spt_x + spt_w / 2, spt_y + spt_h / 2, spt_r, 0, spt_img, true);

  }
  /*ボタン表示*/
  /*所持金表示*/
  if (!split) {

    if (D_dbl)DrawFormatString(500, 630, 0xffffff, "掛金：%d", bet_coin * 2);
    else DrawFormatString(500, 630, 0xffffff, "掛金：%d", bet_coin);

  }
  else {

    DrawFormatString(440, 630, 0xffffff, "%d", bet_coin);
    DrawFormatString(640, 630, 0xffffff, "%d", spt_bet_coin);
  }
  DrawFormatString(500, 680, 0xffffff, "所持金：%d", p_coin);
  /*所持金表示*/
  SetFontSize(DEFAULT_FONT_SIZE);

  Player::Show_Hand();
  if (split) {
    Player::Spt_Show_Hand();
  }
  Player::Show_Play();

  /*デバッグ用*/
  Player::Debug_Draw(true);
  /*デバッグ用*/

}
void Player::Debug_Draw(bool debug) {

  if (debug) {

    //DrawFormatString(spt_x, spt_y/100+40, color, "%d",hit+c);
    //DrawFormatString(spt_x, spt_y / 100 +60, color2, "%d",std+c2);
    //DrawFormatString(spt_x, spt_y / 100 +80, color3, "%d",dbl+c3);
    //DrawFormatString(spt_x, spt_y / 100 +100, color4, "%d",spt+c4);
    //DrawFormatString(spt_x+40, spt_y / 100 +40, color4, "p_coin：%d",p_coin);
    //DrawFormatString(spt_x+40, spt_y / 100 +80, color4, "spt_num：%d",spt_hand_num);
    //DrawFormatString(spt_x+40, spt_y / 100 +60, color4, "spt_a：%d",spt_a);

    //DrawFormatString(spt_x+40, spt_y / 100 +100, color4, "%d",dealer_calc);

    DrawFormatString(spt_x - 80, spt_y / 100 + 40, 0xffffff, "%Win %d", win);
    DrawFormatString(spt_x - 80, spt_y / 100 + 60, 0xffffff, "Los %d", los);
    DrawFormatString(spt_x - 80, spt_y / 100 + 80, 0xffffff, "psh %d", psh);
    DrawFormatString(spt_x - 80, spt_y / 100 + 100, 0xffffff, "BlJ %d", BlackJack);
    DrawFormatString(spt_x - 80, spt_y / 100 + 120, 0xffffff, "bst %d", bst);
    DrawFormatString(spt_x - 80, spt_y / 100 + 140, 0xffffff, "spt_win %d", spt_win);
    DrawFormatString(spt_x - 80, spt_y / 100 + 160, 0xffffff, "spt_bst %d", spt_bst);
    DrawFormatString(spt_x - 80, spt_y / 100 + 180, 0xffffff, "spt_los %d", spt_los);
    DrawFormatString(spt_x - 80, spt_y / 100 + 200, 0xffffff, "spt_psh %d", spt_psh);
    DrawFormatString(spt_x - 80, spt_y / 100 + 220, 0xffffff, "D_dbl %d", D_dbl);
    DrawFormatString(spt_x - 80, spt_y / 100 + 240, 0xffffff, "D_spt_dbl %d", D_spt_dbl);
    DrawFormatString(spt_x - 80, spt_y / 100 + 260, 0xffffff, "hit_num %d", hit_num);
    DrawFormatString(spt_x - 80, spt_y / 100 + 280, 0xffffff, "bet_flg %d", bet_flg);
    DrawFormatString(spt_x - 80, spt_y / 100 + 300, 0xffffff, "spt_BJ %d", spt_BJ);
    DrawFormatString(spt_x - 80, spt_y / 100 + 320, 0xffffff, "D_BJ %d", D_BJ);

  }

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
        spt_hit = false;

      }
      else {
        /*配列の最後にカードを追加*/
        spt_hand.push_back(shoe->Take_Card());
        spt_hand_num++;   /*手札枚数を増やす*/
        spt_hit = true;
      }


    }

  }
  else {

    /*配列の最後にカードを追加*/
    hand.push_back(shoe->Take_Card());
    hand_num++;   /*手札枚数を増やす*/

  }

}

/*手札を表示*/
void Player::Show_Hand() {
  /*標準出力*/

  /*配列の最初から最後までを順に表示*/
  for (int i = 0; i < hand_num; i++) {
    /*カードの種類（スペード、ハート、ダイヤ、クラブ）を探索*/
    type = (hand[i] % 52) / 13;   /*デッキごとに分けた後、13で割った数（0-3）で4種類を分割*/

    if (!split) {
      DrawRotaGraph(img_x + i * 30, img_y, img_size, 0, card_type[type][hand[i] % 13], 1);
    }
    else {
      DrawRotaGraph(img_x - 120 + i * 30, img_y, img_size, 0, card_type[type][hand[i] % 13], 1);
    }

  }

  SetFontSize(60);
  if (!split) {
    DrawFormatString(570, 440, 0, "%d\n", Player::Calc());
  }
  else {
    DrawFormatString(460, 440, 0, "%d\n", Player::Calc());
  }
  SetFontSize(DEFAULT_FONT_SIZE);

}
/*手札を表示*/
void Player::Spt_Show_Hand() {
  /*標準出力*/

  /*配列の最初から最後までを順に表示*/
  for (int i = 0; i < spt_hand_num; i++) {
    /*カードの種類（スペード、ハート、ダイヤ、クラブ）を探索*/
    spt_type = (spt_hand[i] % 52) / 13;   /*デッキごとに分けた後、13で割った数（0-3）で4種類を分割*/

    /*アニメーション予定地_Player_spt*/
    DrawRotaGraph(img_x + 80 + i * 30, img_y, img_size, 0, card_type[spt_type][spt_hand[i] % 13], 1);
    if (hit_num >= 1) {
      DrawGraph(440, 530, std_img, true);
    }
    if (hit_num >= 2 || spt_std) {
      DrawGraph(640, 530, std_img, true);
    }
  }

  SetFontSize(60);
  DrawFormatString(650, 440, 0, "%d\n", Player::Spt_Calc());
  SetFontSize(DEFAULT_FONT_SIZE);

}

void Player::Show_Play() {

  if (!split) {

    if (D_BJ) {
      DrawRotaGraph(620, 300, 1, 0, btn_hdl[4], 1);
    }
    if (win) {

      if (D_bst) {

        DrawRotaGraph(620, 300, 1, 0, btn_hdl[2], 1);
        if (BlackJack)DrawRotaGraph(620, 400, 1, 0, btn_hdl[4], 1);
        else DrawRotaGraph(620, 400, 1, 0, btn_hdl[0], 1);

      }
      else if (BlackJack) {

        DrawRotaGraph(620, 400, 1, 0, btn_hdl[4], 1);

      }
      else {
        if (!BlackJack)DrawRotaGraph(620, 400, 1, 0, btn_hdl[0], 1);
      }

    }
    else if (los) {

      if (bst) {

        DrawRotaGraph(620, 400, 1, 0, btn_hdl[2], 1);

      }
      else {

        DrawRotaGraph(620, 400, 1, 0, btn_hdl[1], 1);

      }

    }
    else if (psh) {

      DrawRotaGraph(620, 400, 1, 0, btn_hdl[3], 1);

    }

  }
  else if (split) {

    if (D_bst) {
      DrawRotaGraph(620, 300, 1, 0, btn_hdl[2], 1);
    }
    if (D_BJ) {
      DrawRotaGraph(620, 300, 1, 0, btn_hdl[4], 1);
    }
    if (BlackJack && spt_BJ) {
      DrawRotaGraph(620, 410, 1, 0, btn_hdl[4], 1);
    }
    if (BlackJack && !spt_BJ) {
      DrawRotaGraph(490, 410, 1, 0, btn_hdl[4], 1);
    }
    if (spt_BJ && !BlackJack) {
      //DrawFormatString(0, 620, 0xffffff, "BlackJack\n");
      DrawRotaGraph(700, 410, 1, 0, btn_hdl[4], 1);
    }
    if (win && !BlackJack) {
      //DrawFormatString(100, 640, 0xffffff, "手札1の勝ち\n");
      DrawRotaGraph(490, 410, 1, 0, btn_hdl[0], 1);
    }
    if (spt_win && !spt_BJ) {
      //DrawFormatString(100, 620, 0xffffff, "手札2の勝ち\n");
      DrawRotaGraph(700, 410, 1, 0, btn_hdl[0], 1);
    }
    if (los && !bst) {
      //DrawFormatString(100, 600, 0xffffff, "手札1の負け\n");
      DrawRotaGraph(490, 410, 1, 0, btn_hdl[1], 1);
    }
    else if (bst) {
      //DrawFormatString(100, 580, 0xffffff, "手札1のバスト\n");
      DrawRotaGraph(490, 410, 1, 0, btn_hdl[2], 1);
    }
    if (spt_los && !spt_bst) {
      //DrawFormatString(100, 560, 0xffffff, "手札2の負け\n");
      DrawRotaGraph(700, 410, 1, 0, btn_hdl[1], 1);
    }
    else if (spt_bst) {
      //DrawFormatString(100, 540, 0xffffff, "手札2のバスト\n");
      DrawRotaGraph(700, 410, 1, 0, btn_hdl[2], 1);
    }
    if (psh) {
      //DrawFormatString(100, 520, 0xffffff, "手札1の引き分け\n");
      DrawRotaGraph(490, 410, 1, 0, btn_hdl[3], 1);
    }
    if (spt_psh) {
      //DrawFormatString(100, 500, 0xffffff, "手札2の引き分け\n");
      DrawRotaGraph(700, 410, 1, 0, btn_hdl[3], 1);
    }

  }

}

void Player::Score(Player player, Dealer dealer) {   /*プレイヤーとディーラーのスコア勝負*/
  /*最終スコアがプレイヤーのほうが高い場合*/

  if (win) {
    if (bet_flg) {

      if (split) {

          if (!BlackJack && !D_dbl)p_coin += dealer.Set_Magnification(rate_wn, bet_coin);
          if (D_dbl) {
            p_coin += dealer.Set_Magnification(rate_db, bet_coin);
          }
          if (BlackJack && !D_dbl)p_coin += dealer.Set_Magnification(rate_bj, bet_coin);

          if (!spt_BJ && !D_dbl)p_coin += dealer.Set_Magnification(rate_wn, spt_bet_coin);
          if (D_spt_dbl) {
            p_coin += dealer.Set_Magnification(rate_db, spt_bet_coin);
          }
          if (BlackJack && !D_dbl)p_coin += dealer.Set_Magnification(rate_bj, spt_bet_coin);
          if (spt_BJ && !D_spt_dbl)p_coin += dealer.Set_Magnification(rate_bj, spt_bet_coin);


        bet_flg = false;
      }
      else {

          if (!BlackJack && !D_dbl)p_coin += dealer.Set_Magnification(rate_wn, bet_coin);
          if (D_dbl) {
            p_coin += dealer.Set_Magnification(rate_db, bet_coin);
          }
          if (BlackJack && !D_dbl)p_coin += dealer.Set_Magnification(rate_bj, bet_coin);


        bet_flg = false;
      }
    }
  }
  else if (psh) {

    if (bet_flg) {

      if (insurance && D_BJ) {
        p_coin += dealer.Set_Magnification(rate_ps, ins_coin);
        insurance = false;
      }
      p_coin += dealer.Set_Magnification(rate_ps, bet_coin);

      bet_flg = false;
    }

  }

  D_BJ = dealer.BlackJack();
  if (dealer.Calc() > 21) {
    D_bst = true;
    if (!bst) {
      win = true;

    }
    if (!spt_bst) {
      spt_win = true;
    }
  }

  if (player.Calc() > 21) {
    bst = true;
    los = true;
  }


  if (!game_flg && !D_bst) {

    if (!split && !bst) {

      /*プレイヤーのほうが高い場合*/
      if (player.Calc() > dealer.Calc() && !D_BJ) {
        /*プレイヤーの勝利*/
        win = true;

      }
      else if (player.Calc() < dealer.Calc()) {    /*ディーラーのほうが高い場合*/

          /*プレイヤーの負け*/
        los = true;

      }
      else {    /*同点の場合*/
        /*引き分け*/
        if (D_BJ && BlackJack) {

          win = false;
          psh = true;

        }
        else if (player.Calc() == dealer.Calc() && !D_BJ && !BlackJack) {
          win = false;
          psh = true;

        }
        else {
          win = true;
        }

      }

    }
    else if (split && bet_flg) {

      /*プレイヤーのほうが高い場合*/
      if (player.Calc() > dealer.Calc() && !bst) {
        /*プレイヤーの勝利*/
        win = true;
        p_coin += dealer.Set_Magnification(rate_wn, bet_coin);

      }
      if (player.Spt_Calc() > dealer.Calc() && !spt_bst) {

        /*split手札の勝利*/
        spt_win = true;
        p_coin += dealer.Set_Magnification(rate_wn, spt_bet_coin);

      }
      if (player.Calc() < dealer.Calc()) {    /*ディーラーのほうが高い場合*/

        /*プレイヤーの負け*/
        los = true;

      }
      if (player.Spt_Calc() < dealer.Calc()) {

        spt_los = true;

      }
      /*引き分け*/
      if (D_BJ && BlackJack && spt_BJ) {

        psh = true;
        p_coin += dealer.Set_Magnification(rate_ps, bet_coin + spt_bet_coin);

      }
      if (D_BJ && BlackJack && !spt_BJ) {

        psh = true;
        p_coin += dealer.Set_Magnification(rate_ps, bet_coin + spt_bet_coin);

      }
      if (D_BJ && spt_BJ) {
        spt_psh = true;
        p_coin += dealer.Set_Magnification(rate_ps, spt_bet_coin);
      }
      if (player.Calc() == dealer.Calc() && !BlackJack && !D_BJ) {

        psh = true;
        p_coin += dealer.Set_Magnification(rate_ps, bet_coin);

      }
      if (player.Spt_Calc() == dealer.Calc() && !spt_BJ && !D_BJ) {

        spt_psh = true;
        p_coin += dealer.Set_Magnification(rate_ps, spt_bet_coin);

      }
      bet_flg = false;

    }

  }

  if (bet_flg) {

    if (split) {
      if (insurance && D_BJ) {
        p_coin += dealer.Set_Magnification(rate_is, ins_coin);
        insurance = false;
        bet_flg = false;
      }
    }
    else {
      if (insurance && D_BJ) {
        p_coin += dealer.Set_Magnification(rate_is, ins_coin);
        insurance = false;
        bet_flg = false;
      }
    }

  }

}


int Player::P_MaxCoin() {

  return p_coin;

}


void Player::Bet_Flg(bool get_flg) {
  bet_flg = get_flg;
}

void Player::Set_Bet(int setbet) {
  bet_coin = setbet;
  p_coin -= bet_coin;
}

bool Player::Now_Game() {
  return now_game_flg;
}

bool Player::ButtonHit(int x, int y, int w, int h) {

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

bool Player::P_BJ() {

  if (split) {

    if (BlackJack && spt_BJ) {
      return BlackJack;
    }

  }
  else {

    return BlackJack;
  }

}
