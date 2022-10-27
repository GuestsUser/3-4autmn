#include "DxLib.h"
#include "Title.h"
#include "./../../SceneManager.h"
#include "./../../GetKey.h"
#include "./../../Worldval.h"
#include "./../../Scene/Sugoroku/SR_Title.h"

Title::Title() :posX(0), posY(720), scrollSpeed(8), state(State::Moving) {
	titleImage = LoadGraph("Resource/image/Title.png");
	score = WorldVal::Get<int>("score"); //WorldVal取得テスト、アドレスで受け取るので一度取得したら他の場所で値の操作があっても変更がこちらにも適用される
	hiscore = WorldVal::Get<int>("highScore");
}

Title::~Title() { DeleteGraph(titleImage); } //独自に読み込みやインスタンス作成を行った場合削除

void Title::Update() {
	switch (state) {

	case Title::State::Moving: //タイトル画面が上から出てくる処理
		Move();
		break;

	case Title::State::Stop:
		if (key->GetKeyState(REQUEST_MOUSE_LEFT) == KEY_PUSH) { //Aボタン(緑ボタン)が押された瞬間
			SetNext(new SR_Title()); //ゲームシーンへ遷移
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
	posY -= scrollSpeed; //スクロール速に合わせて座標を動かす
	if (posY <= 0) { //座標が目標に到達したら
		posY = 0; //目標を超過していてもいいように目標に合わせる
		state = State::Stop; //次以降実行する処理をStopの物に切り替える
	}
}
