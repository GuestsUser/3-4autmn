#include "3DSoundSystemCoordinateData.h"

std::unordered_map<SoundSystemCoordinateData::Type, Vector3> SoundSystemCoordinateData::front = std::unordered_map<SoundSystemCoordinateData::Type, Vector3>();
std::unordered_map<SoundSystemCoordinateData::Type, Vector3> SoundSystemCoordinateData::up = std::unordered_map<SoundSystemCoordinateData::Type, Vector3>();

void SoundSystemCoordinateData::SetUp() {
	front[Type::twoDimension] = Vector3(1, 0, 0); //2d���W�f�[�^�̐ݒ�
	up[Type::twoDimension] = Vector3(0, 0, 1);

	front[Type::threeDimension] = Vector3(0, 0, 1); //3d���W�f�[�^�̐ݒ�
	up[Type::threeDimension] = Vector3(0, 1, 0);
}
