//#include"BJ_Head.h"
//
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
