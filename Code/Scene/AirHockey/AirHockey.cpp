#include <DxLib.h>
#include "./../Title/Scene_Select.h"
#include "../../SceneManager.h"
#include "./../Scene.h"
#include "AirHockey.h"

void AirHockey_Scene::AirHockey_Initialize() {
	//Parent = 
	//�F�錾
	 White = GetColor(255, 255, 255);
	 Red = GetColor(255, 50, 50);
	 Blue = GetColor(0, 191, 255);
	 DarkRed = GetColor(128, 50, 50);
	 DarkBule = GetColor(0,0 ,139 );
	 Yellow = GetColor(255, 255, 50);
	 Purple = GetColor(218, 112, 214);
	 Black = GetColor(0, 0, 0);

	 score1 = 0,score2 =- 1;//���_�i�[�p(1���v���C���[ 2��CPU)
	 mouseX = 0, mouseY = 0;//�}�E�X�̍��W�i�[�p

	 //���� �}�W�b�N�i���o�[���g�p���Ă��܂��Ă� ��ӏ��̓}���b�g�̏������W�A�S�[���͈̔͐ݒ�A�ǂ̏c���̒��S(wall_xC,yC)
	 //���� ��ʃT�C�Y��x1280 y720  �t�B�[���h�T�C�Y x150+980=1130 y180+480=660 1050			//�V�[���ڍs�@parent->SetNext(new Scene_Select());
	 wall_L = 150, wall_R = 1130, wall_T = 180, wall_B = 660, wall_xC = 640, wall_yC = 420;

	//�v���C���[�ACPU�̏����ʒu�Ɣ��a��ݒ�    �p�b�N�͉����ă}���b�g����̉^���ʁAX�AY���̑��x�A���x�����ݒ�
	Status_Reset();
}

//�ʒu���Z�b�g
void AirHockey_Scene::Status_Reset() {
	t_circle1.m_X = wall_xC -160, t_circle1.m_Y = wall_yC + 120, t_circle1.m_R = 27.0f;	//�v���C���[
	t_circle2.m_X = wall_xC +160, t_circle2.m_Y = wall_yC - 120, t_circle2.m_R = 27.0f;	//CPU
	t_circle3.m_X = wall_xC, t_circle3.m_Y = wall_yC, t_circle3.m_R = 20.0f, t_circle3.m_boundP = 6.0f, t_circle3.X_spd = 0.0f, t_circle3.Y_spd = 0.0f, t_circle3.Maxspd = 15.0f;	//�p�b�N
};

//���s�̃t���O�֐�
bool AirHockey_Scene::Resalt() {
	if (score1 >= 3 || score2 >= 3) {
		return true;
	}
		return false;
};

