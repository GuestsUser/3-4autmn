#pragma once
class Button;

class ButtonResetData { //buttonのResetを実行した時isUpdate等をどういう状態に戻すか纏めたデータ
	//このコンポーネントはbuttonのalways、clickどちらに格納してもよし
	Button* parent; //このコンポーネントを持つbutton

	bool isUpdate;
	bool isDraw;
	bool clickMonitor;
public:
	ButtonResetData(Button& parent, bool isUpdate = true, bool isDraw = true, bool clickMonitor = true) :parent(&parent), isUpdate(isUpdate), isDraw(isDraw), clickMonitor(clickMonitor) {}

	void Update() {}
	void Reset(); //このResetが呼ばれた時parentにButtonResetDataが持つデータを設定する
	void FullReset() { Reset(); } //Reset同様

	bool GetUpdateData() const { return isUpdate; }
	bool GetDrawData() const { return isDraw; }
	bool GetClickMonitorData() const { return clickMonitor; }
};
