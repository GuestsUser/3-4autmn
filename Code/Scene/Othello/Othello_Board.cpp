#include "./Othello_Board.h"
#include"DxLib.h"
#include"windows.h"
#include <string.h>

void Othello_Board::Othello_Board_Initialize() {
	//Board = LoadGraph("Resource/image/Othello_Board.jpg");

    BlackCr = GetColor(0, 0, 0);
    GreenCr = GetColor(0, 255, 0);
    WhiteCr = GetColor(255, 255, 255);

    Init_DataBoard(Board);

}
void Othello_Board::Othello_Board_Finalize() {
	//DeleteGraph(Board);
}

void Othello_Board::Othello_Board_Update() {

}

void Othello_Board::Othello_Board_Draw() {
	//DrawRotaGraph(640, 360, 1.0, 0, Board, TRUE);
    DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
    Print_DataBoard(Board);
}

void Othello_Board::Init_DataBoard(int board[PB][PB]) {
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

void Othello_Board::Print_DataBoard(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 0) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
            }
            if (board[i][j] == 1) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                // 黒石を置く
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2), j * MAP_SIZE + (MAP_SIZE / 2), 27, BlackCr, TRUE);
            }
            if (board[i][j] == 2) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                // 白石を置く
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2), j * MAP_SIZE + (MAP_SIZE / 2), 27, WhiteCr, TRUE);
            }
        }
    }
}