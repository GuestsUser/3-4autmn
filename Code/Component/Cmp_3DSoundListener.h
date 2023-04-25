#pragma once
#include "Component.h"
#include "Cmp_Transform.h"
#include "3DSoundSystemCoordinateData.h"

class Cmp_3DSoundListener :public Component { //3d��ԏ�ŃT�E���h�𕷂����ʒu��ݒ肵����
	static Cmp_Transform ts;
	static SoundSystemCoordinateData::Type coordinateType; //��Ԑݒ�Ɏg�p������W�n���w�肷��ׂ̕ϐ�
public:
	void Update() {}

	static void SetUp(); //�ŏ��ɂ�����Ăяo�����ŕێ����鏉���������X�i�[�ɐݒ肵�A���̃R���|�[�l���g�����퓮�삷��悤�ɂ���
	static void SetPos(const Vector3& pos); //3d��ԏ�̃T�E���h�������ʒu��ݒ�
	static void SetRotate(const Vector3& rotate); //3d��ԏ�ŃT�E���h�𕷂��ׂɌ����Ă��������ύX�A���W�A���p�w��
	static void SetCoordinateType(const SoundSystemCoordinateData::Type& set); //���W�n�w���ύX����

	static const Cmp_Transform* const ReadTransform() { return &ts; } //3d��ԏ�̈ʒu��]��ǂݎ���p�`���Ŏ󂯎��
	static Cmp_Transform* EditTransform() { return &ts; } //3d��ԏ�̈ʒu��]�����������\�`���Ŏ󂯎��A����ɂ��ҏW�\��SetUp���Ă΂Ȃ��Ɣ��f����Ȃ��̂Ŏg�p�͔񏧗�

private:
	//���̐����֎~
	Cmp_3DSoundListener() = delete;
	Cmp_3DSoundListener(Cmp_3DSoundListener&) = delete;
};