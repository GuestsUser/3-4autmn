#include"DxLib.h"
#include"windows.h"
#include <string.h>
#include "./../Code/GetKey.h"
#include "./Othello_Board.h"
#include "./Othello_Player.h"
#include "./../Scene.h"
#include "./../Title/Scene_Select.h"

//Othello_Board* OB;

// ������
void Othello_Board::Othello_Board_Initialize(Scene* scene) {

    Parent = scene;

    PutCheckImage = LoadGraph("Resource/image/Othello_Image/OthelloPutCheck2.png");   // �u����ꏊ�̃J�b�R�̉摜�̓ǂݍ���

    BGM = LoadSoundMem("Resource/bgm/Othello_BGM/OthelloBGM.mp3");      // �Q�[������BGM�̓ǂݍ���
    PutSE = LoadSoundMem("Resource/se/Othello_SE/OthelloPut.mp3");      // �΂�u��������SE�̓ǂݍ���
    PassSE = LoadSoundMem("Resource/se/Othello_SE/OthelloPass.mp3");    // �p�X���ꂽ�Ƃ���SE�̓ǂݍ���

    ChangeVolumeSoundMem(55, BGM);      // BGM�̉��ʐݒ�
    ChangeVolumeSoundMem(100, PutSE);   // �΂�u��������SE�̉��ʐݒ�
    ChangeVolumeSoundMem(100, PassSE);  // �p�X���ꂽ�Ƃ���SE�̉��ʐݒ�


    BlackCr = GetColor(0, 0, 0);        // ���F��ݒ�
    GreenCr = GetColor(0, 255, 0);      // �ΐF��ݒ�
    WhiteCr = GetColor(255, 255, 255);  // ���F��ݒ�
    Cr = GetColor(255, 222, 173);

    OrderNum = 0;   // 0 = ���΁A 1 = ����
    BlackNum = 0;   // ���΂̑����̏�����
    WhiteNum = 0;   // ���΂̑����̏�����
    TimeCount = 0;  // �b�����J�E���g���邽�߂̕ϐ���������
    ReturnNumMax = 0;   // ��ԑ����Ђ�����Ԃ��鐔������ϐ�
    RandomNum = 0;

    DrawFlag = false;
    CheckFlag = false;
    PassFlag = false;
    EndFlag = false;
    RandomFlag = false;
    CornerFlag = false;

    Init_OthelloBoard(Board);           // �{�[�h��������
    
}

// -------------�I������---------------------------
void Othello_Board::Othello_Board_Finalize() {
	DeleteGraph(PutCheckImage);
    DeleteSoundMem(PutSE);
    DeleteSoundMem(BGM);
}
// ------------------------------------------------


