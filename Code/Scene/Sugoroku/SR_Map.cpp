#include "SR_Map.h"
#include "./../../GlovalLoading.h"	
#include "./../../GetKey.h"
#include "./../../SceneManager.h"
#include "SR_Saikoro.h"
#include "SR_Game.h"
extern int Player1sum;
SR_Map::SR_Map() {
	/*ƒXƒ^[ƒg*/
	MassX[0] = 20; MassY[0] = 600;		
	/*‚P`‚P‚R@ˆê”Ô‰º‚Ì’i*/
	MassX[1] = 20; MassY[1] = 470;
	MassX[2] = 115; MassY[2] = 470;		MassX[3] = 210; MassY[3] = 470;
	MassX[4] = 305; MassY[4] = 470;		MassX[5] = 400; MassY[5] = 470;
	MassX[6] = 495; MassY[6] = 470;		MassX[7] = 590; MassY[7] = 470;
	MassX[8] = 685; MassY[8] = 470;		MassX[9] = 780; MassY[9] = 470;
	MassX[10] = 875; MassY[10] = 470;	MassX[11] = 970; MassY[11] = 470;
	MassX[12] = 1065; MassY[12] = 470;	
	/*‚P‚R`‚P‚V@‰E’[‚Ì’i*/
	MassX[13] = 1160; MassY[13] = 470;
	MassX[14] = 1160; MassY[14] = 350;	MassX[15] = 1160; MassY[15] = 230;
	MassX[16] = 1160; MassY[16] = 110;	MassX[17] = 1160; MassY[17] = -5;	/*‰Eã*/
	/*‚P‚V`‚Q‚X@ˆê”Ôã‚Ì’i*/
	MassX[18] = 1065; MassY[18] = -5;	MassX[19] = 970; MassY[19] = -5;
	MassX[20] = 875; MassY[20] = -5;	MassX[21] = 780; MassY[21] = -5;
	MassX[22] = 685; MassY[22] = -5;	MassX[23] = 590; MassY[23] = -5;
	MassX[24] = 495; MassY[24] = -5;	MassX[25] = 400; MassY[25] = -5;
	MassX[26] = 305; MassY[26] = -5;	MassX[27] = 210; MassY[27] = -5;
	MassX[28] = 115; MassY[28] = -5;	MassX[29] = 20; MassY[29] = -5;
	/*‚R‚O`‚R‚Q@¶’[*/
	MassX[30] = 20; MassY[30] = 110;	MassX[31] = 20; MassY[31] = 230;
	MassX[32] = 20; MassY[32] = 350;	
	/*‚R‚R‚S‚R@‰º‚©‚ç“ñ”Ô–Ú‚Ì’i*/
	MassX[33] = 115; MassY[33] = 350;
	MassX[34] = 210; MassY[34] = 350;	MassX[35] = 305; MassY[35] = 350;
	MassX[36] = 400; MassY[36] = 350;	MassX[37] = 495; MassY[37] = 350;
	MassX[38] = 590; MassY[38] = 350;	MassX[39] = 685; MassY[39] = 350;
	MassX[40] = 780; MassY[40] = 350;	MassX[41] = 875; MassY[41] = 350;
	MassX[42] = 970; MassY[42] = 350;	MassX[43] = 1065; MassY[43] = 350;
	/*‚S‚S`‚S‚T@‰E‚©‚ç“ñ’i–Ú‚Ì’i*/
	MassX[44] = 1065; MassY[44] = 230;	MassX[45] = 1065; MassY[45] = 110;
	/*‚S‚U`‚T‚T@ã‚©‚ç“ñ’i–Ú‚Ì’i*/
	MassX[46] = 970; MassY[46] = 110;	MassX[47] = 875; MassY[47] = 110;
	MassX[48] = 780; MassY[48] = 110;	MassX[49] = 685; MassY[49] = 110;
	MassX[50] = 590; MassY[50] = 110;	MassX[51] = 497; MassY[51] = 110;
	MassX[52] = 400; MassY[52] = 110;	MassX[53] = 305; MassY[53] = 110;
	MassX[54] = 210; MassY[54] = 110;	MassX[55] = 115; MassY[55] = 110;
	/*56*/
	MassX[56] = 115; MassY[56] = 230;	
	/*‚T‚V`‚U‚R@^‚ñ’†‚Ì’i*/
	MassX[57] = 210; MassY[57] = 230;
	MassX[58] = 305; MassY[58] = 230;	MassX[59] = 400; MassY[59] = 230;
	MassX[60] = 497; MassY[60] = 230;	MassX[61] = 590; MassY[61] = 230;
	MassX[62] = 685; MassY[62] = 230;	MassX[63] = 780; MassY[63] = 230;

	MassX[64] = 900; MassY[64] = 230;	
	Player1 = LoadGraph("Resource/image/SR_Player1.png");
}
void SR_Map::Update() {
}


void SR_Map::Draw() {	
	DrawGraph(MassX[Player1sum], MassY[Player1sum], Player1, true);
	DrawFormatString(300, 600, GetColor(255, 255, 255), "i = %d", Player1sum);
}
