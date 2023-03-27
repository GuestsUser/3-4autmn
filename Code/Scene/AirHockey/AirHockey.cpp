#include <DxLib.h>
#include "./../Title/Title_Select.h"
#include "../../SceneManager.h"
#include "./../Scene.h"
#include "AirHockey.h"

void AirHockey_Scene::AirHockey_Initialize(Scene* scene) {
	Parent = scene;
	//�F�錾
	 White = GetColor(255, 255, 255);
	 Red = GetColor(255, 50, 50);
	 Blue = GetColor(0, 191, 255);
	 DarkRed = GetColor(128, 50, 50);
	 DarkBule = GetColor(0,0 ,139 );
	 Yellow = GetColor(255, 255, 50);
	 Purple = GetColor(218, 112, 214);
	 Black = GetColor(0, 0, 0);

	 score1 = 0,score2 = -1;//���_�i�[�p(1���v���C���[ 2��CPU)
	 mouseX = 0, mouseY = 0;//�}�E�X�̍��W�i�[�p
	 
	 //���� �}�W�b�N�i���o�[���g�p���Ă��܂��Ă� ��ӏ��̓}���b�g�̏������W�A�S�[���͈̔͐ݒ�A�ǂ̏c���̒��S(wall_xC,yC)
	 //���� ��ʃT�C�Y��x1280 y720  �t�B�[���h�T�C�Y x150+980=1130 y180+480=660 1050
	 wall_L = 150, wall_R = 1130, wall_T = 180, wall_B = 660, wall_xC = 640, wall_yC = 420;

	Status_Reset();
}

//�ʒu���Z�b�g
void AirHockey_Scene::Status_Reset() {//�v���C���[�ACPU�̏����ʒu�A���a�AX,Y���̑��x��ݒ�    �p�b�N�͂���Ƀ}���b�g�����X,Y���ɉ����^���ʂƑ��x�����ݒ�
	t_circle1.m_X = wall_L +30, t_circle1.m_Y = wall_yC , t_circle1.m_R = 27.0f,t_circle1.X_spd = 3.0f,t_circle1.Y_spd = 3.0f;	//�v���C���[
	t_circle2.m_X = wall_R -30, t_circle2.m_Y = wall_yC , t_circle2.m_R = 27.0f,t_circle2.X_spd = 3.0f,t_circle2.Y_spd = 3.0f;//CPU
	t_circle3.m_X = wall_xC, t_circle3.m_Y = wall_yC, t_circle3.m_R = 20.0f, t_circle3.m_boundPx = 5.0f,t_circle3.m_boundPy = 5.0f, t_circle3.X_spd = 0.0f, t_circle3.Y_spd = 0.0f, t_circle3.Maxspd = 15.0f;	//�p�b�N
};

//���s�̃t���O�֐�
bool AirHockey_Scene::Resalt() {
	if (score1 >= 3 || score2 >= 3) {
		return true;
	}
		return false;
};


//�Փˎ��̃G�t�F�N�g����
//void AirHockey_Scene::Effect()
//{
//	if (wall_R < t_circle3.m_r) {
//		for (int i = 0; i <= 120; i++) {
//			DrawPixel(t_circle3.m_r, t_circle3.m_t - t_circle3.m_r, Purple);
//			DrawPixel(t_circle3.m_r + i, t_circle3.m_t - t_circle3.m_r + i, Purple);
//		};
//	}
//	if (wall_L > t_circle3.m_l) {
//		for (int i = 0; i <= 120; i++) {
//			DrawPixel(t_circle3.m_r, t_circle3.m_t - t_circle3.m_r, Purple);
//			DrawPixel(t_circle3.m_r + i, t_circle3.m_t - t_circle3.m_r + i, Purple);
//		};
//	}
//	if (wall_T > t_circle3.m_t) {
//		for (int i = 0; i <= 120; i++) {
//			DrawPixel(t_circle3.m_r, t_circle3.m_t - t_circle3.m_r, Purple);
//			DrawPixel(t_circle3.m_r + i, t_circle3.m_t - t_circle3.m_r + i, Purple);
//		};
//	}
//	if (wall_B < t_circle3.m_b) {
//		for (int i = 0; i <= 120; i++) {
//			DrawPixel(t_circle3.m_r, t_circle3.m_t - t_circle3.m_r, Purple);
//			DrawPixel(t_circle3.m_r + i, t_circle3.m_t - t_circle3.m_r + i, Purple);
//		};
//	}
//};

