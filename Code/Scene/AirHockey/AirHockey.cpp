#include <DxLib.h>
#include "AirHockey.h"

void AirHockey_Scene::AirHockey_Initialize() {

	//�F�錾
	 White = GetColor(255, 255, 255);
	 Red = GetColor(255, 50, 50);
	 Bule = GetColor(50, 50, 255);
	//int Green = GetColor(50, 255, 50);
	 Yellow = GetColor(255, 255, 50);
	 Purple = GetColor(218, 112, 214);
	 Black = GetColor(0, 0, 0);

	 mouseX, mouseY;//�}�E�X�̍��W���i�[

	//Circle t_circle1, t_circle2, t_circle3;//�~�̍\���̂��O���̉�

	//�v���C���[�ACPU�̏����ʒu�Ɣ��a��ݒ� �p�b�N�͉����ă}���b�g����̉^���ʁAX�AY���̑��x�A���x�����ݒ�
	Status_Reset();
}

void AirHockey_Scene::Status_Reset() {
	t_circle1.m_X = 80.0f, t_circle1.m_Y = 150.0f, t_circle1.m_R = 18.0f;	//�v���C���[
	t_circle2.m_X = 560.0f, t_circle2.m_Y = 150.0f, t_circle2.m_R = 18.0f;	//CPU
	t_circle3.m_X = 320.0f, t_circle3.m_Y = 150.0f, t_circle3.m_R = 15.0f, t_circle3.m_boundP = 6.0f, t_circle3.X_spd = 0.0f, t_circle3.Y_spd = 0.0f, t_circle3.Maxspd = 15.0f;	//�p�b�N
};

////////�����蔻��֐��V���[�Y//////

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
	t_circle1.m_r = t_circle1.m_X + t_circle1.m_R; //�E
	t_circle1.m_l = t_circle1.m_X - t_circle1.m_R; //��
	t_circle1.m_b = t_circle1.m_Y + t_circle1.m_R; //��
	t_circle1.m_t = t_circle1.m_Y - t_circle1.m_R; //��

	if (50 > t_circle1.m_l || 320 < t_circle1.m_r) {
		return true;
	}
	if (100 > t_circle1.m_b || 400 < t_circle1.m_t) {
		return true;
	}
	return false;
};

//�p�b�N�ƕǂ̓����蔻��
bool AirHockey_Scene::Puck_Wall_Check_Hit() {
	t_circle3.m_r = t_circle3.m_X + t_circle3.m_R;//�E
	t_circle3.m_l = t_circle3.m_X - t_circle3.m_R;//��
	t_circle3.m_b = t_circle3.m_Y + t_circle3.m_R;//��
	t_circle3.m_t = t_circle3.m_Y - t_circle3.m_R;//��

	if (50 > t_circle3.m_l || 590 < t_circle3.m_r) {
		return true;
	}
	if (100 > t_circle3.m_t || 400 < t_circle3.m_b) {
		return true;
	}
	return false;
};
////////////�����܂�////////////



///////////�ړ�������ړ��n�̏�������܂Ƃ�//////////


