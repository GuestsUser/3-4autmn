#pragma once
#define Board_Xsize 7 //�p�l���̉��̃}�X�̐�
#define Board_Ysize 6 //�p�l���̏c�̃}�X�̐�
#define Coin_Space 0 //�R�C���������Ă��Ȃ��ꏊ
#define Coin_Player 1 //�v���C���[�̃R�C��������ꏊ
#define Coin_CPU 2 //CPU�̃R�C��������ꏊ

class CF_Player {
private:
	int CF_Back; //�w�i
	int CF_Panel; //�p�l��
	int CF_Board[Board_Xsize][Board_Ysize]; //�p�l���̏��̓񎟌��z��
	int CF_PCoin; //�v���C���[�̃R�C��
	int CF_CCoin; //CPU�̃R�C��
	int CF_Yajirusi; //���
	int i,j,k; //for���̕ϐ�
	int Yajirusi_Col[7]; //���̐F
	int Mouse_X; //�}�E�X��X���W
	int Mouse_Y; //�}�E�X��Y���W
	int Player_X; //�v���C���[��X���W
	int Player_Y; //�v���C���[��Y���W
	int PlayUser; //���v���C���Ă���R�C���̏�����
	
	float yadd; //�d�͉����x
	float Yajirusi_Move; //���̃A�j���[�V�����̒l
	float Yajirusi_Y; //����Y���W
	float FallCount;

	bool Mouse_Push; //�}�E�X�̍��N���b�N�����ꂽ���̃t���O
	bool CF_Clear; //�R�l�N�g�t�H�[���N���A�������̃t���O
	bool CF_Draw; //�R�l�N�g�t�H�[�ň����������������̃t���O
	
public:
	void CF_Player_Initialize();
	void CF_Player_Finalize();
	void CF_Player_Update();
	void CF_Player_Draw();

	void Coin_Fall();
	void Board_Init();
	void ChangeTurn(int *PlayUser);

	int ClearCheck(int board[Board_Xsize][Board_Ysize], int x, int y);
	int DrawCheck(int board[Board_Xsize][Board_Ysize]);

};
//
//extern CF_Player cf_player;