#include <DxLib.h>
#include "AirHockey.h"

void AirHockey_Scene::AirHockey_Initialize() {

	//色宣言
	 White = GetColor(255, 255, 255);
	 Red = GetColor(255, 50, 50);
	 Bule = GetColor(50, 50, 255);
	//int Green = GetColor(50, 255, 50);
	 Yellow = GetColor(255, 255, 50);
	 Purple = GetColor(218, 112, 214);
	 Black = GetColor(0, 0, 0);

	 mouseX, mouseY;//マウスの座標格納用

	 //メモ 画面サイズはx1280 y720  フィールドサイズ x150+980=1130 y180+480=660 1050
	 wall_L = 150, wall_R = 1130, wall_T = 180, wall_B = 660, wall_xC = 640, wall_yC = 420;

	//Circle t_circle1, t_circle2, t_circle3;//円の構造体を三つ実体化

	//プレイヤー、CPUの初期位置と半径を設定 パックは加えてマレットからの運動量、X、Y軸の速度、速度上限を設定
	Status_Reset();
}

void AirHockey_Scene::Status_Reset() {
	t_circle1.m_X = 230.0f, t_circle1.m_Y = 490.0f, t_circle1.m_R = 24.0f;	//プレイヤー
	t_circle2.m_X = 1060.0f, t_circle2.m_Y = 150.0f, t_circle2.m_R = 24.0f;	//CPU
	t_circle3.m_X = 980.0f, t_circle3.m_Y = 490.0f, t_circle3.m_R = 18.0f, t_circle3.m_boundP = 6.0f, t_circle3.X_spd = 0.0f, t_circle3.Y_spd = 0.0f, t_circle3.Maxspd = 15.0f;	//パック
};

////////当たり判定関数シリーズ//////

//プレイヤーとパックの当たり判定
bool AirHockey_Scene::Player_Puck_Check_Hit() {
	//三平方の定理
	float a = t_circle1.m_X - t_circle3.m_X;
	float b = t_circle1.m_Y - t_circle3.m_Y;
	float c = a * a + b * b;
	float sum_radius = t_circle1.m_R + t_circle3.m_R;
	if (c < sum_radius * sum_radius) {
		return true;
	}
	return false;
};

//プレイヤーと壁の当たり判定
bool AirHockey_Scene::Player_Wall_Check_Hit() {
	t_circle1.m_r = t_circle1.m_X + t_circle1.m_R; //右
	t_circle1.m_l = t_circle1.m_X - t_circle1.m_R; //左
	t_circle1.m_b = t_circle1.m_Y + t_circle1.m_R; //下
	t_circle1.m_t = t_circle1.m_Y - t_circle1.m_R; //上

	if (wall_L > t_circle1.m_l || wall_xC < t_circle1.m_r) {
		return true;
	}
	if (wall_B < t_circle1.m_b || wall_T > t_circle1.m_t) {
		return true;
	}
	return false;
};

//パックと壁の当たり判定
bool AirHockey_Scene::Puck_Wall_Check_Hit() {
	t_circle3.m_r = t_circle3.m_X + t_circle3.m_R;//右
	t_circle3.m_l = t_circle3.m_X - t_circle3.m_R;//左
	t_circle3.m_b = t_circle3.m_Y + t_circle3.m_R;//下
	t_circle3.m_t = t_circle3.m_Y - t_circle3.m_R;//上

	if (wall_L > t_circle3.m_l || wall_R < t_circle3.m_r) {
		return true;
	}
	if (wall_T > t_circle3.m_t || wall_B < t_circle3.m_b) {
		return true;
	}
	return false;
};
////////////ここまで////////////



///////////移動処理や移動系の条件分岐まとめ//////////


