#include "DxLib.h"

#include "../Code/Component/Component.h"
#include "Chara.h"
#include "PK_Player.h"
#include "CPU.h"

#include "PK_Dealer.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/OriginMath.h"

#include <typeinfo>
#include <deque>

#include "Cmp_ThinkingImage.h"

Cmp_ThinkingImage::Cmp_ThinkingImage(Poker::Character parent, PK_Dealer& setDealer, const Vector3& place) :parent(parent), dealer(&setDealer) {
	image = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_cpu_thinking.png")), 1); //�摜�쐬
	image->EditTranform()->EditPos().SetXYZ(place.GetX(), place.GetY(), place.GetZ()); //x��space�����炵���ʒu�ɔz�u����
}

void Cmp_ThinkingImage::Update() {
	if (!GetRunUpdate()) { return; } //�֎~�߂��o�Ă�ꍇ���s���Ȃ�
	image->Update();
}
void Cmp_ThinkingImage::Draw() {
	if (!GetRunDraw()) { return; } //�֎~�߂��o�Ă�ꍇ���s���Ȃ�
	if (dealer->GetActionCharaSub() != (int)parent) { return; } //���݃A�N�V�������s���L���������g�����I�u�W�F�N�g�ƈႤ�ꍇ���s���Ȃ�

	image->Draw(); //�`��
}