#include"DxLib.h"
#include<stdlib.h>
#include<time.h>
#include"windows.h"
#include <string.h>
#include "./../Code/GetKey.h"
#include "./Othello_Board.h"
#include "./../Scene.h"
#include "./../Title/Scene_Select.h"
#include "../Title/Scene_GameTitle.h"
#include "../../SceneManager.h"

//Othello_Board* OB;

// ������
void Othello_Board::Othello_Board_Initialize(Scene* scene) {

    Parent = scene;

    PutCheckImage = LoadGraph("Resource/image/Othello_Image/OthelloPutCheck2.png");     // �u����ꏊ�̃J�b�R�̉摜�̓ǂݍ���
    ResultImage = LoadGraph("Resource/image/Othello_Image/Othello_Result2.png");        // ���U���g��ʂ̉摜�̓ǂݍ���
    Black = LoadGraph("Resource/image/Othello_Image/Black.png");            // ���΂̉摜�̓ǂݍ���
    White = LoadGraph("Resource/image/Othello_Image/White.png");            // ���΂̉摜�̓ǂݍ���
    SenteGote = LoadGraph("Resource/image/Othello_Image/SenteGote.png");    // ���E���̉摜�̓ǂݍ��� 

    // �����E�����E���������̉摜�̓ǂݍ���
    LoadDivGraph("Resource/image/Othello_Image/winlosedraw.png", 3, 3, 1, 400, 120, WinLoseImage);
    // �v���C���[��CPU���̉摜�̓ǂݍ���
    LoadDivGraph("Resource/image/Othello_Image/Player.png", 2, 2, 1, 450, 150, PlayerImage);
    // �i���o�[�摜�̓ǂݍ���
    LoadDivGraph("Resource/image/Othello_Image/Number.png", 10, 10, 1, 45, 70, NumberImage);

    Pause_Button = LoadGraph("Resource/image/PauseButton.png");     // �|�[�Y�{�^���̉摜�̓ǂݍ���
    Pause_Back = LoadGraph("Resource/image/PauseBack.png");         // �|�[�Y��ʂ̔w�i�̉摜�̓ǂݍ���
    // �u�Â���v�{�^���̉摜�̓ǂݍ���
    Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
    // �u�Z���N�g�ɖ߂�v�{�^���̉摜�̓ǂݍ��� 
    Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);

    BGM = LoadSoundMem("Resource/bgm/Othello_BGM/OthelloBGM.mp3");      // �Q�[������BGM�̓ǂݍ���
    PutSE = LoadSoundMem("Resource/se/Othello_SE/OthelloPut.mp3");      // �΂�u��������SE�̓ǂݍ���
    PassSE = LoadSoundMem("Resource/se/Othello_SE/OthelloPass.mp3");    // �p�X���ꂽ�Ƃ���SE�̓ǂݍ���
    PauseClickSE = LoadSoundMem("Resource/se/Pause_Click.wav");
    PauseSelectSE = LoadSoundMem("Resource/se/Pause_Cursor.wav");

    ChangeVolumeSoundMem(55, BGM);      // BGM�̉��ʐݒ�
    ChangeVolumeSoundMem(100, PutSE);   // �΂�u��������SE�̉��ʐݒ�
    ChangeVolumeSoundMem(100, PassSE);  // �p�X���ꂽ�Ƃ���SE�̉��ʐݒ�
    ChangeVolumeSoundMem(100, PauseClickSE);
    ChangeVolumeSoundMem(100, PauseSelectSE);


    BlackCr = GetColor(0, 0, 0);        // ���F��ݒ�
    GreenCr = GetColor(0, 255, 0);      // �ΐF��ݒ�
    WhiteCr = GetColor(255, 255, 255);  // ���F��ݒ�
    RedCr = GetColor(255, 0, 0);        // �ԐF��ݒ�
    Cr = GetColor(255, 222, 173);       // �w�i�F��ݒ�

    OrderNum = 0;       // 0 = ���΁A 1 = ����
    BlackNum = 0;       // ���΂̑����̏�����
    WhiteNum = 0;       // ���΂̑����̏�����
    TimeCount = 0;      // �b�����J�E���g���邽�߂̕ϐ���������
    ReturnNumMax = 0;   // ��ԑ����Ђ�����Ԃ��鐔������ϐ�
    RandomNum = 0;      // �����_���Ȓl������ϐ��̏����� 
    PutPlace_X = -10;   // �u�����ꏊ�ɏ\������`�悷����WX�̏�����
    PutPlace_Y = -10;   // �u�����ꏊ�ɏ\������`�悷����WY�̏�����

    BoardShift_X = 180 - 99;        // �{�[�h�����炵������X���W�̒l��ݒ�
    BoardShift_Y = (80 - 66) * 2;   // �{�[�h�����炵������Y���W�̒l��ݒ�

    SizeCount = 0.5f;

    srand(time(NULL));  // ���݂̎������擾

    DrawFlag = false;       // �J�[�\�����΂�u����ꏊ�ɗ������Ɏg���t���O�̏�����
    CheckFlag = false;      // �΂��u����ꏊ�����邩�ǂ������ׂ�Ƃ��Ɏg���t���O�̏�����
    PassFlag = false;       // �p�X����邩�ǂ������ׂ�Ƃ��Ɏg���t���O�̏�����
    EndFlag = false;        // �Q�[���̏I�������𖞂��������ǂ����Ɏg���t���O�̏�����
    RandomFlag = false;     // �����_���Ȓl���擾�������ǂ����Ɏg���t���O�̏�����
    PauseFlg = false;       // �|�[�Y��ʂ�\�������邩�ǂ����Ɏg���t���O�̏�����
    SizeFlag = false;

    for (int i = 0; i < 4; i++) {
        SEFlag[i] = false;
    }

    RandomOrder();      // �v���C���[�����E��肩�������_���Ɍ��߂�֐�
    Init_OthelloBoard(Board);           // �{�[�h��������
    BoardScore(ScoreBoard);             // �{�[�h�ɕ]���l������
}

