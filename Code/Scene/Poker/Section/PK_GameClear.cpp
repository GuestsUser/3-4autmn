#include <DxLib.h>
#include "PK_GameClear.h"

#include "Scene.h"
#include "Poker.h"
#include "ConstVal.h"

#include "PK_SectionLibrary.h"
#include "PokerFontData.h"

#include "Button.h"
#include "Cmp_3DSoundListener.h"
#include "Cmp_Button_ClickCheck.h"
#include "Cmp_ButtonOverlapGroup.h"
#include "Cmp_Sound.h"

Poker::GameClear::GameClear(Poker& set) :parent(&set), count(0), clickStartTime(60), blink(30), nextButton(WINDOW_X / 2, WINDOW_Y / 2, WINDOW_X / 2, WINDOW_Y / 2, false) {
	titlePos.SetXYZ(513, 189, 0); //�Q�[���N���A�ł��鎖���������b�Z�[�W�̈ʒu�ݒ�
	explainPos.SetXYZ(472, 312, 0); //�{�^�������z�u�ʒu

	nextButton.EditClick()->SetCmp(new Cmp_Button_ClickCheck()); //�N���b�N�`�F�b�N�p�R���|�[�l���g�ǉ�
	parent->pauseButon->EditAlways()->EditCmp<Cmp_ButtonOverlapGroup>()->EditGroup()->push_back(&nextButton); //�|�[�Y�{�^���ɏd�Ȃ��Ă��鎟�V�[���ڍs�{�^�����d�Ȃ薳�����R���|�[�l���g�֊i�[����

	sound = new Cmp_Sound(LoadSoundMem("Resource/se/Poker_SE/gameClear.wav"), -1, -1, true, Cmp_3DSoundListener::EditTransform());
}

void Poker::GameClear::Update() {
	nextButton.Update(); //�{�^��Update���s
	if (count == 0) { sound->Play(); } //���߂Ẵ^�C�~���O�Ȃ�T�E���h��炷
	if (count == clickStartTime) { nextButton.SetRunClickMonitor(true); } //�J�n�^�C�~���O�ɂȂ�����N���b�N���m�J�n

	if (nextButton.GetRunUpdateClick()) { parent->SetNextSection(Poker::Section::newgamereset); } //�N���b�N���ꂽ�ꍇ�Q�[���̊��S���Z�b�g�V�[���ֈڍs
	++count;
}

void Poker::GameClear::Draw() {
	DrawStringToHandle(titlePos.GetX(), titlePos.GetY(), "�Q�[���N���A!!", *PokerFontData::GetColor(PokerFontData::color::normal), *PokerFontData::GetHandle(PokerFontData::type::normal));
	if (count >= clickStartTime && ((count - clickStartTime) / blink) % 2 == 0) { DrawStringToHandle(explainPos.GetX(), explainPos.GetY(), "��ʂ��N���b�N�ŐV�����n�߂�", *PokerFontData::GetColor(PokerFontData::color::edgeColor), *PokerFontData::GetHandle(PokerFontData::type::edge), *PokerFontData::GetColor(PokerFontData::color::edgeNormal)); }
}

void Poker::GameClear::Reset() {
	nextButton.EditClick()->SetRunUpdate(false); //�N���b�N��Ԃ�߂�
	nextButton.EditClick()->SetRunDraw(false); //�O�̈�Draw���߂�
	nextButton.SetRunClickMonitor(false); //�N���b�N���m�̖�����
	count = 0; //�J�E���g���Z�b�g
}