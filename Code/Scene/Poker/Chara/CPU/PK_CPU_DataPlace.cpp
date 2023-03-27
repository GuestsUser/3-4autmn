#include "Poker.h"

#include "PK_CPU.h"
#include "PK_CPU_DataPlace.h"

#include "Cmp_ThinkingImage.h"
#include "Cmp_Transform.h"

#include "OriginMath.h"

void GetFirstCardPos(int sub, Vector3& edit) { //editに入れたVector3へ添え字に応じたカード先頭座標を返す
	switch ((Poker::Character)sub) {
	case Poker::Character::leftCom: edit = Vector3(91, 301, 0); return; //leftCpuの一番最初に配置するカード位置
	case Poker::Character::topLeftCom: edit = Vector3(199, 91, 0); return; //topLeftCpuの一番最初に配置するカード位置
	case Poker::Character::topRightCom: edit = Vector3(756, 91, 0); return; //topRightCpuの一番最初に配置するカード位置
	case Poker::Character::rightCom: edit = Vector3(1024, 296, 0); return; //rightCpuの一番最初に配置するカード位置
	}
}

void GetCoinBackPos(int sub, Vector3& edit) { //editへ入れたVector3へ添え字に応じたコイン表示背景位置を返す
	switch ((Poker::Character)sub) {
	case Poker::Character::leftCom: edit = Vector3(151, 434, 0); return; //leftCpu位置
	case Poker::Character::topLeftCom: edit = Vector3(502, 78, 0); return; //topLeftCpu位置
	case Poker::Character::topRightCom: edit = Vector3(1059, 78, 0); return; //topRightCpu位置
	case Poker::Character::rightCom: edit = Vector3(1082, 428, 0); return; //rightCpu位置
	}
}

void GetThinkingPos(int sub, Vector3& edit) { //editへ入れたVector3へ添え字に応じたコイン表示背景位置を返す
	switch ((Poker::Character)sub) {
	case Poker::Character::leftCom: edit = Vector3(269, 434, 0); return; //leftCpu位置
	case Poker::Character::topLeftCom: edit = Vector3(620, 78, 0); return; //topLeftCpu位置
	case Poker::Character::topRightCom: edit = Vector3(1177, 78, 0); return; //topRightCpu位置
	case Poker::Character::rightCom: edit = Vector3(1200, 428, 0); return; //rightCpu位置
	}
}

void PK_CPU::DataPlace::Run(PK_CPU& parent, int sub) {
	int cardPlaceSpace = 33; //カード配置間隔
	Vector3 firstCardPos; //カードの先頭位置
	GetFirstCardPos(sub, firstCardPos); //先頭位置の取得

	std::deque<Cmp_Transform> cardPos = std::deque<Cmp_Transform>(5); //カード配置受け渡し用変数
	Cmp_Transform backPos = Cmp_Transform(); //コイン表示背景配置受け渡し用
	GetCoinBackPos(sub, backPos.EditPos()); //コイン表示背景位置取得

	for (int j = 0; j < cardPos.size(); ++j) { //カード配置
		cardPos[j].EditPos() = firstCardPos; //現在操作対象キャラに合わせて位置の初期設定
		cardPos[j].EditPos().SetX(firstCardPos.GetX() + cardPlaceSpace * j); //配置回数に合わせて位置ずらしを行う
	}
	parent.Place(cardPos, backPos); //カードとコイン表示背景の配置

	Vector3 pos;
	GetThinkingPos(sub, pos);
	parent.EditAppendCmp()->SetCmp(new Cmp_ThinkingImage((Poker::Character)sub, *parent.dealer, pos)); //考え用画像を表示するコンポーネントの導入
}