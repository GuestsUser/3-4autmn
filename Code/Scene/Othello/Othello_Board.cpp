#include"DxLib.h"
#include<stdlib.h>
#include<time.h>
#include"windows.h"
#include <string.h>
#include "./../Code/GetKey.h"
#include "./Othello_Board.h"
#include "./../Scene.h"
#include "./../Title/Scene_Select.h"
#include "../Title/Scene_GameTitle.h"
#include "../../SceneManager.h"

//Othello_Board* OB;

// 初期化
void Othello_Board::Othello_Board_Initialize(Scene* scene) {

    Parent = scene;

    PutCheckImage = LoadGraph("Resource/image/Othello_Image/OthelloPutCheck2.png");     // 置ける場所のカッコの画像の読み込み
    ResultImage = LoadGraph("Resource/image/Othello_Image/Othello_Result2.png");        // リザルト画面の画像の読み込み
    Black = LoadGraph("Resource/image/Othello_Image/Black.png");            // 黒石の画像の読み込み
    White = LoadGraph("Resource/image/Othello_Image/White.png");            // 白石の画像の読み込み
    SenteGote = LoadGraph("Resource/image/Othello_Image/SenteGote.png");    // 先手・後手の画像の読み込み 

    // 勝ち・負け・引き分けの画像の読み込み
    LoadDivGraph("Resource/image/Othello_Image/winlosedraw.png", 3, 3, 1, 400, 120, WinLoseImage);
    // プレイヤーかCPUかの画像の読み込み
    LoadDivGraph("Resource/image/Othello_Image/Player.png", 2, 2, 1, 450, 150, PlayerImage);
    // ナンバー画像の読み込み
    LoadDivGraph("Resource/image/Othello_Image/Number.png", 10, 10, 1, 45, 70, NumberImage);

    Pause_Button = LoadGraph("Resource/image/PauseButton.png");     // ポーズボタンの画像の読み込み
    Pause_Back = LoadGraph("Resource/image/PauseBack.png");         // ポーズ画面の背景の画像の読み込み
    // 「つづける」ボタンの画像の読み込み
    Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
    // 「セレクトに戻る」ボタンの画像の読み込み 
    Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);

    BGM = LoadSoundMem("Resource/bgm/Othello_BGM/OthelloBGM.mp3");      // ゲーム中のBGMの読み込み
    PutSE = LoadSoundMem("Resource/se/Othello_SE/OthelloPut.mp3");      // 石を置いた時のSEの読み込み
    PassSE = LoadSoundMem("Resource/se/Othello_SE/OthelloPass.mp3");    // パスされたときのSEの読み込み
    PauseClickSE = LoadSoundMem("Resource/se/Pause_Click.wav");
    PauseSelectSE = LoadSoundMem("Resource/se/Pause_Cursor.wav");

    ChangeVolumeSoundMem(55, BGM);      // BGMの音量設定
    ChangeVolumeSoundMem(100, PutSE);   // 石を置いた時のSEの音量設定
    ChangeVolumeSoundMem(100, PassSE);  // パスされたときのSEの音量設定
    ChangeVolumeSoundMem(100, PauseClickSE);
    ChangeVolumeSoundMem(100, PauseSelectSE);


    BlackCr = GetColor(0, 0, 0);        // 黒色を設定
    GreenCr = GetColor(0, 255, 0);      // 緑色を設定
    WhiteCr = GetColor(255, 255, 255);  // 白色を設定
    RedCr = GetColor(255, 0, 0);        // 赤色を設定
    Cr = GetColor(255, 222, 173);       // 背景色を設定

    OrderNum = 0;       // 0 = 黒石、 1 = 白石
    BlackNum = 0;       // 黒石の総数の初期化
    WhiteNum = 0;       // 白石の総数の初期化
    TimeCount = 0;      // 秒数をカウントするための変数を初期化
    ReturnNumMax = 0;   // 一番多くひっくり返せる数を入れる変数
    RandomNum = 0;      // ランダムな値を入れる変数の初期化 
    PutPlace_X = -10;   // 置いた場所に十字線を描画する座標Xの初期化
    PutPlace_Y = -10;   // 置いた場所に十字線を描画する座標Yの初期化

    BoardShift_X = 180 - 99;        // ボードをずらした分のX座標の値を設定
    BoardShift_Y = (80 - 66) * 2;   // ボードをずらした分のY座標の値を設定

    SizeCount = 0.5f;

    srand(time(NULL));  // 現在の時刻を取得

    DrawFlag = false;       // カーソルが石を置ける場所に来た時に使うフラグの初期化
    CheckFlag = false;      // 石が置ける場所があるかどうか調べるときに使うフラグの初期化
    PassFlag = false;       // パスされるかどうか調べるときに使うフラグの初期化
    EndFlag = false;        // ゲームの終了条件を満たしたかどうかに使うフラグの初期化
    RandomFlag = false;     // ランダムな値を取得したかどうかに使うフラグの初期化
    PauseFlg = false;       // ポーズ画面を表示させるかどうかに使うフラグの初期化
    SizeFlag = false;

    for (int i = 0; i < 4; i++) {
        SEFlag[i] = false;
    }

    RandomOrder();      // プレイヤーが先手・後手かをランダムに決める関数
    Init_OthelloBoard(Board);           // ボードを初期化
    BoardScore(ScoreBoard);             // ボードに評価値を入れる
}

