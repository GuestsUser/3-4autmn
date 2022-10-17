#include "./Othello_Player.h"
#include"DxLib.h"
#include"windows.h"
#include <string.h>

void Othello_Player::Othello_Plyaer_Initialize() {
	Board = LoadGraph("Resource/image/Othello_Board.jpg");

    BlackCr = GetColor(0, 0, 0);
    GreenCr = GetColor(0, 255, 0);


}
void Othello_Player::Othello_Player_Finalize() {
	DeleteGraph(Board);
}

void Othello_Player::Othello_Player_Update() {

}

void Othello_Player::Othello_Player_Draw() {
	//DrawRotaGraph(640, 360, 1.0, 0, Board, TRUE);
    DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
    init_DataMap(Board);
}

void Othello_Player::init_DataMap(int Board) {
    int i, j;
    static int InitBoard[10][10] =
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
    memcopy(Board, InitBoard, sizeof(InitBoard));


    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (Board2[i][j] == 0) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE_X, j * MAP_SIZE_Y,
                    (i * MAP_SIZE_X) + MAP_SIZE_X, (j * MAP_SIZE_Y) + MAP_SIZE_Y, BlackCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE_X) + 1, (j * MAP_SIZE_Y) + 1,
                    (i * MAP_SIZE_X) + MAP_SIZE_X - 1, (j * MAP_SIZE_Y) + MAP_SIZE_Y - 1, GreenCr, TRUE);
            }
            if (Board2[i][j] == 1) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE_X, j * MAP_SIZE_Y,
                    (i * MAP_SIZE_X) + MAP_SIZE_X, (j * MAP_SIZE_Y) + MAP_SIZE_Y, BlackCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE_X) + 1, (j * MAP_SIZE_Y) + 1,
                    (i * MAP_SIZE_X) + MAP_SIZE_X - 1, (j * MAP_SIZE_Y) + MAP_SIZE_Y - 1, GreenCr, TRUE);
            }
            if (Board2[i][j] == 2) {
                // ボードのマス目を見やすくするために黒色で囲む
                DrawBox(i * MAP_SIZE_X, j * MAP_SIZE_Y,
                    (i * MAP_SIZE_X) + MAP_SIZE_X, (j * MAP_SIZE_Y) + MAP_SIZE_Y, BlackCr, TRUE);
                // ボードのマスの設定
                DrawBox((i * MAP_SIZE_X) + 1, (j * MAP_SIZE_Y) + 1,
                    (i * MAP_SIZE_X) + MAP_SIZE_X - 1, (j * MAP_SIZE_Y) + MAP_SIZE_Y - 1, GreenCr, TRUE);
            }
        }
    }
}