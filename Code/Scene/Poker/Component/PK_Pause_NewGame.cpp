#include "Poker.h"
#include "Cmp_PK_Pause.h"
#include "PK_Pause_NewGame.h"

#include "Button.h"

void Cmp_PK_Pause::NewGame::Update() {
	if (count > runTime) { //�{�^����������Ă���w�莞�Ԃ��o�߂�����
		parent->poker->SetNextSection(Poker::Section::newgamereset); //Poker�̎��s�Z�N�V���������Z�b�g�V�[���ɕύX
		parent->CloseOrder(); //�|�[�Y��ʂ��I������w��
	}
	++count;
}