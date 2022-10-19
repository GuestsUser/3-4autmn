#include"DxLib.h"
#include"windows.h"
#include <string.h>
#include "./Othello_Player.h"
#include "./../Code/GetKey.h"

void Othello_Player::Othello_Plyaer_Initialize() {

    BlackCr = GetColor(0, 0, 0);

    WhiteCr = GetColor(255, 255, 255);

}

void Othello_Player::Othello_Player_Finalize() {

}

void Othello_Player::Othello_Player_Update() {
    GetMousePoint(&Mouse_X, &Mouse_Y);
    //if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
    //    DrawBox(10, 10, 100, 100, BlackCr, true);
    //}
}

void Othello_Player::Othello_Player_Draw() {
    if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_FREE) {
        //if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
            DrawBox(10, 10, 100, 100, BlackCr, TRUE);
        //}
    }
}