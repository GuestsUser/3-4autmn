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

Cmp_ThinkingImage::Cmp_ThinkingImage(Chara& setParent, std::deque<Chara*>& setChara, PK_Dealer& setDealer, const Vector3& place) : parent(&setParent), chara(&setChara), dealer(&setDealer) {
	int space = 118; //place�ɂ��̐��l������x�����炵���ʒu�ɔz�u����

	image = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_cpu_thinking.png")), 1); //�摜�쐬
	image->EditTranform()->EditPos().SetXYZ(place.GetX() + space, place.GetY(), place.GetZ()); //x��space�����炵���ʒu�ɔz�u����

	isPlayer = typeid(*parent) == typeid(PK_Player);
}


void Cmp_ThinkingImage::Update() {
	if (!GetRunUpdate()) { return; } //�֎~�߂��o�Ă�ꍇ���s���Ȃ�
	image->Update();
}
void Cmp_ThinkingImage::Draw() {
	if (!GetRunDraw()) { return; } //�֎~�߂��o�Ă�ꍇ���s���Ȃ�
	if (isPlayer) { return; } //�v���C���[�̏ꍇ�\�����Ȃ�
	if ((*chara)[dealer->GetActionCharaSub()] != parent) { return; } //���݃A�N�V�������s���L�������e�ł͂Ȃ��ꍇ���s���Ȃ�

	image->Draw(); //�`��
}