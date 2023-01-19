#include <DxLib.h>

#include "../Scene.h"
#include "Poker.h"
#include "PokerSections.h" //Poker管理のシーン定義を行っている
#include "PokerFontData.h"

#include "PK_Card.h"
#include "CPU.h"
#include "Pot.h"
#include "Chara.h"
#include "PK_Dealer.h"
#include "PK_Player.h"
#include "CardDealer.h"
#include "../Code/OriginMath.h"

#include "Cmp_BetActionRecord.h"
#include "Cmp_CPUBetLogic.h"
#include "Cmp_ThinkingImage.h"
#include "Cmp_PlayerRaiseDraw.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Gage.h"
#include "../Code/Component/Cmp_Button_ClickCheck.h"
#include "../Code/Component/Cmp_Gage_MouseControl.h"
#include "../Code/Component/Cmp_Gage_Border.h"
#include "../Code/Component/Cmp_Gage_UpperBorder.h"
#include "../Code/Component/Cmp_Image.h"

#include <deque>

void SetCardPlaceDate(Cmp_Transform* cardPos); //cardPos配列に各キャラ毎のカード初期位置を設定する
void SetCoinBackPlaceDate(Cmp_Transform* backPos); //backPos配列に各キャラ毎のコイン表示背景初期位置を設定する

void Poker::Update() {
	run->Update(); //Update実行
	for (auto itr : chara) { if (itr->GetRunUpdate()) { itr->Update(); } } //キャラ内の追加機能を実行

	run = run->GetNext(); //次シーンの取得
	for (auto itr : list) { //次シーンがlist内にある物かどうかチェック
		if (run == itr) { return; } //list内にあった場合Drawに処理を移す
	}

	SetNext(run); //次シーンがPoker管理のScene以外だった場合それを次シーンに設定してPokerは終了する
}

void Poker::Draw() {
	back->Draw(); //背景描写
	pot->Draw(); //ポット描写
	dealer->Draw(); //ボタンポジションの描写
	for (auto itr : chara) { itr->Draw(); } //各キャラの手札とか所持金とか描写

	run->Draw();
}