// ---------------�X�V---------------------------
void Othello_Board::Othello_Board_Update() {

    RandomOrder();

    GetMousePoint(&Mouse_X, &Mouse_Y);  // �}�E�X�J�[�\���̈ʒu���擾
    Square_X = Mouse_X / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE �Ŋ������l����
    Square_Y = Mouse_Y / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE �Ŋ������l����

    if (EndFlag == false) {   // �Q�[�����I��������ǂ���

        PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, false);

        if (PassFlag == false) {    // �p�X�t���O�� false �Ȃ�

            if (RandomFlag == true) {
                switch (Player) {
                case 0:
                    if (OrderNum == 0) {    // ���̔Ԃ�������

                         // ���΂̒u����ꏊ���Ȃ��Ȃ�
                        if (!BoardSearchBlack(Board))
                        {
                            PlaySoundMem(PassSE, DX_PLAYTYPE_BACK, true);
                            PassFlag = true;    // �p�X�t���O�� true �ɂ���
                        }

                        BoardSearchBlack(Board);

                        if (Board[Square_X][Square_Y] == 3 ||
                            Board[Square_X][Square_Y] == 6 ||
                            Board[Square_X][Square_Y] == 8 ) {   // ���΂��u����ꏊ�ɃJ�[�\���������Ă�����
                            DrawFlag = true;
                            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
                                DrawFlag = false;
                                Board[Square_X][Square_Y] = 1;      // ���΂�u��
                                BlackPut();                         // �u�����ꏊ���甒�����ɂЂ�����Ԃ�
                                PlaySoundMem(PutSE, DX_PLAYTYPE_BACK, true);
                                OrderNum = 1;                       // ���̎�Ԃɂ���
                                BoardSearchBWNumber(Board);         // ���΂Ɣ��΂̐��𐔂���֐����s

                                if (EndGame(Board)) {               // �Q�[�����I�������𖞂�������
                                    EndFlag = true;   // �G���h�t���O�� true �ɂ���
                                }

                                DrawFlag = false;
                            }

                        }
                        else {
                            DrawFlag = false;
                        }
                    }
                    else {      // ���̔Ԃ�������

                        //---------- CPU ----------------------

                        // �����u���ꏊ������������
                        if (!BoardSearchWhite(Board)) {
                            PlaySoundMem(PassSE, DX_PLAYTYPE_BACK, true);
                            PassFlag = true;    // �p�X�t���O�� true �ɂ���
                        }


                        // 1�b�o���Ă���
                        if (TimeCount++ >= 60) {
                            TimeCount = 0;      // TimeCount ��������
                            CPUWhite(Board);    // ��ԂЂ�����Ԃ���ꏊ�ɒu��
                            PlaySoundMem(PutSE, DX_PLAYTYPE_BACK, true);
                            OrderNum = 0;       // ���̔Ԃɂ���
                        }

                        BoardSearchBWNumber(Board);     // ���΂Ɣ��΂̐��𐔂���

                        // �Q�[���̏I�������������Ă�����  
                        if (EndGame(Board)) {
                            EndFlag = true;     // �G���h�t���O�� true �ɂ���
                        }
                    }
                    break;

                case 1:
                    // �����Ƀv���C���[�����F�ŁACPU�����F�̏���������
                    if (OrderNum == 0) {
                        //--------------- CPU ---------------------
                        // �����u���ꏊ������������
                        if (!BoardSearchBlack(Board)) {
                            PlaySoundMem(PassSE, DX_PLAYTYPE_BACK, true);
                            PassFlag = true;    // �p�X�t���O�� true �ɂ���
                        }

                        // 1�b�o���Ă���
                        if (TimeCount++ >= 60) {
                            TimeCount = 0;      // TimeCount ��������
                            CPUBlack(Board);    // ��ԂЂ�����Ԃ���ꏊ�ɒu��
                            PlaySoundMem(PutSE, DX_PLAYTYPE_BACK, true);
                            OrderNum = 1;       // ���̔Ԃɂ���
                        }

                        BoardSearchBWNumber(Board);     // ���΂Ɣ��΂̐��𐔂���

                        // �Q�[���̏I�������������Ă�����  
                        if (EndGame(Board)) {
                            EndFlag = true;     // �G���h�t���O�� true �ɂ���
                        }
                    }
                    else {
                        // ���΂̒u����ꏊ���Ȃ��Ȃ�
                        if (!BoardSearchWhite(Board))
                        {
                            PlaySoundMem(PassSE, DX_PLAYTYPE_BACK, true);
                            PassFlag = true;    // �p�X�t���O�� true �ɂ���
                        }

                        if (Board[Square_X][Square_Y] == 4 ||
                            Board[Square_X][Square_Y] == 6 ||
                            Board[Square_X][Square_Y] == 8 ) {   // ���΂��u����ꏊ�ɃJ�[�\���������Ă�����
                            DrawFlag = true;
                            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������

                                DrawFlag = false;
                                Board[Square_X][Square_Y] = 2;      // ���΂�u��
                                WhitePut();                         // �u�����ꏊ���獕�𔒂ɂЂ�����Ԃ�
                                PlaySoundMem(PutSE, DX_PLAYTYPE_BACK, true);
                                OrderNum = 0;                       // ���̎�Ԃɂ���
                                BoardSearchBWNumber(Board);         // ���΂Ɣ��΂̐��𐔂���֐����s

                                if (EndGame(Board)) {               // �Q�[�����I�������𖞂�������
                                    EndFlag = true;   // �G���h�t���O�� true �ɂ���
                                }
                                DrawFlag = false;
                            }

                        }
                        else {
                            DrawFlag = false;
                        }
                    }
                    break;
                }
                
            }
        }
    }
}
// -----------------------------------------------


