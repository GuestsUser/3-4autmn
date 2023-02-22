#pragma once
#include "../Scene.h"
#include "Poker.h"
#include "../Code/Component/Component.h"

#include <deque>

class Cmp_Image;
class Cmp_BetActionRecord;
class Cmp_CPUBetLogic;
class Cmp_Gage_Border;
class Cmp_Gage_UpperBorder;
class Cmp_Gage_MouseControl;
class Button;
class Gage;

class Poker::Main :public Scene { //メインベットフェイズ
	std::deque<Cmp_BetActionRecord*> actionRecord; //charaから抜き出したコンポーネントを保持、配列の添え字はキャラと同様なので同じ列挙型でそのキャラのコンポーネントが取れる
	std::deque<Cmp_CPUBetLogic*> betLogic;
	std::deque<Button*> playerButton; //プレイヤーが保持するボタンコンポーネント

	Button* actionButton; //playerButtonの中でも各種アクションを行うボタンを入れる
	Button* foldButton; //playerButtonの中でもfold専用のボタンを入れる
	Cmp_Image* actionButtonImage; //action用ボタンの画像コンポーネントを入れる変数
	std::deque<Cmp_Image*> thinkingImage; //考え中である事を示す為の画像を格納する配列


	Gage* playerGage; //プレイヤー保持のゲージ
	Cmp_Gage_Border* playerGageBorder; //プレイヤーのゲージ下限設定機能のコンポーネント
	Cmp_Gage_UpperBorder* playerGageUpper; //プレイヤーのゲージ上限設定機能のコンポーネント
	Cmp_Gage_MouseControl* gageControl; //ゲージ操作を受け付けるコンポーネント

	Poker* parent; //このクラスの実体を持つPokerへの参照
	int phase; //これが何回目のベットフェイズか持っておく変数
	int count; //時間カウント

	int cpuWait; //cpuがアクションを行うまでの待機時間、フレーム数指定

public:
	Main(Poker& set);
	void Update();
	void SetPhase(int set) { phase = set; } //現在のベットフェイズをセット、runにMainを入れたらやっておくといい
};
