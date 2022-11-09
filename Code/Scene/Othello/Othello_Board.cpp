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

    OrderNum = 0;   // 0 = ���΁A 1 = ����
    BlackNum = 0;
    WhiteNum = 0;
    TimeCount = 0;

    DrawFlag = false;
    CheckFlag = false;
    TimeFlag = false;

    Init_OthelloBoard(Board);           // �{�[�h��������
    
}
void Othello_Board::Othello_Board_Finalize() {
	//DeleteGraph(Board);
}

void Othello_Board::Othello_Board_Update() {

    if (TimeFlag == false) {
        // �f�o�b�O�p
        if (OrderNum == 0) {
            DrawFormatString(650, 90, WhiteCr, "���N���b�N�F���̔Ԃł�");
        }
        else {
            DrawFormatString(650, 90, WhiteCr, "���N���b�N�F���̔Ԃł�");
        }
    }
    else {
        DrawFormatString(650, 90, WhiteCr, "�p�X�I");
        TimeCount++;
        if (TimeCount >= 60) 
        {
            TimeCount = 0;
            TimeFlag = false;
        }
    }
    DrawFormatString(650, 140, WhiteCr, "����:%d", BlackNum);
    DrawFormatString(650, 190, WhiteCr, "����:%d", WhiteNum);
    DrawFormatString(650, 240, WhiteCr, "TimeCount:%d", TimeCount);



    //DrawFormatString(500, 120, WhiteCr, "���݁F%d", Board[Square_X][Square_Y]);
    //DrawFormatString(500, 150, WhiteCr, "���W�w %d�@�@���W�x %d", Mouse_X / MAP_SIZE, Mouse_Y / MAP_SIZE);
    //DrawFormatString(500, 170, WhiteCr, "CheckFlag�F%d", CheckFlag);
    //DrawFormatString(500, 190, WhiteCr, "CheckNum�F%d", CheckNum);
    //DrawFormatString(500, 210, WhiteCr, "Board[%d][%d]", Square_X, Square_Y);



    GetMousePoint(&Mouse_X, &Mouse_Y);  // �}�E�X�J�[�\���̈ʒu���擾
    Square_X = Mouse_X / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE �Ŋ������l����
    Square_Y = Mouse_Y / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE �Ŋ������l����

    if (OrderNum == 0) {    // ���̔Ԃ�������
        if (!BoardSearchBlack(Board)) {
            TimeFlag = true;
            OrderNum = 1;
        }

        if (Board[Square_X][Square_Y] == 3) {   // ���΂��u����ꏊ�ɃJ�[�\���������Ă�����
            DrawFlag = true;
            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
                Board[Square_X][Square_Y] = 1;      // ���΂�u��
                BlackPut();     // �u�����ꏊ���甒�����ɂЂ�����Ԃ�
                OrderNum = 1;   // ���̎�Ԃɂ���
                BoardSearchBWNumber(Board);
            }
        }
        else {
            DrawFlag = false;
        }
    }
    else {      // ���̔Ԃ�������

        if (!BoardSearchWhite(Board)) {
            TimeFlag = true;
            OrderNum = 0;
        }

        if (Board[Square_X][Square_Y] == 4) {   // ���΂��u����ꏊ�ɃJ�[�\���������Ă�����
            DrawFlag = true;
            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
                Board[Square_X][Square_Y] = 2;      // ���΂�u��
                WhitePut();     // �u�����ꏊ���獕�𔒂ɂЂ�����Ԃ�
                OrderNum = 0;   // ���̎�Ԃɂ���
                BoardSearchBWNumber(Board);
            }
        }
        else {
            DrawFlag = false;
        }
    }
}


