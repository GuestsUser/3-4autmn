#pragma once
#include "OriginMath.h"

#include <unordered_map>

class SoundSystemCoordinateData { //3d�T�E���h�̃��X�i�[�ɐݒ肷����W�n����Z�߂��N���X
public:
	enum class Type { twoDimension, threeDimension }; //���W�^�C�v���w�肷��ׂ̗񋓌^

private:
	//���̐����֎~
	SoundSystemCoordinateData() = delete;
	SoundSystemCoordinateData(const SoundSystemCoordinateData&) = delete;

	static std::unordered_map<Type, Vector3> front; //�p�x(0,0,0)�̎������������Ă��邩�𐳋K�����ꂽ���l�ŕ\��
	static std::unordered_map<Type, Vector3> up; //3d��ԏ�ł̏�����A2d�ł������̉������𐳋K�����ꂽ���l�ŕ\��

public:
	static void SetUp(); //�ϐ��̏��������s���g�p�\�ɂ���A������Ăяo���Ă��Ӗ��͂Ȃ������Ȃ�

	static Vector3 GetFrontCoordinate(Type sub) { return front[sub]; } //sub�Ŏw�肳�ꂽfront�f�[�^���擾
	static Vector3 GetUpCoordinate(Type sub) { return up[sub]; } //sub�Ŏw�肳�ꂽup�f�[�^���擾
};