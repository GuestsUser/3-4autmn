#include "Poker.h"
#include "Cmp_PK_Pause.h"
#include "PK_Pause_GameEnd.h"

#include "Button.h"

void Cmp_PK_Pause::GameEnd::Update() {
	if (count > runTime) { //�{�^����������Ă���w�莞�Ԃ��o�߂�����
		parent->poker->SetNextSection(Poker::Section::titleback); //�����Poker::Update�I������Q�[���Z���N�g�֖߂�悤�w��
		parent->CloseOrder(); //�|�[�Y��ʂ��I������w��
	}
	++count;
}
