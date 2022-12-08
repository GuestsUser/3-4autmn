#pragma once
#include "DxLib.h"
#include "./../Scene.h"
#define PB 10			// �{�[�h�̔z��̐�
#define MAP_SIZE 66		// �{�[�h��1�}�X������̑傫��


class Othello_Board {
private:
	Scene* Parent;

	int PutCheckImage;	// �������̉摜������p�̕ϐ�
	int ResultImage;
	int WinLoseImage[3];
	int Black;
	int White;

	int Pause_Button;
	int Pause_Back;
	int Pause_Continue;
	int Pause_Select;

	int pause_continue[2];
	int pause_select[2];

	int BGM;		// BGM�p�̕ϐ�
	int PutSE;		// �΂�u���Ƃ���SE�p�̕ϐ�
	int PassSE;		// �p�X���ꂽ�Ƃ���SE�p�̕ϐ�
	int PauseClickSE;
	int PauseSelectSE;

	int BlackCr;	// ���F���Z�b�g���Ă����p�̕ϐ�
	int WhiteCr;	// ���F���Z�b�g���Ă����p�̕ϐ�
	int GreenCr;	// �ΐF���Z�b�g���Ă����p�̕ϐ�
	int RedCr;
	int Cr;

	int OrderNum;	// ��Ԃ����߂鐔������ϐ�
	int BlackNum;	// ���΂̐�������ϐ�
	int WhiteNum;	// ���΂̐�������ϐ�
	int TimeCount;	// ���Ԃ𑪂�p�̕ϐ�
	int CheckNum;	// 
	int ReturnNum;	// 
	int ReturnNumMax;		// 
	int Board_X, Board_Y;	//�@board[Board_X][Board_Y] �݂����Ȋ����ŁA�{�[�h�̃}�X������ϐ�
	int RandomNum;	// 
	int Player;		// �v���C���[���ǂ����𔻒肷�邽�߂̕ϐ�
	int PutPlace_X, PutPlace_Y;		// �u�����ꏊ��ۑ�����ϐ�
	int BoardShift_X, BoardShift_Y;
	
	int Mouse_X;		// �}�E�X��X���W�̃|�C���^������p�ϐ�
	int Mouse_Y;		// �}�E�X��Y���W�̃|�C���^������p�ϐ�
	int OldKey;
	int nowKey;

	bool DrawFlag;		// �J�[�\�����}�X�̏�ɗ������ɐԂ��`�悵�Ă���������
	bool CheckFlag;		// 
	bool PassFlag;		// �p�X���ꂽ���ǂ����𔻒�
	bool EndFlag;		// �I�������𖞂����Ă��邩�ǂ����𔻒�
	bool RandomFlag;	// �����_���ɒl��U�������ǂ���
	bool CornerFlag;	// �p�����邩�ǂ����𔻒�
	bool PauseFlg;		// �|�[�Y��ʂ��J���Ă��邩�ǂ���

public:
	int Square_X;		// �}�E�X����ǂ݂Ƃ���X���W���AMAP_SIZE�Ŋ������l����ꂽ�ϐ�
	int Square_Y;		// �}�E�X����ǂݎ����Y���W���AMAP_SIZE�Ŋ������l����ꂽ�ϐ�
	int Board[PB][PB];	// �{�[�h�̃}�b�v�`�b�v��������p�ϐ�
	int ScoreBoard[PB][PB];

	void Othello_Board_Initialize(Scene* scene);	// ������
	void Othello_Board_Finalize();					// �I������
	void Othello_Board_Update();					// �X�V
	void Othello_Board_Draw();						// �`��

	void Init_OthelloBoard(int board[PB][PB]);		// �{�[�h��������
	void Print_OthelloBoard(int board[PB][PB]);		// �{�[�h��\��

	void CursorOn_OthelloBoard();		// �u����ꏊ�ɃJ�[�\���������}�X��Ԃ�����

	int CursorPutOnCheck(int board[PB][PB], int p, int q, int enemy, int player);			// �I�������}�X�ɐ΂�u���Đ΂��Ђ�����Ԃ�
	int CPUPutOnCheck(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);	// CPU���I�������}�X�ɐ΂�u���ĂЂ�����Ԃ�

	int PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);	// �u����ꏊ���Ȃ����T��

	int BlackPutCheck(int d, int e);			// ���΂��u����ꏊ�����邩�ǂ������ׂ�
	int BlackPut();								// ���΂�u��
	int BlackPutCPU(int d, int e);				// ���΂�CPU�̏ꍇ�̒u����ꏊ�����邩�ǂ������ׂ�֐�
	int BoardSearchBlack(int board[PB][PB]);	// ���΂�u����悤�ɂ��鏈���̊֐�
	int CPUBlack(int board[PB][PB], int scoreboard[PB][PB]);			// ���΂�CPU�̏ꍇ�̍��΂�u������


	int WhitePutCheck(int d, int e);			// ���΂��u����ꏊ�����邩�ǂ������ׂ�
	int WhitePut();								// ���΂�u��
	int WhitePutCPU(int d, int e);				// ���΂�CPU�̏ꍇ�̒u����ꏊ�����邩�ǂ������ׂ�֐�
	int BoardSearchWhite(int board[PB][PB]);	// ���΂�u����悤�ɂ��鏈���̊֐�	
	int CPUWhite(int board[PB][PB], int scoreboard[PB][PB]);			// ���΂�CPU�̏ꍇ�̒u������

	void BoardSearchBWNumber(int board[PB][PB]);	// ���E���΂��A���݂ǂꂾ�����邩���ׂ�֐�


	int EndGame(int board[PB][PB]);				// �Q�[���̏I�������𖞂�������I������

	void RandomOrder();							// ���E�������߂�֐�

	void BoardScore(int board[PB][PB]);			//�@�ÓI�]�������v����֐�
};

extern Othello_Board* OB;