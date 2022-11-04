#include"BJ_Head.h"

BlackJack::BlackJack() {

  shoe = new Shoe();
  player = new Player();
  dealer = new Dealer();

  game_endflg = false;
  next_flg = true;

  hit_flg = 0;

  end_img = LoadGraph("Resource/image/BJ_Image/BJ_Help.png");
  game_img = LoadGraph("Resource/image/BJ_Image/BJ_Game.png");
  title_img = LoadGraph("Resource/image/BJ_Image/BJ_Title.png");

  shoe->Inisialize();
  player->Initialize();
  dealer->Initialize();
}

BlackJack::~BlackJack() {

  delete shoe;
  delete player;
  delete dealer;

  BlackJack::Finalize();

}

void BlackJack::Initialize() {

  shoe->Inisialize();
  player->Initialize();
  dealer->Initialize();
  next_flg = true;

  hit_flg = 0;

}

void BlackJack::Update() {

  //player->Update();
    /*ゲームを開始 or 続けるか判定*/

  if (next_flg) {

    BlackJack::Initialize();
    next_flg = false;

  }
  if (hit_flg < 1) {
    dealer->Hit(shoe);
    hit_flg++;
  }
  if (player->Play(shoe)) {

    dealer->Play(shoe);
    player->Score(*player, *dealer);

  }
  if (!game_endflg) {

    if (player->ButtonHit(280,480,20,40)) {

      next_flg = true;

    }
    if (player->ButtonHit(340,480,20,40)) {

      game_endflg = true;

    }

  }

}
void BlackJack::Draw() {

  //DrawGraph(0,0,title_img,true);
  DrawGraph(0,0,game_img,true);
  //DrawGraph(0,0,end_img,true);

  player->Draw();
  dealer->Draw();

  DrawFormatString(550, 100, 0xffffff, "ゲーム画面");

  DrawFormatString(100, 80, 0xffffff, "ゲームを開始しますか？\n");
  DrawFormatString(100, 100, 0xffffff, "==============\n");
  DrawFormatString(100, 120, 0xffffff, "BLACK JACK\n");
  DrawFormatString(100, 140, 0xffffff, "==============\n");
  DrawFormatString(100, 160, 0xffffff, "player\n");
  DrawFormatString(100, 180, 0xffffff, "==============\n");
  DrawFormatString(100, 200, 0xffffff, "==============\n");
  DrawFormatString(100, 220, 0xffffff, "dealer\n");
  DrawFormatString(100, 240, 0xffffff, "==============\n");
  DrawFormatString(100, 260, 0xffffff, "==============\n");
  if (!next_flg) {
    DrawFormatString(100, 480, 0xffffff, "ゲームを続けますか？ yes or no\n");
  }
  if (game_endflg) {
    DrawFormatString(100, 500, 0xffffff, "ゲームを終了します\n");
  }


}

void BlackJack::Finalize() {

  DeleteGraph(title_img);
  DeleteGraph(game_img);
  DeleteGraph(end_img);

}

/*勝負開始*/
/*ゲームを開始するか聞く*/
//next = buf;
//next = KeyInputSingleCharString(100, 100, 10, buf, TRUE);
//next = "yes";

//if (next != "yes" && next != "no" && next != "debug") {

//  DrawFormatString(100, 50, 0xffffff, "ゲームを開始しますか？\n");

//  if (next == "end") {
//    //break;
//  }
//}
//if (!game_endflg) {
//  /*ゲームを開始 or 続けるか判定*/
//  if (next == "yes") {
//    shoe->Inisialize();
//    player->Initialize();
//    dealer->Initialize();
//    /*カードの配布*/

//    DrawFormatString(100, 120, 0xffffff, "==============\n");

//    DrawFormatString(100, 140, 0xffffff, "BLACK JACK\n");
//    /*プレイヤーに1枚目を配布*/
//    player->Hit(shoe);
//    /*手札の表示*/

//    DrawFormatString(100, 160, 0xffffff, "==============\n");

//    DrawFormatString(100, 180, 0xffffff, "player\n");
//    player->Show_Hand();

//    DrawFormatString(100, 200, 0xffffff, "==============\n");

//    /*ディーラーに1枚目を配布*/
//    dealer->Hit(shoe);
//    /*手札の表示*/

//    DrawFormatString(100, 220, 0xffffff, "==============\n");

//    DrawFormatString(100, 240, 0xffffff, "dealer\n");
//    dealer->Show_Hand();

//    DrawFormatString(100, 240, 0xffffff, "==============\n");

//    /*プレイヤーに2枚目を配布*/
//    player->Hit(shoe);
//    /*手札の表示*/