// -------------�I������---------------------------
void Othello_Board::Othello_Board_Finalize() {
	DeleteGraph(PutCheckImage);     // �J�b�R�̉摜�̍폜
    DeleteGraph(ResultImage);       // ���U���g��ʂ̉摜�̍폜
    DeleteGraph(Black);             // ���΂̉摜�̍폜
    DeleteGraph(White);             // ���΂̉摜�̍폜
    DeleteGraph(Pause_Button);      // �|�[�Y�{�^���̉摜�̍폜
    DeleteGraph(Pause_Back);        // �|�[�Y��ʂ̔w�i�̉摜�̍폜
    DeleteGraph(SenteGote);

    // �|�[�Y�́u�Â���v�Ɓu�Z���N�g�ɖ߂�v�̉摜�̍폜
    for (int i = 0; i < 2; i++) {
        DeleteGraph(pause_continue[i]);
        DeleteGraph(pause_select[i]);
        DeleteGraph(PlayerImage[i]);
    }
    // �����E�����E���������̉摜�̍폜
    for (int i = 0; i < 3; i++) {
        DeleteGraph(WinLoseImage[i]);
    }

    DeleteGraph(Pause_Continue);
    DeleteGraph(Pause_Select);
    DeleteSoundMem(PutSE);      // �΂�u��������SE�̍폜
    DeleteSoundMem(BGM);        // BGM�̍폜
    DeleteSoundMem(PauseClickSE);
    DeleteSoundMem(PauseSelectSE);
}
// ------------------------------------------------


