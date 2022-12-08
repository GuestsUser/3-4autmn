#pragma once
#include "Component.h"
#include "../Code/OriginMath.h"

#include <deque>

class Cmp_Transform;

class Cmp_Image :public Component { //Draw���Ăяo�����ŉ摜�`�ʂ��s���A�w����W�ɉ摜�����������čs���A�g�嗦���]�ɉ����ĕό`�`�ʂ���
	

	int* gh; //�O���t�B�b�N�n���h���A�󂯎��������ێ����邾��
	int length; //�O���t�B�b�N�n���h���̗v�f���A���I�z�񂶂�Ȃ��̂ňꏏ�Ɏ󂯎��K�v����
	int use; //�z��O���t�B�b�N�̏ꍇ�ǂ̗v�f��`�ʂɎg�����w�肷��ϐ�
	bool isSelfTs; //Transform�R���|�[�l���g���R���X�g���N�^�ŏȂ����ꍇ�����true�ɂ���Transform�̍폜���͂�����ōs��

	OriginMath::HorizonPivot drawPivotHorizon; //�g�k�Ɖ�]�̍��W�ό`�̍ۂɒ��S�Ƃ���|�C���g
	OriginMath::VerticalPivot drawPivotVertical; //��L�̏c�ʒu

	Cmp_Transform* ts; //�`�ʈʒu���]�A�g�嗦�̎Q��
	std::deque<Component*> cmp; //�摜�`�ʂɍۂ��Ă���Ă��������ǉ�����������΂�����ɒǉ�

public:
	Cmp_Image(int& setGh, int setLen, Cmp_Transform* setTs = nullptr, int setUse = 0); //������ōs������摜�ǂݍ��݂̃n���h�����󂯎��`�œ��삷��A���ɑΉ�����Transform�������
	~Cmp_Image(); //�폜����ۂ͓����ɊǗ��摜���폜����A�ǉ���������ꂽcmp�̍폜���s��

	void Update(); //Image�ɒǉ������R���|�[�l���g��Update�����s����
	void Draw(); //Image�ɒǉ������R���|�[�l���g��Draw�����s����A�ǉ��R���|�[�l���g��Draw��Image�̕`�ʏ������s���O�ɍs����


	void SetImage(int& setGh, int setLen); //�n���h���ƃT�C�Y���󂯎��A�v�f��1�Ȃ�*(new int(�n���h��))�A�z��Ȃ�n���h���󂯎��Ɏg�����ϐ��̐擪��*��t���ēn���A�v�f��1�ł�setLen�ɂ�1������A�摜�A�h���X�ւ̎Q�Ƃ�n�������͂�����ō폜���̊Ǘ����s���A�摜�����ɓ����Ă����ꍇ���̉摜�͍폜����
	const int* ReadImage() const { return gh; } //�摜�n���h����Ԃ��A�ǂݏo����p�A�`�ʂ�Draw�ōs���̂ł���̎g�p�p�r�͎�ɉ摜�T�C�Y�Ȃǂ��`�F�b�N���鎞�ɗp����

	const Cmp_Transform* ReadTranform() const { return ts; } //�ǂݎ���p�`����Transform���擾
	Cmp_Transform* EditTranform() { return ts; } //���������\�Ȍ`����Transform���擾
	int GetAnimeSub() const { return use; } //�摜�`�ʂɎg�p����Y�������擾
	int GetAnimeLength()const { return length; } //�摜�`�ʂɎg�p����Y�����̍ő吔(�܂蕪�������摜��)���擾
	void SetAnimeSub(int set) { use = set; } //�摜�`�ʂɎg�p����Y������ݒ�

	void SstDrawPivot(OriginMath::HorizonPivot hSet, OriginMath::VerticalPivot vSet) { drawPivotHorizon = hSet; drawPivotVertical = vSet; } //���S�_�ݒ�(�`�ʗp�A�������W�͒��S�Œ�)

	OriginMath::HorizonPivot GetDrawHorizonPivot() const { return drawPivotHorizon; } //�g�k��]�p���S�_�Ԃ��A��������
	OriginMath::VerticalPivot GetDrawVerticalPivot() const { return drawPivotVertical; } //�g�k��]�p���S�_�Ԃ��A��������
};