Poker::Poker() :pot(new Pot()), dealer(new PK_Dealer()), cardDealer(new CardDealer()), back(nullptr), list(std::deque<Scene*>()) {
	back = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_back.png")), 1); //背景画像作成
	back->EditTranform()->EditPos().SetXYZ(1280 / 2, 720 / 2, 0); //画面中央に配置
	PokerFontData::SetUp(); //フォントデータ参照用クラスのセットアップ

	int cardPlaceSpace = 134; //カード配置間隔
	int cardPlaceSpaceCpu = 33; //カード配置間隔、cpu用
	Vector3 monitorArea = Vector3(1.2, 2); //ゲージ実体画像サイズに対しこの数値分掛けた値をクリック検知範囲とする
	Vector3 gagePlace = Vector3(442, 633); //ゲージの配置座標
	Vector3 actionPlace = Vector3(573, 663); //Call,Raise等各種アクションボタンの配置座標
	Vector3 actionSize = Vector3(110, 90); //Call,Raise等各種アクションボタンの画像サイズ
	Vector3 foldPlace = Vector3(772, 684); //foldButton配置座標
	Vector3 foldSize = Vector3(90, 45); //foldButton画像サイズ

	std::deque<Cmp_Transform> cardPos = std::deque<Cmp_Transform>(5); //カード配置受け渡し用変数
	Cmp_Transform backPos = Cmp_Transform(); //コイン表示背景配置受け渡し用
	Cmp_Transform cardPosFirst[] = { Cmp_Transform(), Cmp_Transform() ,Cmp_Transform() ,Cmp_Transform() }; //カード配置の際の初期位置入れ
	Cmp_Transform backPosFirst[] = { Cmp_Transform(), Cmp_Transform() ,Cmp_Transform() ,Cmp_Transform() }; //コイン表示背景配置の際の初期位置入れ

	SetCardPlaceDate(cardPosFirst); //初期位置集を設定
	SetCoinBackPlaceDate(backPosFirst);

	
	for (int i = 0; i < (int)Character::length; ++i) { //キャラクター精製
		bool isPlayer = i == (int)Character::player; //今回の作成キャラがプレイヤーか否か、trueでプレイヤー
		Chara* current = nullptr;
		int useSpace = isPlayer ? cardPlaceSpace : cardPlaceSpaceCpu; //カード配置に使う配置間隔
		cardPos[0] = cardPosFirst[i]; //カード先頭を現在キャラに応じた位置に変更
		backPos = backPosFirst[i]; //現在キャラに応じたコイン表示位置に設定

		for (int j = 0; j < cardPos.size(); ++j) { //カード配置
			cardPos[j].EditPos() = cardPosFirst[i].ReadPos(); //現在操作対象キャラに合わせて位置の初期設定
			cardPos[j].EditPos().SetX(cardPosFirst[i].ReadPos().GetX() + useSpace * j); //配置回数に合わせて位置ずらしを行う
		}


		if (isPlayer) { //プレイヤーの精製を指定された場合
			useSpace = cardPlaceSpace; //配置間隔をプレイヤーの物に変更
			current = new PK_Player(); //プレイヤーの精製


			Button* action = new Button(actionPlace.GetX(), actionPlace.GetY(), actionSize.GetX() / 2, actionSize.GetY() / 2, true); //アクションボタンの作成
			Button* fold = new Button(foldPlace.GetX(), foldPlace.GetY(), foldSize.GetX() / 2, foldSize.GetY() / 2, true); //foldボタンの作成

			int* handle = new int[5]; //分割読み込み画像の保存用領域確保
			LoadDivGraph("Resource/image/poker_action_button.png", 5, 5, 1, 110, 90, handle); //各種アクション用ボタンの画像分割読み込み

			Cmp_Image* foldImage = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_fold.png")), 1, fold->EditTransform()); //foldボタン画像作成
			Cmp_Image* actionImage = new Cmp_Image(*handle, 5, action->EditTransform()); //アクションボタン画像作成

			action->SetAlways(actionImage); //ボタンに画像を追加
			fold->SetAlways(foldImage);
			action->SetClick(new Cmp_Button_ClickCheck()); //クリックにクリック検知用空コンポーネントの追加
			fold->SetClick(new Cmp_Button_ClickCheck());

			action->SetRunUpdate(false); //ボタン系は必要時以外完全に隠す
			fold->SetRunUpdate(false);
			action->SetRunDraw(false);
			fold->SetRunDraw(false);


			Cmp_Image* base = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_gage_back.png")), 1); //ゲージ画像の作成
			Cmp_Image* full = new Cmp_Image(*new int(LoadGraph("Resource/image/poker_gage_full.png")), 1);
			base->EditTranform()->EditPos().SetXYZ(gagePlace.GetX(), gagePlace.GetY(), 0); //ゲージ位置設定
			full->EditTranform()->EditPos().SetXYZ(gagePlace.GetX(), gagePlace.GetY(), 0);

			Gage* gage = new Gage(*base, *full); //ゲージの作成
			int sizeX = -1; int sizeY = -1;
			GetGraphSize(*full->ReadImage(), &sizeX, &sizeY); //ゲージサイズ取得

			Cmp_Gage_MouseControl* control = new Cmp_Gage_MouseControl(*gage, Vector3(sizeX * monitorArea.GetX(), sizeY * monitorArea.GetY()), dealer->GetMaxBet()); //ゲージのマウスコントロール受け付けコンポーネント作成
			control->SetRunUpdate(false); //コントロールコンポーネントは通常実行を切っておく
			gage->SetCmp(control); //ゲージをマウスからコントロールする機能の追加
			gage->SetCmp(new Cmp_Gage_Border(*gage)); //ゲージ下限設定機能の追加
			gage->SetCmp(new Cmp_Gage_UpperBorder(*gage)); //ゲージ上限設定機能の追加


			

			std::deque<PK_Card*> card = *current->EditCard();
			for (int j = 0; j < card.size(); ++j) { //カードを取得
				Button* button = new Button(cardPos[j].ReadPos().GetX(), cardPos[j].ReadPos().GetY(), 60, 75, false); //カードクリック判定用ボタンの作成
				button->SetClick(new Cmp_Button_ClickCheck()); //クリック検知用空コンポーネントの追加

				card[j]->SetCmp(button); //カードにボタンを追加
			}


			current->SetCmp(gage); //ゲージをプレイヤーに追加
			current->SetCmp(action); //アクションボタンをプレイヤーに追加
			current->SetCmp(fold); //foldボタンをプレイヤーに追加
			current->SetCmp(new Cmp_PlayerRaiseDraw(*current, *pot, *dealer)); //プレイヤーの現在ゲージでの支払額表示用コンポーネントを追加
		}
		else { //cpuの精製を指定された場合
			current = new CPU(); //cpuの精製
			current->SetCmp(new Cmp_CPUBetLogic(*dealer)); //cpuのベットに必要なデータを纏めたBetLogicを導入
		}


		current->Place(cardPos, backPos); //カードとコイン表示背景の配置
		current->SetCmp(new Cmp_BetActionRecord()); //アクションの状態を記録するActionRecordを導入
		current->SetCmp(new Cmp_ThinkingImage(*current, chara, *dealer, backPosFirst[i].ReadPos())); //考え用画像を表示するコンポーネントの導入

		chara.push_back(current);
	}
	cardDealer->Reset(); //最初はIniを実行しないので山札だけは初期化しておく

	list.push_back(new Ini(*this));
	list.push_back(new Pre(*this));
	list.push_back(new Main(*this));
	list.push_back(new Change(*this));
	list.push_back(new ShowDown(*this));
	list.push_back(new NoContest(*this));
	list.push_back(new GameOver(*this));



	run = list[1];
}

Poker::~Poker() {
	for (auto itr : list) { delete itr; } //Pokerで管理していたシーンの削除
	for (int i = 0; i < (int)Character::length; ++i) { delete chara[i]; }
	delete pot;
	delete dealer;
	delete cardDealer;
	delete back;
}



void SetCardPlaceDate(Cmp_Transform* cardPos) {
	cardPos[(int)Poker::Character::leftCom].EditPos().SetXYZ(91, 301, 0); //leftCpuの一番最初に配置するカード位置
	cardPos[(int)Poker::Character::topCom].EditPos().SetXYZ(517, 95, 0); //topCpuの一番最初に配置するカード位置
	cardPos[(int)Poker::Character::rightCom].EditPos().SetXYZ(1024, 296, 0); //rightCpuの一番最初に配置するカード位置
	cardPos[(int)Poker::Character::player].EditPos().SetXYZ(360, 520, 0); //playerの一番最初に配置するカード位置
}
void SetCoinBackPlaceDate(Cmp_Transform* backPos) {
	backPos[(int)Poker::Character::leftCom].EditPos().SetXYZ(151, 434, 0); //leftCpuの一番最初に配置する位置
	backPos[(int)Poker::Character::topCom].EditPos().SetXYZ(819, 82, 0); //topCpuの一番最初に配置する位置
	backPos[(int)Poker::Character::rightCom].EditPos().SetXYZ(1082, 428, 0); //rightCpuの一番最初に配置する位置
	backPos[(int)Poker::Character::player].EditPos().SetXYZ(418, 678, 0); //playerの一番最初に配置する位置
}