// ---------------�X�V---------------------------
void Othello_Board::Othello_Board_Update() {
    GetMousePoint(&Mouse_X, &Mouse_Y);  // �}�E�X�J�[�\���̈ʒu���擾

    Square_X = (Mouse_X - BoardShift_X) / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE + BoardShift_X �Ŋ������l����
    Square_Y = (Mouse_Y - BoardShift_Y) / MAP_SIZE;      // �}�E�X�J�[�\���̈ʒu�� MAP_SIZE + BoardShift_X �Ŋ������l����


    /* �v���C���[��CPU�̑���Ǘ� */
    if (PauseFlg == false) {

        if (EndFlag == false) {   // �Q�[�����I��������ǂ���

            if (PassFlag == false) {    // �p�X�t���O�� false �Ȃ�

                if (RandomFlag == true) {

                    PlaySoundMem(BGM, DX_PLAYTYPE_LOOP, false);

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
                                Board[Square_X][Square_Y] == 8) {   // ���΂��u����ꏊ�ɃJ�[�\���������Ă�����
                                DrawFlag = true;
                                if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
                                    DrawFlag = false;
                                    Board[Square_X][Square_Y] = 1;      // ���΂�u��
                                    PutPlace_X = Square_X;
                                    PutPlace_Y = Square_Y;
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
                                CPUWhite(Board, ScoreBoard);    // ��ԂЂ�����Ԃ���ꏊ�ɒu��
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
                                CPUBlack(Board, ScoreBoard);    // ��ԂЂ�����Ԃ���ꏊ�ɒu��
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
                                Board[Square_X][Square_Y] == 8) {   // ���΂��u����ꏊ�ɃJ�[�\���������Ă�����
                                DrawFlag = true;
                                if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { // ���N���b�N������
                                    DrawFlag = false;
                                    Board[Square_X][Square_Y] = 2;      // ���΂�u��
                                    PutPlace_X = Square_X;
                                    PutPlace_Y = Square_Y;
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


    /* �|�[�Y�{�^�������������̏����ƁA�|�[�Y��ʂ́u�Â���v�Ɓu�Z���N�g�ɖ߂�v�̏��� */
    nowKey = key->GetKeyState(REQUEST_MOUSE_LEFT); //���݂̃}�E�X���{�^���̓��͏�Ԃ̎�
    if (PauseFlg == false) {        // �|�[�Y�{�^���������Ă��Ȃ�������
        if (10 <= Mouse_X && Mouse_X <= 170 && 5 <= Mouse_Y && Mouse_Y <= 75) {     // �|�[�Y�{�^���͈̔͂���������
            if (OldKey != KEY_FREE && nowKey == KEY_PULL) {
                if (EndFlag == false) {
                    StopSoundMem(BGM);
                    PlaySoundMem(PauseClickSE, DX_PLAYTYPE_BACK, true);
                    PauseFlg = true;
                }
            }
        }
    }
    else if (PauseFlg == true) {   // �|�[�Y�{�^����������Ă�����
        // �u�Â���v�{�^�����A�|�[�Y�{�^���������ƃQ�[�����ĊJ����
        if ((450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) ||
            (10 <= Mouse_X && Mouse_X <= 170 && 5 <= Mouse_Y && Mouse_Y <= 75)) {
            if (!SEFlag[0]) {
                PlaySoundMem(PauseSelectSE, DX_PLAYTYPE_BACK);
                SEFlag[0] = true;
            }
            if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
                PauseFlg = false;       // �|�[�Y��ʂ����
                PlaySoundMem(PauseClickSE, DX_PLAYTYPE_BACK, true);
            }
        }
        else {
            SEFlag[0] = false;
        }

        // �u�Z���N�g�ɖ߂�v�������ƁA�Z���N�g��ʂɖ߂�
        if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590){
            if (!SEFlag[1]) {
                PlaySoundMem(PauseSelectSE, DX_PLAYTYPE_BACK);
                SEFlag[1] = true;
            }
            if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
                StopSoundMem(BGM);      // BGM���~�߂�
                PlaySoundMem(PauseClickSE, DX_PLAYTYPE_BACK, true);
                Parent->SetNext(new Scene_Select());    // �Z���N�g�V�[���Ɉړ�
            }
        }
        else {
            SEFlag[1] = false;
        }
        OldKey = nowKey; //�O�ɓ��͂��Ă����L�[�������͂��Ă����L�[�ɏ㏑������
    }

    // ���U���g��ʂ̕\��
    if (EndFlag == true) {
        // �u�Â���v�{�^�����A�|�[�Y�{�^���������ƃQ�[�����ĊJ����
        if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
            if (!SEFlag[2]) {
                PlaySoundMem(PauseSelectSE, DX_PLAYTYPE_BACK);
                SEFlag[2] = true;
            }

            //if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
                PlaySoundMem(PauseClickSE, DX_PLAYTYPE_NORMAL);
                Othello_Board_Finalize();
                Othello_Board_Initialize(Parent);
            }
        }
        else {
            SEFlag[2] = false;
        }
        // �u�Z���N�g�ɖ߂�v�������ƁA�Z���N�g��ʂɖ߂�
        if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
            if (!SEFlag[3]) {
                PlaySoundMem(PauseSelectSE, DX_PLAYTYPE_BACK);
                SEFlag[3] = true;
            }

            // if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  //�O�̓��͂ō��L�[��b���Ă��Ȃ��āA���}�E�X�̍��L�[�𗣂�����
            if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) {
                PlaySoundMem(PauseClickSE, DX_PLAYTYPE_BACK, true);
                StopSoundMem(BGM);                      // BGM���~�߂�
                Parent->SetNext(new Scene_Select());    // �Z���N�g�V�[���Ɉړ�
            }
        }
        else {
            SEFlag[3] = false;
        }
        OldKey = nowKey; //�O�ɓ��͂��Ă����L�[�������͂��Ă����L�[�ɏ㏑������
    }
}
// -----------------------------------------------


