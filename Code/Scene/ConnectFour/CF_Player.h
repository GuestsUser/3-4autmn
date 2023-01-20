#pragma once
#define Board_Xsize 7 //�p�l���̉��̃}�X�̐�
#define Board_Ysize 7 //�p�l���̏c�̃}�X�̐�
#define Coin_Space 0 //�R�C���������Ă��Ȃ��ꏊ
#define Coin_Player 1 //�v���C���[�̃R�C��������ꏊ
#define Coin_CPU 2 //CPU�̃R�C��������ꏊ

#include "./../Scene.h"


class CF_Player{
private:
	Scene* parent;
	int CF_Back; //�w�i
	int CF_Panel; //�p�l��
	int CF_Board[Board_Xsize][Board_Ysize]; //�p�l���̏��̓񎟌��z��
	int CF_CircleBoard[Board_Xsize][Board_Ysize]; //�N���A���ɕ\������~�̓񎟌��z��
	int CF_PCoin; //�v���C���[�̃R�C��
	int pcoin[2];
	int ccoin[2];
	int CF_CCoin; //CPU�̃R�C��
	int CF_Yajirusi; //���
	int CF_GameBGM; //�Q�[������BGM
	int CF_StartSE; //��U��U��\�����鎞��SE
	int CF_ClickSE;
	int CF_CoinFallSE;
	int Pause_Cursol;
	int Pause_Click;
	int Pause_Button;
	int Pause_Back;
	int Pause_Continue;
	int pause_continue[2];
	int Pause_Select;
	int pause_select[2];
	int i,j,k; //for���̕ϐ�
	int Yajirusi_Col[7]; //���̐F
	int Mouse_X; //�}�E�X��X���W
	int Mouse_Y; //�}�E�X��Y���W
	int OldKey; 
	int nowKey;
	int Player_X; //�v���C���[��X���W
	int CPU_X;
	int CPU_j;
	int CPU_Position;
	int PlayUser; //���v���C���Ă���R�C���̏�����
	int DlayCount; //�R�C���������Ă���v���C���[�ɕς��܂ł̃f�B���C����
	int CPU_Start; //CPU��1�ԍŏ��ɒu���R�C��
	 
	float yadd; //�d�͉����x
	float Yajirusi_Move; //���̃A�j���[�V�����̒l
	float Yajirusi_Y; //����Y���W
	float FallCount;
	float Player_Y; //�v���C���[��Y���W
	float Coin_Exp[Board_Xsize][Board_Ysize]; //�R�C���̊g�嗦
	float Coin_Switch; //�N���A���̃R�C���̓_�ł̐؂�ւ�

	bool Mouse_Push; //�}�E�X�̍��N���b�N�����ꂽ���̃t���O
	bool CF_Clear; //�R�l�N�g�t�H�[���N���A�������̃t���O
	bool CF_Draw; //�R�l�N�g�t�H�[�ň����������������̃t���O
	bool CF_Start; //�Q�[�����X�^�[�g�������ǂ����̃t���O
	bool FallSEflg; //CoinFallSE�����Ă��邩�ǂ����̃t���O
	bool CF_ClearText; //�����҂��o���e�L�X�g���o���t���O
	bool PauseFlg;

	bool Pause_OneClick;
	bool Pause_OneCursol;

public:
	void CF_Player_Initialize(Scene* scene);
	void CF_Player_Finalize();
	void CF_Player_Update();
	void CF_Player_Draw();

	void Coin_Fall();
	void Board_Init();
	void ChangeTurn(int *PlayUser);
	void SpaceDoubleCheck(int board[Board_Xsize][Board_Ysize], int x, int y);
	void SpaceCheck(int board[Board_Xsize][Board_Ysize], int x, int y);
	void CPU_CoinCheck(int board[Board_Xsize][Board_Ysize], int x, int y);
	void CPU_RandomFall();

	int ClearCheck(int board[Board_Xsize][Board_Ysize], int x, int y);
	int DrawCheck(int board[Board_Xsize][Board_Ysize]);

};
//
//extern CF_Player cf_player;