//�f�o�b�N�\��
void AirHockey_Scene::Debug_Data(){
	if (Player_Puck_Check_Hit()== true) {
		DrawFormatString(150, 80, Red, "x:%d y:%d", mouseX, mouseY);//�f�o�b�N�p �}�E�X���W�\��
	}
	else {
		DrawFormatString(150, 80, White, "x:%d y:%d", mouseX, mouseY);//�f�o�b�N�p �}�E�X���W�\��
	}

	if (t_circle3.m_X < wall_xC) {
		DrawFormatString(150, 50, Red, "px:%3f py:%3%f", t_circle1.m_X, t_circle1.m_Y);
	}
	else if (t_circle3.m_X > wall_xC) 
	{
		DrawFormatString(150, 50, Blue, "px:%3f py:%3%f", t_circle1.m_X, t_circle1.m_Y);
	}
	
};

////////�����蔻��t���O//////
//�v���C���[�ƃp�b�N�̓����蔻��
bool AirHockey_Scene::Player_Puck_Check_Hit() {
	//�O�����̒藝
	float a = t_circle1.m_X - t_circle3.m_X;
	float b = t_circle1.m_Y - t_circle3.m_Y;
	float c = a * a + b * b;
	float sum_radius = t_circle1.m_R + t_circle3.m_R;
	if (c < sum_radius * sum_radius) {
		return true;
	}
	return false;
};

//�v���C���[�ƕǂ̓����蔻��
bool AirHockey_Scene::Player_Wall_Check_Hit() {
	//�Փ˓_�����E�㉺�ݒ�
	t_circle1.m_r = t_circle1.m_X + t_circle1.m_R; //�E
	t_circle1.m_l = t_circle1.m_X - t_circle1.m_R; //��
	t_circle1.m_b = t_circle1.m_Y + t_circle1.m_R; //��
	t_circle1.m_t = t_circle1.m_Y - t_circle1.m_R; //��

	if (wall_L > t_circle1.m_l || wall_xC < t_circle1.m_r) {
		return true;
	}
	if (wall_B < t_circle1.m_b || wall_T > t_circle1.m_t) {
		return true;
	}
	return false;
};

//CPU�ƃp�b�N�̏Փ˔���
bool AirHockey_Scene::CPU_Puck_Check_Hit() {
	//�O�����̒藝
	float a = t_circle2.m_X - t_circle3.m_X;
	float b = t_circle2.m_Y - t_circle3.m_Y;
	float c = a * a + b * b;
	float sum_radius = t_circle2.m_R + t_circle3.m_R;
	if (c < sum_radius * sum_radius) {
		return true;
	}
	return false;
}

//�p�b�N�ƕǂ̓����蔻��
bool AirHockey_Scene::Puck_Wall_Check_Hit() {
	//�Փ˓_���l�����ɐݒ�
	t_circle3.m_r = t_circle3.m_X + t_circle3.m_R;//�E
	t_circle3.m_l = t_circle3.m_X - t_circle3.m_R;//��
	t_circle3.m_b = t_circle3.m_Y + t_circle3.m_R;//��
	t_circle3.m_t = t_circle3.m_Y - t_circle3.m_R;//��

	if (wall_yC - 90 > t_circle3.m_t || wall_yC + 90 < t_circle3.m_b) {
		if (wall_L > t_circle3.m_l || wall_R < t_circle3.m_X + t_circle3.m_R /2 ) {
			return true;
		}
	}
	if (wall_T > t_circle3.m_t || wall_B < t_circle3.m_b) {
		return true;
	}
	if (wall_R < t_circle3.m_X + t_circle3.m_R / 2 || wall_L > t_circle3.m_X - t_circle3.m_R / 2) {
		if (wall_yC - 90 > t_circle3.m_t || wall_yC + 90 < t_circle3.m_b) {
			return true;
		}
	}
	return false;
};
////////////�����܂�////////////

///////////�ړ������t���O/////////////

