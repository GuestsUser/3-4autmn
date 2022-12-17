#pragma once

class AirHockey_Scene {
private:
	typedef struct {
		float m_X, m_Y, m_R, m_boundP,
			m_r, m_l, m_b, m_t,
			X_spd, Y_spd, Maxspd;

	}Circle;

	Circle t_circle1, t_circle2, t_circle3;//円の構造体を三つ実体化

	int White;
	int DarkRed;
	int Red;
	int DarkBule;
	int Bule;
	int Yellow;
	int Purple;
	int Black;

	int mouseX, mouseY;//マウスの座標を格納

	int wall_L, wall_R, wall_T, wall_B, wall_xC, wall_yC;

public:
	void AirHockey_Initialize();
	void AirHockey_Draw();
	void AirHockey_Update();
	void AirHockey_Finalize();

	//プロトタイプ宣言
	void Draw_All(); //描画
	//void Field_Out();
	void Player_Control();//プレイヤー等速移動
	void Status_Reset();//プレイヤー、CPU、パックの初期位置と半径
	bool Player_Puck_Check_Hit();//プレイヤーとパックの衝突判定
	void Player_Hit();//プレイヤーの衝突判定と動きのまとめ
	bool Player_Wall_Check_Hit();//プレイヤーと壁の衝突判定
	bool Puck_Wall_Check_Hit();//パックと壁の衝突
	void Puck_Move();
};