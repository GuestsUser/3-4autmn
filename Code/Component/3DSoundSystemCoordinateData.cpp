#include "3DSoundSystemCoordinateData.h"

std::unordered_map<SoundSystemCoordinateData::Type, Vector3> SoundSystemCoordinateData::front = std::unordered_map<SoundSystemCoordinateData::Type, Vector3>();
std::unordered_map<SoundSystemCoordinateData::Type, Vector3> SoundSystemCoordinateData::up = std::unordered_map<SoundSystemCoordinateData::Type, Vector3>();

void SoundSystemCoordinateData::SetUp() {
	front[Type::twoDimension] = Vector3(1, 0, 0); //2d座標データの設定
	up[Type::twoDimension] = Vector3(0, 0, 1);

	front[Type::threeDimension] = Vector3(0, 0, 1); //3d座標データの設定
	up[Type::threeDimension] = Vector3(0, 1, 0);
}