// -------------終了処理---------------------------
void Othello_Board::Othello_Board_Finalize() {
	DeleteGraph(PutCheckImage);     // カッコの画像の削除
    DeleteGraph(ResultImage);       // リザルト画面の画像の削除
    DeleteGraph(Black);             // 黒石の画像の削除
    DeleteGraph(White);             // 白石の画像の削除
    DeleteGraph(Pause_Button);      // ポーズボタンの画像の削除
    DeleteGraph(Pause_Back);        // ポーズ画面の背景の画像の削除
    DeleteGraph(SenteGote);

    // ポーズの「つづける」と「セレクトに戻る」の画像の削除
    for (int i = 0; i < 2; i++) {
        DeleteGraph(pause_continue[i]);
        DeleteGraph(pause_select[i]);
        DeleteGraph(PlayerImage[i]);
    }
    // 勝ち・負け・引き分けの画像の削除
    for (int i = 0; i < 3; i++) {
        DeleteGraph(WinLoseImage[i]);
    }

    DeleteGraph(Pause_Continue);
    DeleteGraph(Pause_Select);
    DeleteSoundMem(PutSE);      // 石を置いた時のSEの削除
    DeleteSoundMem(BGM);        // BGMの削除
    DeleteSoundMem(PauseClickSE);
    DeleteSoundMem(PauseSelectSE);
}
// ------------------------------------------------


// ---------------更新---------------------------
void Othello_Board::Othello_Board_Update() {
    GetMousePoint(&Mouse_X, &Mouse_Y);  // マウスカーソルの位置を取得

    Square_X = (Mouse_X - BoardShift_X) / MAP_SIZE;      // マウスカーソルの位置を MAP_SIZE + BoardShift_X で割った値を代入
    Square_Y = (Mouse_Y - BoardShift_Y) / MAP_SIZE;      // マウスカーソルの位置を MAP_SIZE + BoardShift_X で割った値を代入


    /* プレイヤーとCPUの操作管理 */
    if (PauseFlg == false) {

        if (EndFlag == false) {   // ゲームが終わったかどうか

            if (PassFlag == false) {    // パスフラグが false なら

                if (RandomFlag == true) {

                    PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, false);

                    switch (Player) {
                    case 0:
                        if (OrderNum == 0) {    // 黒の番だったら

                             // 黒石の置ける場所がないなら
                            if (!BoardSearchBlack(Board))
                            {
                                PlaySoundMem(PassSE, DX_PLAYTYPE_BACK, true);
                                PassFlag = true;    // パスフラグを true にする
                            }

                            BoardSearchBlack(Board);

                            if (Board[Square_X][Square_Y] == 3 ||
                                Board[Square_X][Square_Y] == 6 ||
                                Board[Square_X][Square_Y] == 8) {   // 黒石が置ける場所にカーソルがあっていたら
                                DrawFlag = true;
                                if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
                                    DrawFlag = false;
                                    Board[Square_X][Square_Y] = 1;      // 黒石を置く
                                    PutPlace_X = Square_X;
                                    PutPlace_Y = Square_Y;
                                    BlackPut();                         // 置いた場所から白を黒にひっくり返す
                                    PlaySoundMem(PutSE, DX_PLAYTYPE_BACK, true);
                                    OrderNum = 1;                       // 白の手番にする
                                    BoardSearchBWNumber(Board);         // 黒石と白石の数を数える関数実行

                                    if (EndGame(Board)) {               // ゲームが終わる条件を満たしたら
                                        EndFlag = true;   // エンドフラグを true にする
                                    }

                                    DrawFlag = false;
                                }

                            }
                            else {
                                DrawFlag = false;
                            }
                        }
                        else {      // 白の番だったら

                            //---------- CPU ----------------------

                            // もし置く場所が無かったら
                            if (!BoardSearchWhite(Board)) {
                                PlaySoundMem(PassSE, DX_PLAYTYPE_BACK, true);
                                PassFlag = true;    // パスフラグを true にする
                            }


                            // 1秒経ってから
                            if (TimeCount++ >= 60) {
                                TimeCount = 0;      // TimeCount を初期化
                                CPUWhite(Board, ScoreBoard);    // 一番ひっくり返せる場所に置く
                                PlaySoundMem(PutSE, DX_PLAYTYPE_BACK, true);
                                OrderNum = 0;       // 黒の番にする
                            }

                            BoardSearchBWNumber(Board);     // 黒石と白石の数を数える

                            // ゲームの終了条件が揃っていたら  
                            if (EndGame(Board)) {
                                EndFlag = true;     // エンドフラグを true にする
                            }
                        }
                        break;

                    case 1:
                        // ここにプレイヤーが白色で、CPUが黒色の処理を入れる
                        if (OrderNum == 0) {
                            //--------------- CPU ---------------------
                            // もし置く場所が無かったら
                            if (!BoardSearchBlack(Board)) {
                                PlaySoundMem(PassSE, DX_PLAYTYPE_BACK, true);
                                PassFlag = true;    // パスフラグを true にする
                            }

                            // 1秒経ってから
                            if (TimeCount++ >= 60) {
                                TimeCount = 0;      // TimeCount を初期化
                                CPUBlack(Board, ScoreBoard);    // 一番ひっくり返せる場所に置く
                                PlaySoundMem(PutSE, DX_PLAYTYPE_BACK, true);
                                OrderNum = 1;       // 白の番にする
                            }

                            BoardSearchBWNumber(Board);     // 黒石と白石の数を数える

                            // ゲームの終了条件が揃っていたら  
                            if (EndGame(Board)) {
                                EndFlag = true;     // エンドフラグを true にする
                            }
                        }
                        else {
                            // 白石の置ける場所がないなら
                            if (!BoardSearchWhite(Board))
                            {
                                PlaySoundMem(PassSE, DX_PLAYTYPE_BACK, true);
                                PassFlag = true;    // パスフラグを true にする
                            }

                            if (Board[Square_X][Square_Y] == 4 ||
                                Board[Square_X][Square_Y] == 6 ||
                                Board[Square_X][Square_Y] == 8) {   // 白石が置ける場所にカーソルがあっていたら
                                DrawFlag = true;
                                if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
                                    DrawFlag = false;
                                    Board[Square_X][Square_Y] = 2;      // 白石を置く
                                    PutPlace_X = Square_X;
                                    PutPlace_Y = Square_Y;
                                    WhitePut();                         // 置いた場所から黒を白にひっくり返す
                                    PlaySoundMem(PutSE, DX_PLAYTYPE_BACK, true);
                                    OrderNum = 0;                       // 黒の手番にする
                                    BoardSearchBWNumber(Board);         // 黒石と白石の数を数える関数実行

                                    if (EndGame(Board)) {               // ゲームが終わる条件を満たしたら
                                        EndFlag = true;   // エンドフラグを true にする
                                    }
                                    DrawFlag = false;
                                }

                            }
                            else {
                                DrawFlag = false;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }


    /* ポーズボタンを押した時の処理と、ポーズ画面の「つづける」と「セレクトに戻る」の処理 */
    nowKey = key->GetKeyState(REQUEST_MOUSE_LEFT); //現在のマウス左ボタンの入力状態の取
    if (PauseFlg == false) {        // ポーズボタンを押していなかったら
        if (10 <= Mouse_X && Mouse_X <= 170 && 5 <= Mouse_Y && Mouse_Y <= 75) {     // ポーズボタンの範囲を押したら
            if (OldKey != KEY_FREE && nowKey == KEY_PULL) {
                if (EndFlag == false) {
                    StopSoundMem(BGM);
                    PlaySoundMem(PauseClickSE, DX_PLAYTYPE_BACK, true);
                    PauseFlg = true;
                }
            }
        }
    }
    else if (PauseFlg == true) {   // ポーズボタンが押されていたら
        // 「つづける」ボタンか、ポーズボタンを押すとゲームを再開する
        if ((450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) ||
            (10 <= Mouse_X && Mouse_X <= 170 && 5 <= Mouse_Y && Mouse_Y <= 75)) {
            if (!SEFlag[0]) {
                PlaySoundMem(PauseSelectSE, DX_PLAYTYPE_BACK);
                SEFlag[0] = true;
            }
            if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //前の入力で左キーを話していなくて、今マウスの左キーを離した時
                PauseFlg = false;       // ポーズ画面を閉じる
                PlaySoundMem(PauseClickSE, DX_PLAYTYPE_BACK, true);
            }
        }
        else {
            SEFlag[0] = false;
        }

        // 「セレクトに戻る」を押すと、セレクト画面に戻る
        if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590){
            if (!SEFlag[1]) {
                PlaySoundMem(PauseSelectSE, DX_PLAYTYPE_BACK);
                SEFlag[1] = true;
            }
            if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //前の入力で左キーを話していなくて、今マウスの左キーを離した時
                StopSoundMem(BGM);      // BGMを止める
                PlaySoundMem(PauseClickSE, DX_PLAYTYPE_BACK, true);
                Parent->SetNext(new Scene_Select());    // セレクトシーンに移動
            }
        }
        else {
            SEFlag[1] = false;
        }
        OldKey = nowKey; //前に入力していたキーを今入力していたキーに上書きする
    }

    // リザルト画面の表示
    if (EndFlag == true) {
        // 「つづける」ボタンか、ポーズボタンを押すとゲームを再開する
        if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
            if (!SEFlag[2]) {
                PlaySoundMem(PauseSelectSE, DX_PLAYTYPE_BACK);
                SEFlag[2] = true;
            }

            //if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //前の入力で左キーを話していなくて、今マウスの左キーを離した時
            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
                PlaySoundMem(PauseClickSE, DX_PLAYTYPE_NORMAL);
                Othello_Board_Finalize();
                Othello_Board_Initialize(Parent);
            }
        }
        else {
            SEFlag[2] = false;
        }
        // 「セレクトに戻る」を押すと、セレクト画面に戻る
        if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
            if (!SEFlag[3]) {
                PlaySoundMem(PauseSelectSE, DX_PLAYTYPE_BACK);
                SEFlag[3] = true;
            }

            // if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //前の入力で左キーを話していなくて、今マウスの左キーを離した時
            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
                PlaySoundMem(PauseClickSE, DX_PLAYTYPE_BACK, true);
                StopSoundMem(BGM);                      // BGMを止める
                Parent->SetNext(new Scene_Select());    // セレクトシーンに移動
            }
        }
        else {
            SEFlag[3] = false;
        }
        OldKey = nowKey; //前に入力していたキーを今入力していたキーに上書きする
    }
}
// -----------------------------------------------


