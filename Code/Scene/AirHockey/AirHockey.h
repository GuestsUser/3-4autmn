#pragma once

class AirHockey_Scene {
private:

	//Scene* 

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
	int Blue;
	int Yellow;
	int Purple;
	int Black;

	int score1, score2;//得点を格納
	int mouseX, mouseY;//マウスの座標を格納

	int wall_L, wall_R, wall_T, wall_B, wall_xC, wall_yC;

public:
	void AirHockey_Initialize();
	void AirHockey_Draw();
	void AirHockey_Update();
	void AirHockey_Finalize();

	//プロトタイプ宣言
	void Draw_All(); //描画
	void Status_Reset();//プレイヤー、CPU、パックの初期位置と半径
	bool Resalt();//勝敗のフラグ

	void Player_Control();//プレイヤー操作
	bool Player_Puck_Check_Hit();//プレイヤーとパックの衝突判定フラグ
	bool Player_Wall_Check_Hit();//プレイヤーと壁の衝突判定フラグ
	void Player_Hit();//プレイヤー動きのまとめ

	bool CPU_Puck_Check_Hit();//CPUとパックの衝突判定フラグ

	bool Puck_Wall_Check_Hit();//パックと壁の衝突
	void CPU_Movement();//CPUの動き
	void Puck_Movement();//パックの動き
	void Effect();//パック衝突時のエフェクト
};