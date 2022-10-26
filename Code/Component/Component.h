#pragma once

class Component { //������p�������N���X�ɃI�u�W�F�N�g�ւ̒ǉ��@�\�Ȃǂ������Ɣėp���̍����v���O�����ɂł���
private:
	bool isUpdate; //true��Update�����s
	bool isDraw; //true��Draw�����s
public:
	Component() :isUpdate(true), isDraw(true) {}
	virtual ~Component() = 0;

	virtual void Update() = 0;
	virtual void Draw() {}

	bool GetRunUpdate() { return isUpdate; }
	bool GetRunDraw() { return isDraw; }

	void SetRunUpdate(bool set) { isUpdate = set; }
	void SetRunDraw(bool set) { isDraw = set; }
};