// ------------------描画-----------------------------------------------
void Othello_Board::Othello_Board_Draw() {
    // 先手・後手を分かりやすくするための処理
    if (RandomFlag == false) {
        switch (Player) {
        case 0:
            // プレイヤーが黒
            DrawRotaGraph(640, 360, 1.0, 0.0, SenteGote, TRUE);     // 背景の描画
            // "あなた"の文字のサイズを縮小・拡大を繰り返す
            if (SizeFlag == false) {
                if (SizeCount <= 1.0f) {
                    SizeCount += 0.01f;
                }
                else {
                    SizeFlag = true;
                }
            }
            else {
                if (SizeCount >= 0.5f) {
                    SizeCount -= 0.01f;
                }
                else {
                    SizeFlag = false;
                }
            }
            DrawRotaGraph(1050, 150, SizeCount, 0.0, PlayerImage[0], TRUE); // プレイヤー
            DrawRotaGraph(1050, 570, 1.0, 0.0, PlayerImage[1], TRUE);       // CPU
            if (TimeCount++ >= 180) {
                TimeCount = 0;
                RandomFlag = true;
            }
            break;

        case 1:
            // プレイヤーが白
            //DrawBox(0, 0, 1280, 720, BlackCr, true);
            DrawRotaGraph(640, 360, 1.0, 0.0, SenteGote, TRUE);
            // "あなた"の文字のサイズを縮小・拡大を繰り返す
            if (SizeFlag == false) {
                if (SizeCount <= 1.0f) {
                    SizeCount += 0.01f;
                }
                else {
                    SizeFlag = true;
                }
            }
            else {
                if (SizeCount >= 0.5f) {
                    SizeCount -= 0.01f;
                }
                else {
                    SizeFlag = false;
                }
            }
            DrawRotaGraph(1050, 150, 1.0, 0.0, PlayerImage[1], TRUE);       // CPU
            DrawRotaGraph(1050, 570, SizeCount, 0.0, PlayerImage[0], TRUE); // プレイヤー
            if (TimeCount++ >= 180) {
                TimeCount = 0;
                RandomFlag = true;
            }
            break;
        }
    }
    else {
        // 背景を一色に染める
        DrawBox(0, 0, 1280, 720, Cr, TRUE);

        // ボードの後ろを黒色で囲む
        DrawBox(60 + BoardShift_X, 60 + BoardShift_Y,
            (MAP_SIZE * 9) + BoardShift_X + 6, (MAP_SIZE * 9) + BoardShift_Y + 6, BlackCr, TRUE);

        Print_OthelloBoard(Board);      // オセロボードの描画

        switch (Player) {
        case 0:
            DrawRotaGraph(800, 184, 0.35, 0, Black, TRUE);
            DrawRotaGraph(800, 304, 0.35, 0, White, TRUE);

            DrawFormatString(800 + MAP_SIZE / 2, 167, BlackCr, "黒:%d ← あなた", BlackNum);      // 黒石の現在の数を表示
            DrawFormatString(800 + MAP_SIZE / 2, 287, BlackCr, "白:%d ← C P U", WhiteNum);      // 白石の現在の数を表示

            break;
        case 1:
            DrawRotaGraph(800, 184, 0.35, 0, Black, TRUE);
            DrawRotaGraph(800, 304, 0.35, 0, White, TRUE);

            DrawFormatString(800 + MAP_SIZE / 2, 167, BlackCr, "黒:%d ← C P U", BlackNum);      // 黒石の現在の数を表示
            DrawFormatString(800 + MAP_SIZE / 2, 287, BlackCr, "白:%d ← あなた", WhiteNum);      // 白石の現在の数を表示

            break;
        }

    
    // ----- ゲームの終了条件を満たしたら -----
    if (EndFlag == true) {

        if (WhiteNum < BlackNum) {  // 黒石の数の方が多かったら、黒の勝利
            switch (Player) {
            case 0: // プレイヤーが黒で黒の方が多かったら
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[0], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d ← あなた", BlackNum);      // 黒石の現在の数を表示
                DrawFormatString(660, 445, BlackCr, "%d", WhiteNum);                // 白石の現在の数を表示

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;

            case 1: // プレイヤーが白で黒の方が多かったら
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[1], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d", BlackNum);                // 黒石の現在の数を表示
                DrawFormatString(660, 445, BlackCr, "%d ← あなた", WhiteNum);      // 白石の現在の数を表示

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;
            }
        }
        else if (BlackNum < WhiteNum) { // 白石の数の方が多かったら、白の勝利
            switch (Player) {
            case 0: // プレイヤーが黒で白の方が多かったら
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[1], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d ← あなた", BlackNum);      // 黒石の現在の数を表示
                DrawFormatString(660, 445, BlackCr, "%d", WhiteNum);                // 白石の現在の数を表示

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;

            case 1: // プレイヤーが白で白の方が多かったら
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[0], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d", BlackNum);                // 黒石の現在の数を表示
                DrawFormatString(660, 445, BlackCr, "%d ← あなた", WhiteNum);      // 白石の現在の数を表示

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;
            }
        }
        else {  // 引き分けなら
            switch (Player) {
            case 0: // プレイヤーが黒
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[2], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d ← あなた", BlackNum);      // 黒石の現在の数を表示
                DrawFormatString(660, 445, BlackCr, "%d", WhiteNum);                // 白石の現在の数を表示

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;

            case 1: // プレイヤーが白
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[2], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d", BlackNum);                 // 黒石の現在の数を表示
                DrawFormatString(660, 445, BlackCr, "%d ← あなた", WhiteNum);      // 白石の現在の数を表示

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;
            }
        }
    }
    // ----- ゲームの最中なら -----
    else {
        if (PassFlag == false) {    // パスされてないなら
            switch (Player) {
            case 0:
                if (OrderNum == 0) {    // 黒の番だったら
                    DrawFormatString(800, 90, BlackCr, "あなたの番です");
                    BoardSearchBlack(Board);    // 黒石が置ける場所を描画する
                }
                else {                  // 白の番だったら
                    DrawFormatString(800, 90, BlackCr, "CPUの番です");
                    BoardSearchWhite(Board);    // 白石が置ける場所を描画する
                }
                break;

            case 1:
                if (OrderNum == 0) {    // 黒の番だったら
                    DrawFormatString(800, 90, BlackCr, "CPUの番です");
                    BoardSearchBlack(Board);    // 黒石が置ける場所を描画する
                }
                else {                  // 白の番だったら
                    DrawFormatString(800, 90, BlackCr, "あなたの番です");
                    BoardSearchWhite(Board);    // 白石が置ける場所を描画する
                }
                break;
            }
        }
        else {

            DrawFormatString(800, 90, BlackCr, "パス！");      // パス！と表示する
            // 1秒経ったら
            if (TimeCount++ >= 60)
            {
                TimeCount = 0;      // TimeCount を初期化

                // 黒の手番なら白の手番にして、白の手番なら黒の手番にする
                if (OrderNum == 0)
                {
                    OrderNum = 1;
                }
                else
                {
                    OrderNum = 0;
                }
                PassFlag = false;   // パスフラグを false にする
            }
        }

        // ----- 置いた場所を示す十字の線を描画 -----
        DrawLine((PutPlace_X * MAP_SIZE - 10) + (MAP_SIZE / 2) + BoardShift_X, PutPlace_Y * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_Y,
            (PutPlace_X * MAP_SIZE + 10) + (MAP_SIZE / 2) + BoardShift_X, PutPlace_Y * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_Y, RedCr, 3);

        DrawLine(PutPlace_X * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_X, (PutPlace_Y * MAP_SIZE - 10) + (MAP_SIZE / 2) + BoardShift_Y,
            PutPlace_X * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_X, (PutPlace_Y * MAP_SIZE + 10) + (MAP_SIZE / 2) + BoardShift_Y, RedCr, 3);
        // ------------------------------------------


        // ----- ポーズ画面を表示 -------------------------------------------------------
        if (PauseFlg == true) {
            DrawRotaGraph(650, 380, 1.15, 0, Pause_Back, TRUE);
            if (450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) {
                if (nowKey == KEY_HOLD) {
                    DrawRotaGraph(650, 380, 0.9, 0, pause_continue[1], TRUE);
                }
                else {
                    DrawRotaGraph(650, 380, 1.0, 0, pause_continue[1], TRUE);
                }
            }
            else {
                DrawRotaGraph(650, 380, 1.0, 0, pause_continue[0], TRUE);
            }
            if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
                if (nowKey == KEY_HOLD) {
                    DrawRotaGraph(650, 530, 0.9, 0, pause_select[1], TRUE);
                }
                else {
                    DrawRotaGraph(650, 530, 1.0, 0, pause_select[1], TRUE);
                }
            }
            else {
                DrawRotaGraph(650, 530, 1.0, 0, pause_select[0], TRUE);
            }
        }
    }
    DrawRotaGraph(90, 40, 0.9, 0, Pause_Button, TRUE);      // ポーズボタンの表示
    // ------------------------------------------------------------------------
    }
    DrawFormatString(900, 600, WhiteCr, "%d", RandomNum);
}
// ---------------------------------------------------------------------


