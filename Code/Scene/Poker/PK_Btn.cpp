#include "DxLib.h"

#include "PK_Btn.h"
#include "Section/Poker.h"

#include "Component.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include <deque>

PK_Btn::PK_Btn() :posList(std::deque<Cmp_Transform>((int)Poker::Character::length)) {
	img = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_dealer.png")), 1); //ゲージ画像の作成

	posList[(int)Poker::Character::leftCom].EditPos().SetXYZ(87, 511, 0); //各キャラがボタンポジションになった際、ボタンを配置する座標を設定
	posList[(int)Poker::Character::topLeftCom].EditPos().SetXYZ(437, 142, 0);
	posList[(int)Poker::Character::topRightCom].EditPos().SetXYZ(994, 142, 0);
	posList[(int)Poker::Character::rightCom].EditPos().SetXYZ(1015, 491, 0);
	posList[(int)Poker::Character::player].EditPos().SetXYZ(674, 671, 0);

	FullReset(); //初期ボタンポジションをランダム決定
}

PK_Btn::~PK_Btn() { delete img; } //新しく生産していた画像は終わりと共に削除する

void PK_Btn::Reset() {
	usePos = (usePos + 1) % (int)Poker::Character::length; //使用ポジションの更新
	img->EditTranform()->EditPos() = posList[usePos].ReadPos(); //新しいポジションに合わせてボタンの位置も更新する
}

void PK_Btn::FullReset() {
	usePos = GetRand((int)Poker::Character::length - 1); //ポジションをランダム決定、GetRandは括弧内の数値も含むランダムなので-1する
	Reset(); //ボタン位置設定の為の呼び出し
}

void PK_Btn::Draw() {
	img->Draw(); //ボタンの描写
}