#pragma once

class AirHockey_Scene {
private:

	Scene* Parent;

	typedef struct {
		float m_X, m_Y, m_R, m_boundPx, m_boundPy,
			m_r, m_l, m_b, m_t,
			X_spd, Y_spd, Maxspd;

	}Circle;

	Circle t_circle1, t_circle2, t_circle3;//�~�̍\���̂��O���̉�

	int White;
	int DarkRed;
	int Red;
	int DarkBule;
	int Blue;
	int Yellow;
	int Purple;
	int Black;

	int score1, score2;//���_���i�[
	int mouseX, mouseY;//�}�E�X�̍��W���i�[

	int wall_L, wall_R, wall_T, wall_B, wall_xC, wall_yC;

public:
	void AirHockey_Initialize(Scene* scene);
	void AirHockey_Draw();
	void AirHockey_Update();
	void AirHockey_Finalize();

	//�v���g�^�C�v�錾
	void Draw_All(); //�`��
	void Status_Reset();//�v���C���[�ACPU�A�p�b�N�̏����ʒu�Ɣ��a
	bool Resalt();//���s�̃t���O
	void Debug_Data();//�f�o�b�N�\��

	void Player_Control();//�v���C���[����
	bool Player_Puck_Check_Hit();//�v���C���[�ƃp�b�N�̏Փ˔���t���O
	bool Player_Wall_Check_Hit();//�v���C���[�ƕǂ̏Փ˔���t���O
	bool Player_Move_Right();//�v���C���[���E�Ɉړ����̃t���O
	bool Player_Move_Left();//�v���C���[�����Ɉړ����̃t���O
	bool Player_Move_Up();//�v���C���[����Ɉړ����̃t���O
	bool Player_Move_Under();//�v���C���[�����Ɉړ����̃t���O
	void Player_Hit();//�v���C���[�����̂܂Ƃ�

	void CPU_Movement();//CPU�̎v�l���[�`��
	bool CPU_Puck_Check_Hit();//CPU�ƃp�b�N�̏Փ˔���t���O
	bool CPU_Move_Right();//CPU���E�Ɉړ����̔���t���O
	bool CPU_Move_Left();//CPU�����Ɉړ����̔���t���O
	bool CPU_Move_Up();//CPU����Ɉړ����̔���t���O
	bool CPU_Move_Under();//CPU�����Ɉړ����̔���t���O
	
	void Puck_Movement();//�p�b�N�̓���
	bool Puck_Wall_Check_Hit();//�p�b�N�ƕǂ̏Փ�
	void Effect();//�p�b�N�Փˎ��̃G�t�F�N�g

	//****�v���C���[���猩���p�b�N�̈ʒu�����t���O****
	bool PlayerBase_PuckPosition_Up();//��
	bool PlayerBase_PuckPosition_UpperRight();//�E��
	bool PlayerBase_PuckPosition_Right();//�E
	bool PlayerBase_PuckPosition_UnderRight();//�E��
	bool PlayerBase_PuckPosition_Under();//��
	bool PlayerBase_PuckPosition_UnderLeft();//����
	bool PlayerBase_PuckPosition_Left();//��
	bool PlayerBase_PuckPosition_UpperLeft();//����
	//****CPU���猩���p�b�N�̈ʒu�����t���O
	bool CPUBase_PuckPosition_Up();//��
	bool CPUBase_PuckPosition_UpperRight();//�E��
	bool CPUBase_PuckPosition_Right();//�E
	bool CPUBase_PuckPosition_UnderRight();//�E��
	bool CPUBase_PuckPosition_Under();//��
	bool CPUBase_PuckPosition_UnderLeft();//����
	bool CPUBase_PuckPosition_Left();//��
	bool CPUBase_PuckPosition_UpperLeft();//����
};