// ------------------�`��-----------------------------------------------
void Othello_Board::Othello_Board_Draw() {
    // ���E���𕪂���₷�����邽�߂̏���
    if (RandomFlag == false) {
        switch (Player) {
        case 0:
            // �v���C���[����
            DrawRotaGraph(640, 360, 1.0, 0.0, SenteGote, TRUE);     // �w�i�̕`��
            // "���Ȃ�"�̕����̃T�C�Y���k���E�g����J��Ԃ�
            if (SizeFlag == false) {
                if (SizeCount <= 1.0f) {
                    SizeCount += 0.01f;
                }
                else {
                    SizeFlag = true;
                }
            }
            else {
                if (SizeCount >= 0.5f) {
                    SizeCount -= 0.01f;
                }
                else {
                    SizeFlag = false;
                }
            }
            DrawRotaGraph(1050, 150, SizeCount, 0.0, PlayerImage[0], TRUE); // �v���C���[
            DrawRotaGraph(1050, 570, 1.0, 0.0, PlayerImage[1], TRUE);       // CPU
            if (TimeCount++ >= 180) {
                TimeCount = 0;
                RandomFlag = true;
            }
            break;

        case 1:
            // �v���C���[����
            //DrawBox(0, 0, 1280, 720, BlackCr, true);
            DrawRotaGraph(640, 360, 1.0, 0.0, SenteGote, TRUE);
            // "���Ȃ�"�̕����̃T�C�Y���k���E�g����J��Ԃ�
            if (SizeFlag == false) {
                if (SizeCount <= 1.0f) {
                    SizeCount += 0.01f;
                }
                else {
                    SizeFlag = true;
                }
            }
            else {
                if (SizeCount >= 0.5f) {
                    SizeCount -= 0.01f;
                }
                else {
                    SizeFlag = false;
                }
            }
            DrawRotaGraph(1050, 150, 1.0, 0.0, PlayerImage[1], TRUE);       // CPU
            DrawRotaGraph(1050, 570, SizeCount, 0.0, PlayerImage[0], TRUE); // �v���C���[
            if (TimeCount++ >= 180) {
                TimeCount = 0;
                RandomFlag = true;
            }
            break;
        }
    }
    else {
        // �w�i����F�ɐ��߂�
        DrawBox(0, 0, 1280, 720, Cr, TRUE);

        // �{�[�h�̌������F�ň͂�
        DrawBox(60 + BoardShift_X, 60 + BoardShift_Y,
            (MAP_SIZE * 9) + BoardShift_X + 6, (MAP_SIZE * 9) + BoardShift_Y + 6, BlackCr, TRUE);

        Print_OthelloBoard(Board);      // �I�Z���{�[�h�̕`��

        switch (Player) {
        case 0:
            DrawRotaGraph(800, 184, 0.35, 0, Black, TRUE);
            DrawRotaGraph(800, 304, 0.35, 0, White, TRUE);

            DrawFormatString(800 + MAP_SIZE / 2, 167, BlackCr, "��:%d �� ���Ȃ�", BlackNum);      // ���΂̌��݂̐���\��
            DrawFormatString(800 + MAP_SIZE / 2, 287, BlackCr, "��:%d �� C P U", WhiteNum);      // ���΂̌��݂̐���\��

            break;
        case 1:
            DrawRotaGraph(800, 184, 0.35, 0, Black, TRUE);
            DrawRotaGraph(800, 304, 0.35, 0, White, TRUE);

            DrawFormatString(800 + MAP_SIZE / 2, 167, BlackCr, "��:%d �� C P U", BlackNum);      // ���΂̌��݂̐���\��
            DrawFormatString(800 + MAP_SIZE / 2, 287, BlackCr, "��:%d �� ���Ȃ�", WhiteNum);      // ���΂̌��݂̐���\��

            break;
        }

    
    // ----- �Q�[���̏I�������𖞂������� -----
    if (EndFlag == true) {

        if (WhiteNum < BlackNum) {  // ���΂̐��̕�������������A���̏���
            switch (Player) {
            case 0: // �v���C���[�����ō��̕�������������
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[0], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d �� ���Ȃ�", BlackNum);      // ���΂̌��݂̐���\��
                DrawFormatString(660, 445, BlackCr, "%d", WhiteNum);                // ���΂̌��݂̐���\��

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;

            case 1: // �v���C���[�����ō��̕�������������
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[1], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d", BlackNum);                // ���΂̌��݂̐���\��
                DrawFormatString(660, 445, BlackCr, "%d �� ���Ȃ�", WhiteNum);      // ���΂̌��݂̐���\��

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;
            }
        }
        else if (BlackNum < WhiteNum) { // ���΂̐��̕�������������A���̏���
            switch (Player) {
            case 0: // �v���C���[�����Ŕ��̕�������������
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[1], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d �� ���Ȃ�", BlackNum);      // ���΂̌��݂̐���\��
                DrawFormatString(660, 445, BlackCr, "%d", WhiteNum);                // ���΂̌��݂̐���\��

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;

            case 1: // �v���C���[�����Ŕ��̕�������������
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[0], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d", BlackNum);                // ���΂̌��݂̐���\��
                DrawFormatString(660, 445, BlackCr, "%d �� ���Ȃ�", WhiteNum);      // ���΂̌��݂̐���\��

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;
            }
        }
        else {  // ���������Ȃ�
            switch (Player) {
            case 0: // �v���C���[����
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[2], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d �� ���Ȃ�", BlackNum);      // ���΂̌��݂̐���\��
                DrawFormatString(660, 445, BlackCr, "%d", WhiteNum);                // ���΂̌��݂̐���\��

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;

            case 1: // �v���C���[����
                DrawRotaGraph(650, 380, 1, 0, ResultImage, TRUE);
                DrawRotaGraph(650, 220, 1.2, 0, WinLoseImage[2], TRUE);
                DrawRotaGraph(600, 350, 0.5, 0, Black, TRUE);
                DrawRotaGraph(600, 450, 0.5, 0, White, TRUE);
                DrawFormatString(660, 340, BlackCr, "%d", BlackNum);                 // ���΂̌��݂̐���\��
                DrawFormatString(660, 445, BlackCr, "%d �� ���Ȃ�", WhiteNum);      // ���΂̌��݂̐���\��

                if (350 <= Mouse_X && Mouse_X <= 550 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(450, 530, 0.4, 0, pause_continue[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(450, 530, 0.5, 0, pause_continue[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(450, 530, 0.5, 0, pause_continue[0], TRUE);
                }
                if (750 <= Mouse_X && Mouse_X <= 950 && 500 <= Mouse_Y && Mouse_Y <= 560) {
                    if (nowKey == KEY_HOLD) {
                        DrawRotaGraph(850, 530, 0.4, 0, pause_select[1], TRUE);
                    }
                    else {
                        DrawRotaGraph(850, 530, 0.5, 0, pause_select[1], TRUE);
                    }
                }
                else {
                    DrawRotaGraph(850, 530, 0.5, 0, pause_select[0], TRUE);
                }

                break;
            }
        }
    }
    // ----- �Q�[���̍Œ��Ȃ� -----
    else {
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
            // 1�b�o������
            if (TimeCount++ >= 60)
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

        // ----- �u�����ꏊ�������\���̐���`�� -----
        DrawLine((PutPlace_X * MAP_SIZE - 10) + (MAP_SIZE / 2) + BoardShift_X, PutPlace_Y * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_Y,
            (PutPlace_X * MAP_SIZE + 10) + (MAP_SIZE / 2) + BoardShift_X, PutPlace_Y * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_Y, RedCr, 3);

        DrawLine(PutPlace_X * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_X, (PutPlace_Y * MAP_SIZE - 10) + (MAP_SIZE / 2) + BoardShift_Y,
            PutPlace_X * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_X, (PutPlace_Y * MAP_SIZE + 10) + (MAP_SIZE / 2) + BoardShift_Y, RedCr, 3);
        // ------------------------------------------


        // ----- �|�[�Y��ʂ�\�� -------------------------------------------------------
        if (PauseFlg == true) {
            DrawRotaGraph(650, 380, 1.15, 0, Pause_Back, TRUE);
            if (450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) {
                if (nowKey == KEY_HOLD) {
                    DrawRotaGraph(650, 380, 0.9, 0, pause_continue[1], TRUE);
                }
                else {
                    DrawRotaGraph(650, 380, 1.0, 0, pause_continue[1], TRUE);
                }
            }
            else {
                DrawRotaGraph(650, 380, 1.0, 0, pause_continue[0], TRUE);
            }
            if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
                if (nowKey == KEY_HOLD) {
                    DrawRotaGraph(650, 530, 0.9, 0, pause_select[1], TRUE);
                }
                else {
                    DrawRotaGraph(650, 530, 1.0, 0, pause_select[1], TRUE);
                }
            }
            else {
                DrawRotaGraph(650, 530, 1.0, 0, pause_select[0], TRUE);
            }
        }
    }
    DrawRotaGraph(90, 40, 0.9, 0, Pause_Button, TRUE);      // �|�[�Y�{�^���̕\��
    // ------------------------------------------------------------------------
    }
    DrawFormatString(900, 600, WhiteCr, "%d", RandomNum);
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
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  2,  1,  0,  0,  0, -1},
     {-1,  0, 0,   0,  1,  2,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1,  0, 0,   0,  0,  0,  0,  0,  0, -1},
     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    };
    memcpy(board, InitBoard, sizeof(InitBoard));
}


/*
* �{�[�h��1�}�X���ɕ]���l������
* ����: ScoreBoard ������
* �߂�l�F�Ȃ�
*/
void Othello_Board::BoardScore(int scoreboard[PB][PB]) {
    static int boardScore[PB][PB] =
    {
     {-99, -1, -1, -1, -1, -1, -1, -1, -1, -1},
     {-1, 50,-10, 10, -2, -2, 10,-10, 50, -1},
     {-1,-10,-20, -2, -5, -5, -2,-20,-10, -1},
     {-1, 10, -2,  5, -2, 11,  5, -1, 10, -1},
     {-1, -2, -5, -2,  0,  0, -2, -5, -2, -1},
     {-1, -2, -5, -2,  0,  0, -2, -5, -2, -1},
     {-1, 10, -2,  5, -2, -2,  5, -1, 10, -1},
     {-1,-10,-20, -2, -5, -5, -2,-20,-10, -1},
     {-1, 50,-10, 10, -2, -2, 10,-10, 50, -1},
     {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    };
    memcpy(scoreboard, boardScore, sizeof(boardScore));
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

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "0");
            }

            /* ���΂��u����Ă��� */
            if (board[i][j] == 1) {

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);

                // ���΂�u��
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_X, 
                    j * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_Y, 27, BlackCr, TRUE);
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "1");

            }

            /* ���΂��u����Ă��� */
            if (board[i][j] == 2) {

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);

                // ���΂�u��
                DrawCircle(i * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_X, 
                    j * MAP_SIZE + (MAP_SIZE / 2) + BoardShift_Y, 27, WhiteCr, TRUE);
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "2");

            }

            /* ���΂��u����ꏊ */
            if (board[i][j] == 3) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE + BoardShift_X, j * MAP_SIZE + BoardShift_Y,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "3");

            }

            /* ���΂��u����ꏊ */
            if (board[i][j] == 4) {
                // �{�[�h�̃}�X�ڂ����₷�����邽�߂ɍ��F�ň͂�
                DrawBox(i * MAP_SIZE + BoardShift_X, j * MAP_SIZE + BoardShift_Y,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y, BlackCr, TRUE);

                // �{�[�h�̃}�X�̐ݒ�
                DrawBox((i * MAP_SIZE) + BoardShift_X + 1, (j * MAP_SIZE) + BoardShift_Y + 1,
                    (i * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (j * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, GreenCr, TRUE);

                CursorOn_OthelloBoard();    // �}�E�X�J�[�\���̈ʒu���{�[�h�̃}�X�ڂ̏�ɗ����}�X��Ԃ��\������
                //DrawFormatString(i * MAP_SIZE + BoardShift_X + 5, j * MAP_SIZE + BoardShift_X + 5, GetColor(255, 0, 0), "4");

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
        DrawBox((Square_X * MAP_SIZE) + BoardShift_X + 1, (Square_Y * MAP_SIZE) + BoardShift_Y + 1,
            (Square_X * MAP_SIZE) + MAP_SIZE + BoardShift_X - 1, (Square_Y * MAP_SIZE) + MAP_SIZE + BoardShift_Y - 1, RedCr, TRUE);
    }
}


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

    return 0;
}