/* 
* ボードを初期化する
* 引数: Board を入れる
* 戻り値：なし
*/
void Othello_Board::Init_OthelloBoard(int board[PB][PB]) {

    static int InitBoard[PB][PB] =
    {
     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  2,  1,  0,  0,  0, -1},
     {-1,  0, 0,   0,  1,  2,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    };
    memcpy(board, InitBoard, sizeof(InitBoard));
}


/*
* ボードの1マスずつに評価値を入れる
* 引数: ScoreBoard を入れる
* 戻り値：なし
*/
void Othello_Board::BoardScore(int scoreboard[PB][PB]) {
    static int boardScore[PB][PB] =
    {
     {-99, -1, -1, -1, -1, -1, -1, -1, -1, -1},
     {-1, 50,-10, 10, -2, -2, 10,-10, 50, -1},
     {-1,-10,-20, -2, -5, -5, -2,-20,-10, -1},
     {-1, 10, -2,  5, -2, 11,  5, -1, 10, -1},
     {-1, -2, -5, -2,  0,  0, -2, -5, -2, -1},
     {-1, -2, -5, -2,  0,  0, -2, -5, -2, -1},
     {-1, 10, -2,  5, -2, -2,  5, -1, 10, -1},
     {-1,-10,-20, -2, -5, -5, -2,-20,-10, -1},
     {-1, 50,-10, 10, -2, -2, 10,-10, 50, -1},
     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    };
    memcpy(scoreboard, boardScore, sizeof(boardScore));
}


