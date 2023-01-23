#include "SR_Map.h"
#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"

extern int Player1sum;
extern int Player2sum;
extern int Player3sum;
extern int Player4sum;

SR_Map::SR_Map() {
	/*-------------------------------Player1�p���W----------------------------------------*/
	/*�X�^�[�g*/
	MassX[0] = 20; MassY[0] = 600;		
	/*�P�`�P�R�@��ԉ��̒i*/
	MassX[1] = 20; MassY[1] = 470;
	MassX[2] = 115; MassY[2] = 470;		MassX[3] = 210; MassY[3] = 470;
	MassX[4] = 305; MassY[4] = 470;		MassX[5] = 400; MassY[5] = 470;
	MassX[6] = 495; MassY[6] = 470;		MassX[7] = 590; MassY[7] = 470;
	MassX[8] = 685; MassY[8] = 470;		MassX[9] = 780; MassY[9] = 470;
	MassX[10] = 875; MassY[10] = 470;	MassX[11] = 970; MassY[11] = 470;
	MassX[12] = 1065; MassY[12] = 470;	
	/*�P�R�`�P�V�@�E�[�̒i*/
	MassX[13] = 1160; MassY[13] = 470;
	MassX[14] = 1160; MassY[14] = 350;	MassX[15] = 1160; MassY[15] = 230;
	MassX[16] = 1160; MassY[16] = 110;	MassX[17] = 1160; MassY[17] = -5;	/*�E��*/
	/*�P�V�`�Q�X�@��ԏ�̒i*/
	MassX[18] = 1065; MassY[18] = -5;	MassX[19] = 970; MassY[19] = -5;
	MassX[20] = 875; MassY[20] = -5;	MassX[21] = 780; MassY[21] = -5;
	MassX[22] = 685; MassY[22] = -5;	MassX[23] = 590; MassY[23] = -5;
	MassX[24] = 495; MassY[24] = -5;	MassX[25] = 400; MassY[25] = -5;
	MassX[26] = 305; MassY[26] = -5;	MassX[27] = 210; MassY[27] = -5;
	/*MassX[28] = 115; MassY[28] = -5;	MassX[29] = 20; MassY[29] = -5;*/
	/*�R�O�`�R�Q�@���[*/
	MassX[28] = 20; MassY[28] = 110;	MassX[29] = 20; MassY[29] = 230;
	MassX[30] = 20; MassY[30] = 350;	
	/*�R�R���S�R�@�������Ԗڂ̒i*/
	MassX[31] = 115; MassY[31] = 350;
	MassX[32] = 210; MassY[32] = 350;	MassX[33] = 305; MassY[33] = 350;
	MassX[34] = 400; MassY[34] = 350;	MassX[35] = 495; MassY[35] = 350;
	MassX[36] = 590; MassY[36] = 350;	MassX[37] = 685; MassY[37] = 350;
	MassX[38] = 780; MassY[38] = 350;	MassX[39] = 875; MassY[39] = 350;
	MassX[40] = 970; MassY[40] = 350;	MassX[41] = 1065; MassY[41] = 350;
	/*�S�S�`�S�T�@�E�����i�ڂ̒i*/
	MassX[42] = 1065; MassY[42] = 230;	MassX[43] = 1065; MassY[43] = 110;
	/*�S�U�`�T�T�@�ォ���i�ڂ̒i*/
	MassX[44] = 970; MassY[44] = 110;	MassX[45] = 875; MassY[45] = 110;
	MassX[46] = 780; MassY[46] = 110;	MassX[47] = 685; MassY[47] = 110;
	MassX[48] = 590; MassY[48] = 110;	MassX[49] = 497; MassY[49] = 110;
	MassX[50] = 400; MassY[50] = 110;	MassX[51] = 305; MassY[51] = 110;
	MassX[52] = 210; MassY[52] = 110;	MassX[53] = 115; MassY[53] = 110;
	/*56*/
	MassX[54] = 115; MassY[54] = 230;	
	/*�T�V�`�U�R�@�^�񒆂̒i*/
	MassX[55] = 210; MassY[55] = 230;
	MassX[56] = 305; MassY[56] = 230;	MassX[57] = 400; MassY[57] = 230;
	MassX[58] = 497; MassY[58] = 230;	MassX[59] = 590; MassY[59] = 230;
	MassX[60] = 685; MassY[60] = 230;	MassX[61] = 780; MassY[61] = 230;

	MassX[62] = 900; MassY[62] = 230;	
	/*-------------------------------Player2�p���W----------------------------------------*/
	/*�X�^�[�g X ���W��95���ς��*/
	MassX2[0] = 40; MassY2[0] = 600;
	/*�P�`�P�R�@��ԉ��̒i*/
	MassX2[1] = 40; MassY2[1] = 470;
	MassX2[2] = 135; MassY2[2] = 470;		MassX2[3] = 230; MassY2[3] = 470;
	MassX2[4] = 325; MassY2[4] = 470;		MassX2[5] = 420; MassY2[5] = 470;
	MassX2[6] = 515; MassY2[6] = 470;		MassX2[7] = 610; MassY2[7] = 470;
	MassX2[8] = 705; MassY2[8] = 470;		MassX2[9] = 800; MassY2[9] = 470;
	MassX2[10] = 895; MassY2[10] = 470;		MassX2[11] = 990; MassY2[11] = 470;
	MassX2[12] = 1085; MassY2[12] = 470;
	/*�P�R�`�P�V�@�E�[�̒i*/
	MassX2[13] = 1180; MassY2[13] = 470;
	MassX2[14] = 1180; MassY2[14] = 350;	MassX2[15] = 1180; MassY2[15] = 230;
	MassX2[16] = 1180; MassY2[16] = 110;	MassX2[17] = 1180; MassY2[17] = -5;	/*�E��*/
	/*�P�V�`�Q�X�@��ԏ�̒i*/
	MassX2[18] = 1085; MassY2[18] = -5;	MassX2[19] = 990; MassY2[19] = -5;
	MassX2[20] = 895; MassY2[20] = -5;	MassX2[21] = 800; MassY2[21] = -5;
	MassX2[22] = 705; MassY2[22] = -5;	MassX2[23] = 610; MassY2[23] = -5;
	MassX2[24] = 515; MassY2[24] = -5;	MassX2[25] = 420; MassY2[25] = -5;
	MassX2[26] = 325; MassY2[26] = -5;	MassX2[27] = 230; MassY2[27] = -5;
	/*MassX2[28] = 135; MassY2[28] = -5;	MassX2[29] = 40; MassY2[29] = -5;*/
	/*�R�O�`�R�Q�@���[*/
	MassX2[28] = 40; MassY2[28] = 110;	MassX2[29] = 40; MassY2[29] = 230;
	MassX2[30] = 40; MassY2[30] = 350;
	/*�R�R���S�R�@�������Ԗڂ̒i*/
	MassX2[31] = 135; MassY2[31] = 350;
	MassX2[32] = 230; MassY2[32] = 350;	MassX2[33] = 325; MassY2[33] = 350;
	MassX2[34] = 420; MassY2[34] = 350;	MassX2[35] = 515; MassY2[35] = 350;
	MassX2[36] = 610; MassY2[36] = 350;	MassX2[37] = 705; MassY2[37] = 350;
	MassX2[38] = 800; MassY2[38] = 350;	MassX2[39] = 895; MassY2[39] = 350;
	MassX2[40] = 990; MassY2[40] = 350;	MassX2[41] = 1085; MassY2[41] = 350;
	/*�S�S�`�S�T�@�E�����i�ڂ̒i*/
	MassX2[42] = 1085; MassY2[42] = 230;	MassX2[43] = 1085; MassY2[43] = 110;
	/*�S�U�`�T�T�@�ォ���i�ڂ̒i*/
	MassX2[44] = 990; MassY2[44] = 110;	MassX2[45] = 895; MassY2[45] = 110;
	MassX2[46] = 800; MassY2[46] = 110;	MassX2[47] = 705; MassY2[47] = 110;
	MassX2[48] = 610; MassY2[48] = 110;	MassX2[49] = 517; MassY2[49] = 110;
	MassX2[50] = 420; MassY2[50] = 110;	MassX2[51] = 325; MassY2[51] = 110;
	MassX2[52] = 230; MassY2[52] = 110;	MassX2[53] = 135; MassY2[53] = 110;
	/*56*/
	MassX2[54] = 135; MassY2[54] = 230;
	/*�T�V�`�U�R�@�^�񒆂̒i*/
	MassX2[55] = 230; MassY2[55] = 230;
	MassX2[56] = 325; MassY2[56] = 230;	MassX2[57] = 420; MassY2[57] = 230;
	MassX2[58] = 517; MassY2[58] = 230;	MassX2[59] = 610; MassY2[59] = 230;
	MassX2[60] = 705; MassY2[60] = 230;	MassX2[61] = 800; MassY2[61] = 230;

	MassX2[62] = 920; MassY2[62] = 230;

	/*-------------------------------Player3�p���W----------------------------------------*/
	/*�X�^�[�g*/
	MassX3[0] = 60; MassY3[0] = 600;
	/*�P�`�P�R�@��ԉ��̒i*/
	MassX3[1] = 60; MassY3[1] = 470;
	MassX3[2] = 155; MassY3[2] = 470;		MassX3[3] = 250; MassY3[3] = 470;
	MassX3[4] = 345; MassY3[4] = 470;		MassX3[5] = 440; MassY3[5] = 470;
	MassX3[6] = 535; MassY3[6] = 470;		MassX3[7] = 630; MassY3[7] = 470;
	MassX3[8] = 725; MassY3[8] = 470;		MassX3[9] = 820; MassY3[9] = 470;
	MassX3[10] = 915; MassY3[10] = 470;		MassX3[11] = 1010; MassY3[11] = 470;
	MassX3[12] = 1105; MassY3[12] = 470;
	/*�P�R�`�P�V�@�E�[�̒i*/
	MassX3[13] = 1200; MassY3[13] = 470;
	MassX3[14] = 1200; MassY3[14] = 350;	MassX3[15] = 1200; MassY3[15] = 230;
	MassX3[16] = 1200; MassY3[16] = 110;	MassX3[17] = 1200; MassY3[17] = -5;	/*�E��*/
	/*�P�V�`�Q�X�@��ԏ�̒i*/
	MassX3[18] = 1105; MassY3[18] = -5;		MassX3[19] = 1010; MassY3[19] = -5;
	MassX3[20] = 915; MassY3[20] = -5;		MassX3[21] = 820; MassY3[21] = -5;
	MassX3[22] = 725; MassY3[22] = -5;		MassX3[23] = 630; MassY3[23] = -5;
	MassX3[24] = 535; MassY3[24] = -5;		MassX3[25] = 440; MassY3[25] = -5;
	MassX3[26] = 345; MassY3[26] = -5;		MassX3[27] = 250; MassY3[27] = -5;
	/*MassX3[28] = 155; MassY3[28] = -5;		MassX3[29] = 60; MassY3[29] = -5;*/
	/*�R�O�`�R�Q�@���[*/
	MassX3[28] = 60; MassY3[28] = 110;		MassX3[29] = 60; MassY3[29] = 230;
	MassX3[30] = 60; MassY3[30] = 350;
	/*�R�R���S�R�@�������Ԗڂ̒i*/
	MassX3[31] = 155; MassY3[31] = 350;
	MassX3[32] = 250; MassY3[32] = 350;		MassX3[33] = 345; MassY3[33] = 350;
	MassX3[34] = 440; MassY3[34] = 350;		MassX3[35] = 535; MassY3[35] = 350;
	MassX3[36] = 630; MassY3[36] = 350;		MassX3[37] = 725; MassY3[37] = 350;
	MassX3[38] = 820; MassY3[38] = 350;		MassX3[39] = 915; MassY3[39] = 350;
	MassX3[40] = 1010; MassY3[40] = 350;	MassX3[41] = 1105; MassY3[41] = 350;
	/*�S�S�`�S�T�@�E�����i�ڂ̒i*/
	MassX3[42] = 1105; MassY3[42] = 230;	MassX3[43] = 1105; MassY3[43] = 110;
	/*�S�U�`�T�T�@�ォ���i�ڂ̒i*/
	MassX3[44] = 1010; MassY3[44] = 110;	MassX3[45] = 915; MassY3[45] = 110;
	MassX3[46] = 820; MassY3[46] = 110;		MassX3[47] = 725; MassY3[47] = 110;
	MassX3[48] = 630; MassY3[48] = 110;		MassX3[49] = 537; MassY3[49] = 110;
	MassX3[50] = 440; MassY3[50] = 110;		MassX3[51] = 345; MassY3[51] = 110;
	MassX3[52] = 250; MassY3[52] = 110;		MassX3[53] = 155; MassY3[53] = 110;
	/*56*/
	MassX3[54] = 155; MassY3[54] = 230;
	/*�T�V�`�U�R�@�^�񒆂̒i*/
	MassX3[55] = 250; MassY3[55] = 230;
	MassX3[56] = 345; MassY3[56] = 230;		MassX3[57] = 440; MassY3[57] = 230;
	MassX3[58] = 537; MassY3[58] = 230;		MassX3[59] = 630; MassY3[59] = 230;
	MassX3[60] = 725; MassY3[60] = 230;		MassX3[61] = 820; MassY3[61] = 230;

	MassX3[62] = 940; MassY3[62] = 230;
	/*-------------------------------Player4�p���W----------------------------------------*/
	/*�X�^�[�g*/
	MassX4[0] = 80; MassY4[0] = 600;
	/*�P�`�P�R�@��ԉ��̒i*/
	MassX4[1] = 80; MassY4[1] = 470;
	MassX4[2] = 175; MassY4[2] = 470;		MassX4[3] = 270; MassY4[3] = 470;
	MassX4[4] = 365; MassY4[4] = 470;		MassX4[5] = 460; MassY4[5] = 470;
	MassX4[6] = 555; MassY4[6] = 470;		MassX4[7] = 650; MassY4[7] = 470;
	MassX4[8] = 745; MassY4[8] = 470;		MassX4[9] = 840; MassY4[9] = 470;
	MassX4[10] = 935; MassY4[10] = 470;		MassX4[11] = 1030; MassY4[11] = 470;
	MassX4[12] = 1125; MassY4[12] = 470;
	/*�P�R�`�P�V�@�E�[�̒i*/
	MassX4[13] = 1220; MassY4[13] = 470;
	MassX4[14] = 1220; MassY4[14] = 350;	MassX4[15] = 1220; MassY4[15] = 230;
	MassX4[16] = 1220; MassY4[16] = 110;	MassX4[17] = 1220; MassY4[17] = -5;	/*�E��*/
	/*�P�V�`�Q�X�@��ԏ�̒i*/
	MassX4[18] = 1125; MassY4[18] = -5;		MassX4[19] = 1030; MassY4[19] = -5;
	MassX4[20] = 935; MassY4[20] = -5;		MassX4[21] = 840; MassY4[21] = -5;
	MassX4[22] = 745; MassY4[22] = -5;		MassX4[23] = 650; MassY4[23] = -5;
	MassX4[24] = 555; MassY4[24] = -5;		MassX4[25] = 460; MassY4[25] = -5;
	MassX4[26] = 365; MassY4[26] = -5;		MassX4[27] = 270; MassY4[27] = -5;
	/*MassX4[28] = 175; MassY4[28] = -5;		MassX4[29] = 80; MassY4[29] = -5;*/
	/*�R�O�`�R�Q�@���[*/
	MassX4[28] = 80; MassY4[28] = 110;		MassX4[29] = 80; MassY4[29] = 230;
	MassX4[30] = 80; MassY4[30] = 350;
	/*�R�R���S�R�@�������Ԗڂ̒i*/
	MassX4[31] = 175; MassY4[31] = 350;
	MassX4[32] = 270; MassY4[32] = 350;		MassX4[33] = 365; MassY4[33] = 350;
	MassX4[34] = 460; MassY4[34] = 350;		MassX4[35] = 555; MassY4[35] = 350;
	MassX4[36] = 650; MassY4[36] = 350;		MassX4[37] = 745; MassY4[37] = 350;
	MassX4[38] = 840; MassY4[38] = 350;		MassX4[39] = 935; MassY4[39] = 350;
	MassX4[40] = 1030; MassY4[40] = 350;	MassX4[41] = 1125; MassY4[41] = 350;
	/*�S�S�`�S�T�@�E�����i�ڂ̒i*/
	MassX4[42] = 1125; MassY4[42] = 230;	MassX4[43] = 1125; MassY4[43] = 110;
	/*�S�U�`�T�T�@�ォ���i�ڂ̒i*/
	MassX4[44] = 1030; MassY4[44] = 110;	MassX4[45] = 935; MassY4[45] = 110;
	MassX4[46] = 840; MassY4[46] = 110;		MassX4[47] = 685; MassY4[47] = 110;
	MassX4[48] = 650; MassY4[48] = 110;		MassX4[49] = 557; MassY4[49] = 110;
	MassX4[50] = 460; MassY4[50] = 110;		MassX4[51] = 365; MassY4[51] = 110;
	MassX4[52] = 270; MassY4[52] = 110;		MassX4[53] = 175; MassY4[53] = 110;
	/*56*/
	MassX4[54] = 175; MassY4[54] = 230;
	/*�T�V�`�U�R�@�^�񒆂̒i*/
	MassX4[55] = 270; MassY4[55] = 230;
	MassX4[56] = 365; MassY4[56] = 230;		MassX4[57] = 460; MassY4[57] = 230;
	MassX4[58] = 557; MassY4[58] = 230;		MassX4[59] = 650; MassY4[59] = 230;
	MassX4[60] = 745; MassY4[60] = 230;		MassX4[61] = 840; MassY4[61] = 230;

	MassX4[62] = 960; MassY4[62] = 230;

	game = true;
	/*---------------------------------�摜�p------------------------------------------*/
	Player1 = LoadGraph("Resource/image/SR_Player1.png");
	Player2 = LoadGraph("Resource/image/SR_Player2.png");
	Player3 = LoadGraph("Resource/image/SR_Player3.png");
	Player4 = LoadGraph("Resource/image/SR_Player4.png");

}
void SR_Map::Update() {
	if (Player1sum >= 62|| Player2sum >= 62 || Player3sum >= 62 || Player4sum >= 62) {
		game = false;
	}
}


void SR_Map::Draw() {	
	if (game == true) {
		DrawGraph(MassX[Player1sum], MassY[Player1sum], Player1, true);
		DrawGraph(MassX2[Player2sum], MassY2[Player2sum], Player2, true);
		DrawGraph(MassX3[Player3sum], MassY3[Player3sum], Player3, true);
		DrawGraph(MassX4[Player4sum], MassY4[Player4sum], Player4, true);
	}
}