/*
* CPU�����΂�u�����ʒu����A����ŕς����锒�΂�T���č��΂ɕς���
* �����F�Ȃ�
* �߂�l�F�Ђ�����Ԃ���ꏊ���Ȃ������� retun 0 ��Ԃ�
*/
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


/*
* CPU�����΂�u�����ʒu����A����ŕς����鍕�΂�T���Ĕ��΂ɕς���
* �����F�Ȃ�
* �߂�l�F�Ђ�����Ԃ���ꏊ���Ȃ������� retun 0 ��Ԃ�
*/
int Othello_Board::WhitePutCPU(int d, int e) {
    CPUPutOnCheck(Board, 1, 0, d, e, 1, 2);
    CPUPutOnCheck(Board, -1, 0, d, e, 1, 2);
    CPUPutOnCheck(Board, 0, 1, d, e, 1, 2);
    CPUPutOnCheck(Board, 0, -1, d, e, 1, 2);
    CPUPutOnCheck(Board, 1, 1, d, e, 1, 2);
    CPUPutOnCheck(Board, -1, 1, d, e, 1, 2);
    CPUPutOnCheck(Board, 1, -1, d, e, 1, 2);
    CPUPutOnCheck(Board, -1, -1, d, e, 1, 2);

    return 0;
}


