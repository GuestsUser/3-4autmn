#include"DxLib.h"
#include"windows.h"
#include <string.h>
#include "./../Code/GetKey.h"
#include "./Othello_Board.h"
#include "./Othello_Player.h"

Othello_Board* OB;

// ������
void Othello_Board::Othello_Board_Initialize() {
	//Board = LoadGraph("Resource/image/Othello_Board.jpg");

    BlackCr = GetColor(0, 0, 0);        // ���F��ݒ�
    GreenCr = GetColor(0, 255, 0);      // �ΐF��ݒ�
    WhiteCr = GetColor(255, 255, 255);  // ���F��ݒ�

    OrderNum = 0;   // 0 = ���΁A 1 = ����
    BlackNum = 0;
    WhiteNum = 0;
    TimeCount = 0;
    ReturnNum = 0;
    ReturnNumMax = 0;

    DrawFlag = false;
    CheckFlag = false;
    PassFlag = false;
    EndFlag = false;

    Init_OthelloBoard(Board);           // �{�[�h��������
    
}

// �I������
void Othello_Board::Othello_Board_Finalize() {
	//DeleteGraph(Board);
}

// �X�V
void Othello_Board::Othello_Board_Update() {

    if (PassFlag == false) {    // �p�X������t���O�� false �Ȃ�
        if (OrderNum == 0) {    // ��Ԃ����Ȃ�
            DrawFormatString(650, 90, WhiteCr, "���N���b�N�F���̔Ԃł�");
        }
        else {      // ��Ԃ����Ȃ�
            DrawFormatString(650, 90, WhiteCr, "���N���b�N�F���̔Ԃł�");
        }
    }
    else {      // �p�X������t���O�� true �Ȃ�
        DrawFormatString(650, 90, WhiteCr, "�p�X�I");      // �p�X�I�ƕ\������
        TimeCount++;
        // 1�b�o������
        if (TimeCount >= 60)
        {
            TimeCount = 0;      // TimeCount ��������

            // ���̎�ԂȂ甒�̎�Ԃɂ��āA���̎�ԂȂ獕�̎�Ԃɂ���
            if (OrderNum == 0) 
            {
                OrderNum = 1;
            }
            else 
            {
                OrderNum = 0;
            }
            PassFlag = false;   // �p�X�t���O�� false �ɂ���
        }
    }
    // �f�o�b�O�p
    DrawFormatString(650, 140, WhiteCr, "����:%d", BlackNum);
    DrawFormatString(650, 190, WhiteCr, "����:%d", WhiteNum);
    DrawFormatString(650, 240, WhiteCr, "TimeCount:%d", TimeCount);
    DrawFormatString(1000, 240, WhiteCr, "BoardX:%d", Board_X);
    DrawFormatString(1000, 290, WhiteCr, "BoardY:%d", Board_Y);
    DrawFormatString(1000, 340, WhiteCr, "ReturnNumMax:%d", ReturnNumMax);





    GetMousePoint(&Mouse_X, &Mouse_Y);  // �}�E�X�J�[�\���̈ʒu���擾
    Square_X = Mouse_X / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE �Ŋ������l����
    Square_Y = Mouse_Y / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE �Ŋ������l����

    if (EndFlag == false) {   // �Q�[�����I��������ǂ���
        if (PassFlag == false) {    // �p�X�t���O�� false �Ȃ�
            if (OrderNum == 0) {    // ���̔Ԃ�������

                // ���΂̒u����ꏊ���Ȃ��Ȃ�
                if (!BoardSearchBlack(Board))
                {
                    PassFlag = true;    // �p�X�t���O�� true �ɂ���
                }

                if (Board[Square_X][Square_Y] == 3) {   // ���΂��u����ꏊ�ɃJ�[�\���������Ă�����
                    DrawFlag = true;
                    if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
                        DrawFlag = false;
                        Board[Square_X][Square_Y] = 1;      // ���΂�u��
                        BlackPut();                         // �u�����ꏊ���甒�����ɂЂ�����Ԃ�
                        OrderNum = 1;                       // ���̎�Ԃɂ���
                        BoardSearchBWNumber(Board);         // ���΂Ɣ��΂̐��𐔂���֐����s
                        if (EndGame(Board)) {               // �Q�[�����I�������𖞂�������
                            EndFlag = true;   // �G���h�t���O�� true �ɂ���
                        }
                        DrawFlag = false;
                        // ReturnNumMax = 0;
                    }

                }
                else {
                    DrawFlag = false;
                }
            }
            else {      // ���̔Ԃ�������

                if (!BoardSearchWhite(Board)) {
                    PassFlag = true;
                    //OrderNum = 0;
                }

                if (TimeCount++ >= 60) {
                    TimeCount = 0;
                    ReturnNumWhite(Board);
                    OrderNum = 0;
                }

                BoardSearchBWNumber(Board);
                if (EndGame(Board)) {
                    EndFlag = true;
                }

                // ------------�����Ŕ��΂�u���悤-----------------------------
                //if (Board[Square_X][Square_Y] == 4) {   // ���΂��u����ꏊ�ɃJ�[�\���������Ă�����
                //    DrawFlag = true;
                //    if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
                //        Board[Square_X][Square_Y] = 2;      // ���΂�u��
                //        WhitePut();     // �u�����ꏊ���獕�𔒂ɂЂ�����Ԃ�
                //        OrderNum = 0;   // ���̎�Ԃɂ���
                //        BoardSearchBWNumber(Board);
                //        if (EndGame(Board)) {
                //            EndFlag = true;
                //        }
                //    }
                //}
                //else {
                //    DrawFlag = false;
                //}
                // ----------------------------------------------
            }
        }
    }
}


