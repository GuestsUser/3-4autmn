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

    OrderNum = 0;   // 0 = 黒石、 1 = 白石

    DrawFlag = false;
    CheckFlag = false;

    Init_OthelloBoard(Board);           // ボードを初期化
    
}
void Othello_Board::Othello_Board_Finalize() {
	//DeleteGraph(Board);
}

void Othello_Board::Othello_Board_Update() {
    // デバッグ用
    if (OrderNum == 0) {
        DrawFormatString(650, 90, WhiteCr, "左クリック：黒の番です");
    }
    else {
        DrawFormatString(650, 90, WhiteCr, "左クリック：白の番です");
    }
    DrawFormatString(650, 120, WhiteCr, "CheckNum:%d", CheckNum);


    //DrawFormatString(500, 120, WhiteCr, "現在：%d", Board[Square_X][Square_Y]);
    //DrawFormatString(500, 150, WhiteCr, "座標Ｘ %d　　座標Ｙ %d", Mouse_X / MAP_SIZE, Mouse_Y / MAP_SIZE);
    //DrawFormatString(500, 170, WhiteCr, "CheckFlag：%d", CheckFlag);
    //DrawFormatString(500, 190, WhiteCr, "CheckNum：%d", CheckNum);
    //DrawFormatString(500, 210, WhiteCr, "Board[%d][%d]", Square_X, Square_Y);



    GetMousePoint(&Mouse_X, &Mouse_Y);  // マウスカーソルの位置を取得
    Square_X = Mouse_X / MAP_SIZE;      // マウスカーソルの位置を MAP_SIZE で割った値を代入
    Square_Y = Mouse_Y / MAP_SIZE;      // マウスカーソルの位置を MAP_SIZE で割った値を代入

    if (OrderNum == 0) {    // 黒の番だったら
        if (Board[Square_X][Square_Y] == 3) {   // 黒石が置ける場所にカーソルがあっていたら
            DrawFlag = true;
            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
                Board[Square_X][Square_Y] = 1;      // 黒石を置く
                BlackPut();     // 置いた場所から白を黒にひっくり返す
                OrderNum = 1;   // 白の手番にする
            }
        }
        else {
            DrawFlag = false;
        }
    }
    else {      // 白の番だったら
        if (Board[Square_X][Square_Y] == 4) {   // 白石が置ける場所にカーソルがあっていたら
            DrawFlag = true;
            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // 左クリックしたら
                Board[Square_X][Square_Y] = 2;      // 白石を置く
                WhitePut();     // 置いた場所から黒を白にひっくり返す
                OrderNum = 0;   // 黒の手番にする
            }
        }
        else {
            DrawFlag = false;
        }
    }

}


// 描画
void Othello_Board::Othello_Board_Draw() {
    //DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
    Print_OthelloBoard(Board);      // オセロボードの描画

    if (OrderNum == 0) {    // 黒の番だったら
        BoardSearchBlack(Board);    // 黒石が置ける場所を描画する
    }
    else {                  // 白の番だったら
        BoardSearchWhite(Board);    // 白石が置ける場所を描画する
    }

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

/*
* 1.置けるところを探す
* 2.置けるところに石を置く
* 3.石をひっくり返す
*/

// プレイヤーの石で相手の石を挟むと自分の石の色に変える(ボード、左右、上下、敵の色、プレイヤーの色）
int Othello_Board::PutOnCheck(int board[PB][PB], int p, int q, int enemy, int player) {

    int count = 0;  // CheckNum の値を入れる用変数

    // 調べた方向に対して敵の石があったら
    if (board[Square_X + p][Square_Y + q] == enemy) {

        // カーソルが合っているところから、置いた場合プレイヤーの石があるかどうか調べる
        for (CheckNum = 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != player; CheckNum++) {

            // 調べた方向に空いているマスがあったら
            if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 0) {
                return 0;
            }
        }
    }

    // 調べた方向に対して player が置いてあるマスから逆順に辿って、プレイヤーが置いた場所まで戻るまで
    for (count = CheckNum - 1; board[Square_X + count * p][Square_Y + count * q] != player; count--) {
        // 
        if (board[Square_X + count * p][Square_Y + count * q] == 0 ||
            board[Square_X + count * p][Square_Y + count * q] == 3 ||
            board[Square_X + count * p][Square_Y + count * q] == 4 ) {
            return 0;
        }
        //count++;

    }
    for (CheckNum = CheckNum - 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != player; CheckNum--) {
        if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == enemy) {
            board[Square_X + CheckNum * p][Square_Y + CheckNum * q] = player;
        }
    }
    return CheckNum - 1;
}

int Othello_Board::BWPut(int board[PB][PB], int p, int q, int enemy, int player) {
    int CNcount;

    for (CNcount = PutOnCheck(Board, p, q, enemy, player); board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != player; CNcount--) {
        if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == enemy) {
            board[Square_X + CheckNum * p][Square_Y + CheckNum * q] = player;
        }
    }
    return 0;
}

int Othello_Board::PutOnCheck2(int board[PB][PB], int p, int q, int d, int e, int enemy, int player) {

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (WhitePutCheck(i, j)) {

            }
       }
    }
    return 0;
}

