#include "DxLib.h"
#include "Gage.h"

#include "Component.h"
#include "Cmp_Gage_MouseControl.h"
#include "Cmp_Transform.h"
#include "Cmp_Image.h"

#include "../Code/GetKey.h"
#include "../Code/OriginMath.h"

#include <deque>
#include <math.h>

Cmp_Gage_MouseControl::Cmp_Gage_MouseControl(Gage& setParent, const Vector3& setArea, float setStep, int setKey) :parent(&setParent), area(setArea), step(setStep), monitorKey(setKey), control(false) {}


void Cmp_Gage_MouseControl::Update() {
	if (!GetRunUpdate()) { return; }

	int mouseX = -1; //マウスx
	int mouseY = -1; //マウスy
	GetMousePoint(&mouseX, &mouseY); //マウス位置取得



	if (control) { //ゲージ操作処理
		Vector3 imagePos[] = { Vector3(), Vector3() ,Vector3() ,Vector3() }; //実体画像の変形頂点、左上、右上、右下、左下の格納順
		Cmp_Transform iniScale = Cmp_Transform(*parent->ReadBaseGage()->ReadTranform()); //弄ってない状態の実体拡大率を復元する
		iniScale.EditScale().SetX(parent->GetIniSize()); //初期拡x拡大率を格納

		int sizeX = -1; //画像サイズ格納用
		int sizeY = -1;
		GetGraphSize(*parent->ReadFullGage()->ReadImage(), &sizeX, &sizeY); //サイズ取得
		OriginMath::VertexModification(imagePos, Vector3(sizeX, sizeY), iniScale, parent->ReadFullGage()->GetDrawHorizonPivot(), OriginMath::VerticalPivot::center); //実体画像を変形

		for (int i = 1; i < 4; ++i) { imagePos[i] -= imagePos[0]; } //imagePos[0]を基準に変更する
		mouseX -= imagePos[0].GetX(); //マウスも同じ変更を適用
		mouseY -= imagePos[0].GetY();

		float imageRotate = parent->ReadFullGage()->ReadTranform()->ReadRotate().GetZ(); //画像の回転を取得

		float mouseLine = sqrt(pow(mouseX * cos(imageRotate), 2) + pow(mouseY * sin(imageRotate), 2)); //画像回転に応じてマウスから原点までのラインから取得する数値に制限を掛ける
		float fullLine = sqrt(pow(imagePos[1].GetX(), 2) + pow(imagePos[1].GetY(), 2)); //ゲージの最大値長さ

		float gage = mouseLine / fullLine; //今回のゲージ量、ステップ操作前
		parent->SetVol((float)(1 / step) * (int)(gage / (1 / step))); //stepの倍数以下のゲージ量は切り捨てられるようにゲージへセット

		if (key->GetKeyState(monitorKey) == KEY_PULL) { control = false; } //監視キーが離されたらゲージ操作を一時終了
		return; //終わり
	}



	Vector3 pos[] = { Vector3(), Vector3() ,Vector3() ,Vector3() }; //判定領域の変形頂点、左上、右上、右下、左下の格納順
	OriginMath::VertexModification(pos, area, *parent->ReadBaseGage()->ReadTranform(), parent->ReadFullGage()->GetDrawHorizonPivot(), parent->ReadFullGage()->GetDrawVerticalPivot()); //マウス判定をゲージ画像に合わせて変形

	if (fmod(parent->ReadBaseGage()->ReadTranform()->ReadRotate().GetZ(), OriginMath::MPI / 2) == 0) { //ゲージに回転がかかってなかった場合
		control = mouseX > pos[0].GetX() && mouseX < pos[1].GetX() && mouseY > pos[0].GetY() && mouseY < pos[2].GetY() && key->GetKeyState(monitorKey) == KEY_PUSH; //普通に範囲チェックする
		return; //おわり
	}

	LinerFunction line[] = { LinerFunction(pos[0],pos[1]),LinerFunction(pos[1],pos[2]),LinerFunction(pos[2],pos[3]),LinerFunction(pos[3],pos[0]) }; //判定領域の境界を一次関数で保持

	bool plus = false; //マウス位置からx軸へ平行に線を伸ばした際、lineに接触したx位置がマウスxより大きかった場合これをtrueとする
	bool minus = false; //xより小さいならこっちをtrueにする
	
	for (int i = 0; i < 4; ++i) { //回転に応じた範囲チェック
		int next = (i + 1) % 4; //lineは0→1のように要素の小さい方から1つ大きい方へ引かれていったのでlineの2点を、iを始点、nextを終点として使える

		int x = line[i].GetX(mouseY); //マウスyと今回のラインが接触したx地点

		int min = pos[i].GetX(); //回転によりpos配列の座標が大きい要素が変わる事があるのでmin、bigに入れるという形で対応する
		int big = pos[next].GetX();
		if (pos[i].GetX() > pos[next].GetX()) { min = pos[next].GetX(); big = pos[i].GetX(); } //要素の大小が違った場合入れ直し
		if (x >= min && x <= big) { //xがlineの2点の間にあった場合true
			if (x > mouseX) { plus = true; } //xがマウスより大きい場合plusをtrue
			else { minus = true; } //そうでないならminusをtrue
		}
		if (plus && minus) { break; } //マウス位置からx軸へ平行に伸ばした線をlineに接触して止めた際、+方向と-方向に延びていた場合範囲内にマウスが存在するのでもう判定は不要
	}

	if (plus && minus && key->GetKeyState(monitorKey) == KEY_PUSH) { control = true; } //判定範囲内にある且つ監視キーを押したなら次からゲージ操作を開始する
}