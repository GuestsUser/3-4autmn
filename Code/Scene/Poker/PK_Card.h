#pragma once
#include "Component.h"
#include "ComponentArray.h"
#include <deque>

class Cmp_Image;
class Cmp_Transform;

class PK_Card :public Component { //�J�[�h�ɕK�v�ȕϐ��Q��Z�߂��N���X
public:
	enum class DrawMode { back, front, fold }; //�\�����[�h�Aback�͔w�ʕ\���Afront�͕\���\���Afold��fold�p�̊D�F�\��

private:
	Cmp_Image* image; //�J�[�h�摜
	Cmp_Image* markingImage; //�}�[�L���O�p�摜
	int card; //�J�[�h�摜����ړI�̉摜�����o���Y�����ϐ�
	DrawMode drawMode; //�\�����[�h�i�[�ϐ�

	ComponentArray cmp;
public:
	PK_Card();
	~PK_Card();

	void Reset(); //�V�������E���h���J�n���鎞�Ăяo���A�����ڂ��������(�}�[�L���O�Ȃ��A�����\��)�ɖ߂�
	void FullReset() { Reset(); } //Reset�Ɠ��e�͓���

	void Place(int x, int y); //�J�[�h��z�u����

	const Cmp_Transform* ReadTransform() const; //���W�n����ǂݎ���p�`���Ŏ擾
	Cmp_Transform* EditTransform(); //���W�n����ҏW�\�ȏ�ԂŎ擾

	void Update();
	void Draw();

	int GetCard() const { return card; } //image�Ŏg�p����J�[�h�Y������Ԃ�

	void SetCard(int number) { card = number; } //image�Ŏg�p����Y������n���ăJ�[�h�̋����Ǝ�ނ�ݒ肷��
	void SetMarking(bool set); //true�ŃJ�[�h�Ƀ}�[�L���O��\��

	void SetDrawMode(DrawMode set) { drawMode = set; } //�\���`���̐ݒ�


	ComponentArray* EditAppendCmp() { return &cmp; } //�ǉ��@�\�W�ւ̃A�N�Z�X��n��
	const ComponentArray* const ReadAppendCmp() { return &cmp; } //�ǉ��@�\�W�ւ̃A�N�Z�X�A������͓ǂݏo����p
};