/*
* ���΂�u�����ʒu����A���E�㉺�΂߂ɂЂ�����Ԃ���΂��Ȃ������ׂ�
* �����F�Ȃ�
* �߂�l�F�Ђ�����Ԃ���ꏊ���Ȃ������� retun 0 ��Ԃ�
*/
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

/*
* ���΂�u�����ʒu����A���E�㉺�΂߂ɂЂ�����Ԃ���΂��Ȃ������ׂ�
* �����F�Ȃ�
* �߂�l�F�Ђ�����Ԃ���ꏊ���Ȃ������� retun 0 ��Ԃ�
*/
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


/*
* �w�肵�������ɑ΂��āA�Ђ�����Ԃ���΂�����Ή��Ђ�����Ԃ��邩���ׂ�
* ���� : board[PB][PB], p, q, d, e, enemy, player
* �߂�l�F i - 1 �łЂ�����Ԃ��鐔�̒l��Ԃ�
*/
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


/*
* ���΂��u����ꏊ��T���A�u����ꏊ���������番����₷������
* �����Fboard[PB][PB]
* �߂�l�F�Ђ�����Ԃ���ꏊ����������A return 1 ��Ԃ�
*/
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

                    // �u����ꏊ�𕪂���₷�����邽�߂Ɉ͂�
                    DrawGraph(i * MAP_SIZE + BoardShift_X, j * MAP_SIZE + BoardShift_Y, PutCheckImage, true);

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


