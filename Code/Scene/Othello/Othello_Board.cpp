#include"DxLib.h"
#include"windows.h"
#include <string.h>
#include "./../Code/GetKey.h"
#include "./Othello_Board.h"
#include "./Othello_Player.h"

Othello_Board* OB;

void Othello_Board::Othello_Board_Initialize() {
	//Board = LoadGraph("Resource/image/Othello_Board.jpg");

    BlackCr = GetColor(0, 0, 0);        // ���F��ݒ�
    GreenCr = GetColor(0, 255, 0);      // �ΐF��ݒ�
    WhiteCr = GetColor(255, 255, 255);  // ���F��ݒ�

    DrawFlag = false;
    CheckFlag = false;

    Init_OthelloBoard(Board);           // �{�[�h��������
}
void Othello_Board::Othello_Board_Finalize() {
	//DeleteGraph(Board);
}

void Othello_Board::Othello_Board_Update() {
    // �f�o�b�O�p
    DrawFormatString(1000,  90, WhiteCr, "���N���b�N�F���@�E�N���b�N�F��");
    DrawFormatString(1000, 120, WhiteCr, "���݁F%d", Board[Square_X][Square_Y]);
    DrawFormatString(1000, 150, WhiteCr, "���W�w %d�@�@���W�x %d", Mouse_X / MAP_SIZE, Mouse_Y / MAP_SIZE);
    DrawFormatString(1000, 170, WhiteCr, "CheckFlag�F%d", CheckFlag);
    DrawFormatString(1000, 190, WhiteCr, "CheckNum�F%d", CheckNum);
    DrawFormatString(1000, 210, WhiteCr, "Board[%d][%d]", Square_X, Square_Y);



    GetMousePoint(&Mouse_X, &Mouse_Y);  // �}�E�X�J�[�\���̈ʒu���擾
    Square_X = Mouse_X / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE �Ŋ������l����
    Square_Y = Mouse_Y / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE �Ŋ������l����

    //Check(Board);

    // �{�[�h�̃}�X�̏�Ƀ}�E�X�J�[�\�����d�Ȃ����Ƃ��낪 0 ��������
    if (Board[Square_X][Square_Y] == 0) {

        DrawFlag = true;

        // ���N���b�N��������
        if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
            Board[Square_X][Square_Y] = 1;      // ���΂�u��
            Check3();
        }

        // �E�N���b�N��������
        if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
            Board[Square_X][Square_Y] = 2;      // ���΂�u��
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

// �{�[�h������������
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

// �{�[�h��\������
void Othello_Board::Print_OthelloBoard(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 0) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
            }
            if (board[i][j] == 1) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                // ���΂�u��
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2), j * MAP_SIZE + (MAP_SIZE / 2), 27, BlackCr, TRUE);
            }
            if (board[i][j] == 2) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                // ���΂�u��
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2), j * MAP_SIZE + (MAP_SIZE / 2), 27, WhiteCr, TRUE);
            }
        }
    }
}

// �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�̏�ɗ����}�X��Ԃ��\������
void Othello_Board::CursorOn_OthelloBoard() {
    if (DrawFlag == true)
    {
        DrawBox((Square_X * MAP_SIZE) + 1, (Square_Y * MAP_SIZE) + 1,
            (Square_X * MAP_SIZE) + MAP_SIZE - 1, (Square_Y * MAP_SIZE) + MAP_SIZE - 1, GetColor(255, 0, 0), TRUE);
    }
}

// ���΂��u����ꏊ��T��
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

// ���΂Ŕ��΂����ނƍ��΂ɕς���(�{�[�h�A���E�A�㉺�A�G�̐F�A�v���C���[�̐F�j
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

// �㉺���E�΂߂ɐ΂����邩�ǂ���
void Othello_Board::Check3() {
    Check2(Board, 1, 0, 2, 1);
    Check2(Board, -1, 0, 2, 1);
    Check2(Board, 0, 1, 2, 1);
    Check2(Board, 0, -1, 2, 1);
    Check2(Board, 1, 1, 2, 1);
    Check2(Board, -1, 1, 2, 1);
    Check2(Board, 1, -1, 2, 1);
    Check2(Board, -1, -1, 2, 1);

    //if (Check2(Board, 1, 0, 2, 1)) {    // �E
    //    return 1;
    //}

    //if (Check2(Board, -1, 0, 2, 1)) {    // ��
    //    return 1;
    //}

    //if (Check2(Board, 0, 1, 2, 1)) {     // ��
    //    return 1;
    //}

    //if (Check2(Board, 0, -1, 2, 1)) {   // ��
    //    return 1;
    //}

    //if (Check2(Board, 1, 1, 2, 1)) {   // �E��
    //    return 1;
    //}

    //if(Check2(Board, -1, 1, 2, 1)){     // ����
    //    return 1;
    //}

    //if (Check2(Board, 1, -1, 2, 1)) {   // �E��
    //    return 1;
    //}

    //if (Check2(Board, -1, -1, 2, 1)) {  // ����
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