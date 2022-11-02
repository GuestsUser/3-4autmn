#pragma once
#include "../Code/OriginMath.h"
#include "../Code/Component/Component.h"

class Cmp_Transform :public Component { //�ڍׂȉ摜�`�ʂɕK�v�ȏ���Z�߂���
private:
	Vector3* xyz; //�\�����W�A����(0,0)�ŊǗ�
	Vector3* scale; //�g�嗦
	Vector3* rotate; //��]�A0�`2PI�̃��W�A���p�ŊǗ�
public:
	Cmp_Transform() :xyz(new Vector3()), scale(new Vector3(1, 1, 1)), rotate(new Vector3()) {}
	Cmp_Transform(const Cmp_Transform& cmp) :xyz(new Vector3(cmp.ReadPos())), scale(new Vector3(cmp.ReadScale())), rotate(new Vector3(cmp.ReadRotate())) {} //�R�s�[�R���X�g���N�^

	~Cmp_Transform() {
		delete xyz;
		delete scale;
		delete rotate;
	}

	void Update() {} //�f�[�^�I�ȈӖ������̃R���|�[�l���g�Ȃ̂ŉ������Ȃ�
	void Draw() {} //Update���l�������Ȃ�

	const Vector3& ReadPos() const { return *xyz; } //�ʒu�̏���ǂݎ��
	const Vector3& ReadScale() const { return *scale; } //�g�嗦�̏���ǂݎ��
	const Vector3& ReadRotate() const { return *rotate; } //��]�̏���ǂݎ��

	Vector3& EditPos() { return *xyz; } //�ʒu�̏���ҏW�\�ȏ�ԂŕԂ�
	Vector3& EditScale() { return *scale; } //�g�嗦�̏���ҏW�\�ȏ�ԂŕԂ�
	Vector3& EditRotate() { return *rotate; } //��]�̏���ҏW�\�ȏ�ԂŕԂ�
};