// 黒石を置いた位置から、挟んで変えられる白石を探して黒石に変える
int Othello_Board::BlackPut() {
    PutOnCheck(Board, 1, 0, 2, 1);
    PutOnCheck(Board, -1, 0, 2, 1);
    PutOnCheck(Board, 0, 1, 2, 1);
    PutOnCheck(Board, 0, -1, 2, 1);
    PutOnCheck(Board, 1, 1, 2, 1);
    PutOnCheck(Board, -1, 1, 2, 1);
    PutOnCheck(Board, 1, -1, 2, 1);
    PutOnCheck(Board, -1, -1, 2, 1);
    /* 置く関数と区別する関数を別にしてみる　*/
    //if (PutOnCheck(Board, 1, 0, 2, 1)) {
    //    BWPut()
    //}
    //if (PutOnCheck(Board, -1,  0, 2, 1)) return 1;
    //if (PutOnCheck(Board,  0,  1, 2, 1)) return 1;
    //if (PutOnCheck(Board,  0, -1, 2, 1)) return 1;
    //if (PutOnCheck(Board,  1,  1, 2, 1)) return 1;
    //if (PutOnCheck(Board, -1,  1, 2, 1)) return 1;
    //if (PutOnCheck(Board,  1, -1, 2, 1)) return 1;
    //if (PutOnCheck(Board, -1, -1, 2, 1)) return 1;

    return 0;
}

// 白石を置いた位置から、挟んで変えられる黒石を探して白石に変える
int Othello_Board::WhitePut() {
    PutOnCheck(Board, 1, 0, 1, 2);
    PutOnCheck(Board, -1, 0, 1, 2);
    PutOnCheck(Board, 0, 1, 1, 2);
    PutOnCheck(Board, 0, -1, 1, 2);
    PutOnCheck(Board, 1, 1, 1, 2);
    PutOnCheck(Board, -1, 1, 1, 2);
    PutOnCheck(Board, 1, -1, 1, 2);
    PutOnCheck(Board, -1, -1, 1, 2);

    //if (PutOnCheck(Board, 1, 0, 1, 2)) return 1;
    //if (PutOnCheck(Board, -1, 0, 1, 2)) return 1;
    //if (PutOnCheck(Board, 0, 1, 1, 2)) return 1;
    //if (PutOnCheck(Board, 0, -1, 1, 2)) return 1;
    //if (PutOnCheck(Board, 1, 1, 1, 2)) return 1;
    //if (PutOnCheck(Board, -1, 1, 1, 2)) return 1;
    //if (PutOnCheck(Board, 1, -1, 1, 2)) return 1;
    //if (PutOnCheck(Board, -1, -1, 1, 2)) return 1;

    return 0;
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

    int i;

    // 指定した方向に enemy（敵の石) があったら
    if (board[d + p][e + q] == enemy) {

        // マップチップの -1（盤外） にいくまでに player(自分の石) があるかどうか調べる
        for (i = 1; board[d + i * p][e + i * q] != player; i++) {

            if (board[d + i * p][e + i * q] == 0 ||
                board[d + i * p][e + i * q] == 3 ||
                board[d + i * p][e + i * q] == 4 ) {
                return 0;
            }
        }
        //for(i = 1; board[d + i * p][e + i * q] != -1; i++){
        //    if (board[d + i * p][e + i * q] == player) {

        //        return 1;
        //    }
        //}
        return 1;

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
                        (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GetColor(100, 0, 0), false);

                    board[i][j] = 3;

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
                        (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GetColor(100, 0, 0), false);

                    board[i][j] = 4;
                }

            }
        }
    }
}


//// プレイヤーを探した座標から戻るように辿っていって、board[][] == 0 がないかどうか調べる
                //// 右方向に調べていたら
                //if (p == 1 && q == 0) {
                //    for (i = i; i < 1; i--) {
                //        if (board[d + i * p][e + i * q] == 0) {
                //            return 0;
                //        }
                //    }
                //}
                //// 左方向に調べていたら
                //if (p == -1 && q == 0) {
                //    for (i = i; i <= 1; i--) {
                //        if (board[(d + i * p)][e + i * q] == 0) {
                //            return 0;
                //        }
                //    }
                //}
                //// 上方向に調べていたら
                //if (p == 0 && q == -1) {
                //    for (i = i; i <= 1; i--) {
                //        if (board[(d + i * p)][e + i * q] == 0) {
                //            return 0;
                //        }
                //    }
                //}
                //// 下方向に調べていたら
                //if (p == 0 && q == 1) {
                //    for (i = i; i <= 1; i--) {
                //        if (board[d + i * p][e + i * q] == 0) {
                //            return 0;
                //        }
                //    }
                //}
                //// 右下方向に調べていたら
                //if (p == 1 && q == 1) {
                //    for (i = i; i <= 1; i--) {
                //        if (board[d + i * p][e + i * q] == 0) {
                //            return 0;
                //        }
                //    }
                //}
                //// 左下方向に調べていたら
                //if (p == -1 && q == 1) {
                //    for (i = i; i <= 1; i--) {
                //        if (board[d + i * p][e + i * q] == 0) {
                //            return 0;
                //        }
                //    }
                //}
                //// 右上方向に調べていたら
                //if (p == 1 && q == -1) {
                //    for (i = i; i <= 1; i--) {
                //        if (board[d + i * p][e + i * q] == 0) {
                //            return 0;
                //        }
                //    }
                //}
                //// 左上方向に調べていたら
                //if (p == -1 && q == -1) {
                //    for (i = i; i <= 1; i--) {
                //        if (board[d + i * p][e + i * q] == 0) {
                //            return 0;
                //        }
                //    }
                //}