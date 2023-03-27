#pragma once
class Button;

class ButtonResetData { //button��Reset�����s������isUpdate�����ǂ�������Ԃɖ߂����Z�߂��f�[�^
	//���̃R���|�[�l���g��button��always�Aclick�ǂ���Ɋi�[���Ă��悵
	Button* parent; //���̃R���|�[�l���g������button

	bool isUpdate;
	bool isDraw;
	bool clickMonitor;
public:
	ButtonResetData(Button& parent, bool isUpdate = true, bool isDraw = true, bool clickMonitor = true) :parent(&parent), isUpdate(isUpdate), isDraw(isDraw), clickMonitor(clickMonitor) {}

	void Update() {}
	void Reset(); //����Reset���Ă΂ꂽ��parent��ButtonResetData�����f�[�^��ݒ肷��
	void FullReset() { Reset(); } //Reset���l

	bool GetUpdateData() const { return isUpdate; }
	bool GetDrawData() const { return isDraw; }
	bool GetClickMonitorData() const { return clickMonitor; }
};
