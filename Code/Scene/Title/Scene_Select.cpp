#include "DxLib.h"

#include "../Code/Scene/Scene.h"
#include "../Code/Component/Button.h"
#include "../Code/Component/Cmp_Image.h"
#include "../Code/Component/Cmp_ButtonGroup.h"
#include "Cmp_SelectSelector.h"
#include "Scene_Select.h"
#include "Scene_Explain.h"

//�v���C����Q�[���V�[�����C���N���[�h
#include"../Code/Scene/Karuta/Scene_Karuta.h"
#include"../Code/Scene/ConnectFour/Scene_ConnectFour.h"
#include"../Code/Scene/daifugou/CP_Scene.h"
#include"../Code/Scene/BlackJack/BJ_Main.h"
#include"../Code/Scene/Asuma/Scene_PageOne.h"
#include"../Code/Scene/Othello/Scene_Othello.h"
#include"../Code/Scene/Sugoroku/SR_Game.h"
#include <deque>


Scene_Select::Scene_Select() :explain(std::deque<Scene_Explain*>()), button(std::deque<Button*>()), run(nullptr) {
	SetFontSize(36); //�`�ʕ����T�C�Y�w��

	int place = 9; //�{�^���z�u��
	int xSplit = 4; //�{�^����1��̔z�u��
	int ySplit = place / xSplit; //�{�^���̔z�u�s��
	int xSize = 260; //�{�^���̉摜�T�C�Yx
	int ySize = 203; //�{�^���̉摜�T�C�Yy

	for (int i = 0; i < place; ++i) {
		std::deque<Cmp_Image*>* explainImage = new std::deque<Cmp_Image*>(); //�����摜�i�[�p�ϐ�
		Scene* gameScene = nullptr; //������ʂŃN���b�N���������s�������Q�[���V�[��
		int* img = new int(0); //�摜�n���h���i�[�p�ϐ�
		button.push_back(new Button((1240 / xSplit) / 2 + xSize * (i % xSplit), (720 / ySplit) / 2 + ySize * (int)(i / xSplit), xSize / 2, ySize / 2));
		
		switch (i) {
		case 0: //�G�A�z�b�P�[�̐����摜�Ƃ������鍀��
			*img = LoadGraph("Resource/image/Select_AirHockey.png"); //�{�^���摜������
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_AirHockey1.png")), 1)); //�����摜������A�y�[�W���͍ŏ��ɓ��ꂽ����1�y�[�W�ɂȂ�
			break;
		case 1: //�u���b�N�W���b�N
			*img = LoadGraph("Resource/image/Select_Blackjack.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Blackjack1.png")), 1));
			break;
		case 2: //��x��
			*img = LoadGraph("Resource/image/Select_CareerPoker.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_CareerPoker1.png")), 1));
			break;
		case 3: //�R�l�N�g�t�H�[
			*img = LoadGraph("Resource/image/Select_ConnectFour.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_ConnectFour1.png")), 1));
			break;
		case 4: //���邽
			*img = LoadGraph("Resource/image/Select_Karuta.png");
			gameScene = new Scene_Karuta(); //�ʃV�[����΂����Ascm�ɓ���Ă����̂�gameScene�ɂȂ������x�̈Ⴂ
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Karuta1.png")), 1));
			break;
		case 5: //�y�[�W����
			*img = LoadGraph("Resource/image/Select_PageOne.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_PageOne1.png")), 1));
			break;
		case 6: //�|�[�J�[
			*img = LoadGraph("Resource/image/Select_Poker.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker1.png")), 1));
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Poker2.png")), 1)); //�����̐�����ʓ������
			break;
		case 7: //�����낭
			*img = LoadGraph("Resource/image/Select_Sugoroku.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Sugoroku1.png")), 1));
			gameScene = new SR_Game(); //�ʃV�[����΂����Ascm�ɓ���Ă����̂�gameScene�ɂȂ������x�̈Ⴂ
			break;
		case 8: //�I�Z��
			*img = LoadGraph("Resource/image/Select_Othello.png");
			explainImage->push_back(new Cmp_Image(*new int(LoadGraph("Resource/image/Explain_Othello1.png")), 1));
			break;
		}
		explain.push_back(new Scene_Explain(*explainImage, gameScene)); //�{�^�����������ۂ̐����V�[���쐬

		button[i]->SetAlways(new Cmp_Image(*img, 1, button[i]->EditTransform())); //�{�^���ɉ摜��ǉ�
		button[i]->SetClick(new Cmp_ButtonGroup(*button[i], button)); //�{�^���������ꂽ�ہA�����ꂽ�{�^���ȊO���~����@�\�̒ǉ�
		button[i]->SetClick(new Cmp_SelectSelector(explain[i], &run, button)); //�{�^���������ꂽ�ہArun��explain[i]������@�\�̒ǉ�

		
	}

	
	//button.push_back(new Poker());
}

Scene_Select::~Scene_Select() {
	for (int i = 0; i < button.size(); ++i) {
		delete button[i]; //new����button�̍폜
		delete explain[i]; //new���������V�[���̍폜
	}
}

void Scene_Select::Update() {
	if (run != nullptr) { //run�ɉ��������Ă����ꍇ�������D����s
		run->Update(); //run���s

		run = run->GetNext(); //run�ɐݒ肳�ꂽ���̎��s�V�[�����擾run�ɐݒ�
		if (run == nullptr) { return; }  //��ɂ��ꂽ�甲���A���񂩂�͕��펞��Update�����s����
		for (auto itr : explain) {
			if (run == itr) { return; } //explain�Ɠ��������������ꍇ�����A�����run�����s����
		}
		SetNext(run); //�����܂ŗ�����ݒ肳�ꂽ�V�[���̓Q�[�����s�V�[���ɂȂ�̂ŃZ���N�g��ʂ��I����������Ɉڍs����
		return;
	}

	//run�ɉ��������ĂȂ��ꍇ
	for (auto itr : button) { itr->Update(); } //�{�^��update�����s
}

void Scene_Select::Draw() {
	if (run != nullptr) { run->Draw(); } //run�ɉ��������Ă����ꍇ�������D����s
	else {
		for (auto itr : button) { itr->Draw(); } //�{�^��draw�����s
	}
}