//�Փˎ��̃G�t�F�N�g����
void AirHockey_Scene::Effect()
{
	if (wall_R < t_circle3.m_r) {
		for (int i = 0; i <= 120; i++) {
			DrawPixel(t_circle3.m_r, t_circle3.m_t - t_circle3.m_r, Purple);
			DrawPixel(t_circle3.m_r + i, t_circle3.m_t - t_circle3.m_r + i, Purple);
		};
	}
	if (wall_L > t_circle3.m_l) {
		for (int i = 0; i <= 120; i++) {
			DrawPixel(t_circle3.m_r, t_circle3.m_t - t_circle3.m_r, Purple);
			DrawPixel(t_circle3.m_r + i, t_circle3.m_t - t_circle3.m_r + i, Purple);
		};
	}
	if (wall_T > t_circle3.m_t) {
		for (int i = 0; i <= 120; i++) {
			DrawPixel(t_circle3.m_r, t_circle3.m_t - t_circle3.m_r, Purple);
			DrawPixel(t_circle3.m_r + i, t_circle3.m_t - t_circle3.m_r + i, Purple);
		};
	}
	if (wall_B < t_circle3.m_b) {
		for (int i = 0; i <= 120; i++) {
			DrawPixel(t_circle3.m_r, t_circle3.m_t - t_circle3.m_r, Purple);
			DrawPixel(t_circle3.m_r + i, t_circle3.m_t - t_circle3.m_r + i, Purple);
		};
	}
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

//�p�b�N�ƕǂ̓����蔻��
bool AirHockey_Scene::Puck_Wall_Check_Hit() {
	//�Փ˓_�����E�㉺�ɐݒ�
	t_circle3.m_r = t_circle3.m_X + t_circle3.m_R;//�E
	t_circle3.m_l = t_circle3.m_X - t_circle3.m_R;//��
	t_circle3.m_b = t_circle3.m_Y + t_circle3.m_R;//��
	t_circle3.m_t = t_circle3.m_Y - t_circle3.m_R;//��

	if (wall_yC - 90 > t_circle3.m_t || wall_yC + 90 < t_circle3.m_b) {
		if (wall_L > t_circle3.m_l || wall_R < t_circle3.m_r) {
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


///////////�ړ�������ړ��n�̏�������܂Ƃ�//////////


//�v���C���[���ǂƃp�b�N�ɏՓˎ��̂��ꂼ��̏���
void  AirHockey_Scene::Player_Hit() {

	if (Player_Wall_Check_Hit() == true)		//�v���C���[�ƕǂ̏Փ˂����m�����ꍇ
	{
		DrawFormatString(150, 80,Red , "x:%d y:%d", mouseX, mouseY);
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
		DrawFormatString(150, 80, White, "x:%d y:%d", mouseX, mouseY);
		Player_Control();					//�Փ˂��Ă��Ȃ��Ȃ瓮����
	}



	if (Player_Puck_Check_Hit() == true) {	//�v���C���[�ƃp�b�N�̏Փ˂�����

		if (t_circle1.m_X != mouseX) {

			if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundP) { //�p�b�N�̑��x������p�b�N�̑��x�Ɖ��Z���x�����킹�����x������Ȃ����
				t_circle3.X_spd += t_circle3.m_boundP;					   //�p�b�N��X���x�ɉ��Z���x�𑫂�
			}
			else {														   //���x����������Ă�����
				t_circle3.X_spd = t_circle3.Maxspd;						   // ������x�Ɠ������x�ɒu��������
			}
		}
		else {
			t_circle3.X_spd *= -1.0f;//��������
			t_circle3.Y_spd *= -1.0f;//�c������
		}

		if (t_circle1.m_Y != mouseY) {

			if (t_circle3.Maxspd > t_circle3.Y_spd + t_circle3.m_boundP) {//��L������Y���o�[�W����
				t_circle3.Y_spd += t_circle3.m_boundP;
			}
			else {
				t_circle3.Y_spd = t_circle3.Maxspd;
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

	//�S�[���ɓ�������
	if (wall_R < t_circle3.m_l || wall_L > t_circle3.m_r) {
		if (wall_xC < t_circle3.m_X) {//�v���C���[���S�[��
			score1 += 1;
			Status_Reset();
			t_circle3.m_X + 30.0f;
		}
		else//CPU���S�[��
		{
			score2 += 1;
			Status_Reset();
			t_circle3.m_X - 30.0f;
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

		if (wall_R < t_circle3.m_X || wall_L > t_circle3.m_X) {//�S�[���Ƀp�b�N��������葽�������Ă�����
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
	t_circle3.m_X += t_circle3.X_spd;
	t_circle3.m_Y += t_circle3.Y_spd;
};

//�v���C���[�����ړ�����
void AirHockey_Scene::Player_Control() {
	GetMousePoint(&mouseX, &mouseY);//�}�E�X���W��int�^�Ŏ擾
	//�}�E�X���W�ƃ}���b�g�̒��S���W������Ă�����}���b�g�����獷�𖄂߂鏈��
	//��a���̂Ȃ��`��ƒ��悢�ړ����x�m�ۂ̌��ˍ��������Ȃ� �v�����W
	// for���ō��ƕǂɎh����̂ň�Uif���d�˂ĕۗ�

	//�E�ړ�
	if (t_circle1.m_X < mouseX) {

		if (wall_xC > t_circle1.m_r + 3.0f) {
			t_circle1.m_X += 3.0f;

			if (wall_xC > t_circle1.m_r + 3.0f) {
						t_circle1.m_X += 3.0f;

				if (wall_xC > t_circle1.m_r + 3.0f) {
							t_circle1.m_X += 3.0f;

					if (wall_xC > t_circle1.m_r + 0.5f) {
								t_circle1.m_X += 0.5f;
					}
				}
			}
		}
	}

	//���ړ�
	if (t_circle1.m_X > mouseX) {

		if (wall_L < t_circle1.m_l - 3.0f) {
			t_circle1.m_X -= 3.0f;

			/*if (Player_Puck_Check_Hit()== true && 0.0f == t_circle3.X_spd) {
				t_circle3.m_X -= t_circle3.X_spd;
			}*/

			if (wall_L < t_circle1.m_l - 3.0f) {
				t_circle1.m_X -= 3.0f;

				/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
					t_circle3.m_X -= t_circle3.X_spd;
				}*/

				if (wall_L < t_circle1.m_l - 3.0f) {
					t_circle1.m_X -= 3.0f;

					/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
						t_circle3.m_X -= t_circle3.X_spd;
					}*/

					if (wall_L > t_circle1.m_l - 0.5f) {
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

		if (wall_B > t_circle1.m_b + 3.0f) {
			t_circle1.m_Y += 3.0f;

			/*if (Player_Puck_Check_Hit()== true && 0.0f == t_circle3.Y_spd) {
				t_circle3.m_Y += t_circle3.Y_spd;
			}*/

			if (wall_B > t_circle1.m_b + 3.0f) {
				t_circle1.m_Y += 3.0f;

				//if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
				//	t_circle3.m_Y += t_circle3.Y_spd;
				//}

				if (wall_B > t_circle1.m_b + 3.0f) {
					t_circle1.m_Y += 3.0f;

					/*	if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
							t_circle3.m_Y += t_circle3.Y_spd;
						}*/

					if (wall_B > t_circle1.m_b + 0.5f) {
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

		if (wall_T < t_circle1.m_t - 3.0f) {
			t_circle1.m_Y -= 3.0f;

			/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
				t_circle3.m_Y -= t_circle3.Y_spd;
			}*/

			if (wall_T < t_circle1.m_t - 3.0f) {
				t_circle1.m_Y -= 3.0f;

				/*	if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
						t_circle3.m_Y -= t_circle3.Y_spd;
					}*/

				if (wall_T < t_circle1.m_t - 3.0f) {
					t_circle1.m_Y -= 3.0f;

					/*	if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.Y_spd) {
							t_circle3.m_Y -= t_circle3.Y_spd;
						}*/

					if (wall_T < t_circle1.m_t - 0.5f) {
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

void AirHockey_Scene::AirHockey_Update(){
	Player_Hit();
	Puck_Move();
}

void AirHockey_Scene::AirHockey_Draw() {
	Draw_All();
}

void AirHockey_Scene::Draw_All() {
	//DrawLine(wall_L,wall_yC, wall_R, wall_yC, Yellow);

	DrawLine(wall_xC, wall_T, wall_xC, wall_B, Yellow);//���S��
	DrawOvalAA(wall_L, wall_yC, 20, 90, 30, DarkRed, TRUE);//�v���C���[�S�[����
	DrawOvalAA(wall_R, wall_yC, 20, 90, 30, DarkBule, TRUE);//CPU�S�[����
	DrawCircleAA(wall_xC, wall_yC, 100, 30, Yellow, FALSE);//���S�~
	DrawBox(wall_L - 20, wall_yC - 100, wall_L + 1, wall_yC + 101, Black, TRUE);	//�͂ݏo�������S�[�����㏑��
	DrawBox(wall_R, wall_yC - 101, wall_R + 21, wall_yC + 101, Black, TRUE);    //�͂ݏo���E���S�[�����㏑��
	DrawBox(wall_L, wall_T, wall_R, wall_B, White, FALSE);							//�t�B�[���h��
	DrawBox(wall_L - 10, wall_T - 10, wall_R + 11, wall_B + 11, White, FALSE);	//�t�B�[���h��

	if (Resalt() == false) {
		//DrawLine(wall_xC, wall_T, wall_xC, wall_B, Yellow);//���S��
		//DrawOvalAA(wall_L, wall_yC, 20, 90, 30, DarkRed, TRUE);//�v���C���[�S�[����
		//DrawOvalAA(wall_R, wall_yC, 20, 90, 30, DarkBule, TRUE);//CPU�S�[����
		//DrawCircleAA(wall_xC, wall_yC, 100, 30, Yellow, FALSE);//���S�~

		DrawCircleAA(t_circle3.m_X, t_circle3.m_Y, t_circle3.m_R, 30, Purple, 1);	//�p�b�N
		DrawCircleAA(t_circle1.m_X, t_circle1.m_Y, t_circle1.m_R, 30, Red);			//�v���C���[
		DrawCircleAA(t_circle2.m_X, t_circle2.m_Y, t_circle2.m_R, 30, Blue);		//CPU

		//DrawBox(wall_L - 20, wall_yC - 100, wall_L + 1, wall_yC + 101, Black, TRUE);	//�͂ݏo�������S�[�����㏑��
		//DrawBox(wall_R, wall_yC - 101, wall_R + 21, wall_yC + 101, Black, TRUE);    //�͂ݏo���E���S�[�����㏑��
		//DrawBox(wall_L, wall_T, wall_R, wall_B, White, FALSE);							//�t�B�[���h��
		//DrawBox(wall_L - 10, wall_T - 10, wall_R + 11, wall_B + 11, White, FALSE);	//�t�B�[���h��

		//Effect();
		DrawFormatString(wall_xC - 50, wall_T - 50, White, "%d - %d", score1, score2);
	}
	if (Resalt() == true) {
		if (score1 > score2) {
			for (int i = 0; i < 60; i++) {

				DrawFormatString(wall_xC - 80, wall_yC, Red, "Victory!!");
				//Parent->SetNext(new Scene_Select());    // �Z���N�g�V�[���Ɉړ�
			}
		}

		if (score1 < score2) {
			for (int i = 0; i < 60; i++) {
				DrawFormatString(wall_xC -100, wall_yC, Blue, "Defeat���");
				//Parent->SetNext(new Scene_Select());    // �Z���N�g�V�[���Ɉړ�
			}
		}
	}
}