#include "DxLib.h"

#include "GlovalLoading.h"
#include "ConstVal.h"
#include "Worldval.h"

void GlovalLoading() { //�F�X�ȑS�̌����ϐ��̏���
	WorldVal::Set("pokerNormalFont", new int(CreateFontToHandle(nullptr, -1, -1, DX_FONTTYPE_NORMAL))); //�|�[�J�[�Ŏg�p����ʏ�t�H���쐬
	WorldVal::Set("pokerNormalFontColor", new unsigned int(GetColor(0, 0, 0))); //�|�[�J�[�Ŏg�p����ʏ�t�H���̐F

	WorldVal::Set("pokerEdgeFont", new int(CreateFontToHandle(nullptr, -1, -1, DX_FONTTYPE_EDGE))); //�|�[�J�[�Ŏg�p����t�H���A���t��
	WorldVal::Set("pokerEdgeFontColor", new unsigned int(GetColor(255, 255, 255))); //�|�[�J�[�Ŏg�p����G�b�W�t���t�H���̐F
	WorldVal::Set("pokerEdgeFontEdgeColor", new unsigned int(GetColor(0, 0, 0))); //�|�[�J�[�Ŏg�p����G�b�W�t���t�H���̃G�b�W�J���[


	WorldVal::Set("score", new int(0)); //WorldVal����e�X�g�p���l
	WorldVal::Set("highScore", new int(0)); //��L���l�̃e�X�g�p���l
}