// ------------------�`��-----------------------------------------------
void Othello_Board::Othello_Board_Draw() {
    DrawBox(0, 0, 1280, 720, Cr, TRUE);
    //DrawGraph(1000, 100, PutCheckImage, false);
    DrawBox(60, 60, 66 * 9 + 6, 66 * 9 + 6, BlackCr, TRUE);
    Print_OthelloBoard(Board);      // �I�Z���{�[�h�̕`��

    DrawCircle(800, 187, 27, BlackCr, TRUE);
    DrawCircle(800, 307, 27, WhiteCr, TRUE);
    DrawFormatString(800 + MAP_SIZE / 2, 167, BlackCr, "����:%d", BlackNum);
    DrawFormatString(800 + MAP_SIZE / 2 , 287, BlackCr, "����:%d", WhiteNum);

    if (PassFlag == false) {    // �p�X����ĂȂ��Ȃ�
        switch (Player) {
        case 0:
            if (OrderNum == 0) {    // ���̔Ԃ�������
                DrawFormatString(800, 90, BlackCr, "���Ȃ��̔Ԃł�");
                BoardSearchBlack(Board);    // ���΂��u����ꏊ��`�悷��
            }
            else {                  // ���̔Ԃ�������
                DrawFormatString(800, 90, BlackCr, "CPU�̔Ԃł�");
                BoardSearchWhite(Board);    // ���΂��u����ꏊ��`�悷��
            }
            break;
            
        case 1:
            if (OrderNum == 0) {    // ���̔Ԃ�������
                DrawFormatString(800, 90, BlackCr, "CPU�̔Ԃł�");
                BoardSearchBlack(Board);    // ���΂��u����ꏊ��`�悷��
            }
            else {                  // ���̔Ԃ�������
                DrawFormatString(800, 90, BlackCr, "���Ȃ��̔Ԃł�");
                BoardSearchWhite(Board);    // ���΂��u����ꏊ��`�悷��
            }
            break;
        }
    }
    else {

        DrawFormatString(800, 90, BlackCr, "�p�X�I");      // �p�X�I�ƕ\������
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

    // �Q�[�����I��������
    if (EndFlag == true) {

        DrawFormatString(800, 400, BlackCr, "�Q�[���I���I");
        DrawFormatString(800, 500, BlackCr, "3�b��Ƀ��Z�b�g���܂�");

        if (WhiteNum < BlackNum) {  // ���΂̐��̕�������������A���̏���
            switch (Player) {
            case 0:
                DrawFormatString(800, 450, BlackCr, "���Ȃ��̏����I");
                if (TimeCount++ >= 180) {   // 3�b�o������
                    TimeCount = 0;      // TimeCount ��������
                    BlackNum = 0;       // ���΂̐���������
                    WhiteNum = 0;       // ���΂̐���������
                    OrderNum = 0;       // ���̎�Ԃɂ���
                    EndFlag = false;    // �I��������������
                    RandomFlag = false;
                    Parent->SetNext(new Scene_Select());
                    Init_OthelloBoard(Board);   // �I�Z���{�[�h��������
                }
                break;

            case 1:
                DrawFormatString(800, 450, BlackCr, "CPU�̏����I");
                if (TimeCount++ >= 180) {   // 3�b�o������
                    TimeCount = 0;      // TimeCount ��������
                    BlackNum = 0;       // ���΂̐���������
                    WhiteNum = 0;       // ���΂̐���������
                    OrderNum = 0;       // ���̎�Ԃɂ���
                    EndFlag = false;    // �I��������������
                    RandomFlag = false;
                    Parent->SetNext(new Scene_Select());
                    Init_OthelloBoard(Board);   // �I�Z���{�[�h��������
                }
                break;
            }
        }
        else if (BlackNum < WhiteNum) { // ���΂̐��̕�������������A���̏���
            switch (Player) {
            case 0:
                DrawFormatString(800, 450, BlackCr, "CPU�̏����I");
                if (TimeCount++ >= 180) {   // 3�b�o������
                    TimeCount = 0;      // TimeCount ��������
                    BlackNum = 0;       // ���΂̐���������
                    WhiteNum = 0;       // ���΂̐���������
                    OrderNum = 0;       // ���̎�Ԃɂ���
                    EndFlag = false;    // �I��������������
                    RandomFlag = false;
                    Parent->SetNext(new Scene_Select());
                    Init_OthelloBoard(Board);   // �I�Z���{�[�h��������
                }
                break;

            case 1:
                DrawFormatString(800, 450, BlackCr, "���Ȃ��̏����I");
                if (TimeCount++ >= 180) {   // 3�b�o������
                    TimeCount = 0;      // TimeCount ��������
                    BlackNum = 0;       // ���΂̐���������
                    WhiteNum = 0;       // ���΂̐���������
                    OrderNum = 0;       // ���̎�Ԃɂ���
                    EndFlag = false;    // �I��������������
                    RandomFlag = false;
                    Parent->SetNext(new Scene_Select());
                    Init_OthelloBoard(Board);   // �I�Z���{�[�h��������
                }
                break;
            }
        }
        else {
            DrawFormatString(800, 450, BlackCr, "���������I");
            if (TimeCount++ >= 180) {   // 3�b�o������
                TimeCount = 0;      // TimeCount ��������
                BlackNum = 0;       // ���΂̐���������
                WhiteNum = 0;       // ���΂̐���������
                OrderNum = 0;       // ���̎�Ԃɂ���
                EndFlag = false;    // �I��������������
                RandomFlag = false;
                Parent->SetNext(new Scene_Select());
                Init_OthelloBoard(Board);   // �I�Z���{�[�h��������
            }
        }

    }
    DrawFormatString(800, 600, BlackCr, "%d", RandomNum);

}
// ---------------------------------------------------------------------


/* 
* �{�[�h������������
* ����: Board ������
* �߂�l�F�Ȃ�
*/
void Othello_Board::Init_OthelloBoard(int board[PB][PB]) {
    static int InitBoard[PB][PB] =
    {
     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
     {-1,  5,  7,  0,  0,  0,  0,  7,  5, -1},
     {-1,  7,  7,  0,  0,  0,  0,  7,  7, -1},
     {-1,  0,  0,  0,  0,  0,  0,  0,  0, -1},
     {-1,  0,  0,  0,  2,  1,  0,  0,  0, -1},
     {-1,  0,  0,  0,  1,  2,  0,  0,  0, -1},
     {-1,  0,  0,  0,  0,  0,  0,  0,  0, -1},
     {-1,  7,  7,  0,  0,  0,  0,  7,  7, -1},
     {-1,  5,  7,  0,  0,  0,  0,  7,  5, -1},
     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    };
    memcpy(board, InitBoard, sizeof(InitBoard));
}


/*
* �{�[�h��\������
* ����: Board ������
* �߂�l�F�Ȃ�
*/
void Othello_Board::Print_OthelloBoard(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {

            /* ���ɋ������Ȃ������u����Ă��Ȃ� */
            if (board[i][j] == 0) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                DrawFormatString(i * MAP_SIZE + 5, j * MAP_SIZE + 5, GetColor(255, 0, 0), "0");
            }

            /* ���΂��u����Ă��� */
            if (board[i][j] == 1) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                // ���΂�u��
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2), j * MAP_SIZE + (MAP_SIZE / 2), 27, BlackCr, TRUE);
                DrawFormatString(i * MAP_SIZE + 5, j * MAP_SIZE + 5, GetColor(255, 0, 0), "1");

            }

            /* ���΂��u����Ă��� */
            if (board[i][j] == 2) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                // ���΂�u��
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2), j * MAP_SIZE + (MAP_SIZE / 2), 27, WhiteCr, TRUE);
                DrawFormatString(i * MAP_SIZE + 5, j * MAP_SIZE + 5, GetColor(255, 0, 0), "2");

            }

            /* ���΂��u����ꏊ */
            if (board[i][j] == 3) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
                DrawFormatString(i * MAP_SIZE + 5, j * MAP_SIZE + 5, GetColor(255, 0, 0), "3");

            }

            /* ���΂��u����ꏊ */
            if (board[i][j] == 4) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
                DrawFormatString(i * MAP_SIZE + 5, j * MAP_SIZE + 5, GetColor(255, 0, 0), "4");

            }

            /* �p */
            if (board[i][j] == 5) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                DrawFormatString(i * MAP_SIZE + 5, j * MAP_SIZE + 5, GetColor(255, 0, 0), "5");

            }

            /* �u����悤�ɂȂ����p */
            if (board[i][j] == 6) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
                DrawFormatString(i * MAP_SIZE + 5, j * MAP_SIZE + 5, GetColor(255, 0, 0), "6");
            }

            /* �p�̎���� 3 �}�X */
            if (board[i][j] == 7) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);
                DrawFormatString(i* MAP_SIZE + 5, j* MAP_SIZE + 5, GetColor(255, 0, 0), "7");

            }

            /* ����悤�ɂȂ����p�̎���� 3 �}�X*/
            if (board[i][j] == 8) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE, j * MAP_SIZE,
                    (i * MAP_SIZE) + MAP_SIZE, (j * MAP_SIZE) + MAP_SIZE, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + 1, (j * MAP_SIZE) + 1,
                    (i * MAP_SIZE) + MAP_SIZE - 1, (j * MAP_SIZE) + MAP_SIZE - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
                DrawFormatString(i* MAP_SIZE + 5, j* MAP_SIZE + 5, GetColor(255, 0, 0), "8");

            }
        }
    }
}