//プレイヤーが壁とパックに衝突時のそれぞれの処理
void  AirHockey_Scene::Player_Hit() {

	if (Player_Wall_Check_Hit() == true)		//プレイヤーと壁の衝突を検知した場合
	{
		DrawFormatString(150, 80,Red , "x:%d y:%d", mouseX, mouseY);
		if (wall_L > t_circle1.m_l) {	//押し戻す処理　なんかガクガクする
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
		Player_Control();					//衝突していないなら動ける
	}



	if (Player_Puck_Check_Hit() == true) {	//プレイヤーとパックの衝突した時

		if (t_circle1.m_X != mouseX) {

			if (t_circle3.Maxspd > t_circle3.X_spd + t_circle3.m_boundP) { //パックの速度上限をパックの速度と加算速度を合わせた速度が上回らなければ
				t_circle3.X_spd += t_circle3.m_boundP;					   //パックのX速度に加算速度を足す
			}
			else {														   //速度上限を上回っていたら
				t_circle3.X_spd = t_circle3.X_spd + t_circle3.m_boundP - t_circle3.X_spd + t_circle3.m_boundP - t_circle3.Maxspd;//(上限速度からオーバーした分を引く式) 上限速度と同じ速度に置き換える
			}
		}
		else {
			t_circle3.X_spd *= -1.0f;//横軸反射
			t_circle3.Y_spd *= -1.0f;//縦軸反射
		}

		if (t_circle1.m_Y != mouseY) {

			if (t_circle3.Maxspd > t_circle3.Y_spd + t_circle3.m_boundP) {//上記処理の?軸バージョン
				t_circle3.Y_spd += t_circle3.m_boundP;
			}
			else {
				t_circle3.Y_spd = t_circle3.Y_spd + t_circle3.m_boundP - t_circle3.Y_spd + t_circle3.m_boundP - t_circle3.Maxspd;
			}
		}
		else {
			t_circle3.X_spd *= -1.0f;//横軸反射
			t_circle3.Y_spd *= -1.0f;//縦軸反射
		}
	}
}

//パック
void  AirHockey_Scene::Puck_Move() {

	//停止するまで減速し続ける
	if (0.0f < t_circle3.X_spd) {
		t_circle3.X_spd -= 0.01f;
	}
	if (0.0f < t_circle3.Y_spd) {
		t_circle3.Y_spd -= 0.01f;
	}

	if (Puck_Wall_Check_Hit() == true) {

		if (wall_R < t_circle3.m_r) {
			t_circle3.m_X -= t_circle3.m_R;//右
			t_circle3.X_spd *= -1.0f;//横軸反射
		}
		if (wall_L > t_circle3.m_l) {
			t_circle3.m_X += t_circle3.m_R;//左
			t_circle3.X_spd *= -1.0f;//横軸反射
		}
		if (wall_B < t_circle3.m_b) {
			t_circle3.m_Y -= t_circle3.m_R;//下
			t_circle3.Y_spd *= -1.0f;//縦軸反射
		}
		if (wall_T > t_circle3.m_t) {
			t_circle3.m_Y += t_circle3.m_R;//上
			t_circle3.Y_spd *= -1.0f;//縦軸反射
		}
	}
	else {
		if (wall_R > t_circle3.m_r + t_circle3.X_spd && wall_L < t_circle3.m_l - t_circle3.X_spd) {
			t_circle3.m_X += t_circle3.X_spd;
		}
		else {
			t_circle3.m_X += t_circle3.X_spd - 1.0f;
		}
		if (wall_B > t_circle3.m_Y + t_circle3.Y_spd && wall_T < t_circle3.m_Y - t_circle3.Y_spd) {
			t_circle3.m_Y += t_circle3.Y_spd;
		}
		else {
			t_circle3.m_Y += t_circle3.Y_spd - 1.0f;
		}
	}
};

//プレイヤー等速移動処理
void AirHockey_Scene::Player_Control() {
	GetMousePoint(&mouseX, &mouseY);//マウス座標をint型で取得
	//マウス座標とプレイヤーの中心座標がずれていたらプレイヤー側から差を埋める処理
	// for文で作ると壁に刺さるので一旦if文重ねて妥協

	//右移動
	if (t_circle1.m_X < mouseX) {

		if (wall_xC > t_circle1.m_r + 3.0f) {
			t_circle1.m_X += 3.0f;

			/*	if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
					t_circle3.m_X += t_circle3.X_spd;
				}*/

			if (wall_xC > t_circle1.m_r + 3.0f) {
				t_circle1.m_X += 3.0f;

				/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
					t_circle3.m_X += t_circle3.X_spd;
				}*/

				if (wall_xC > t_circle1.m_r + 3.0f) {
					t_circle1.m_X += 3.0f;

					/*		if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
								t_circle3.m_X += t_circle3.X_spd;
							}*/

					if (wall_xC > t_circle1.m_r + 0.5f) {
						t_circle1.m_X += 0.5f;

						/*if (Player_Puck_Check_Hit() == true && 0.0f == t_circle3.X_spd) {
							t_circle3.m_X += t_circle3.X_spd;
						}*/
					}
				}
			}
		}
	}

	//左移動
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

	//下移動
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

	//上移動
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

/////////ここまで/////////

//描画

void AirHockey_Scene::AirHockey_Update(){
	Player_Hit();
	Puck_Move();
}

void AirHockey_Scene::AirHockey_Draw() {
	Draw_All();
}

void AirHockey_Scene::Draw_All() {
	DrawLine(wall_L,wall_yC, wall_R, wall_yC, Yellow);
	DrawLine(wall_xC,wall_T, wall_xC, wall_B, Yellow);//中心線
	DrawOvalAA(wall_L, wall_yC, 20, 90, 25, Red, FALSE);//プレイヤーゴール線
	DrawOvalAA(wall_R, wall_yC, 20, 90, 25, Bule, FALSE);//CPUゴール線
	DrawCircleAA(wall_xC, wall_yC, 100, 30, Yellow, FALSE);//中心円

	DrawCircleAA(t_circle3.m_X, t_circle3.m_Y, t_circle3.m_R, 30, Purple, 1);//パック
	DrawCircleAA(t_circle1.m_X, t_circle1.m_Y, t_circle1.m_R, 30, Red);	//プレイヤー
	DrawCircleAA(t_circle2.m_X, t_circle2.m_Y, t_circle2.m_R, 30, Bule);	//CPU

	DrawBox(wall_L - 20, wall_yC - 100, wall_L, wall_yC + 100, Black, TRUE);	//はみ出た左側ゴール線上書き
	DrawBox(wall_R, wall_yC - 101, wall_R + 20, wall_yC + 100, Black, TRUE);//はみ出た右側ゴール線上書き
	DrawBox(wall_L,wall_T,wall_R,wall_B, White, FALSE);//フィールド壁
	DrawBox(wall_L - 10,wall_T - 10, wall_R + 11, wall_B + 11, White, FALSE);//フィールド壁
}