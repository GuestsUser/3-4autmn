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

    if (Board[Square_X][Square_Y] == 3) {
        DrawFlag = true;
        if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
            Board[Square_X][Square_Y] = 1;      // ���΂�u��
            BlackPut();
        }
    }
    else {
        DrawFlag = false;
    }

    if (Board[Square_X][Square_Y] == 4) {
        DrawFlag = true;
        if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
            Board[Square_X][Square_Y] = 2;      // ���΂�u��
            WhitePut();
        }
    }
    else {
        DrawFlag = false;
    }


    // �{�[�h�̃}�X�̏�Ƀ}�E�X�J�[�\�����d�Ȃ����Ƃ��낪 0 ��������
    if (Board[Square_X][Square_Y] == 0) {

        //DrawFlag = true;

        //// �E�N���b�N��������
        //if (key->GetKeyState(REQUEST_MOUSE_RIGHT) == KEY_PUSH) {
        //    Board[Square_X][Square_Y] = 2;      // ���΂�u��
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
            if (board[i][j] == 3) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
            }
            if (board[i][j] == 4) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, WhiteCr, TRUE);
                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
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



// ���΂Ŕ��΂����ނƍ��΂ɕς���(�{�[�h�A���E�A�㉺�A�G�̐F�A�v���C���[�̐F�j
int Othello_Board::PutOnCheck(int board[PB][PB], int p, int q, int enemy, int player) {

    // �J�[�\���������Ă���Ƃ��납��A�u�����ꍇ�Ђ�����Ԃ��邩�ǂ������ׂ�
    for (CheckNum = 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != -1; CheckNum++) {

        // ���ׂ������ɂȂɂ��u���Ă��Ȃ�������
        // 3 4 ��������
        if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 0) {
            return 0;
        }
        // �u�����ꏊ����v���C���[���w�肵�������ɂ�����
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

// ���΂�u�����ʒu����A����ŕς����锒�΂�T���č��΂ɕς���
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

// ���΂�u�����ʒu����A����ŕς����鍕�΂�T���Ĕ��΂ɕς���
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

// ���E��΂߂ɐ΂����邩�ǂ������ׂ�
int Othello_Board::BlackPutCheck(int d, int e) {

    if (PutSearch(Board, 1, 0, d, e, 2, 1)){    // �E
        return 1;
    }
    if (PutSearch(Board, -1, 0, d, e, 2, 1)) {  // ��
        return 1;
    }
    if (PutSearch(Board, 0, -1, d, e, 2, 1)) {  // ��
        return 1;
    }
    if (PutSearch(Board, 0, 1, d, e, 2, 1)) {   // ��
        return 1;
    }

    if (PutSearch(Board, 1, 1, d, e, 2, 1)) {   // �E��
        return 1;
    }
    if (PutSearch(Board, -1, 1, d, e, 2, 1)) {  // ����
        return 1;
    }
    if (PutSearch(Board, 1, -1, d, e, 2, 1)) {  // �E��
        return 1;
    }
    if (PutSearch(Board, -1, -1, d, e, 2, 1)) { // ����
        return 1;
    }

    return 0;
}

int Othello_Board::WhitePutCheck(int d, int e) {

    if (PutSearch(Board, 1, 0, d, e, 1, 2)) {    // �E
        return 1;
    }
    if (PutSearch(Board, -1, 0, d, e, 1, 2)) {  // ��
        return 1;
    }
    if (PutSearch(Board, 0, -1, d, e, 1, 2)) {  // ��
        return 1;
    }
    if (PutSearch(Board, 0, 1, d, e, 1, 2)) {   // ��
        return 1;
    }

    if (PutSearch(Board, 1, 1, d, e, 1, 2)) {   // �E��
        return 1;
    }
    if (PutSearch(Board, -1, 1, d, e, 1, 2)) {  // ����
        return 1;
    }
    if (PutSearch(Board, 1, -1, d, e, 1, 2)) {  // �E��
        return 1;
    }
    if (PutSearch(Board, -1, -1, d, e, 1, 2)) { // ����
        return 1;
    }

    return 0;
}

// 8�����𒲂ׂĐ΂�������� return 0 �A�΂������ return 1 ��Ԃ�
int Othello_Board::PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player) {

    // �w�肵�������� enemy�i�G�̐�) ����������
    if (board[d + p][e + q] == enemy) {

        // �}�b�v�`�b�v�� -1�i�ՊO�j �ɂ����܂ł� player(�����̐�) �����邩�ǂ������ׂ�
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

//���΂��u����ꏊ��T��
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

//���΂��u����ꏊ��T��
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