/*
* ボードを表示する
* 引数: Board を入れる
* 戻り値：なし
*/
void Othello_Board::Print_OthelloBoard(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {

            /* 特に強くもない何も置かれていない */
            if (board[i][j] == 0) {

                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "0");
            }

            /* 黒石が置かれている */
            if (board[i][j] == 1) {

                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);

                // 黒石を置く
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_X, 
                    j * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_Y, 27, BlackCr, TRUE);
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "1");

            }

            /* 白石が置かれている */
            if (board[i][j] == 2) {

                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);

                // 白石を置く
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_X, 
                    j * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_Y, 27, WhiteCr, TRUE);
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "2");

            }

            /* 黒石が置ける場所 */
            if (board[i][j] == 3) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE + BoardShift_X, j * MAP_SIZE + BoardShift_Y,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y, BlackCr, TRUE);

                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // マウスカーソルの位置がボードのマス目の上に来たマスを赤く表示する
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "3");

            }

            /* 白石が置ける場所 */
            if (board[i][j] == 4) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE + BoardShift_X, j * MAP_SIZE + BoardShift_Y,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y, BlackCr, TRUE);

                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // マウスカーソルの位置がボードのマス目の上に来たマスを赤く表示する
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "4");

            }
        }
    }
}

/*
* カーソルが置けるマスに来た時に赤く表示する
* 引数: なし
* 戻り値：なし
*/
void Othello_Board::CursorOn_OthelloBoard() {
    if (DrawFlag == true)
    {
        DrawBox((Square_X * MAP_SIZE) + BoardShift_X + 1, (Square_Y * MAP_SIZE) + BoardShift_Y + 1,
            (Square_X * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (Square_Y * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, RedCr, TRUE);
    }
}


/*
* プレイヤーの石で相手の石を挟むと自分の石の色の変える
* 引数: Board を入れる, X軸の向きを指定, Y軸の向きを指定, 敵の石, プレイヤーの石
* 戻り値：ひっくり返せる場所がなかったら retun 0, あったら return 1 を返す
*/
int Othello_Board::CursorPutOnCheck(int board[PB][PB], int p, int q, int enemy, int player) {

    int count = 0;  // CheckNum の値を入れる用変数

    // 調べた方向に対して敵の石があったら
    if (board[Square_X + p][Square_Y + q] == enemy) {

        // カーソルが合っているところから、置いた場合プレイヤーの石があるかどうか調べる
        for (CheckNum = 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != player; CheckNum++) {

            // 調べた方向に空いているマスがあったら
            if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 0 ||
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 5 ||
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 7 ||
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == -1) {
                return 0;
            }
        }


        // 調べた方向に対して player が置いてあるマスから逆順に辿って、プレイヤーが置いた場所まで戻るまで
        for (count = CheckNum - 1; board[Square_X + count * p][Square_Y + count * q] != player; count--) {

            // 調べたところが、0, 3, 4, -1 のいずれかなら return 0
            if (board[Square_X + count * p][Square_Y + count * q] == 0 ||
                board[Square_X + count * p][Square_Y + count * q] == 3 ||
                board[Square_X + count * p][Square_Y + count * q] == 4 ||
                board[Square_X + count * p][Square_Y + count * q] == 5 ||
                board[Square_X + count * p][Square_Y + count * q] == 7 ||
                board[Square_X + count * p][Square_Y + count * q] == -1) {
                return 0;
            }
        }
        // 調べた方向に対して、 もう一度逆順に辿って player の石にひっくり返す
        for (CheckNum = CheckNum - 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != player; CheckNum--) {
            // 調べたマスが enemy のマスだったら
            if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == enemy) {
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] = player;   // player の石にひっくり返す
            }
        }
    }
    return 1;
}


