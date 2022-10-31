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

    if (Board[Square_X][Square_Y] == 3) {
        DrawFlag = true;
        if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
            Board[Square_X][Square_Y] = 1;      // 黒石を置く
            BlackPut();
        }
    }
    else {
        DrawFlag = false;
    }

    if (Board[Square_X][Square_Y] == 4) {
        DrawFlag = true;
        if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
            Board[Square_X][Square_Y] = 2;      // 黒石を置く
            WhitePut();
        }
    }
    else {
        DrawFlag = false;
    }


    // ボードのマスの上にマウスカーソルが重なったところが 0 だったら
    if (Board[Square_X][Square_Y] == 0) {

        //DrawFlag = true;

        //// 右クリックをしたら
        //if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
        //    Board[Square_X][Square_Y] = 2;      // 白石を置く
        //    //Check2(Board, -1, 0);
        //}
        
    }
    else {
        //DrawFlag = false;
    }
}


void Othello_Board::Othello_Board_Draw() {
    //DrawRotaGraph(640, 360, 1.0, 0, Board, TRUE);
    //DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
    Print_OthelloBoard(Board);
    BoardSearchBlack(Board);
    BoardSearchWhite(Board);

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
            if (board[i][j] == 3) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // マウスカーソルの位置がボードのマス目の上に来たマスを赤く表示する
            }
            if (board[i][j] == 4) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // マウスカーソルの位置がボードのマス目の上に来たマスを赤く表示する
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



// 黒石で白石を挟むと黒石に変える(ボード、左右、上下、敵の色、プレイヤーの色）
int Othello_Board::PutOnCheck(int board[PB][PB], int p, int q, int enemy, int player) {

    // カーソルが合っているところから、置いた場合ひっくり返せるかどうか調べる
    for (CheckNum = 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != -1; CheckNum++) {

        // 調べた方向になにも置いていなかったら
        // 3 4 だったら
        if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 0) {
            return 0;
        }
        // 置いた場所からプレイヤーが指定した方向にいたら
        else if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == player) {
            if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == enemy) {
                return 0;
            }
            CheckFlag = true;
            //return 1;
            break;
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

// 黒石を置いた位置から、挟んで変えられる白石を探して黒石に変える
void Othello_Board::BlackPut() {
    PutOnCheck(Board, 1, 0, 2, 1);
    PutOnCheck(Board, -1, 0, 2, 1);
    PutOnCheck(Board, 0, 1, 2, 1);
    PutOnCheck(Board, 0, -1, 2, 1);
    PutOnCheck(Board, 1, 1, 2, 1);
    PutOnCheck(Board, -1, 1, 2, 1);
    PutOnCheck(Board, 1, -1, 2, 1);
    PutOnCheck(Board, -1, -1, 2, 1);


}

// 白石を置いた位置から、挟んで変えられる黒石を探して白石に変える
void Othello_Board::WhitePut() {
    PutOnCheck(Board, 1, 0, 1, 2);
    PutOnCheck(Board, -1, 0, 1, 2);
    PutOnCheck(Board, 0, 1, 1, 2);
    PutOnCheck(Board, 0, -1, 1, 2);
    PutOnCheck(Board, 1, 1, 1, 2);
    PutOnCheck(Board, -1, 1, 1, 2);
    PutOnCheck(Board, 1, -1, 1, 2);
    PutOnCheck(Board, -1, -1, 1, 2);


}

// 左右上斜めに石があるかどうか調べる
int Othello_Board::BlackPutCheck(int d, int e) {

    if (PutSearch(Board, 1, 0, d, e, 2, 1)){    // 右
        return 1;
    }
    if (PutSearch(Board, -1, 0, d, e, 2, 1)) {  // 左
        return 1;
    }
    if (PutSearch(Board, 0, -1, d, e, 2, 1)) {  // 上
        return 1;
    }
    if (PutSearch(Board, 0, 1, d, e, 2, 1)) {   // 下
        return 1;
    }

    if (PutSearch(Board, 1, 1, d, e, 2, 1)) {   // 右下
        return 1;
    }
    if (PutSearch(Board, -1, 1, d, e, 2, 1)) {  // 左下
        return 1;
    }
    if (PutSearch(Board, 1, -1, d, e, 2, 1)) {  // 右上
        return 1;
    }
    if (PutSearch(Board, -1, -1, d, e, 2, 1)) { // 左上
        return 1;
    }

    return 0;
}

int Othello_Board::WhitePutCheck(int d, int e) {

    if (PutSearch(Board, 1, 0, d, e, 1, 2)) {    // 右
        return 1;
    }
    if (PutSearch(Board, -1, 0, d, e, 1, 2)) {  // 左
        return 1;
    }
    if (PutSearch(Board, 0, -1, d, e, 1, 2)) {  // 上
        return 1;
    }
    if (PutSearch(Board, 0, 1, d, e, 1, 2)) {   // 下
        return 1;
    }

    if (PutSearch(Board, 1, 1, d, e, 1, 2)) {   // 右下
        return 1;
    }
    if (PutSearch(Board, -1, 1, d, e, 1, 2)) {  // 左下
        return 1;
    }
    if (PutSearch(Board, 1, -1, d, e, 1, 2)) {  // 右上
        return 1;
    }
    if (PutSearch(Board, -1, -1, d, e, 1, 2)) { // 左上
        return 1;
    }

    return 0;
}

// 8方向を調べて石が無ければ return 0 、石があれば return 1 を返す
int Othello_Board::PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player) {

    // 指定した方向に enemy（敵の石) があったら
    if (board[d + p][e + q] == enemy) {

        // マップチップの -1（盤外） にいくまでに player(自分の石) があるかどうか調べる
        for (int i = 1; board[d + i * p][e + i * q] != -1; i++) {

            if (board[d + i * p][e + i * q] == 0) {
                return 0;
            }
            if (board[d + i * p][e + i * q] == player) {
                return 1;
            }
        }
    }
    return 0;
}

//黒石が置ける場所を探す
void Othello_Board::BoardSearchBlack(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 3) {
                board[i][j] = 0;
            }
            if (board[i][j] == 0) {
                if (BlackPutCheck(i, j)) {

                    DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                        (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GetColor(0, 0, 0), true);

                    board[i][j] = 3;

                //    if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
                //        board[i][j] = 1;
                //        BlackPut();
                //    }
                }

            }
        }
    }
}

//白石が置ける場所を探す
void Othello_Board::BoardSearchWhite(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 4) {
                board[i][j] = 0;
            }
            if (board[i][j] == 0) {
                if (WhitePutCheck(i, j)) {

                    DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                        (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GetColor(255, 255, 255), true);

                    board[i][j] = 4;

                    //if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
                    //    board[i][j] = 2;
                    //    WhitePut();
                    //}
                }

            }
        }
    }
}