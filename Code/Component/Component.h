#pragma once

class Component { //������p�������N���X�ɃI�u�W�F�N�g�ւ̒ǉ��@�\�Ȃǂ������Ɣėp���̍����v���O�����ɂł���
private:
	bool isUpdate; //true��Update�����s
	bool isDraw; //true��Draw�����s

public:
	Component() :isUpdate(true), isDraw(true) {}
	virtual ~Component() {  }

	virtual void Update() = 0;
	virtual void Draw() {}

	virtual void FullReset() {} //�R���|�[�l���g�������������Q�[�����ăX�^�[�g����ۂɎg�p���郊�Z�b�g
	virtual void Reset() {} //�Q�[����1�s���I�h���I���������A���Ɉڍs����׎��s���郊�Z�b�g

	bool GetRunUpdate() const { return isUpdate; }
	bool GetRunDraw() const { return isDraw; }

	void SetRunUpdate(bool set) { isUpdate = set; }
	void SetRunDraw(bool set) { isDraw = set; }
	void SetRunUpdateDraw(bool update, bool draw) { //update��draw�̎��s�ݒ�𓯎��ɍs���A2�𓯂��^�C�~���O�ɐݒ肵�����ꍇ�̃V���^�b�N�X�V���K�[
		isUpdate = update;
		isDraw = draw;
	}
};