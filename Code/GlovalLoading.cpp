#include "GlovalLoading.h"
#include "ConstVal.h"
#include "Worldval.h"

void GlovalLoading() { //�F�X�ȑS�̌����ϐ��̏���
	WorldVal::Set("score", new int(0)); //WorldVal����e�X�g�p���l
	WorldVal::Set("highScore", new int(0)); //��L���l�̃e�X�g�p���l
}