#include"DxLib.h"
#include"windows.h"
#include <string.h>
#include "./Othello_Player.h"
#include "./Othello_Board.h"
#include "./../Code/GetKey.h"

Othello_Player* OP;

void Othello_Player::Othello_Plyaer_Initialize() {

    BlackCr = GetColor(0, 0, 0);

    WhiteCr = GetColor(255, 255, 255);
    
    Flag = false;

    //SetOB(Othello_Board* ob);
}

void Othello_Player::Othello_Player_Finalize() {

}

void Othello_Player::Othello_Player_Update() {
    //// デバッグ用
    //DrawFormatString(1200, 150, BlackCr, "座標Ｘ %d　　座標Ｙ %d", Mouse_X, Mouse_Y);


    //Player_X = Mouse_X / MAP_SIZE;
    //Player_Y = Mouse_Y / MAP_SIZE;
    //GetMousePoint(&Mouse_X, &Mouse_Y);

    //if (OB->Board[Player_X][Player_Y] == 0) {
    //    if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
    //        OB->Board[Player_X][Player_Y] = 1;
    //    }
    //}
    //else {
    //    Player_X = Mouse_X / MAP_SIZE;
    //    Player_Y = Mouse_Y / MAP_SIZE;
    //}
}

void Othello_Player::Othello_Player_Draw() {
    if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_FREE) {
        if (Flag == true) {

            //if (OB->Board[Mouse_X / MAP_SIZE][Mouse_Y / MAP_SIZE] == 0) {
            //    // 黒石を置く
            //    DrawCircle(Player_X * MAP_SIZE + (MAP_SIZE / 2), Player_Y * MAP_SIZE + (MAP_SIZE / 2), 27, BlackCr, TRUE);
            //}
                //DrawCircle((Mouse_X / MAP_SIZE) * MAP_SIZE + (MAP_SIZE / 2), 
                //    (Mouse_Y / MAP_SIZE) * MAP_SIZE + (MAP_SIZE / 2), 27, BlackCr, TRUE);
        }
    }
}

//void Othello_Player::SetOB(Othello_Board* ob) {
//    OB = ob;
//}