// �`��
void Othello_Board::Othello_Board_Draw() {
    //DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
    Print_OthelloBoard(Board);      // �I�Z���{�[�h�̕`��

    if (TimeFlag == false) {
        if (OrderNum == 0) {    // ���̔Ԃ�������
            BoardSearchBlack(Board);    // ���΂��u����ꏊ��`�悷��
        }
        else {                  // ���̔Ԃ�������
            BoardSearchWhite(Board);    // ���΂��u����ꏊ��`�悷��
        }
    }

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

/*
* 1.�u����Ƃ����T��
* 2.�u����Ƃ���ɐ΂�u��
* 3.�΂��Ђ�����Ԃ�
*/

// �v���C���[�̐΂ő���̐΂����ނƎ����̐΂̐F�ɕς���(�{�[�h�A���E�A�㉺�A�G�̐F�A�v���C���[�̐F�j
int Othello_Board::PutOnCheck(int board[PB][PB], int p, int q, int enemy, int player) {

    int count = 0;  // CheckNum �̒l������p�ϐ�

    // ���ׂ������ɑ΂��ēG�̐΂���������
    if (board[Square_X + p][Square_Y + q] == enemy) {

        // �J�[�\���������Ă���Ƃ��납��A�u�����ꍇ�v���C���[�̐΂����邩�ǂ������ׂ�
        for (CheckNum = 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != player; CheckNum++) {

            // ���ׂ������ɋ󂢂Ă���}�X����������
            if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 0 ||
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == -1) {
                return 0;
            }
        }
    }

    // ���ׂ������ɑ΂��� player ���u���Ă���}�X����t���ɒH���āA�v���C���[���u�����ꏊ�܂Ŗ߂�܂�
    for (count = CheckNum - 1; board[Square_X + count * p][Square_Y + count * q] != player; count--) {

        // ���ׂ��Ƃ��낪�A0, 3, 4, -1 �̂����ꂩ�Ȃ� return 0
        if (board[Square_X + count * p][Square_Y + count * q] == 0 ||
            board[Square_X + count * p][Square_Y + count * q] == 3 ||
            board[Square_X + count * p][Square_Y + count * q] == 4 ||
            board[Square_X + count * p][Square_Y + count * q] == -1) {
            return 0;
        }
    }
    // ���ׂ������ɑ΂��āA ������x�t���ɒH���� player �̐΂ɂЂ�����Ԃ�
    for (CheckNum = CheckNum - 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != player; CheckNum--) {
        // ���ׂ��}�X�� enemy �̃}�X��������
        if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == enemy) {
            board[Square_X + CheckNum * p][Square_Y + CheckNum * q] = player;   // player �̐΂ɂЂ�����Ԃ�
        }
    }
    return CheckNum - 1;
}

// ���΂�u�����ʒu����A����ŕς����锒�΂�T���č��΂ɕς���
int Othello_Board::BlackPut() {
    PutOnCheck(Board, 1, 0, 2, 1);
    PutOnCheck(Board, -1, 0, 2, 1);
    PutOnCheck(Board, 0, 1, 2, 1);
    PutOnCheck(Board, 0, -1, 2, 1);
    PutOnCheck(Board, 1, 1, 2, 1);
    PutOnCheck(Board, -1, 1, 2, 1);
    PutOnCheck(Board, 1, -1, 2, 1);
    PutOnCheck(Board, -1, -1, 2, 1);

    //if (PutOnCheck(Board, -1,  0, 2, 1)) return 1;
    //if (PutOnCheck(Board,  0,  1, 2, 1)) return 1;
    //if (PutOnCheck(Board,  0, -1, 2, 1)) return 1;
    //if (PutOnCheck(Board,  1,  1, 2, 1)) return 1;
    //if (PutOnCheck(Board, -1,  1, 2, 1)) return 1;
    //if (PutOnCheck(Board,  1, -1, 2, 1)) return 1;
    //if (PutOnCheck(Board, -1, -1, 2, 1)) return 1;

    return 0;
}

// ���΂�u�����ʒu����A����ŕς����鍕�΂�T���Ĕ��΂ɕς���
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

    int i;

    // �w�肵�������� enemy�i�G�̐�) ����������
    if (board[d + p][e + q] == enemy) {

        // �}�b�v�`�b�v�� -1�i�ՊO�j �ɂ����܂ł� player(�����̐�) �����邩�ǂ������ׂ�
        for (i = 1; board[d + i * p][e + i * q] != player; i++) {

            if (board[d + i * p][e + i * q] == 0 ||
                board[d + i * p][e + i * q] == 3 ||
                board[d + i * p][e + i * q] == 4 ) {
                return 0;
            }
        }
        for(i = 1; board[d + i * p][e + i * q] != -1; i++){
            if (board[d + i * p][e + i * q] == player) {

                return 1;
            }
        }

    }
    return 0;
}

//���΂��u����ꏊ��T��
int Othello_Board::BoardSearchBlack(int board[PB][PB]) {
    int count = 0;

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
                    count++;

                }

            }
        }
    }

    if (count == 0) {
        //DrawFormatString(650, 300, WhiteCr, "�p�X�I");
        //WaitTimer(1000);
        TimeFlag = true;
        return 0;
    }
}

//���΂��u����ꏊ��T��
int Othello_Board::BoardSearchWhite(int board[PB][PB]) {
    int count = 0;

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 4) {
                board[i][j] = 0;
            }
            if (board[i][j] == 0) {
                if (WhitePutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                        (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GetColor(100, 0, 0), false);

                    board[i][j] = 4;
                    count++;
                }
            }
        }
    }

    if (count == 0) {
        //DrawFormatString(650, 300, WhiteCr, "�p�X�I");
        TimeFlag = true;
        //WaitTimer(1000);
        return 0;
    }
}

// ���΂Ɣ��΂̐��𒲂ׂ�
void Othello_Board::BoardSearchBWNumber(int board[PB][PB]) {
    BlackNum = 0;   // ���΂̐���������
    WhiteNum = 0;   // ���΂̐���������

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 1) {     // ���΂̃}�X��������
                BlackNum++; // ���΂̐��𑝂₷
            }

            if (board[i][j] == 2) {     // ���΂̃}�X��������
                WhiteNum++; // ���΂̐��𑝂₷
            }
        }
    }
}