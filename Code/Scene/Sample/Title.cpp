#include "DxLib.h"
#include "Title.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"
#include "./../../Worldval.h"
#include "./../../Scene/Sugoroku/SR_Title.h"

Title::Title() :posX(0), posY(720), scrollSpeed(8), state(State::Moving) {
	titleImage = LoadGraph("Resource/image/Title.png");
	score = WorldVal::Get<int>("score"); //WorldVal�擾�e�X�g�A�A�h���X�Ŏ󂯎��̂ň�x�擾�����瑼�̏ꏊ�Œl�̑��삪�����Ă��ύX��������ɂ��K�p�����
	hiscore = WorldVal::Get<int>("highScore");
}

Title::~Title() { DeleteGraph(titleImage); } //�Ǝ��ɓǂݍ��݂�C���X�^���X�쐬���s�����ꍇ�폜

void Title::Update() {
	switch (state) {

	case Title::State::Moving: //�^�C�g����ʂ��ォ��o�Ă��鏈��
		Move();
		break;

	case Title::State::Stop:
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //A�{�^��(�΃{�^��)�������ꂽ�u��
			SetNext(new SR_Title()); //�Q�[���V�[���֑J��
		}
		break;
	}
}

void Title::Draw() {
	DrawGraph(posX, posY, titleImage, FALSE);
	SetFontSize(35);
	DrawFormatString(350+posX, 100+posY, GetColor(255, 255, 255), "%7d", *score);
	DrawFormatString(700+posX, 100+posY, GetColor(255, 255, 255), "%7d", *hiscore);
}

void Title::Move() {
	posY -= scrollSpeed; //�X�N���[�����ɍ��킹�č��W�𓮂���
	if (posY <= 0) { //���W���ڕW�ɓ��B������
		posY = 0; //�ڕW�𒴉߂��Ă��Ă������悤�ɖڕW�ɍ��킹��
		state = State::Stop; //���ȍ~���s���鏈����Stop�̕��ɐ؂�ւ���
	}
}
