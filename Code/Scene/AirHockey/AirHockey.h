#pragma once

class AirHockey_Scene {
private:

	Scene* Parent;

	typedef struct {
		float m_X, m_Y, m_R, m_boundPx, m_boundPy,
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
	void AirHockey_Initialize(Scene* scene);
	void AirHockey_Draw();
	void AirHockey_Update();
	void AirHockey_Finalize();

	//プロトタイプ宣言
	void Draw_All(); //描画
	void Status_Reset();//プレイヤー、CPU、パックの初期位置と半径
	bool Resalt();//勝敗のフラグ
	void Debug_Data();//デバック表示

	void Player_Control();//プレイヤー操作
	bool Player_Puck_Check_Hit();//プレイヤーとパックの衝突判定フラグ
	bool Player_Wall_Check_Hit();//プレイヤーと壁の衝突判定フラグ
	bool Player_Move_Right();//プレイヤーが右に移動時のフラグ
	bool Player_Move_Left();//プレイヤーが左に移動時のフラグ
	bool Player_Move_Up();//プレイヤーが上に移動時のフラグ
	bool Player_Move_Under();//プレイヤーが下に移動時のフラグ
	void Player_Hit();//プレイヤー動きのまとめ

	void CPU_Movement();//CPUの思考ルーチン
	bool CPU_Puck_Check_Hit();//CPUとパックの衝突判定フラグ
	bool CPU_Move_Right();//CPUが右に移動時の判定フラグ
	bool CPU_Move_Left();//CPUが左に移動時の判定フラグ
	bool CPU_Move_Up();//CPUが上に移動時の判定フラグ
	bool CPU_Move_Under();//CPUが下に移動時の判定フラグ
	
	void Puck_Movement();//パックの動き
	bool Puck_Wall_Check_Hit();//パックと壁の衝突
	void Effect();//パック衝突時のエフェクト

	//****プレイヤーから見たパックの位置方向フラグ****
	bool PlayerBase_PuckPosition_Up();//上
	bool PlayerBase_PuckPosition_UpperRight();//右上
	bool PlayerBase_PuckPosition_Right();//右
	bool PlayerBase_PuckPosition_UnderRight();//右下
	bool PlayerBase_PuckPosition_Under();//下
	bool PlayerBase_PuckPosition_UnderLeft();//左下
	bool PlayerBase_PuckPosition_Left();//左
	bool PlayerBase_PuckPosition_UpperLeft();//左上
	//****CPUから見たパックの位置方向フラグ
	bool CPUBase_PuckPosition_Up();//上
	bool CPUBase_PuckPosition_UpperRight();//右上
	bool CPUBase_PuckPosition_Right();//右
	bool CPUBase_PuckPosition_UnderRight();//右下
	bool CPUBase_PuckPosition_Under();//下
	bool CPUBase_PuckPosition_UnderLeft();//左下
	bool CPUBase_PuckPosition_Left();//左
	bool CPUBase_PuckPosition_UpperLeft();//左上
};