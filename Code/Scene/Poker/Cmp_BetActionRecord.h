#pragma once
#include "../Code/Component/Component.h"

#include <deque>

class Cmp_BetActionRecord :public Component {
public:
	enum class Action { check, call, raise, allIn, change, fold, length }; //�L�����N�^�[�̍s����A�N�V����
private:
	std::deque<bool> actionRecord; //action�̗񋓌^�ɑΉ������Y�����ɂ��̃A�N�V�������s�������ۂ��L�^����Atrue�ŃA�N�V�����ς݁Afalse�Ŗ����s
	bool isAction; //�A�N�V�����I���ς݂�true�A����raise���Ă����L������������false�ɒ���
	bool isLoose; //������0��Ԃŕ������ꍇ�Atrue�ɂ��Ă��̃L�������Q�[�����珜�O����
	int raiseRunCount; //���C�Y������(���ۂɉ��񃌃C�Y���s������)���L�^

public:
	Cmp_BetActionRecord() :actionRecord(std::deque<bool>((int)Action::length)), raiseRunCount(0), isAction(false), isLoose(false) {}
	void Update() {}

	void FullReset() { //���S���Z�b�g��isLoose���߂�
		isLoose = false;
		Reset();
	}

	void Reset() { //���E���h�J�n����V�����t�F�[�Y�Ɉڂ����ۂɎ��s�A�ϐ���false�ɖ߂��Ă����
		for (auto itr : actionRecord) { itr = false; } //�S�A�N�V�������s���ĂȂ���Ԃɖ߂�
		isAction = false;
		raiseRunCount = 0;
	}

	bool GetActionRecord(Action get) { return actionRecord[(int)get]; } //Action�񋓌^��Y�����Ɏw�肷�鎖�ŊY���A�N�V�������s�������ǂ�����bool�Ŏ󂯎���Atrue�ŃA�N�V�����ς�
	bool GetIsAction() const { return isAction; } //true�ŃA�N�V�����I����Ă�
	bool GetIsLoose() const { return isLoose; } //true�Ŕs�k�ς�
	int GetRaiseRunCount() const { return raiseRunCount; } //���̃t�F�[�Y���̃��C�Y�����񐔂�Ԃ�

	void SetActionRecord(Action get, bool result) { actionRecord[(int)get] = result; } //�Y���A�N�V�����̎��s�ς݂��ۂ���ݒ肷��
	void SetIsAction(bool set) { isAction = set; } //�A�N�V�����I��点�����ݒ�
	void SetIsLoose(bool set) { isLoose = set; } //�s�k�������ۂ��̐ݒ�
	void SetRaiseRunCount(int set) { raiseRunCount = set; } //���̃t�F�[�Y���̃��C�Y�����񐔂�ݒ�
};