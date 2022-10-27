#include"DxLib.h"
#include"windows.h"
#include <string.h>
#include "./../Code/GetKey.h"
#include "./Othello_Board.h"
#include "./Othello_Player.h"

Othello_Board* OB;

void Othello_Board::Othello_Board_Initialize() {
	//Board = LoadGraph("Resource/image/Othello_Board.jpg");

    BlackCr = GetColor(0, 0, 0);        // 黒色を設定
    GreenCr = GetColor(0, 255, 0);      // 緑色を設定
    WhiteCr = GetColor(255, 255, 255);  // 白色を設定

    DrawFlag = false;
    CheckFlag = false;

    Init_OthelloBoard(Board);           // ボードを初期化
}
void Othello_Board::Othello_Board_Finalize() {
	//DeleteGraph(Board);
}

void Othello_Board::Othello_Board_Update() {
    // デバッグ用
    DrawFormatString(1000,  90, WhiteCr, "左クリック：黒　右クリック：白");
    DrawFormatString(1000, 120, WhiteCr, "現在：%d", Board[Square_X][Square_Y]);
    DrawFormatString(1000, 150, WhiteCr, "座標Ｘ %d　　座標Ｙ %d", Mouse_X / MAP_SIZE, Mouse_Y / MAP_SIZE);
    DrawFormatString(1000, 170, WhiteCr, "CheckFlag：%d", CheckFlag);
    DrawFormatString(1000, 190, WhiteCr, "CheckNum：%d", CheckNum);
    DrawFormatString(1000, 210, WhiteCr, "Board[%d][%d]", Square_X, Square_Y);



    GetMousePoint(&Mouse_X, &Mouse_Y);  // マウスカーソルの位置を取得
    Square_X = Mouse_X / MAP_SIZE;      // マウスカーソルの位置を MAP_SIZE で割った値を代入
    Square_Y = Mouse_Y / MAP_SIZE;      // マウスカーソルの位置を MAP_SIZE で割った値を代入

    //Check(Board);

    // ボードのマスの上にマウスカーソルが重なったところが 0 だったら
    if (Board[Square_X][Square_Y] == 0) {

        DrawFlag = true;

        // 左クリックをしたら
        if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
            Board[Square_X][Square_Y] = 1;      // 黒石を置く
            Check3();
        }

        // 右クリックをしたら
        if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
            Board[Square_X][Square_Y] = 2;      // 黒石を置く
            //Check2(Board, -1, 0);
        }
        
    }
    else {
        DrawFlag = false;
    }
}

void Othello_Board::Othello_Board_Draw() {
    //DrawRotaGraph(640, 360, 1.0, 0, Board, TRUE);
    //DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
    Print_OthelloBoard(Board);
}

// ボードを初期化する
void Othello_Board::Init_OthelloBoard(int board[PB][PB]) {
static int InitBoard[PB][PB] =
{
 {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
 {-1,  0,  0,  0,  0,  0,  0,  0,  0, -1},
 {-1,  0,  0,  0,  0,  0,  0,  0,  0, -1},
 {-1,  0,  0,  0,  0,  0,  0,  0,  0, -1},
 {-1,  0,  0,  0,  2,  1,  0,  0,  0, -1},
 {-1,  0,  0,  0,  1,  2,  0,  0,  0, -1},
 {-1,  0,  0,  0,  0,  0,  0,  0,  0, -1},
 {-1,  0,  0,  0,  0,  0,  0,  0,  0, -1},
 {-1,  0,  0,  0,  0,  0,  0,  0,  0, -1},
 {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};
memcpy(board, InitBoard, sizeof(InitBoard));
}

// ボードを表示する
void Othello_Board::Print_OthelloBoard(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 0) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // マウスカーソルの位置がボードのマス目の上に来たマスを赤く表示する
            }
            if (board[i][j] == 1) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                // 黒石を置く
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2), j * MAP_SIZE + (MAP_SIZE / 2), 27, BlackCr, TRUE);
            }
            if (board[i][j] == 2) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                // 白石を置く
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2), j * MAP_SIZE + (MAP_SIZE / 2), 27, WhiteCr, TRUE);
            }
        }
    }
}

// マウスカーソルの位置がボードのマスの上に来たマスを赤く表示する
void Othello_Board::CursorOn_OthelloBoard() {
    if (DrawFlag == true)
    {
        DrawBox((Square_X * MAP_SIZE) + 1, (Square_Y * MAP_SIZE) + 1,
            (Square_X * MAP_SIZE) + MAP_SIZE - 1, (Square_Y * MAP_SIZE) + MAP_SIZE - 1, GetColor(255, 0, 0), TRUE);
    }
}

// 黒石が置ける場所を探す
//void Othello_Board::Check(int board[PB][PB]) {
//    for (int i = 1; i <= 8; i++) {
//        for (int j = 1; j <= 8; i++) {
//            if (board[i][j] == 0) {
//                if (Check3()) {
//                    DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
//                        (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GetColor(255, 0, 0), TRUE);
//                }
//            }
//        }
//    }
//}

// 黒石で白石を挟むと黒石に変える(ボード、左右、上下、敵の色、プレイヤーの色）
int Othello_Board::Check2(int board[PB][PB], int p, int q, int enemy, int player) {
    for (CheckNum = 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != -1; CheckNum++) {
        if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == player) {
            CheckFlag = true;
            //return 1;
            break;
        }
        else if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 0) {
            return 0;
        }
    }

    if (CheckFlag == true) {
        for (int i = 0; i <= CheckNum - 1; CheckNum--) {
            if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == enemy) {
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] = player;
            }
        }
        CheckFlag = false;
        return 1;
    }
}

// 上下左右斜めに石があるかどうか
void Othello_Board::Check3() {
    Check2(Board, 1, 0, 2, 1);
    Check2(Board, -1, 0, 2, 1);
    Check2(Board, 0, 1, 2, 1);
    Check2(Board, 0, -1, 2, 1);
    Check2(Board, 1, 1, 2, 1);
    Check2(Board, -1, 1, 2, 1);
    Check2(Board, 1, -1, 2, 1);
    Check2(Board, -1, -1, 2, 1);

    //if (Check2(Board, 1, 0, 2, 1)) {    // 右
    //    return 1;
    //}

    //if (Check2(Board, -1, 0, 2, 1)) {    // 左
    //    return 1;
    //}

    //if (Check2(Board, 0, 1, 2, 1)) {     // 下
    //    return 1;
    //}

    //if (Check2(Board, 0, -1, 2, 1)) {   // 上
    //    return 1;
    //}

    //if (Check2(Board, 1, 1, 2, 1)) {   // 右下
    //    return 1;
    //}

    //if(Check2(Board, -1, 1, 2, 1)){     // 左下
    //    return 1;
    //}

    //if (Check2(Board, 1, -1, 2, 1)) {   // 右上
    //    return 1;
    //}

    //if (Check2(Board, -1, -1, 2, 1)) {  // 左上
    //    return 1;
    //}
}

void Othello_Board::BlackOn_OthelloBoard(int board[PB][PB], int p, int q, int enemy, int player) {

    if (CheckFlag == true) {
        for (int i = 0; i <= CheckNum - 1; CheckNum--) {
            if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == enemy) {
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] = player;
            }
        }
        CheckFlag = false;
    }
}