/*
* CPUの石で相手の石を挟むと自分の石の色の変える
* 引数: Board を入れる, X軸の向きを指定, Y軸の向きを指定, CPUのX軸の位置, CPUのY軸の位置, 敵の石, プレイヤーの石
* 戻り値：ひっくり返せる場所がなかったら retun 0, あったら return 1 を返す
*/
int Othello_Board::CPUPutOnCheck(int board[PB][PB], int p, int q, int d, int e, int enemy, int player) {

    int count = 0;  // CheckNum の値を入れる用変数

    // 調べた方向に対して敵の石があったら
    if (board[d + p][e + q] == enemy) {

        // 置いた場合、指定した方向にプレイヤーの石があるかどうか調べる
        for (CheckNum = 1; board[d + CheckNum * p][e + CheckNum * q] != player; CheckNum++) {

            // 調べた方向に空いているマスがあったら
            if (board[d + CheckNum * p][e + CheckNum * q] == 0 ||
                board[d + CheckNum * p][e + CheckNum * q] == 5 ||
                board[d + CheckNum * p][e + CheckNum * q] == 7 ||
                board[d + CheckNum * p][e + CheckNum * q] == -1) {
                return 0;
            }
        }


        // 調べた方向に対して player が置いてあるマスから逆順に辿って、プレイヤーが置いた場所まで戻るまで
        for (count = CheckNum - 1; board[d + count * p][e + count * q] != player; count--) {

            // 調べたところが、0, 3, 4, -1 のいずれかなら return 0
            if (board[d + count * p][e + count * q] == 0 ||
                board[d + count * p][e + count * q] == 3 ||
                board[d + count * p][e + count * q] == 4 ||
                board[d + count * p][e + count * q] == 5 ||
                board[d + count * p][e + count * q] == 6 ||
                board[d + count * p][e + count * q] == 7 ||
                board[d + count * p][e + count * q] == 8 ||
                board[d + count * p][e + count * q] == -1) {
                return 0;
            }
        }



        // 調べた方向に対して、 もう一度逆順に辿って player の石にひっくり返す
        for (CheckNum = CheckNum - 1; board[d + CheckNum * p][e + CheckNum * q] != player; CheckNum--) {
            // 調べたマスが enemy のマスだったら
            if (board[d + CheckNum * p][e + CheckNum * q] == enemy) {
                board[d + CheckNum * p][e + CheckNum * q] = player;   // player の石にひっくり返す
            }
        }
    }
    return 1;
}


/*
* 黒石を置いた位置から、挟んで変えられる白石を探して黒石に変える
* 引数: なし
* 戻り値：ひっくり返せる場所が無かったら return 0 を返す
*/
int Othello_Board::BlackPut() {
    CursorPutOnCheck(Board, 1, 0, 2, 1);
    CursorPutOnCheck(Board, -1, 0, 2, 1);
    CursorPutOnCheck(Board, 0, 1, 2, 1);
    CursorPutOnCheck(Board, 0, -1, 2, 1);
    CursorPutOnCheck(Board, 1, 1, 2, 1);
    CursorPutOnCheck(Board, -1, 1, 2, 1);
    CursorPutOnCheck(Board, 1, -1, 2, 1);
    CursorPutOnCheck(Board, -1, -1, 2, 1);

    return 0;
}


/*
* 白石を置いた位置から、挟んで変えられる黒石を探して白石に変える
* 引数：なし
* 戻り値：ひっくり返せる場所がなかったら retun 0 を返す
*/
int Othello_Board::WhitePut() {
    CursorPutOnCheck(Board, 1, 0, 1, 2);
    CursorPutOnCheck(Board, -1, 0, 1, 2);
    CursorPutOnCheck(Board, 0, 1, 1, 2);
    CursorPutOnCheck(Board, 0, -1, 1, 2);
    CursorPutOnCheck(Board, 1, 1, 1, 2);
    CursorPutOnCheck(Board, -1, 1, 1, 2);
    CursorPutOnCheck(Board, 1, -1, 1, 2);
    CursorPutOnCheck(Board, -1, -1, 1, 2);

    return 0;
}


/*
* CPUが黒石を置いた位置から、挟んで変えられる白石を探して黒石に変える
* 引数：なし
* 戻り値：ひっくり返せる場所がなかったら retun 0 を返す
*/
int Othello_Board::BlackPutCPU(int d, int e) {
    CPUPutOnCheck(Board,  1,  0, d, e, 2, 1);
    CPUPutOnCheck(Board, -1,  0, d, e, 2, 1);
    CPUPutOnCheck(Board,  0,  1, d, e, 2, 1);
    CPUPutOnCheck(Board,  0, -1, d, e, 2, 1);
    CPUPutOnCheck(Board,  1,  1, d, e, 2, 1);
    CPUPutOnCheck(Board, -1,  1, d, e, 2, 1);
    CPUPutOnCheck(Board,  1, -1, d, e, 2, 1);
    CPUPutOnCheck(Board, -1, -1, d, e, 2, 1);

    return 0;
}