//    DrawFormatString(100, 260, 0xffffff, "==============\n");

//    DrawFormatString(100, 280, 0xffffff, "player\n");
//    player->Show_Hand();

//    DrawFormatString(100, 300, 0xffffff, "==============\n");

//    /*ディーラーに2枚目を配布*/
//    dealer->Hit(shoe);

//    /*プレイヤーの実行*/
//    /*バーストしているかどうか判別*/
//    if (player->Play(shoe)) {   /*バーストしていない場合*/
//      /*ディーラーの手札を表示*/
//      DrawFormatString(100, 320, 0xffffff, "==============\n");
//      DrawFormatString(100, 340, 0xffffff, "dealer\n");
//      dealer->Show_Hand();
//      DrawFormatString(100, 360, 0xffffff, "==============\n");

//      /*ディーラーの自動実行*/
//      dealer->Play(shoe);
//      /*結果の表示*/
//      player->Score(*player, *dealer);

//    }
//    else {    /*バーストしている場合*/
//      /*標準出力*/

//      DrawFormatString(100, 380, 0xffffff, "Burst Player Lose\n");

//    }

//    DrawFormatString(100, 400, 0xffffff, "==============\n");
//    /*ゲームを続けるか聞く*/
//    next = "\0";
//    if (next != "yes" && next != "no" && next != "end" && next != "debug") {

//      DrawFormatString(100, 420, 0xffffff, "ゲームを続けますか？ yes or no\n");

//      if (next == "no" || next == "end") {
//        /*ゲームを終了する*/

//        DrawFormatString(100, 440, 0xffffff, "ゲームを終了します\n");
//        game_endflg = true;

//      }
//    }

//  }
//  else if (next == "end" || next == "no") {   /*ゲームを終了する場合*/

//    DrawFormatString(100, 440, 0xffffff, "ゲームを終了します\n");
//    game_endflg = true;

//  }
//  /*デバッグ用処理*/
//  if (next == "debug") {
//    /*シューの中身を見る*/
//    shoe->Show_Shoe(true);
//    next = "yes";

//  }

//}

//while (next != "yes" && next != "no" && next != "debug") {
//  DrawFormatString(100,50,0xffffff,"ゲームを開始しますか？\n");
//  if (next == "end") {
//    break;
//  }
//}
//while (!game_endflg) {
//  /*ゲームを開始 or 続けるか判定*/
//  if (next == "yes") {
//    shoe->Inisialize();
//    player->Initialize();
//    dealer->Initialize();
//    /*カードの配布*/
//    DrawFormatString(100,120,0xffffff, "==============\n");
//    DrawFormatString(100,140,0xffffff, "BLACK JACK\n");
//    /*プレイヤーに1枚目を配布*/
//    player->Hit(shoe);
//    /*手札の表示*/
//    DrawFormatString(100,160,0xffffff, "==============\n");
//    DrawFormatString(100,180,0xffffff,"player\n");
//    player->Show_Hand();
//    DrawFormatString(100,200,0xffffff, "==============\n");

//    /*ディーラーに1枚目を配布*/
//    dealer->Hit(shoe);
//    /*手札の表示*/
//    DrawFormatString(100,220,0xffffff, "==============\n");
//    DrawFormatString(100,240,0xffffff, "dealer\n");
//    dealer->Show_Hand();
//    DrawFormatString(100,240,0xffffff, "==============\n");

//    /*プレイヤーに2枚目を配布*/
//    player->Hit(shoe);
//    /*手札の表示*/
//    DrawFormatString(100,260,0xffffff, "==============\n");
//    DrawFormatString(100,280,0xffffff,"player\n");
//    player->Show_Hand();
//    DrawFormatString(100,300,0xffffff, "==============\n");

//    /*ディーラーに2枚目を配布*/
//    dealer->Hit(shoe);

//    /*プレイヤーの実行*/
//    /*バーストしているかどうか判別*/
//    if (player->Play(shoe)) {   /*バーストしていない場合*/
//      /*ディーラーの手札を表示*/
//      DrawFormatString(100,320,0xffffff, "==============\n");
//      DrawFormatString(100,340,0xffffff,"dealer\n");
//      dealer->Show_Hand();
//      DrawFormatString(100,360,0xffffff, "==============\n");

//      /*ディーラーの自動実行*/
//      dealer->Play(shoe);
//      /*結果の表示*/
//      player->Score(*player, *dealer);

//    }
//    else {    /*バーストしている場合*/
//      /*標準出力*/
//      DrawFormatString(100,380,0xffffff,"Burst Player Lose\n");