/*
* ���΂��u����ꏊ��T���A�u����ꏊ���������番����₷������
* �����Fboard[PB][PB]
* �߂�l�F�Ђ�����Ԃ���ꏊ����������A return 1 ��Ԃ�
*/
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
                    DrawGraph(i * MAP_SIZE + BoardShift_X, j * MAP_SIZE + BoardShift_Y, PutCheckImage, true);

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


/*
* ���΂Ɣ��΂̐��𒲂ׂ�
* �����Fboard[PB][PB]
* �߂�l�F�Ȃ�
*/
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


/*
* �Q�[���̏I�������𖞂�������
* �����Fboard[PB][PB]
* �߂�l�F�Q�[���̏I�������𖞂������� return 1 ��Ԃ�
*/
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


/*
* �u����ꏊ�𒲂ׂāA��ԕ]���l�������}�X�ɔ��΂�u��CPU�̏���
* �����Fboard[PB][PB], scoreboard[PB][PB]
* �߂�l�F���ׂĈȏ�Ȃ��ʂ����� return 1 ��Ԃ�
*/
int Othello_Board::CPUWhite(int board[PB][PB], int scoreboard[PB][PB]) {
    Board_X = 0;
    Board_Y = 0;
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            //// ��ԑ������鏊�ɒu������
            //if (board[i][j] == 4) {
            //    if (ReturnNumMax < WhitePutCheck(i, j)) {
            //        ReturnNumMax = WhitePutCheck(i, j);
            //        Board_X = i;
            //        Board_Y = j;
            //    }

            // scoreboard[][]�ɍŏ��l�����āA�����ׂ�������
            if (board[i][j] == 4) {
                if (scoreboard[Board_X][Board_Y] < scoreboard[i][j]) {
                    Board_X = i;
                    Board_Y = j;
                }
            }
        }
    }
    board[Board_X][Board_Y] = 2;
    WhitePutCPU(Board_X, Board_Y);
    PutPlace_X = Board_X;
    PutPlace_Y = Board_Y;
    Board_X = 0;
    Board_Y = 0;
    ReturnNumMax = 0;
    return 1;
}


