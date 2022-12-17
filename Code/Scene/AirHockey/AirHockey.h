#pragma once

class AirHockey_Scene {
private:
	typedef struct {
		float m_X, m_Y, m_R, m_boundP,
			m_r, m_l, m_b, m_t,
			X_spd, Y_spd, Maxspd;

	}Circle;

	Circle t_circle1, t_circle2, t_circle3;//�~�̍\���̂��O���̉�

	int White;
	int DarkRed;
	int Red;
	int DarkBule;
	int Bule;
	int Yellow;
	int Purple;
	int Black;

	int mouseX, mouseY;//�}�E�X�̍��W���i�[

	int wall_L, wall_R, wall_T, wall_B, wall_xC, wall_yC;

public:
	void AirHockey_Initialize();
	void AirHockey_Draw();
	void AirHockey_Update();
	void AirHockey_Finalize();

	//�v���g�^�C�v�錾
	void Draw_All(); //�`��
	//void Field_Out();
	void Player_Control();//�v���C���[�����ړ�
	void Status_Reset();//�v���C���[�ACPU�A�p�b�N�̏����ʒu�Ɣ��a
	bool Player_Puck_Check_Hit();//�v���C���[�ƃp�b�N�̏Փ˔���
	void Player_Hit();//�v���C���[�̏Փ˔���Ɠ����̂܂Ƃ�
	bool Player_Wall_Check_Hit();//�v���C���[�ƕǂ̏Փ˔���
	bool Puck_Wall_Check_Hit();//�p�b�N�ƕǂ̏Փ�
	void Puck_Move();
};