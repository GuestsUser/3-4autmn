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

	 mouseX, mouseY;//マウスの座標を格納

	//Circle t_circle1, t_circle2, t_circle3;//円の構造体を三つ実体化

	//プレイヤー、CPUの初期位置と半径を設定 パックは加えてマレットからの運動量、X、Y軸の速度、速度上限を設定
	Status_Reset();
}

void AirHockey_Scene::Status_Reset() {
	t_circle1.m_X = 80.0f, t_circle1.m_Y = 150.0f, t_circle1.m_R = 18.0f;	//プレイヤー
	t_circle2.m_X = 560.0f, t_circle2.m_Y = 150.0f, t_circle2.m_R = 18.0f;	//CPU
	t_circle3.m_X = 320.0f, t_circle3.m_Y = 150.0f, t_circle3.m_R = 15.0f, t_circle3.m_boundP = 6.0f, t_circle3.X_spd = 0.0f, t_circle3.Y_spd = 0.0f, t_circle3.Maxspd = 15.0f;	//パック
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

	if (50 > t_circle1.m_l || 320 < t_circle1.m_r) {
		return true;
	}
	if (100 > t_circle1.m_b || 400 < t_circle1.m_t) {
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

	if (50 > t_circle3.m_l || 590 < t_circle3.m_r) {
		return true;
	}
	if (100 > t_circle3.m_t || 400 < t_circle3.m_b) {
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
		//DrawFormatString(0, 0, Red, "x:%d y:%d", mouseX, mouseY);
		if (50 > t_circle1.m_l) {	//押し戻す処理　なんかガクガクする
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
		Player_Control();					//衝突していないなら動ける
	}



	if (Player_Puck_Check_Hit() == true) {	//プレイヤーとパックの衝突した時
		//DrawFormatString(0, 0, Purple, "x:%d y:%d", mouseX, mouseY);

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

		if (590 < t_circle3.m_r) {
			t_circle3.m_X -= t_circle3.m_R;//右
			t_circle3.X_spd *= -1.0f;//横軸反射
		}
		if (50 > t_circle3.m_l) {
			t_circle3.m_X += t_circle3.m_R;//左
			t_circle3.X_spd *= -1.0f;//横軸反射
		}
		if (400 < t_circle3.m_b) {
			t_circle3.m_Y -= t_circle3.m_R;//下
			t_circle3.Y_spd *= -1.0f;//縦軸反射
		}
		if (100 > t_circle3.m_t) {
			t_circle3.m_Y += t_circle3.m_R;//上
			t_circle3.Y_spd *= -1.0f;//縦軸反射
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

//プレイヤー等速移動処理
void AirHockey_Scene::Player_Control() {
	GetMousePoint(&mouseX, &mouseY);//マウス座標をint型で取得
	//マウス座標とプレイヤーの中心座標がずれていたらプレイヤー側から差を埋める処理
	// for文で作ると壁に刺さるので一旦if文重ねて妥協

	//右移動
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

	//左移動
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

	//下移動
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

	//上移動
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
	DrawLine(320, 101, 320, 400, Yellow);//中心線
	DrawOvalAA(50, 250, 18, 55, 25, Red, FALSE);//プレイヤーゴール線
	DrawOvalAA(590, 250, 18, 55, 25, Bule, FALSE);//CPUゴール線
	DrawCircleAA(320, 250, 80, 30, Yellow, FALSE);//中心円

	DrawCircleAA(t_circle3.m_X, t_circle3.m_Y, t_circle3.m_R, 30, Purple, 1);//パック
	DrawCircleAA(t_circle1.m_X, t_circle1.m_Y, t_circle1.m_R, 30, Red);		//プレイヤー
	DrawCircleAA(t_circle2.m_X, t_circle2.m_Y, t_circle2.m_R, 30, Bule);	//CPU

	DrawBox(32, 195, 50, 305, Black, TRUE);	//はみ出た左側ゴール線上書き
	DrawBox(591, 195, 609, 305, Black, TRUE);//はみ出た右側ゴール線上書き
	DrawBox(50, 100, 591, 401, White, FALSE);//フィールド壁
	DrawBox(45, 95, 596, 406, White, FALSE);//フィールド壁
}