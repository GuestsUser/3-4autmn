#pragma once
//#include "./Othello_Player.h"
#include "DxLib.h"
#include "./../Scene.h"
#define PB 10
#define MAP_SIZE 66

//
class Othello_Board {
private:
	Scene* Parent;

	int PutCheckImage;	// �������̉摜������p�̕ϐ�

	int BGM;		// BGM�p�̕ϐ�
	int PutSE;		// �΂�u���Ƃ���SE�p�̕ϐ�
	int PassSE;		// �p�X���ꂽ�Ƃ���SE�p�̕ϐ�

	int BlackCr;	// ���F���Z�b�g���Ă����p�̕ϐ�
	int WhiteCr;	// ���F���Z�b�g���Ă����p�̕ϐ�
	int GreenCr;	// �ΐF���Z�b�g���Ă����p�̕ϐ�
	int Cr;

	int OrderNum;	// ��Ԃ����߂鐔������ϐ�
	int BlackNum;	// ���΂̐�������ϐ�
	int WhiteNum;	// ���΂̐�������ϐ�
	int TimeCount;	// ���Ԃ𑪂�p�̕ϐ�
	int CheckNum;	// 
	int ReturnNum;
	int ReturnNumMax;
	int Board_X, Board_Y;
	int RandomNum;
	int Player;

	bool DrawFlag;
	bool CheckFlag;
	bool PassFlag;
	bool EndFlag;
	bool RandomFlag;
	bool CornerFlag;

public:
	int Mouse_X;
	int Mouse_Y;
	int Square_X;
	int Square_Y;
	int Board[PB][PB];

	void Othello_Board_Initialize(Scene* scene);
	void Othello_Board_Finalize();
	void Othello_Board_Update();
	void Othello_Board_Draw();

	void Init_OthelloBoard(int board[PB][PB]);
	void Print_OthelloBoard(int board[PB][PB]);

	void CursorOn_OthelloBoard();

	int CursorPutOnCheck(int board[PB][PB], int p, int q, int enemy, int player);
	int CPUPutOnCheck(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);



	int PutSearch(int board[PB][PB], int p, int q, int d, int e, int enemy, int player);

	int BlackPutCheck(int d, int e);
	int BlackPut();
	int BlackPutCPU(int d, int e);
	int BoardSearchBlack(int board[PB][PB]);


	int WhitePutCheck(int d, int e);
	int WhitePut();
	int WhitePutCPU(int d, int e);
	int BoardSearchWhite(int board[PB][PB]);


	void BoardSearchBWNumber(int board[PB][PB]);

	int CPUWhite(int board[PB][PB]);
	int CPUBlack(int board[PB][PB]);
	int EndGame(int board[PB][PB]);

	int RandomOrder();
	/*
	* �v���C���[�����F�i���j�̏ꍇ�A���F���b�o�t�ɂ�����
	* �v���C���[�����F�i���j�̏ꍇ�A���F���b�o�t�ɂ�����
	*/

};

extern Othello_Board* OB;