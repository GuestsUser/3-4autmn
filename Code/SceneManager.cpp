#include "SceneManager.h"
#include "./Scene/Scene.h"

bool SceneManager::Update() {
	//while (true) { //�ڍs��̃V�[������x��update���Ăяo���׃��[�v�d�l
	//	run->Update(); //update���s
	//	Scene* next = run->GetNext(); //���V�[���̎擾
	//	if (run == next) { break; } //�p���������烋�[�v����

	//	delete run; //�ڍs�𖽗߂��ꂽ�猻�݃V�[���̍폜
	//	if (next == nullptr) { run = nullptr; return false; } //�I������
	//	run = next; //���s����V�[��������̕��ɍX�V
	//}
	while (true) { //�ڍs��̃V�[����update�̌Ăяo�����s��Ȃ��d�l
		run->Update(); //update���s
		Scene* next = run->GetNext(); //���V�[���̎擾
		if (next != nullptr) { break; } //������s����ɂ���ĂȂ���΃��[�v����

		delete run; //���݃V�[���̍폜
		run = nullptr; //�l�����
		return false; //main�ɃQ�[���I����ʒm����
	}
	return true; //Draw�ɏ������ڂ�
}

void SceneManager::Draw() { run->Draw(); }