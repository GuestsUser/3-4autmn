#include "DxLib.h"

#include "Btn.h"
#include "Poker.h"
#include "../Code/Component/Component.h"
#include "../Code/Component/Cmp_Transform.h"
#include "../Code/Component/Cmp_Image.h"

#include <deque>

Btn::Btn() :posList(std::deque<Cmp_Transform>((int)Poker::Character::length)) {
	img = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_dealer.png")), 1); //ゲージ画像の作成

	posList[(int)Poker::Character::leftCom].EditPos().SetXYZ(87, 511, 0); //各キャラがボタンポジションになった際、ボタンを配置する座標を設定
	posList[(int)Poker::Character::topCom].EditPos().SetXYZ(754, 146, 0);
	posList[(int)Poker::Character::rightCom].EditPos().SetXYZ(1015, 491, 0);
	posList[(int)Poker::Character::player].EditPos().SetXYZ(677, 699, 0);

	FullReset(); //初期ボタンポジションをランダム決定
}

Btn::~Btn() { delete img; } //新しく生産していた画像は終わりと共に削除する

void Btn::Reset() {
	usePos = (usePos + 1) % (int)Poker::Character::length; //使用ポジションの更新
	img->EditTranform()->EditPos() = posList[usePos].ReadPos(); //新しいポジションに合わせてボタンの位置も更新する
}

void Btn::FullReset() {
	usePos = GetRand((int)Poker::Character::length - 1); //ポジションをランダム決定、GetRandは括弧内の数値も含むランダムなので-1する
	Reset(); //ボタン位置設定の為の呼び出し
}

void Btn::Draw() {
	img->Draw(); //ボタンの描写
}