//*****�v���C���[******
bool AirHockey_Scene::Player_Move_Right() {//�E�Ɉړ���
	if (t_circle1.m_X < mouseX) {
		return true;
	}
	return false;
}

bool AirHockey_Scene::Player_Move_Left() {//���Ɉړ���
	if (t_circle1.m_X > mouseX) {
		return	true;
	}
	return false;
}

bool AirHockey_Scene::Player_Move_Up() {//��Ɉړ���
	if (t_circle1.m_Y > mouseY) {
		return true;
	}
	return false;
}

bool AirHockey_Scene::Player_Move_Under() {//���Ɉړ���
	if (t_circle1.m_Y < mouseY) {
		return true;
	}
	return false;
}

//*******CPU********
bool AirHockey_Scene::CPU_Move_Right() {//�E�Ɉړ���
	if (0.0f < t_circle2.X_spd) {
		return true;
	}
	return false;
}

bool AirHockey_Scene::CPU_Move_Left() {//���Ɉړ���
	if (0.0f > t_circle2.X_spd) {
		return true;
	}
	return false;
}

bool AirHockey_Scene::CPU_Move_Up() {//��Ɉړ���
	if (0.0f > t_circle2.Y_spd) {
		return true;
	}
	return false;
}

bool AirHockey_Scene::CPU_Move_Under() {//���Ɉړ���
	if (0.0f < t_circle2.Y_spd) {
		return true;
	}
	return false;
}
/////////�����܂�//////////

///////�p�b�N�ʒu�t���O//////////
//*****�v���C���[���猩�ăp�b�N���ǂ��Ɉʒu���Ă��邩�̃t���O(8����)*****
bool AirHockey_Scene::PlayerBase_PuckPosition_Up() { //��
	if (t_circle1.m_Y > t_circle3.m_Y) {
		if (t_circle3.m_X > t_circle1.m_X - t_circle1.m_R / 2 && t_circle3.m_X < t_circle1.m_X + t_circle1.m_R / 2) {
			return true;
		}
	}
	return false;
}

bool AirHockey_Scene::PlayerBase_PuckPosition_UpperRight() {//�E��
	if (t_circle3.m_X > t_circle1.m_X + t_circle1.m_R / 2 && t_circle3.m_Y < t_circle1.m_Y - t_circle1.m_R / 2) {
			return true;
	}
	return false;
};

bool AirHockey_Scene::PlayerBase_PuckPosition_Right() {//�E
	if (t_circle1.m_X < t_circle3.m_X) {
		if (t_circle3.m_Y > t_circle1.m_Y - t_circle1.m_R / 2 && t_circle3.m_Y < t_circle1.m_Y + t_circle1.m_R / 2) {
			return true;
		}
	}
	return false;
};

bool AirHockey_Scene::PlayerBase_PuckPosition_UnderRight() {//�E��
	if (t_circle3.m_Y > t_circle1.m_Y + t_circle1.m_R / 2 && t_circle3.m_X > t_circle1.m_X + t_circle1.m_R / 2) {
		return true;
	}
	return false;
};

bool AirHockey_Scene::PlayerBase_PuckPosition_Under() {//��
	if (t_circle1.m_Y < t_circle3.m_Y) {
		if (t_circle3.m_X > t_circle1.m_X - t_circle1.m_R / 2 && t_circle3.m_X < t_circle1.m_X + t_circle1.m_R / 2) {
			return true;
		}
		return false;
	}
};

bool AirHockey_Scene::PlayerBase_PuckPosition_UnderLeft() {//����
	if (t_circle3.m_X < t_circle1.m_X - t_circle1.m_R / 2 && t_circle3.m_Y > t_circle1.m_Y + t_circle1.m_R / 2) {
		return true;
	}
	return false;
};
bool AirHockey_Scene::PlayerBase_PuckPosition_Left() {//��
	if (t_circle1.m_X > t_circle3.m_X) {
		if (t_circle3.m_Y < t_circle1.m_Y + t_circle1.m_R / 2 && t_circle3.m_Y > t_circle1.m_Y - t_circle1.m_R / 2) {
			return true;
		}
	}
	return false;
};
bool AirHockey_Scene::PlayerBase_PuckPosition_UpperLeft() {//����
	if (t_circle3.m_Y < t_circle1.m_Y - t_circle1.m_R / 2 && t_circle3.m_X < t_circle1.m_X - t_circle1.m_R) {
		return true;
	}
	return false;
};

