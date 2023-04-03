#include "PK_Player.h"
#include "PK_Player_Main.h"
#include "PK_Player_Change.h"

#include "PK_CardDealer.h"
#include "PK_Chara.h"
#include "PK_Pot.h"
#include "PK_Card.h"
#include "PK_Dealer.h"

#include "Cmp_PlayerRaiseDraw.h"
#include "Button.h"
#include "Gage.h"
#include "Cmp_Button_ClickCheck.h"
#include "Cmp_Gage_MouseControl.h"
#include "Cmp_Gage_Border.h"
#include "Cmp_Gage_UpperBorder.h"
#include "Cmp_Hand.h"
#include "Cmp_Image.h"

#include <deque>

PK_Player::PK_Player(PK_Pot& pot, PK_Dealer& dealer, PK_CardDealer& cardDealer) :pot(&pot), dealer(&dealer), cardDealer(&cardDealer), sectionModule(0) {
	int cardPlaceSpace = 134; //カード配置間隔
	Vector3 firstCardPos = Vector3(360, 520, 0); //カードの先頭位置

	Vector3 monitorArea = Vector3(1.2, 2); //ゲージ実体画像サイズに対しこの数値分掛けた値をクリック検知範囲とする
	Vector3 gagePlace = Vector3(442, 633); //ゲージの配置座標
	Vector3 actionPlace = Vector3(573, 663); //Call,Raise等各種アクションボタンの配置座標
	Vector3 actionSize = Vector3(110, 90); //Call,Raise等各種アクションボタンの画像サイズ
	Vector3 foldPlace = Vector3(772, 684); //foldButton配置座標
	Vector3 foldSize = Vector3(90, 45); //foldButton画像サイズ

	std::deque<Cmp_Transform> cardPos = std::deque<Cmp_Transform>(5); //カード配置受け渡し用変数
	Cmp_Transform backPos = Cmp_Transform(); //コイン表示背景配置受け渡し用
	backPos.EditPos() = Vector3(418, 678, 0); //表示背景初期位置設定



	for (int j = 0; j < cardPos.size(); ++j) { //カード配置
		cardPos[j].EditPos() = firstCardPos; //現在操作対象キャラに合わせて位置の初期設定
		cardPos[j].EditPos().SetX(firstCardPos.GetX() + cardPlaceSpace * j); //配置回数に合わせて位置ずらしを行う
	}

	actionButton = new Button(actionPlace.GetX(), actionPlace.GetY(), actionSize.GetX() / 2, actionSize.GetY() / 2, true); //アクションボタンの作成
	foldButton = new Button(foldPlace.GetX(), foldPlace.GetY(), foldSize.GetX() / 2, foldSize.GetY() / 2, true); //foldボタンの作成

	int* handle = new int[5]; //分割読み込み画像の保存用領域確保
	LoadDivGraph("Resource/image/poker_action_button.png", 5, 5, 1, 110, 90, handle); //各種アクション用ボタンの画像分割読み込み

	Cmp_Image* foldImage = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_fold.png")), 1, foldButton->EditTransform()); //foldボタン画像作成
	actionButtonImage = new Cmp_Image(*handle, 5, actionButton->EditTransform()); //アクションボタン画像作成

	actionButton->EditAlways()->SetCmp(actionButtonImage); //ボタンに画像を追加
	foldButton->EditAlways()->SetCmp(foldImage);
	actionButton->EditClick()->SetCmp(new Cmp_Button_ClickCheck()); //クリックにクリック検知用空コンポーネントの追加
	foldButton->EditClick()->SetCmp(new Cmp_Button_ClickCheck());

	actionButton->SetRunUpdate(false); //ボタン系は必要時以外完全に隠す
	foldButton->SetRunUpdate(false);
	actionButton->SetRunDraw(false);
	foldButton->SetRunDraw(false);


	Cmp_Image* base = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_gage_back.png")), 1); //ゲージ画像の作成
	Cmp_Image* full = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_gage_full.png")), 1);
	base->EditTranform()->EditPos().SetXYZ(gagePlace.GetX(), gagePlace.GetY(), 0); //ゲージ位置設定
	full->EditTranform()->EditPos().SetXYZ(gagePlace.GetX(), gagePlace.GetY(), 0);

	gage = new Gage(*base, *full); //ゲージの作成
	gageBorder = new Cmp_Gage_Border(*gage);
	gageUpper = new Cmp_Gage_UpperBorder(*gage);
	int sizeX = -1; int sizeY = -1;
	GetGraphSize(*full->ReadImage(), &sizeX, &sizeY); //ゲージサイズ取得

	gageControl = new Cmp_Gage_MouseControl(*gage, Vector3(sizeX * monitorArea.GetX(), sizeY * monitorArea.GetY()), dealer.GetMaxBet()); //ゲージのマウスコントロール受け付けコンポーネント作成
	gageControl->SetRunUpdate(false); //コントロールコンポーネントは通常実行を切っておく
	gage->EditAppendCmp()->SetCmp(gageControl); //ゲージをマウスからコントロールする機能の追加
	gage->EditAppendCmp()->SetCmp(gageBorder); //ゲージ下限設定機能の追加
	gage->EditAppendCmp()->SetCmp(gageUpper); //ゲージ上限設定機能の追加


	std::deque<PK_Card*> card = *EditHand()->EditCard();
	for (int j = 0; j < card.size(); ++j) { //カードを取得
		Button* button = new Button(cardPos[j].ReadPos().GetX(), cardPos[j].ReadPos().GetY(), 60, 75, false); //カードクリック判定用ボタンの作成
		button->EditClick()->SetCmp(new Cmp_Button_ClickCheck()); //クリック検知用空コンポーネントの追加

		card[j]->EditAppendCmp()->SetCmp(button); //カードにボタンを追加
	}
	record = new Cmp_BetActionRecord();

	EditAppendCmp()->SetCmp(gage); //ゲージをプレイヤーに追加
	EditAppendCmp()->SetCmp(actionButton); //アクションボタンをプレイヤーに追加
	EditAppendCmp()->SetCmp(foldButton); //foldボタンをプレイヤーに追加
	EditAppendCmp()->SetCmp(new Cmp_PlayerRaiseDraw(*this, pot, dealer)); //プレイヤーの現在ゲージでの支払額表示用コンポーネントを追加
	EditAppendCmp()->SetCmp(record); //アクションの状態を記録するActionRecordを導入

	Place(cardPos, backPos); //カードとコイン表示背景の配置

	sectionModule.push_back(new PK_Player::Main(*this));
	sectionModule.push_back(new PK_Player::Change(*this));

	runSection = sectionModule[(int)Section::main]; //mainからスタート
}

PK_Player::~PK_Player() {
	for (auto itr : sectionModule) { delete itr; } //各セクションを削除
}

void PK_Player::SectionUpdate() {
	if (!runSection->GetRunUpdate()) { return; } //セクションが実行禁止なら実行しない
	runSection->Update(); //指定セクションのUpdateを実行
}
