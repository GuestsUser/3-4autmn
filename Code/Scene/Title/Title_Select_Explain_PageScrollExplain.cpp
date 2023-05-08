#include "DxLib.h"
#include "Title_Select_Explain_PageScrollExplain.h"

#include <cmath>


Title_Select_Explain_PageScrollExplain::Title_Select_Explain_PageScrollExplain() :str("�X�N���[���Ńy�[�W�߂���!"), limit(180), pos(120, 670), iniColor(Vector3(255, 25, 65)), finalColor(Vector3(75, 55, 255)) {
	Reset(); //�J�ncount�̃����_����
}

void Title_Select_Explain_PageScrollExplain::Update() {
	if (!GetRunUpdate()) { return; } //���s�֎~��ԂȂ�I���
	++count; //���Ԍo��
}

void Title_Select_Explain_PageScrollExplain::Draw() {
	if (!GetRunDraw()) { return; } //���s�֎~��ԂȂ�I���
	Vector3 color = iniColor + (finalColor - iniColor) * (std::cos(360.0 / limit * (count % limit) * OriginMath::Deg2Rad) + 1) * 0.5; //count���獡��̃J���[�����肷��
	DrawString(pos.GetX(), pos.GetY(), str.c_str(), GetColor(color.GetX(), color.GetY(), color.GetZ())); //�y�[�W�������������ꍇ�y�[�W�߂���\�ł��鎖��\������
}

void Title_Select_Explain_PageScrollExplain::Reset() { count = GetRand(limit); }