//*****CPU���猩�ăp�b�N���ǂ��Ɉʒu���Ă��邩�̃t���O(8����)*******
bool AirHockey_Scene::CPUBase_PuckPosition_Up() { //��
	if (t_circle2.m_Y > t_circle3.m_Y) {
		if (t_circle3.m_X > t_circle2.m_X - t_circle2.m_R / 2 && t_circle3.m_X < t_circle2.m_X + t_circle2.m_R / 2) {
			return true;
		}
	}
	return false;
}

bool AirHockey_Scene::CPUBase_PuckPosition_UpperRight() {//�E��
	if (t_circle3.m_X > t_circle2.m_X + t_circle2.m_R / 2 && t_circle3.m_Y < t_circle2.m_Y - t_circle2.m_R / 2) {
			return true;
	}
	return false;
};

bool AirHockey_Scene::CPUBase_PuckPosition_Right() {//�E
	if (t_circle2.m_X < t_circle3.m_X) {
		if (t_circle3.m_Y > t_circle2.m_Y - t_circle2.m_R / 2 && t_circle3.m_Y < t_circle2.m_Y + t_circle2.m_R / 2) {
			return true;
		}
	}
	return false;
};

bool AirHockey_Scene::CPUBase_PuckPosition_UnderRight() {//�E��
	if (t_circle3.m_Y > t_circle2.m_Y + t_circle2.m_R / 2 && t_circle3.m_X > t_circle2.m_X + t_circle2.m_R / 2) {
		return true;
	}
	return false;
};

bool AirHockey_Scene::CPUBase_PuckPosition_Under() {//��
	if (t_circle2.m_Y < t_circle3.m_Y) {
		if (t_circle3.m_X > t_circle2.m_X - t_circle2.m_R / 2 && t_circle3.m_X < t_circle2.m_X + t_circle2.m_R / 2) {
			return true;
		}
		return false;
	}
};