/*
* CPUが白石を置いた位置から、挟んで変えられる黒石を探して白石に変える
* 引数：なし
* 戻り値：ひっくり返せる場所がなかったら retun 0 を返す
*/
int Othello_Board::WhitePutCPU(int d, int e) {
    CPUPutOnCheck(Board, 1, 0, d, e, 1, 2);
    CPUPutOnCheck(Board, -1, 0, d, e, 1, 2);
    CPUPutOnCheck(Board, 0, 1, d, e, 1, 2);
    CPUPutOnCheck(Board, 0, -1, d, e, 1, 2);
    CPUPutOnCheck(Board, 1, 1, d, e, 1, 2);
    CPUPutOnCheck(Board, -1, 1, d, e, 1, 2);
    CPUPutOnCheck(Board, 1, -1, d, e, 1, 2);
    CPUPutOnCheck(Board, -1, -1, d, e, 1, 2);

    return 0;
}


/*
* 黒石を置いた位置から、左右上下斜めにひっくり返せる石がないか調べる
* 引数：なし
* 戻り値：ひっくり返せる場所がなかったら retun 0 を返す
*/
int Othello_Board::BlackPutCheck(int d, int e) {

    if (PutSearch(Board, 1, 0, d, e, 2, 1)){    // 右
        return PutSearch(Board, 1, 0, d, e, 2, 1);
    }
    if (PutSearch(Board, -1, 0, d, e, 2, 1)) {  // 左
        return PutSearch(Board, -1, 0, d, e, 2, 1);
    }
    if (PutSearch(Board, 0, -1, d, e, 2, 1)) {  // 上
        return PutSearch(Board, 0, -1, d, e, 2, 1);
    }
    if (PutSearch(Board, 0, 1, d, e, 2, 1)) {   // 下
        return PutSearch(Board, 0, 1, d, e, 2, 1);
    }

    if (PutSearch(Board, 1, 1, d, e, 2, 1)) {   // 右下
        return PutSearch(Board, 1, 1, d, e, 2, 1);
    }
    if (PutSearch(Board, -1, 1, d, e, 2, 1)) {  // 左下
        return PutSearch(Board, -1, 1, d, e, 2, 1);
    }
    if (PutSearch(Board, 1, -1, d, e, 2, 1)) {  // 右上
        return PutSearch(Board, 1, -1, d, e, 2, 1);
    }
    if (PutSearch(Board, -1, -1, d, e, 2, 1)) { // 左上
        return PutSearch(Board, -1, -1, d, e, 2, 1);
    }

    return 0;
}

/*
* 白石を置いた位置から、左右上下斜めにひっくり返せる石がないか調べる
* 引数：なし
* 戻り値：ひっくり返せる場所がなかったら retun 0 を返す
*/
int Othello_Board::WhitePutCheck(int d, int e) {

    if (PutSearch(Board, 1, 0, d, e, 1, 2)) {    // 右
        return PutSearch(Board, 1, 0, d, e, 1, 2);
    }

    if (PutSearch(Board, -1, 0, d, e, 1, 2)) {  // 左
        return PutSearch(Board, -1, 0, d, e, 1, 2);
    }

    if (PutSearch(Board, 0, -1, d, e, 1, 2)) {  // 上
        return PutSearch(Board, 0, -1, d, e, 1, 2);
    }
    if (PutSearch(Board, 0, 1, d, e, 1, 2)) {   // 下
        return PutSearch(Board, 0, 1, d, e, 1, 2);
    }

    if (PutSearch(Board, 1, 1, d, e, 1, 2)) {   // 右下
        return PutSearch(Board, 1, 1, d, e, 1, 2);
    }

    if (PutSearch(Board, -1, 1, d, e, 1, 2)) {  // 左下
        return PutSearch(Board, -1, 1, d, e, 1, 2);
    }

    if (PutSearch(Board, 1, -1, d, e, 1, 2)) {  // 右上
        return PutSearch(Board, 1, -1, d, e, 1, 2);
    }

    if (PutSearch(Board, -1, -1, d, e, 1, 2)) { // 左上
        return PutSearch(Board, -1, -1, d, e, 1, 2);
    }

    return 0;
}


/*
* 指定した方向に対して、ひっくり返せる石があれば何個ひっくり返せるか調べる
* 引数 : board[PB][PB], p, q, d, e, enemy, player
* 戻り値： i - 1 でひっくり返せる数の値を返す
*/
int Othello_Board::PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player) {
    int i;

    // 指定した方向に enemy（敵の石) があったら
    if (board[d + p][e + q] == enemy) {

        // 指定した方向に -1 がある所まで調べる
        for (i = 1; board[d + i * p][e + i * q] != -1; i++) {

            // 指定した方向の途中に board[][] == 0 or 3 or 4 があったら return 0
            if (board[d + i * p][e + i * q] == 0 ||
                board[d + i * p][e + i * q] == 3 ||
                board[d + i * p][e + i * q] == 4 || 
                board[d + i * p][e + i * q] == 5 ||
                board[d + i * p][e + i * q] == 6 ||
                board[d + i * p][e + i * q] == 7 ||
                board[d + i * p][e + i * q] == 8) {
                return 0;
            }

            // 指定した方向の途中に board[][] == player があったら return 1 を返す
            if (board[d + i * p][e + i * q] == player) {
                return i - 1;
            }
        }
    }
    return 0;   // 指定した方向に敵の石が無かったら return 0
}