/*
* �J�[�\�����u����}�X�ɗ������ɐԂ��\������
* ����: �Ȃ�
* �߂�l�F�Ȃ�
*/
void Othello_Board::CursorOn_OthelloBoard() {
    if (DrawFlag == true)
    {
        DrawBox((Square_X * MAP_SIZE) + 1, (Square_Y * MAP_SIZE) + 1,
            (Square_X * MAP_SIZE) + MAP_SIZE - 1, (Square_Y * MAP_SIZE) + MAP_SIZE - 1, GetColor(255, 0, 0), TRUE);
    }
}

/*
* ����
* �Z1.�u����Ƃ����T��
* �Z2.�u����Ƃ���ɐ΂�u��
* �Z3.�΂��Ђ�����Ԃ�
*/


/*
* �v���C���[�̐΂ő���̐΂����ނƎ����̐΂̐F�̕ς���
* ����: Board ������, X���̌������w��, Y���̌������w��, �G�̐�, �v���C���[�̐�
* �߂�l�F�Ђ�����Ԃ���ꏊ���Ȃ������� retun 0, �������� return 1 ��Ԃ�
*/
int Othello_Board::CursorPutOnCheck(int board[PB][PB], int p, int q, int enemy, int player) {

    int count = 0;  // CheckNum �̒l������p�ϐ�

    // ���ׂ������ɑ΂��ēG�̐΂���������
    if (board[Square_X + p][Square_Y + q] == enemy) {

        // �J�[�\���������Ă���Ƃ��납��A�u�����ꍇ�v���C���[�̐΂����邩�ǂ������ׂ�
        for (CheckNum = 1; board[Square_X + CheckNum * p][Square_Y + CheckNum * q] != player; CheckNum++) {

            // ���ׂ������ɋ󂢂Ă���}�X����������
            if (board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 0 ||
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 5 ||
                board[Square_X + CheckNum * p][Square_Y + CheckNum * q] == 7 ||
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
                board[Square_X + count * p][Square_Y + count * q] == 5 ||
                board[Square_X + count * p][Square_Y + count * q] == 7 ||
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


/*
* CPU�̐΂ő���̐΂����ނƎ����̐΂̐F�̕ς���
* ����: Board ������, X���̌������w��, Y���̌������w��, CPU��X���̈ʒu, CPU��Y���̈ʒu, �G�̐�, �v���C���[�̐�
* �߂�l�F�Ђ�����Ԃ���ꏊ���Ȃ������� retun 0, �������� return 1 ��Ԃ�
*/
int Othello_Board::CPUPutOnCheck(int board[PB][PB], int p, int q, int d, int e, int enemy, int player) {

    int count = 0;  // CheckNum �̒l������p�ϐ�

    // ���ׂ������ɑ΂��ēG�̐΂���������
    if (board[d + p][e + q] == enemy) {

        // �u�����ꍇ�A�w�肵�������Ƀv���C���[�̐΂����邩�ǂ������ׂ�
        for (CheckNum = 1; board[d + CheckNum * p][e + CheckNum * q] != player; CheckNum++) {

            // ���ׂ������ɋ󂢂Ă���}�X����������
            if (board[d + CheckNum * p][e + CheckNum * q] == 0 ||
                board[d + CheckNum * p][e + CheckNum * q] == 5 ||
                board[d + CheckNum * p][e + CheckNum * q] == 7 ||
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
                board[d + count * p][e + count * q] == 5 ||
                board[d + count * p][e + count * q] == 6 ||
                board[d + count * p][e + count * q] == 7 ||
                board[d + count * p][e + count * q] == 8 ||
                board[d + count * p][e + count * q] == -1) {
                return 0;
            }
        }



        // ���ׂ������ɑ΂��āA ������x�t���ɒH���� player �̐΂ɂЂ�����Ԃ�
        for (CheckNum = CheckNum - 1; board[d + CheckNum * p][e + CheckNum * q] != player; CheckNum--) {
            // ���ׂ��}�X�� enemy �̃}�X��������
            if (board[d + CheckNum * p][e + CheckNum * q] == enemy) {
                board[d + CheckNum * p][e + CheckNum * q] = player;   // player �̐΂ɂЂ�����Ԃ�
            }
        }
    }
    return 1;
}


/*
* ���΂�u�����ʒu����A����ŕς����锒�΂�T���č��΂ɕς���
* ����: �Ȃ�
* �߂�l�F�Ђ�����Ԃ���ꏊ������������ return 0 ��Ԃ�
*/
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


/*
* ���΂�u�����ʒu����A����ŕς����鍕�΂�T���Ĕ��΂ɕς���
* �����F�Ȃ�
* �߂�l�F�Ђ�����Ԃ���ꏊ���Ȃ������� retun 0 ��Ԃ�
*/
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


// 
int Othello_Board::WhitePutCPU(int d, int e) {
    CPUPutOnCheck(Board,  1,  0, d, e, 1, 2);
    CPUPutOnCheck(Board, -1,  0, d, e, 1, 2);
    CPUPutOnCheck(Board,  0,  1, d, e, 1, 2);
    CPUPutOnCheck(Board,  0, -1, d, e, 1, 2);
    CPUPutOnCheck(Board,  1,  1, d, e, 1, 2);
    CPUPutOnCheck(Board, -1,  1, d, e, 1, 2);
    CPUPutOnCheck(Board,  1, -1, d, e, 1, 2);
    CPUPutOnCheck(Board, -1, -1, d, e, 1, 2);

    return 0;
}

int Othello_Board::BlackPutCPU(int d, int e) {
    CPUPutOnCheck(Board,  1,  0, d, e, 2, 1);
    CPUPutOnCheck(Board, -1,  0, d, e, 2, 1);
    CPUPutOnCheck(Board,  0,  1, d, e, 2, 1);
    CPUPutOnCheck(Board,  0, -1, d, e, 2, 1);
    CPUPutOnCheck(Board,  1,  1, d, e, 2, 1);
    CPUPutOnCheck(Board, -1,  1, d, e, 2, 1);
    CPUPutOnCheck(Board,  1, -1, d, e, 2, 1);
    CPUPutOnCheck(Board, -1, -1, d, e, 2, 1);

    return 0;
}

// ���E��΂߂ɐ΂����邩�ǂ������ׂ�
int Othello_Board::BlackPutCheck(int d, int e) {

    if (PutSearch(Board, 1, 0, d, e, 2, 1)){    // �E
        return PutSearch(Board, 1, 0, d, e, 2, 1);
    }
    if (PutSearch(Board, -1, 0, d, e, 2, 1)) {  // ��
        return PutSearch(Board, -1, 0, d, e, 2, 1);
    }
    if (PutSearch(Board, 0, -1, d, e, 2, 1)) {  // ��
        return PutSearch(Board, 0, -1, d, e, 2, 1);
    }
    if (PutSearch(Board, 0, 1, d, e, 2, 1)) {   // ��
        return PutSearch(Board, 0, 1, d, e, 2, 1);
    }

    if (PutSearch(Board, 1, 1, d, e, 2, 1)) {   // �E��
        return PutSearch(Board, 1, 1, d, e, 2, 1);
    }
    if (PutSearch(Board, -1, 1, d, e, 2, 1)) {  // ����
        return PutSearch(Board, -1, 1, d, e, 2, 1);
    }
    if (PutSearch(Board, 1, -1, d, e, 2, 1)) {  // �E��
        return PutSearch(Board, 1, -1, d, e, 2, 1);
    }
    if (PutSearch(Board, -1, -1, d, e, 2, 1)) { // ����
        return PutSearch(Board, -1, -1, d, e, 2, 1);
    }

    return 0;
}


int Othello_Board::WhitePutCheck(int d, int e) {

    if (PutSearch(Board, 1, 0, d, e, 1, 2)) {    // �E
        return PutSearch(Board, 1, 0, d, e, 1, 2);
    }

    if (PutSearch(Board, -1, 0, d, e, 1, 2)) {  // ��
        return PutSearch(Board, -1, 0, d, e, 1, 2);
    }

    if (PutSearch(Board, 0, -1, d, e, 1, 2)) {  // ��
        return PutSearch(Board, 0, -1, d, e, 1, 2);
    }
    if (PutSearch(Board, 0, 1, d, e, 1, 2)) {   // ��
        return PutSearch(Board, 0, 1, d, e, 1, 2);
    }

    if (PutSearch(Board, 1, 1, d, e, 1, 2)) {   // �E��
        return PutSearch(Board, 1, 1, d, e, 1, 2);
    }

    if (PutSearch(Board, -1, 1, d, e, 1, 2)) {  // ����
        return PutSearch(Board, -1, 1, d, e, 1, 2);
    }

    if (PutSearch(Board, 1, -1, d, e, 1, 2)) {  // �E��
        return PutSearch(Board, 1, -1, d, e, 1, 2);
    }

    if (PutSearch(Board, -1, -1, d, e, 1, 2)) { // ����
        return PutSearch(Board, -1, -1, d, e, 1, 2);
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
                board[d + i * p][e + i * q] == 4 || 
                board[d + i * p][e + i * q] == 5 ||
                board[d + i * p][e + i * q] == 6 ||
                board[d + i * p][e + i * q] == 7 ||
                board[d + i * p][e + i * q] == 8) {
                return 0;
            }

            // �w�肵�������̓r���� board[][] == player ���������� return 1 ��Ԃ�
            if (board[d + i * p][e + i * q] == player) {
                return i - 1;
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
            if (board[i][j] == 6) {
                board[i][j] = 5;
            }
            if (board[i][j] == 8) {
                board[i][j] = 7;
            }

            // �����u����ĂȂ��ꏊ��������
            if (board[i][j] == 0) {
                if (BlackPutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawGraph(i * MAP_SIZE, j * MAP_SIZE, PutCheckImage, true);

                    board[i][j] = 3;    // ���΂��u����悤�ɂ���
                    blackcount++;       // ���΂��u����ꏊ�̐������C���N�������g

                }
            }
            if (board[i][j] == 5) {
                if (BlackPutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawGraph(i * MAP_SIZE, j * MAP_SIZE, PutCheckImage, true);

                    board[i][j] = 6;    // ���΂��u����悤�ɂ���
                    blackcount++;       // ���΂��u����ꏊ�̐������C���N�������g

                }
            }
            if (board[i][j] == 7) {
                if (BlackPutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawGraph(i * MAP_SIZE, j * MAP_SIZE, PutCheckImage, true);

                    board[i][j] = 8;    // ���΂��u����悤�ɂ���
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
            if (board[i][j] == 6) {
                board[i][j] = 5;
            }
            if (board[i][j] == 8) {
                board[i][j] = 7;
            }

            // �����u����Ă��Ȃ��ꏊ�Ȃ�
            if (board[i][j] == 0) {
                if (WhitePutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawGraph(i * MAP_SIZE, j * MAP_SIZE, PutCheckImage, true);

                    board[i][j] = 4;    // ���΂��u����悤�ɂ���
                    whitecount++;       // ���΂��u����ꏊ�̐������C���N�������g
                }
            }
            if (board[i][j] == 5) {
                if (WhitePutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawGraph(i * MAP_SIZE, j * MAP_SIZE, PutCheckImage, true);

                    board[i][j] = 6;    // ���΂��u����悤�ɂ���
                    whitecount++;       // ���΂��u����ꏊ�̐������C���N�������g
                }
            }
            if (board[i][j] == 7) {
                if (WhitePutCheck(i, j)) {  // ���΂��u����ꏊ����������

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawGraph(i * MAP_SIZE, j * MAP_SIZE, PutCheckImage, true);

                    board[i][j] = 8;    // ���΂��u����悤�ɂ���
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


// ���΂�CPU
int Othello_Board::CPUWhite(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 8) {
                Board_X = i;
                Board_Y = j;
            }

            if (board[i][j] == 4) {

                if (ReturnNumMax < WhitePutCheck(i, j)) {
                    ReturnNumMax = WhitePutCheck(i, j);
                    Board_X = i;
                    Board_Y = j;
                }
            }

            if (board[i][j] == 6) {
                Board_X = i;
                Board_Y = j;
                CornerFlag = true;
                break;
            }
        }
        if (CornerFlag == true) {
            break;
        }
    }

    board[Board_X][Board_Y] = 2;
    WhitePutCPU(Board_X, Board_Y);
    Board_X = 0;
    Board_Y = 0;
    ReturnNumMax = 0;
    CornerFlag = false;
    return 1;
}



int Othello_Board::CPUBlack(int board[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 3) {

                if (ReturnNumMax < BlackPutCheck(i, j)) {
                    ReturnNumMax = BlackPutCheck(i, j);
                    Board_X = i;
                    Board_Y = j;
                }

            }
        }
    }
    board[Board_X][Board_Y] = 1;
    BlackPutCPU(Board_X, Board_Y);
    Board_X = 0;
    Board_Y = 0;
    ReturnNumMax = 0;
    return 1;
}



int Othello_Board::RandomOrder() {
    if (RandomFlag == false) {
        //RandomNum = GetRand(100);
        RandomNum = 50;
        RandomFlag = true;
    }

    // 50�ȏ�ō��F���v���C���[�A����ȊO�͔��F���v���C���[
    if (RandomNum >= 50) {
        Player = 0;
    }
    else {
        Player = 1;
    }

    return 1;
}