//    }
//    std::cout << "==============" << std::endl;
//    DrawFormatString(100,400,0xffffff, "==============\n");
//    /*ゲームを続けるか聞く*/
//    next = "\0";
//    while (next != "yes" && next != "no" && next != "end" && next != "debug") {
//      DrawFormatString(100,420,0xffffff, "ゲームを続けますか？ yes or no\n");
//      if (next == "no" || next == "end") {
//        /*ゲームを終了する*/
//        DrawFormatString(100,440,0xffffff, "ゲームを終了します\n");
//        game_endflg = true;

//      }
//    }

//  }
//  else if (next == "end" || next == "no") {   /*ゲームを終了する場合*/
//    DrawFormatString(100, 440, 0xffffff, "ゲームを終了します\n");
//    game_endflg = true;

//  }
//  /*デバッグ用処理*/
//  if (next == "debug") {
//    /*シューの中身を見る*/
//    shoe->Show_Shoe(true);
//    next = "yes";

//  }

//}

/*コンソール版*/
///*メイン関数*/
//int main() {
//  /*ゲーム終了フラグ*/
//  bool game_endflg = false;
//  std::string next;
//
//  /*カードシューオブジェクトの生成*/
//  Shoe shoe;
//  /*プレイヤーオブジェクトの生成*/
//  Player player;
//  /*ディーラーオブジェクトの生成*/
//  Dealer dealer;
//
//  /*勝負開始*/
//    /*ゲームを開始するか聞く*/
//  while (next != "yes" && next != "no" && next != "debug") {
//    std::cout << "ゲームを開始しますか？ yes or no" << std::endl;
//    std::cin >> next;
//    if (next == "end") {
//      break;
//    }
//  }
//  while (!game_endflg) {
//    /*ゲームを開始 or 続けるか判定*/
//    if (next == "yes") {
//      shoe.Inisialize();
//      player.Initialize();
//      dealer.Initialize();
//      /*カードの配布*/
//      std::cout << "==============" << std::endl;
//      std::cout << "BLACK JACK" << std::endl;   /*タイトル表示*/
//      /*プレイヤーに1枚目を配布*/
//      player.Hit(&shoe);
//      /*手札の表示*/
//      std::cout << "==============" << std::endl;
//      std::cout << "player" << std::endl;
//      player.Show_Hand();
//      std::cout << "==============" << std::endl;
//
//      /*ディーラーに1枚目を配布*/
//      dealer.Hit(&shoe);
//      /*手札の表示*/
//      std::cout << "==============" << std::endl;
//      std::cout << "dealer" << std::endl;
//      dealer.Show_Hand();
//      std::cout << "==============" << std::endl;
//
//      /*プレイヤーに2枚目を配布*/
//      player.Hit(&shoe);
//      /*手札の表示*/
//      std::cout << "==============" << std::endl;
//      std::cout << "player" << std::endl;
//      player.Show_Hand();
//      std::cout << "==============" << std::endl;
//
//      /*ディーラーに2枚目を配布*/
//      dealer.Hit(&shoe);
//
//      /*プレイヤーの実行*/
//      /*バーストしているかどうか判別*/
//      if (player.Play(&shoe)) {   /*バーストしていない場合*/
//        /*ディーラーの手札を表示*/
//        std::cout << "==============" << std::endl;
//        std::cout << "dealer" << std::endl;
//        dealer.Show_Hand();
//        std::cout << "==============" << std::endl;
//
//        /*ディーラーの自動実行*/
//        dealer.Play(&shoe);
//        /*結果の表示*/
//        player.Score(player, dealer);
//
//      }
//      else {    /*バーストしている場合*/
//        /*標準出力*/
//        std::cout << "Burst Player Lose" << std::endl;    /*プレイヤーの負け*/
//
//      }
//      std::cout << "==============" << std::endl;
//      /*ゲームを続けるか聞く*/
//      next = "\0";
//      while (next != "yes" && next != "no" && next != "end" && next != "debug") {
//        std::cout << "ゲームを続けますか？ yes or no" << std::endl;
//        std::cin >> next;
//        if (next == "no" || next == "end") {
//          /*ゲームを終了する*/
//          std::cout << "ゲームを終了します" << std::endl;
//          game_endflg = true;
//
//        }
//      }
//
//    }
//    else if (next == "end" || next == "no") {   /*ゲームを終了する場合*/
//      std::cout << "ゲームを終了します" << std::endl;
//      game_endflg = true;
//
//    }
//    /*デバッグ用処理*/
//    if (next == "debug") {
//      /*シューの中身を見る*/
//      shoe.Show_Shoe(true);
//      next = "yes";
//
//    }
//
//  }
//
//  return 0;
//}