// �`��
void Othello_Board::Othello_Board_Draw() {
    //DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), TRUE);
    Print_OthelloBoard(Board);      // �I�Z���{�[�h�̕`��

    if (PassFlag == false) {
        if (OrderNum == 0) {    // ���̔Ԃ�������
            BoardSearchBlack(Board);    // ���΂��u����ꏊ��`�悷��
        }
        else {                  // ���̔Ԃ�������
            BoardSearchWhite(Board);    // ���΂��u����ꏊ��`�悷��
        }
    }
    if (EndFlag == true) {
        DrawFormatString(650, 400, WhiteCr, "�Q�[���I���I");
        DrawFormatString(650, 500, WhiteCr, "3�b��Ƀ��Z�b�g���܂�");
        if (WhiteNum < BlackNum) {
            DrawFormatString(650, 450, WhiteCr, "���̏����I");
            if (TimeCount++ >= 180) {
                TimeCount = 0;
                BlackNum = 0;
                WhiteNum = 0;
                EndFlag = false;
                Init_OthelloBoard(Board);
            }
        }
        else if (BlackNum < WhiteNum) {
            DrawFormatString(650, 450, WhiteCr, "���̏����I");
            if (TimeCount++ >= 180) {
                TimeCount = 0;
                BlackNum = 0;
                WhiteNum = 0;
                EndFlag = false;
                Init_OthelloBoard(Board);
            }
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
int Othello_Board::CursorPutOnCheck(int board[PB][PB], int p, int q, int enemy, int player) {

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
    }
    return 1;
}


int Othello_Board::PutOnCheck(int board[PB][PB], int p, int q, int d, int e, int enemy, int player) {

    int count = 0;  // CheckNum �̒l������p�ϐ�
    ReturnNum = 0;

    // ���ׂ������ɑ΂��ēG�̐΂���������
    if (board[d + p][e + q] == enemy) {

        // �u�����ꍇ�A�w�肵�������Ƀv���C���[�̐΂����邩�ǂ������ׂ�
        for (CheckNum = 1; board[d + CheckNum * p][e + CheckNum * q] != player; CheckNum++) {

            // ���ׂ������ɋ󂢂Ă���}�X����������
            if (board[d + CheckNum * p][e + CheckNum * q] == 0 ||
                board[d + CheckNum * p][e + CheckNum * q] == -1) {
                return 0;
            }
        }


        // ���ׂ������ɑ΂��� player ���u���Ă���}�X����t���ɒH���āA�v���C���[���u�����ꏊ�܂Ŗ߂�܂�
        for (count = CheckNum - 1; board[d + count * p][e + count * q] != player; count--) {

            // ���ׂ��Ƃ��낪�A0, 3, 4, -1 �̂����ꂩ�Ȃ� return 0
            if (board[d + count * p][e + count * q] == 0 ||
                board[d + count * p][e + count * q] == 3 ||
                board[d + count * p][e + count * q] == 4 ||
                board[d + count * p][e + count * q] == -1) {
                return 0;
            }
        }



        // ���ׂ������ɑ΂��āA ������x�t���ɒH���� player �̐΂ɂЂ�����Ԃ�
        for (CheckNum = CheckNum - 1; board[d + CheckNum * p][e + CheckNum * q] != player; CheckNum--) {
            // ���ׂ��}�X�� enemy �̃}�X��������
            if (board[d + CheckNum * p][e + CheckNum * q] == enemy) {
                board[d + CheckNum * p][e + CheckNum * q] = player;   // player �̐΂ɂЂ�����Ԃ�
                ReturnNum++;
            }
        }
    }
    return ReturnNum;
}


// ���΂�u�����ʒu����A����ŕς����锒�΂�T���č��΂ɕς���
int Othello_Board::BlackPut() {
    CursorPutOnCheck(Board, 1, 0, 2, 1);
    CursorPutOnCheck(Board, -1, 0, 2, 1);
    CursorPutOnCheck(Board, 0, 1, 2, 1);
    CursorPutOnCheck(Board, 0, -1, 2, 1);
    CursorPutOnCheck(Board, 1, 1, 2, 1);
    CursorPutOnCheck(Board, -1, 1, 2, 1);
    CursorPutOnCheck(Board, 1, -1, 2, 1);
    CursorPutOnCheck(Board, -1, -1, 2, 1);

    //if (CursorPutOnCheck(Board, -1,  0, 2, 1)) return 1;
    //if (CursorPutOnCheck(Board,  0,  1, 2, 1)) return 1;
    //if (CursorPutOnCheck(Board,  0, -1, 2, 1)) return 1;
    //if (CursorPutOnCheck(Board,  1,  1, 2, 1)) return 1;
    //if (CursorPutOnCheck(Board, -1,  1, 2, 1)) return 1;
    //if (CursorPutOnCheck(Board,  1, -1, 2, 1)) return 1;
    //if (CursorPutOnCheck(Board, -1, -1, 2, 1)) return 1;

    return 0;
}

// ���΂�u�����ʒu����A����ŕς����鍕�΂�T���Ĕ��΂ɕς���
int Othello_Board::WhitePut() {
    CursorPutOnCheck(Board, 1, 0, 1, 2);
    CursorPutOnCheck(Board, -1, 0, 1, 2);
    CursorPutOnCheck(Board, 0, 1, 1, 2);
    CursorPutOnCheck(Board, 0, -1, 1, 2);
    CursorPutOnCheck(Board, 1, 1, 1, 2);
    CursorPutOnCheck(Board, -1, 1, 1, 2);
    CursorPutOnCheck(Board, 1, -1, 1, 2);
    CursorPutOnCheck(Board, -1, -1, 1, 2);

    //if (CursorPutOnCheck(Board, 1, 0, 1, 2)) return 1;
    //if (CursorPutOnCheck(Board, -1, 0, 1, 2)) return 1;
    //if (CursorPutOnCheck(Board, 0, 1, 1, 2)) return 1;
    //if (CursorPutOnCheck(Board, 0, -1, 1, 2)) return 1;
    //if (CursorPutOnCheck(Board, 1, 1, 1, 2)) return 1;
    //if (CursorPutOnCheck(Board, -1, 1, 1, 2)) return 1;
    //if (CursorPutOnCheck(Board, 1, -1, 1, 2)) return 1;
    //if (CursorPutOnCheck(Board, -1, -1, 1, 2)) return 1;

    return 0;
}

int Othello_Board::WhitePutCPU(int d, int e) {
    PutOnCheck(Board,  1,  0, d, e, 1, 2);
    PutOnCheck(Board, -1,  0, d, e, 1, 2);
    PutOnCheck(Board,  0,  1, d, e, 1, 2);
    PutOnCheck(Board,  0, -1, d, e, 1, 2);
    PutOnCheck(Board,  1,  1, d, e, 1, 2);
    PutOnCheck(Board, -1,  1, d, e, 1, 2);
    PutOnCheck(Board,  1, -1, d, e, 1, 2);
    PutOnCheck(Board, -1, -1, d, e, 1, 2);

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

        // �w�肵�������� -1 �����鏊�܂Œ��ׂ�
        for (i = 1; board[d + i * p][e + i * q] != -1; i++) {

            // �w�肵�������̓r���� board[][] == 0 or 3 or 4 ���������� return 0
            if (board[d + i * p][e + i * q] == 0 ||
                board[d + i * p][e + i * q] == 3 ||
                board[d + i * p][e + i * q] == 4 ) {
                return 0;
            }

            // �w�肵�������̓r���� board[][] == player ���������� return 1 ��Ԃ�
            if (board[d + i * p][e + i * q] == player) {
                return 1;
            }
        }
    }
    return 0;   // �w�肵�������ɓG�̐΂����������� return 0
}

//���΂��u����ꏊ��T��
int Othello_Board::BoardSearchBlack(int board[PB][PB]) {
    int blackcount = 0;  // ���΂��u����ꏊ�𐔂���p�ϐ�

    // �}�b�v�`�b�v��T��
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            // ���΂ƍ��΂��u����ꏊ��������
            if (board[i][j] == 3 || board[i][j] == 4) {
                board[i][j] = 0;
            }

            // �����u����ĂȂ��ꏊ��������
            if (board[i][j] == 0) {
                if (BlackPutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                        (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GetColor(100, 0, 0), false);

                    board[i][j] = 3;    // ���΂��u����悤�ɂ���
                    blackcount++;       // ���΂��u����ꏊ�̐������C���N�������g

                }

            }
        }
    }

    // ���΂��u����ꏊ������������A�p�X����
    if (blackcount == 0) {
        return 0;
    }
    return 1;
}