//�v���C���[���ǂƃp�b�N�ɏՓˎ��̂��ꂼ��̏���
void  AirHockey_Scene::Player_Hit() {

	if (Player_Wall_Check_Hit() == true)		//�v���C���[�ƕǂ̏Փ˂����m�����ꍇ
	{
		//DrawFormatString(0, 0, Red, "x:%d y:%d", mouseX, mouseY);
		if (50 > t_circle1.m_l) {	//�����߂������@�Ȃ񂩃K�N�K�N����
			t_circle1.m_X += 2.0f;
		}
		else if (320 < t_circle1.m_r) {
			t_circle1.m_X -= 2.0f;
		}
		if (100 > t_circle1.m_t) {
			t_circle1.m_Y += 2.0f;
		}
		else if (400 < t_circle1.m_b) {
			t_circle1.m_Y -= 2.0f;
		}
	}
	else {
		//DrawFormatString(0, 0, White, "x:%d y:%d", mouseX, mouseY);
		Player_Control();					//�Փ˂��Ă��Ȃ��Ȃ瓮����
	}



	if (Player_Puck_Check_Hit() == true) {	//�v���C���[�ƃp�b�N�̏Փ˂�����
		//DrawFormatString(0, 0, Purple, "x:%d y:%d", mouseX, mouseY);

		if (t_circle1.m_X != mouseX) {

			if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundP) { //�p�b�N�̑��x������p�b�N�̑��x�Ɖ��Z���x�����킹�����x������Ȃ����
				t_circle3.X_spd += t_circle3.m_boundP;					   //�p�b�N��X���x�ɉ��Z���x�𑫂�
			}
			else {														   //���x����������Ă�����
				t_circle3.X_spd = t_circle3.X_spd + t_circle3.m_boundP - t_circle3.X_spd + t_circle3.m_boundP - t_circle3.Maxspd;//(������x����I�[�o�[��������������) ������x�Ɠ������x�ɒu��������
			}
		}
		else {
			t_circle3.X_spd *= -1.0f;//��������
			t_circle3.Y_spd *= -1.0f;//�c������
		}

		if (t_circle1.m_Y != mouseY) {

			if (t_circle3.Maxspd > t_circle3.Y_spd + t_circle3.m_boundP) {//��L������?���o�[�W����
				t_circle3.Y_spd += t_circle3.m_boundP;
			}
			else {
				t_circle3.Y_spd = t_circle3.Y_spd + t_circle3.m_boundP - t_circle3.Y_spd + t_circle3.m_boundP - t_circle3.Maxspd;
			}
		}
		else {
			t_circle3.X_spd *= -1.0f;//��������
			t_circle3.Y_spd *= -1.0f;//�c������
		}
	}
}

//�p�b�N
void  AirHockey_Scene::Puck_Move() {

	//��~����܂Ō�����������
	if (0.0f < t_circle3.X_spd) {
		t_circle3.X_spd -= 0.01f;
	}
	if (0.0f < t_circle3.Y_spd) {
		t_circle3.Y_spd -= 0.01f;
	}

	if (Puck_Wall_Check_Hit() == true) {

		if (590 < t_circle3.m_r) {
			t_circle3.m_X -= t_circle3.m_R;//�E
			t_circle3.X_spd *= -1.0f;//��������
		}
		if (50 > t_circle3.m_l) {
			t_circle3.m_X += t_circle3.m_R;//��
			t_circle3.X_spd *= -1.0f;//��������
		}
		if (400 < t_circle3.m_b) {
			t_circle3.m_Y -= t_circle3.m_R;//��
			t_circle3.Y_spd *= -1.0f;//�c������
		}
		if (100 > t_circle3.m_t) {
			t_circle3.m_Y += t_circle3.m_R;//��
			t_circle3.Y_spd *= -1.0f;//�c������
		}
	}
	else {
		if (590 > t_circle3.m_r + t_circle3.X_spd && 50 < t_circle3.m_l - t_circle3.X_spd) {
			t_circle3.m_X += t_circle3.X_spd;
		}
		else {
			t_circle3.m_X += t_circle3.X_spd - 1.0f;
		}
		if (400 > t_circle3.m_Y + t_circle3.Y_spd && 100 < t_circle3.m_Y - t_circle3.Y_spd) {
			t_circle3.m_Y += t_circle3.Y_spd;
		}
		else {
			t_circle3.m_Y += t_circle3.Y_spd - 1.0f;
		}
	}
};