/*
* �u����ꏊ�𒲂ׂāA��ԕ]���l�������}�X�ɍ��΂�u��CPU�̏���
* �����Fboard[PB][PB], scoreboard[PB][PB]
* �߂�l�F���ׂĈȏ�Ȃ��ʂ����� return 1 ��Ԃ�
*/
int Othello_Board::CPUBlack(int board[PB][PB], int scoreboard[PB][PB]) {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            if (board[i][j] == 3) {

                // ��ԑ�������ꏊ�ɒu������
                //if (ReturnNumMax < BlackPutCheck(i, j)) {
                //    ReturnNumMax = BlackPutCheck(i, j);
                //    Board_X = i;
                //    Board_Y = j;
                //}

                // scoreboard[][]�ɍŏ��l�����āA�����ׂ�������
                if (board[i][j] == 3) {
                    if (scoreboard[Board_X][Board_Y] < scoreboard[i][j]) {
                        Board_X = i;
                        Board_Y = j;
                    }
                }
            }
        }
    }
    board[Board_X][Board_Y] = 1;
    BlackPutCPU(Board_X, Board_Y);
    PutPlace_X = Board_X;
    PutPlace_Y = Board_Y;
    Board_X = 0;
    Board_Y = 0;
    ReturnNumMax = 0;
    return 1;
}



/*
* �Q�[���̍ŏ��Ƀ����_���ɒl������āA���E�������߂�
* �����F�Ȃ�
* �߂�l�F�Ȃ�
*/
void Othello_Board::RandomOrder() {

    RandomNum = rand();


    // 50�ȏ�ō��F���v���C���[�A����ȊO�͔��F���v���C���[
    if (RandomNum % 2 == 0) {
        Player = 0;
    }
    else {
        Player = 1;
    }
}