//���΂��u����ꏊ��T��
int Othello_Board::BoardSearchWhite(int board[PB][PB]) {
    int whitecount = 0;     // ���΂��u����ꏊ�𐔂���p�ϐ�

    // �}�b�v�`�b�v��T��
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            // ���΂ƍ��΂�u����ꏊ��������
            if (board[i][j] == 4 || board[i][j] == 3) {
                board[i][j] = 0;
            }

            // �����u����Ă��Ȃ��ꏊ�Ȃ�
            if (board[i][j] == 0) {
                if (WhitePutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                        (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GetColor(100, 0, 0), false);

                    board[i][j] = 4;    // ���΂��u����悤�ɂ���
                    whitecount++;       // ���΂��u����ꏊ�̐������C���N�������g
                }
            }
        }
    }

    // ���΂��u����ꏊ������������A�p�X����
    if (whitecount == 0) {
        return 0;
    }
    return 1;
}

// ���΂Ɣ��΂̐��𒲂ׂ�
void Othello_Board::BoardSearchBWNumber(int board[PB][PB]) {
    BlackNum = 0;   // ���΂̐���������
    WhiteNum = 0;   // ���΂̐���������

    // �}�b�v�`�b�v�����ɒT��
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


// �Q�[�����I�������𖞂����Ă�����A�I�����鏈��(��)
int Othello_Board::EndGame(int board[PB][PB]) {

    // ���΂Ɣ��΁A�����Ƃ��u���Ƃ��낪�Ȃ��Ȃ�����
    if (!BoardSearchBlack(Board)) {
        if (!BoardSearchWhite(Board)) {
            return 1;
        }
    }

    // ���΂Ɣ��΂ŔՖʂ����܂�����
    if (WhiteNum + BlackNum == 64) {
        return 1;
    }

    return 0;
}


// CPU�i���j
int Othello_Board::ReturnNumWhite(int board[PB][PB]) {
    //board[Board_X][Board_Y] = 2;
    //WhitePutCPU();
    // �}�b�v�`�b�v���g���Ă݂�
    // PutOnSearch�����ǂ��Ă݂�

    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 4) {
                // �u����}�X�̂Ђ�����Ԃ��鐔�𒲂ׂ���
                if (ReturnNumMax < ReturnNum) {
                    ReturnNumMax = ReturnNum;
                    Board_X = i;
                    Board_Y = j;
                }

            }
        }
    }
    board[Board_X][Board_Y] = 2;
    WhitePutCPU(Board_X, Board_Y);
    Board_X = 0;
    Board_Y = 0;
    ReturnNumMax = 0;
    return 1;
}