bool AirHockey_Scene::CPUBase_PuckPosition_UnderLeft() {//����
	if (t_circle3.m_X < t_circle2.m_X - t_circle2.m_R / 2 && t_circle3.m_Y > t_circle2.m_Y + t_circle2.m_R / 2) {
		return true;
	}
	return false;
};
bool AirHockey_Scene::CPUBase_PuckPosition_Left() {//��
	if (t_circle2.m_X > t_circle3.m_X) {
		if (t_circle3.m_Y < t_circle2.m_Y + t_circle2.m_R / 2 && t_circle3.m_Y > t_circle2.m_Y - t_circle2.m_R / 2) {
			return true;
		}
	}
	return false;
};
bool AirHockey_Scene::CPUBase_PuckPosition_UpperLeft() {//����
	if (t_circle3.m_Y < t_circle2.m_Y - t_circle2.m_R / 2 && t_circle3.m_X < t_circle2.m_X - t_circle2.m_R) {
		return true;
	}
	return false;
};
///////////�ړ�������Փˎ��̏�������܂Ƃ�//////////
//�v���C���[���ǂƃp�b�N�ɏՓˎ��̂��ꂼ��̏���
void  AirHockey_Scene::Player_Hit() {

	if (Player_Wall_Check_Hit() == true)//�v���C���[�ƕǂ��Փ˂����ꍇ
	{
		if (wall_L > t_circle1.m_l) {	//�����߂������@�Ȃ񂩃K�N�K�N����
			t_circle1.m_X += 2.0f;
		}
		else if (wall_xC < t_circle1.m_r) {
			t_circle1.m_X -= 2.0f;
		}
		if (wall_T > t_circle1.m_t) {
			t_circle1.m_Y += 2.0f;
		}
		else if (wall_B < t_circle1.m_b) {
			t_circle1.m_Y -= 2.0f;
		}
	}
	else {
		Player_Control();//�Փ˂��Ă��Ȃ��Ȃ瓮����
	}

	if (Player_Puck_Check_Hit() == true) {	//�v���C���[�ƃp�b�N���Փ˂�����

		t_circle3.X_spd *= -1.0f;//��������
		t_circle3.Y_spd *= -1.0f;//�c������

		if (Player_Move_Right() == true) {//�v���C���[���E�Ɉړ����Ă�����******************
			if (PlayerBase_PuckPosition_Up() == true) {//�p�b�N���v���C���[�̏�Ɉʒu���Ă�����
				if (0.0f <= t_circle3.X_spd) {//�p�b�N�̉��Z���x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if(0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {//-x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else 
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UpperRight() == true){
				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else 
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Right() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UnderRight() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Under() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UnderLeft()==true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Left()==true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UpperLeft() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			
		}

		if (Player_Move_Left() == true) {//�v���C���[�����Ɉړ����Ă�����****************
			if (PlayerBase_PuckPosition_Up() == true) {
			

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UpperRight() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Right() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UnderRight() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Under() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UnderLeft() == true) {
				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Left() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UpperLeft() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
		}

		if (Player_Move_Up() == true) {//�v���C���[����Ɉړ����Ă�����**************
			if (PlayerBase_PuckPosition_Up() == true) {

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UpperRight() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Right() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UnderRight() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Under() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UnderLeft() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Left() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UpperLeft() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
		}

		if (Player_Move_Under() == true){//�v���C���[�����Ɉړ����Ă�����***************
			if (PlayerBase_PuckPosition_Up() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UpperRight() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Right() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UnderRight() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Under() == true) {

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UnderLeft() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_Left() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
			if (PlayerBase_PuckPosition_UpperLeft() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
		}

	}
}

//CPU
void AirHockey_Scene::CPU_Movement() {
	//CPU�̎v�l�V�[�P���X
	if (Resalt() == false) {//�������̊�
		





	}

	if (CPU_Puck_Check_Hit() == true) {

		t_circle3.X_spd *= -1.0f;//x������
		t_circle3.Y_spd *= -1.0f;//y������

		if (CPU_Move_Right() == true) {//CPU���E�Ɉړ����Ă�����******************
			if (CPUBase_PuckPosition_Up() == true) {//�p�b�N���v���C���[�̏�Ɉʒu���Ă�����
				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (CPUBase_PuckPosition_UpperRight() == true) {
				if (0.0f <= t_circle3.X_spd) 
				{
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) 
				{
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) 
					{
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) 
					{
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (CPUBase_PuckPosition_Right() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}
			}
			if (CPUBase_PuckPosition_UnderRight() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (CPUBase_PuckPosition_Under() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (CPUBase_PuckPosition_UnderLeft() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
			}
			if (CPUBase_PuckPosition_Left() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
			}
			if (CPUBase_PuckPosition_UpperLeft() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
		}

		if (Player_Move_Left() == true) {//�v���C���[�����Ɉړ����Ă�����****************
			if (CPUBase_PuckPosition_Up() == true) {


				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UpperRight() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_Right() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UnderRight() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}

				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_Under() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UnderLeft() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}

				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_Left() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UpperLeft() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}

				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
		}

		if (Player_Move_Up() == true) {//�v���C���[����Ɉړ����Ă�����**************
			if (CPUBase_PuckPosition_Up() == true) {

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UpperRight() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}

				t_circle3.X_spd *= -1.0f;//x������
				t_circle3.Y_spd *= -1.0f;//y������
			}
			if (CPUBase_PuckPosition_Right() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UnderRight() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}

				t_circle3.X_spd *= -1.0f;//x������
				t_circle3.Y_spd *= -1.0f;//y������
			}
			if (CPUBase_PuckPosition_Under() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UnderLeft() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//x������
				t_circle3.Y_spd *= -1.0f;//y������
			}
			if (CPUBase_PuckPosition_Left() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UpperLeft() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//x������
				t_circle3.Y_spd *= -1.0f;//y������
			}
		}

		if (Player_Move_Under() == true) {//�v���C���[�����Ɉړ����Ă�����***************
			if (CPUBase_PuckPosition_Up() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UpperRight() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//x������
				t_circle3.Y_spd *= -1.0f;//y������
			}
			if (CPUBase_PuckPosition_Right() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UnderRight() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//x������
				t_circle3.Y_spd *= -1.0f;//y������
			}
			if (CPUBase_PuckPosition_Under() == true) {

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UnderLeft() == true) {

				if (0.0f <= t_circle3.X_spd) {
					if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundPx) {//+x��
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.X_spd) {
					if (t_circle3.Maxspd * -1.0f < t_circle3.X_spd + t_circle3.m_boundPx * -1.0f) {
						t_circle3.X_spd + t_circle3.m_boundPx * -1.0f;
					}
					else
					{
						t_circle3.X_spd = t_circle3.Maxspd *= -1.0f;
					}
				}

				if (0.0f <= t_circle3.Y_spd) {//���̒l��������
					if (t_circle3.Maxspd >= t_circle3.Y_spd + t_circle3.m_boundPy) {//y��
						t_circle3.Y_spd += t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (t_circle3.Maxspd * -1.0f > t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f) {
						t_circle3.Y_spd + t_circle3.m_boundPy * -1.0f;
					}
					else
					{
						t_circle3.Y_spd = t_circle3.Maxspd * -1.0f;
					}
				}

				t_circle3.X_spd *= -1.0f;//x������
				t_circle3.Y_spd *= -1.0f;//y������
			}
			if (CPUBase_PuckPosition_Left() == true) {

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
				t_circle3.X_spd *= -1.0f;//��������
				t_circle3.Y_spd *= -1.0f;//�c������
			}
			if (CPUBase_PuckPosition_UpperLeft() == true) {

				if (0.0f < t_circle3.X_spd) {//�p�b�N�̑��x�����̒l��������(�p�b�N���E�Ɉړ���)
					if (0.0f < t_circle3.X_spd - t_circle3.m_boundPx) {//+x�� �Œ�l�^�C�v
						t_circle3.X_spd -= t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.X_spd)//�p�b�N�̑��x�����̒l��������(�p�b�N�����Ɉړ���)
				{
					if (0.0f > t_circle3.X_spd + t_circle3.m_boundPx) {
						t_circle3.X_spd += t_circle3.m_boundPx;
					}
					else
					{
						t_circle3.X_spd = 0.0f;
					}
				}

				if (0.0f < t_circle3.Y_spd) {
					if (0.0f < t_circle3.Y_spd - t_circle3.m_boundPy) {//y�� �Œ�l�^�C�v
						t_circle3.Y_spd -= t_circle3.m_boundPy;
					}
					else
					{
						t_circle3.Y_spd = 0.0f;
					}
				}
				else if (0.0f > t_circle3.Y_spd)
				{
					if (0.0f > t_circle3.Y_spd + t_circle3.m_boundPy) {
						t_circle3.Y_spd + t_circle3.Maxspd;
					}
					else {
						t_circle3.Y_spd = 0.0f;
					}
				}
			}
		}

	}
}

//�p�b�N
void  AirHockey_Scene::Puck_Movement() {

	t_circle3.m_X += t_circle3.X_spd;
	t_circle3.m_Y += t_circle3.Y_spd;

	if (Player_Puck_Check_Hit ()== true) 
	{
		if (Player_Move_Right()==true) 
		{
			if (t_circle1.m_X < t_circle3.m_X) {
				t_circle3.m_X += t_circle1.X_spd;
			}
		}

		if (Player_Move_Left()==true) 
		{
			if (t_circle1.m_X > t_circle3.m_X) {
				t_circle3.m_X -= t_circle1.X_spd;
			}
		}

		if (Player_Move_Up()== true) 
		{
			if (t_circle1.m_Y > t_circle3.m_Y) {
				t_circle3.m_Y -= t_circle1.Y_spd;
			}
		}

		if (Player_Move_Under()==true) 
		{
			if (t_circle1.m_Y < t_circle3.m_Y) {
				t_circle3.m_Y += t_circle1.Y_spd;
			}
		}
	}

	if (CPU_Puck_Check_Hit()==true) {
		if (CPU_Move_Right() == true)
		{
			if (t_circle2.m_X < t_circle3.m_X) {
				t_circle3.m_X += t_circle2.X_spd;
			}
		}

		if (CPU_Move_Left() == true)
		{
			if (t_circle2.m_X > t_circle3.m_X) {
				t_circle3.m_X -= t_circle2.X_spd;
			}
		}

		if (CPU_Move_Up() == true)
		{
			if (t_circle2.m_Y > t_circle3.m_Y) {
				t_circle3.m_Y -= t_circle2.Y_spd;
			}
		}

		if (CPU_Move_Under() == true)
		{
			if (t_circle2.m_Y < t_circle3.m_Y) {
				t_circle3.m_Y += t_circle2.Y_spd;
			}
		}
	}

	/*if (t_circle3.X_spd == 0 && t_circle3.Y_spd == 0) {
		if (t_circle3.m_X > wall_xC) {
			Status_Reset();
		}
	}*/

	//��~����܂Ō�����������
	if (0.0f < t_circle3.X_spd) {//���̒l��������
		t_circle3.X_spd -= 0.01f;//����
	}
	else {						//���̒l��������
		t_circle3.X_spd += 0.01f;//����
	};

	if (0.0f < t_circle3.Y_spd) {
		t_circle3.Y_spd -= 0.01f;
	}
	else {
		t_circle3.Y_spd += 0.01f;
	};

	//�S�[���ɓ�������
	if (wall_R < t_circle3.m_l || wall_L > t_circle3.m_r) {
		if (wall_xC < t_circle3.m_X) {//�v���C���[���S�[��
			score1 += 1;
			Status_Reset();
			t_circle3.m_X + 50.0f;
		}
		else//CPU���S�[��
		{
			score2 += 1;
			Status_Reset();
			t_circle3.m_X - 50.0f;
		}
	}

	if (Puck_Wall_Check_Hit() == true) {//�ǂɂԂ�������

		if (wall_R < t_circle3.m_r) {
			t_circle3.m_X -= t_circle3.m_R;//�E
			t_circle3.X_spd *= -1.0f;//��������
		}
		if (wall_L > t_circle3.m_l) {
			t_circle3.m_X += t_circle3.m_R;//��
			t_circle3.X_spd *= -1.0f;//��������
		}

		if (wall_B < t_circle3.m_b) {
			t_circle3.m_Y -= t_circle3.m_R;//��
			t_circle3.Y_spd *= -1.0f;//�c������
		}
		if (wall_T > t_circle3.m_t) {
			t_circle3.m_Y += t_circle3.m_R;//��
			t_circle3.Y_spd *= -1.0f;//�c������
		}

		if (wall_R < t_circle3.m_X + t_circle3.m_R / 2 || wall_L > t_circle3.m_X - t_circle3.m_R / 2) {//�S�[���Ƀp�b�N��
			//�S�[������y������
				if (wall_yC - 90 < t_circle3.m_b) {
					t_circle3.m_Y -= t_circle3.m_R;//��
					t_circle3.Y_spd *= -1.0f;//�c������
				}
				if (wall_yC + 90 > t_circle3.m_t) {
					t_circle3.m_Y += t_circle3.m_R;//��
					t_circle3.Y_spd *= -1.0f;//�c������
				}
		}
		else//�����ĂȂ�������
		{
			t_circle3.m_X -= t_circle3.m_R;//�E
			t_circle3.X_spd *= -1.0f;//��������
			t_circle3.m_X += t_circle3.m_R;//��
			t_circle3.X_spd *= -1.0f;//��������
			t_circle3.m_Y -= t_circle3.m_R;//��
			t_circle3.Y_spd *= -1.0f;//�c������
			t_circle3.m_Y += t_circle3.m_R;//��
			t_circle3.Y_spd *= -1.0f;//�c������
		}
	}
};

//�v���C���[�����ړ�����
void AirHockey_Scene::Player_Control() {
	GetMousePoint(&mouseX, &mouseY);//�}�E�X���W��int�^�Ŏ擾
	//�}�E�X���W�ƃ}���b�g�̒��S���W������Ă�����}���b�g�����獷�𖄂߂鏈��
	//��a���̂Ȃ��`��ƒ��悢�ړ����x�m�ۂ̌��ˍ��������Ȃ� �v�����W
	// for���ō��ƕǂɎh����̂ň�Uif���d�˂ĕۗ�

	//�E�ړ�

		if (Player_Puck_Check_Hit()==false) 
		{
			if (t_circle1.m_X < mouseX) 
			{
				for (int count = 0; count < 3; count++)
				{
					if (wall_xC > t_circle1.m_r + t_circle1.X_spd) 
					{
						t_circle1.m_X += t_circle1.X_spd;
					}
					else
					{
						if (wall_R > t_circle1.m_r + wall_xC - t_circle1.m_r) 
						{
							t_circle1.m_X += wall_xC - t_circle1.m_r;
						}
					};
				}
			}



			//���ړ�
			if (t_circle1.m_X > mouseX) 
			{
				for (int count = 0; count < 3; count++)
				{
					if (wall_L < t_circle1.m_l - t_circle1.X_spd) 
{
						t_circle1.m_X -= t_circle1.X_spd;
					}
					else
					{
						if (wall_L < t_circle1.m_l - t_circle1.m_l - wall_L) 
						{
							t_circle1.m_X -= t_circle1.m_l - wall_L;
						}
					};
				}
			}

			//���ړ�
			if (t_circle1.m_Y < mouseY) {
				for (int count = 0; count < 3; count++)
				{
					if (wall_B > t_circle1.m_b + t_circle3.Y_spd)
					{
						t_circle1.m_Y += t_circle1.Y_spd;
					}
					else
					{
						if (wall_B > t_circle1.m_b + wall_B - t_circle1.m_b)
						{
							t_circle1.m_Y += wall_B - t_circle1.m_b;
						}
					}
				}
			}

			//��ړ�
			if (t_circle1.m_Y > mouseY)
			{
				for (int count = 0; count < 3; count++)
				{
					if (wall_T < t_circle1.m_t - t_circle1.Y_spd)
					{
						t_circle1.m_Y -= t_circle1.Y_spd;
					}
					else
					{
						if (wall_T < t_circle1.m_t - t_circle1.m_t - wall_T)
						{
							t_circle1.m_Y -= t_circle1.m_t - wall_T;
						}
					}
				}
			}
		}
}

/////////�����܂�/////////

void AirHockey_Scene::AirHockey_Update(){
	Player_Hit();
	Puck_Movement();
	CPU_Movement();
	if (Resalt() == true) {
		if (score1 > score2) 
		{
				Parent->SetNext(new Title_Select());    // �Z���N�g�V�[���Ɉړ�
		}
		else
		{
				Parent->SetNext(new Title_Select());    // �Z���N�g�V�[���Ɉړ�
		}
	}
}

void AirHockey_Scene::AirHockey_Draw() {
	Draw_All();
}

void AirHockey_Scene::Draw_All() {
	//Debug_Data();//*****************�f�o�b�N�\��********************//

	DrawLine(wall_xC, wall_T, wall_xC, wall_B, Yellow);//���S��
	DrawOvalAA(wall_L, wall_yC, 20, 90, 30, DarkRed, TRUE);//�v���C���[�S�[����
	DrawOvalAA(wall_R, wall_yC, 20, 90, 30, DarkBule, TRUE);//CPU�S�[����
	DrawCircleAA(wall_xC, wall_yC, 100, 30, Yellow, FALSE);//���S�~
	DrawBox(wall_L - 20, wall_yC - 100, wall_L + 1, wall_yC + 101, Black, TRUE);	//�͂ݏo�������S�[�����㏑��
	DrawBox(wall_R, wall_yC - 101, wall_R + 21, wall_yC + 101, Black, TRUE);    //�͂ݏo���E���S�[�����㏑��
	DrawBox(wall_L, wall_T, wall_R, wall_B, White, FALSE);							//�t�B�[���h��
	DrawBox(wall_L - 10, wall_T - 10, wall_R + 11, wall_B + 11, White, FALSE);	//�t�B�[���h��

	if (Resalt() == false) {

		DrawCircleAA(t_circle3.m_X, t_circle3.m_Y, t_circle3.m_R, 30, Purple, 1);	//�p�b�N
		DrawCircleAA(t_circle1.m_X, t_circle1.m_Y, t_circle1.m_R, 30, Red);			//�v���C���[
		DrawCircleAA(t_circle2.m_X, t_circle2.m_Y, t_circle2.m_R, 30, Blue);		//CPU


		//Effect();
		DrawFormatString(wall_xC - 50, wall_T - 50, White, "%d - %d", score1, score2);//���_
	}
}