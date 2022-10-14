#include "./Othello_Player.h"
#include"DxLib.h"
#include"windows.h"

void Othello_Player::Othello_Plyaer_Initialize() {
	Board = LoadGraph("Resource/image/Othello_Board.jpg");

    Cr = GetColor(0, 255, 0);


}
void Othello_Player::Othello_Player_Finalize() {
	DeleteGraph(Board);
}

void Othello_Player::Othello_Player_Update() {
    init_DataMap();
}

void Othello_Player::Othello_Player_Draw() {
	//DrawRotaGraph(640, 360, 1.0, 0, Board, TRUE);
    init_DataMap();
}

void Othello_Player::init_DataMap() {
    int i, j;
    static int Board2[10][10] =
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

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (Board2[i][j] == 0) {
                DrawBox(i * MAP_SIZE_X, j * MAP_SIZE_Y,
                    (i * MAP_SIZE_X) + MAP_SIZE_X, (j * MAP_SIZE_Y) + MAP_SIZE_Y, Cr, false);
            }
            if (Board2[i][j] == 1) {
                DrawBox(i * MAP_SIZE_X, j * MAP_SIZE_Y,
                    (i * MAP_SIZE_X) + MAP_SIZE_X, (j * MAP_SIZE_Y) + MAP_SIZE_Y, Cr, false);
            }
            if (Board2[i][j] == 2) {
                DrawBox(i * MAP_SIZE_X, j * MAP_SIZE_Y,
                    (i * MAP_SIZE_X) + MAP_SIZE_X, (j * MAP_SIZE_Y) + MAP_SIZE_Y, Cr, false);
            }
        }
    }
}