/*
* 黒石が置ける場所を探す、置ける場所があったら分かりやすくする
* 引数：board[PB][PB]
* 戻り値：ひっくり返せる場所があったら、 return 1 を返す
*/
int Othello_Board::BoardSearchBlack(int board[PB][PB]) {
    int blackcount = 0;  // 黒石が置ける場所を数える用変数

    // マップチップを探索
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            // 白石と黒石が置ける場所を初期化
            if (board[i][j] == 3 || board[i][j] == 4) {
                board[i][j] = 0;
            }

            // 何も置かれてない場所だったら
            if (board[i][j] == 0) {
                if (BlackPutCheck(i, j)) {  // 黒石が置ける場所があったら

                    // 置ける場所を分かりやすくするために囲む
                    DrawGraph(i * MAP_SIZE + BoardShift_X, j * MAP_SIZE + BoardShift_Y, PutCheckImage, true);

                    board[i][j] = 3;    // 黒石が置けるようにする
                    blackcount++;       // 黒石が置ける場所の数だけインクリメント

                }
            }
        }
    }

    // 黒石が置ける場所が無かったら、パスする
    if (blackcount == 0) {
        return 0;
    }
    return 1;
}


/*
* 白石が置ける場所を探す、置ける場所があったら分かりやすくする
* 引数：board[PB][PB]
* 戻り値：ひっくり返せる場所があったら、 return 1 を返す
*/
int Othello_Board::BoardSearchWhite(int board[PB][PB]) {
    int whitecount = 0;     // 白石が置ける場所を数える用変数

    // マップチップを探索
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            // 白石と黒石を置ける場所を初期化
            if (board[i][j] == 4 || board[i][j] == 3) {
                board[i][j] = 0;
            }

            // 何も置かれていない場所なら
            if (board[i][j] == 0) {
                if (WhitePutCheck(i, j)) {  // 白石が置ける場所があったら

                    // 置ける場所を分かりやすくするために囲む
                    DrawGraph(i * MAP_SIZE + BoardShift_X, j * MAP_SIZE + BoardShift_Y, PutCheckImage, true);

                    board[i][j] = 4;    // 白石が置けるようにする
                    whitecount++;       // 白石が置ける場所の数だけインクリメント
                }
            }
        }
    }

    // 白石が置ける場所が無かったら、パスする
    if (whitecount == 0) {
        return 0;
    }
    return 1;
}


/*
* 黒石と白石の数を調べる
* 引数：board[PB][PB]
* 戻り値：なし
*/
void Othello_Board::BoardSearchBWNumber(int board[PB][PB]) {
    BlackNum = 0;   // 黒石の数を初期化
    WhiteNum = 0;   // 白石の数を初期化

    // マップチップを順に探索
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 1) {     // 黒石のマスだったら
                BlackNum++; // 黒石の数を増やす
            }

            if (board[i][j] == 2) {     // 白石のマスだったら
                WhiteNum++; // 白石の数を増やす
            }
        }
    }
}


/*
* ゲームの終了条件を満たしたら
* 引数：board[PB][PB]
* 戻り値：ゲームの終了条件を満たしたら return 1 を返す
*/
int Othello_Board::EndGame(int board[PB][PB]) {

    // 黒石と白石、両方とも置くところがなくなったら
    if (!BoardSearchBlack(Board)) {
        if (!BoardSearchWhite(Board)) {
            return 1;
        }
    }

    // 黒石と白石で盤面が埋まったら
    if (WhiteNum + BlackNum == 64) {
        return 1;
    }

    return 0;
}


/*
* 置ける場所を調べて、一番評価値が高いマスに白石を置くCPUの処理
* 引数：board[PB][PB], scoreboard[PB][PB]
* 戻り値：すべて以上なく通ったら return 1 を返す
*/
int Othello_Board::CPUWhite(int board[PB][PB], int scoreboard[PB][PB]) {
    Board_X = 0;
    Board_Y = 0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            //// 一番多く取れる所に置く処理
            //if (board[i][j] == 4) {
            //    if (ReturnNumMax < WhitePutCheck(i, j)) {
            //        ReturnNumMax = WhitePutCheck(i, j);
            //        Board_X = i;
            //        Board_Y = j;
            //    }

            // scoreboard[][]に最小値を入れて、毎回比べさせたい
            if (board[i][j] == 4) {
                if (scoreboard[Board_X][Board_Y] < scoreboard[i][j]) {
                    Board_X = i;
                    Board_Y = j;
                }
            }
        }
    }
    board[Board_X][Board_Y] = 2;
    WhitePutCPU(Board_X, Board_Y);
    PutPlace_X = Board_X;
    PutPlace_Y = Board_Y;
    Board_X = 0;
    Board_Y = 0;
    ReturnNumMax = 0;
    return 1;
}


/*
* 置ける場所を調べて、一番評価値が高いマスに黒石を置くCPUの処理
* 引数：board[PB][PB], scoreboard[PB][PB]
* 戻り値：すべて以上なく通ったら return 1 を返す
*/
int Othello_Board::CPUBlack(int board[PB][PB], int scoreboard[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 3) {

                // 一番多く取れる場所に置く処理
                //if (ReturnNumMax < BlackPutCheck(i, j)) {
                //    ReturnNumMax = BlackPutCheck(i, j);
                //    Board_X = i;
                //    Board_Y = j;
                //}

                // scoreboard[][]に最小値を入れて、毎回比べさせたい
                if (board[i][j] == 3) {
                    if (scoreboard[Board_X][Board_Y] < scoreboard[i][j]) {
                        Board_X = i;
                        Board_Y = j;
                    }
                }
            }
        }
    }
    board[Board_X][Board_Y] = 1;
    BlackPutCPU(Board_X, Board_Y);
    PutPlace_X = Board_X;
    PutPlace_Y = Board_Y;
    Board_X = 0;
    Board_Y = 0;
    ReturnNumMax = 0;
    return 1;
}



/*
* ゲームの最初にランダムに値を取って、先手・後手を決める
* 引数：なし
* 戻り値：なし
*/
void Othello_Board::RandomOrder() {

    RandomNum = rand();


    // 50以上で黒色がプレイヤー、それ以外は白色がプレイヤー
    if (RandomNum % 2 == 0) {
        Player = 0;
    }
    else {
        Player = 1;
    }
}