//�v���C���[�����ړ�����
void AirHockey_Scene::Player_Control() {
	GetMousePoint(&mouseX, &mouseY);//�}�E�X���W��int�^�Ŏ擾
	//�}�E�X���W�ƃv���C���[�̒��S���W������Ă�����v���C���[�����獷�𖄂߂鏈��
	// for���ō��ƕǂɎh����̂ň�Uif���d�˂đË�

	//�E�ړ�
	if (t_circle1.m_X < mouseX) {

		if (320 > t_circle1.m_r + 3.0f) {
			t_circle1.m_X += 3.0f;

			/*	if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
					t_circle3.m_X += t_circle3.X_spd;
				}*/

			if (320 > t_circle1.m_r + 3.0f) {
				t_circle1.m_X += 3.0f;

				/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
					t_circle3.m_X += t_circle3.X_spd;
				}*/

				if (320 > t_circle1.m_r + 3.0f) {
					t_circle1.m_X += 3.0f;

					/*		if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
								t_circle3.m_X += t_circle3.X_spd;
							}*/

					if (320 > t_circle1.m_r + 0.5f) {
						t_circle1.m_X += 0.5f;

						/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
							t_circle3.m_X += t_circle3.X_spd;
						}*/
					}
				}
			}
		}
	}

	//���ړ�
	if (t_circle1.m_X > mouseX) {

		if (50 < t_circle1.m_l - 3.0f) {
			t_circle1.m_X -= 3.0f;

			/*if (Player_Puck_Check_Hit()== true && 0.0f == t_circle3.X_spd) {
				t_circle3.m_X -= t_circle3.X_spd;
			}*/

			if (50 < t_circle1.m_l - 3.0f) {
				t_circle1.m_X -= 3.0f;

				/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
					t_circle3.m_X -= t_circle3.X_spd;
				}*/

				if (50 < t_circle1.m_l - 3.0f) {
					t_circle1.m_X -= 3.0f;

					/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
						t_circle3.m_X -= t_circle3.X_spd;
					}*/

					if (50 > t_circle1.m_l - 0.5f) {
						t_circle1.m_X -= 0.5f;

						/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
							t_circle3.m_X -= t_circle3.X_spd;
						}*/
					}
				}
			}
		}
	}

	//���ړ�
	if (t_circle1.m_Y < mouseY) {

		if (400 > t_circle1.m_b + 3.0f) {
			t_circle1.m_Y += 3.0f;

			/*if (Player_Puck_Check_Hit()== true && 0.0f == t_circle3.Y_spd) {
				t_circle3.m_Y += t_circle3.Y_spd;
			}*/

			if (400 > t_circle1.m_b + 3.0f) {
				t_circle1.m_Y += 3.0f;

				//if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
				//	t_circle3.m_Y += t_circle3.Y_spd;
				//}

				if (400 > t_circle1.m_b + 3.0f) {
					t_circle1.m_Y += 3.0f;

					/*	if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
							t_circle3.m_Y += t_circle3.Y_spd;
						}*/

					if (400 > t_circle1.m_b + 0.5f) {
						t_circle1.m_Y += 0.5f;

						/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
							t_circle3.m_Y += t_circle3.Y_spd;
						}*/
					}
				}
			}
		}
	}

	//��ړ�
	if (t_circle1.m_Y > mouseY) {

		if (100 < t_circle1.m_t - 3.0f) {
			t_circle1.m_Y -= 3.0f;

			/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
				t_circle3.m_Y -= t_circle3.Y_spd;
			}*/

			if (100 < t_circle1.m_t - 3.0f) {
				t_circle1.m_Y -= 3.0f;

				/*	if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
						t_circle3.m_Y -= t_circle3.Y_spd;
					}*/

				if (100 < t_circle1.m_t - 3.0f) {
					t_circle1.m_Y -= 3.0f;

					/*	if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
							t_circle3.m_Y -= t_circle3.Y_spd;
						}*/

					if (100 < t_circle1.m_t - 0.5f) {
						t_circle1.m_Y -= 0.5f;

						/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
							t_circle3.m_Y -= t_circle3.Y_spd;
						}*/
					}
				}
			}
		}
	}
}

/////////�����܂�/////////

//�`��

void AirHockey_Scene::AirHockey_Update(){
	Player_Hit();
	Puck_Move();
}
void AirHockey_Scene::AirHockey_Draw() {
	Draw_All();
}
void AirHockey_Scene::Draw_All() {
	DrawLine(320, 101, 320, 400, Yellow);//���S��
	DrawOvalAA(50, 250, 18, 55, 25, Red, FALSE);//�v���C���[�S�[����
	DrawOvalAA(590, 250, 18, 55, 25, Bule, FALSE);//CPU�S�[����
	DrawCircleAA(320, 250, 80, 30, Yellow, FALSE);//���S�~

	DrawCircleAA(t_circle3.m_X, t_circle3.m_Y, t_circle3.m_R, 30, Purple, 1);//�p�b�N
	DrawCircleAA(t_circle1.m_X, t_circle1.m_Y, t_circle1.m_R, 30, Red);		//�v���C���[
	DrawCircleAA(t_circle2.m_X, t_circle2.m_Y, t_circle2.m_R, 30, Bule);	//CPU

	DrawBox(32, 195, 50, 305, Black, TRUE);	//�͂ݏo�������S�[�����㏑��
	DrawBox(591, 195, 609, 305, Black, TRUE);//�͂ݏo���E���S�[�����㏑��
	DrawBox(50, 100, 591, 401, White, FALSE);//�t�B�[���h��
	DrawBox(45, 95, 596, 406, White, FALSE);//�t�B�[���h��
}