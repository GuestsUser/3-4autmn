#include <DxLib.h>
#include "./../Title/Scene_Select.h"
#include "../../SceneManager.h"
#include "./../Scene.h"
#include "AirHockey.h"

void AirHockey_Scene::AirHockey_Initialize() {
	//Parent = 
	//色宣言
	 White = GetColor(255, 255, 255);
	 Red = GetColor(255, 50, 50);
	 Blue = GetColor(0, 191, 255);
	 DarkRed = GetColor(128, 50, 50);
	 DarkBule = GetColor(0,0 ,139 );
	 Yellow = GetColor(255, 255, 50);
	 Purple = GetColor(218, 112, 214);
	 Black = GetColor(0, 0, 0);

	 score1 = 0,score2 =- 1;//得点格納用(1がプレイヤー 2がCPU)
	 mouseX = 0, mouseY = 0;//マウスの座標格納用

	 //メモ マジックナンバーを使用してしまってい る箇所はマレットの初期座標、ゴールの範囲設定、壁の縦横の中心(wall_xC,yC)
	 //メモ 画面サイズはx1280 y720  フィールドサイズ x150+980=1130 y180+480=660 1050			//シーン移行　parent->SetNext(new Scene_Select());
	 wall_L = 150, wall_R = 1130, wall_T = 180, wall_B = 660, wall_xC = 640, wall_yC = 420;

	//プレイヤー、CPUの初期位置と半径を設定    パックは加えてマレットからの運動量、X、Y軸の速度、速度上限を設定
	Status_Reset();
}

//位置リセット
void AirHockey_Scene::Status_Reset() {
	t_circle1.m_X = wall_xC -160, t_circle1.m_Y = wall_yC + 120, t_circle1.m_R = 27.0f;	//プレイヤー
	t_circle2.m_X = wall_xC +160, t_circle2.m_Y = wall_yC - 120, t_circle2.m_R = 27.0f;	//CPU
	t_circle3.m_X = wall_xC, t_circle3.m_Y = wall_yC, t_circle3.m_R = 20.0f, t_circle3.m_boundP = 6.0f, t_circle3.X_spd = 0.0f, t_circle3.Y_spd = 0.0f, t_circle3.Maxspd = 15.0f;	//パック
};

//勝敗のフラグ関数
bool AirHockey_Scene::Resalt() {
	if (score1 >= 3 || score2 >= 3) {
		return true;
	}
		return false;
};

//衝突時のエフェクト試作
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
	//衝突点を左右上下設定
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
	//衝突点を左右上下に設定
	t_circle3.m_r = t_circle3.m_X + t_circle3.m_R;//右
	t_circle3.m_l = t_circle3.m_X - t_circle3.m_R;//左
	t_circle3.m_b = t_circle3.m_Y + t_circle3.m_R;//下
	t_circle3.m_t = t_circle3.m_Y - t_circle3.m_R;//上

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
				t_circle3.X_spd = t_circle3.Maxspd;						   // 上限速度と同じ速度に置き換える
			}
		}
		else {
			t_circle3.X_spd *= -1.0f;//横軸反射
			t_circle3.Y_spd *= -1.0f;//縦軸反射
		}

		if (t_circle1.m_Y != mouseY) {

			if (t_circle3.Maxspd > t_circle3.Y_spd + t_circle3.m_boundP) {//上記処理のY軸バージョン
				t_circle3.Y_spd += t_circle3.m_boundP;
			}
			else {
				t_circle3.Y_spd = t_circle3.Maxspd;
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

	//ゴールに入ったら
	if (wall_R < t_circle3.m_l || wall_L > t_circle3.m_r) {
		if (wall_xC < t_circle3.m_X) {//プレイヤーがゴール
			score1 += 1;
			Status_Reset();
			t_circle3.m_X + 30.0f;
		}
		else//CPUがゴール
		{
			score2 += 1;
			Status_Reset();
			t_circle3.m_X - 30.0f;
		}
	}

	if (Puck_Wall_Check_Hit() == true) {//壁にぶつかった時

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

		if (wall_R < t_circle3.m_X || wall_L > t_circle3.m_X) {//ゴールにパックが半分より多く入っていたら
			//ゴール内のy軸反射
				if (wall_yC - 90 < t_circle3.m_b) {
					t_circle3.m_Y -= t_circle3.m_R;//下
					t_circle3.Y_spd *= -1.0f;//縦軸反射
				}
				if (wall_yC + 90 > t_circle3.m_t) {
					t_circle3.m_Y += t_circle3.m_R;//上
					t_circle3.Y_spd *= -1.0f;//縦軸反射
				}
		}
		else//入ってなかったら
		{
			t_circle3.m_X -= t_circle3.m_R;//右
			t_circle3.X_spd *= -1.0f;//横軸反射
			t_circle3.m_X += t_circle3.m_R;//左
			t_circle3.X_spd *= -1.0f;//横軸反射
			t_circle3.m_Y -= t_circle3.m_R;//下
			t_circle3.Y_spd *= -1.0f;//縦軸反射
			t_circle3.m_Y += t_circle3.m_R;//上
			t_circle3.Y_spd *= -1.0f;//縦軸反射
		}
	}
	t_circle3.m_X += t_circle3.X_spd;
	t_circle3.m_Y += t_circle3.Y_spd;
};

//プレイヤー等速移動処理
void AirHockey_Scene::Player_Control() {
	GetMousePoint(&mouseX, &mouseY);//マウス座標をint型で取得
	//マウス座標とマレットの中心座標がずれていたらマレット側から差を埋める処理
	//違和感のない描画と程よい移動速度確保の兼ね合いが取れない 要情報収集
	// for文で作ると壁に刺さるので一旦if文重ねて保留

	//右移動
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

void AirHockey_Scene::AirHockey_Update(){
	Player_Hit();
	Puck_Move();
}

void AirHockey_Scene::AirHockey_Draw() {
	Draw_All();
}

void AirHockey_Scene::Draw_All() {
	//DrawLine(wall_L,wall_yC, wall_R, wall_yC, Yellow);

	DrawLine(wall_xC, wall_T, wall_xC, wall_B, Yellow);//中心線
	DrawOvalAA(wall_L, wall_yC, 20, 90, 30, DarkRed, TRUE);//プレイヤーゴール線
	DrawOvalAA(wall_R, wall_yC, 20, 90, 30, DarkBule, TRUE);//CPUゴール線
	DrawCircleAA(wall_xC, wall_yC, 100, 30, Yellow, FALSE);//中心円
	DrawBox(wall_L - 20, wall_yC - 100, wall_L + 1, wall_yC + 101, Black, TRUE);	//はみ出た左側ゴール線上書き
	DrawBox(wall_R, wall_yC - 101, wall_R + 21, wall_yC + 101, Black, TRUE);    //はみ出た右側ゴール線上書き
	DrawBox(wall_L, wall_T, wall_R, wall_B, White, FALSE);							//フィールド壁
	DrawBox(wall_L - 10, wall_T - 10, wall_R + 11, wall_B + 11, White, FALSE);	//フィールド壁

	if (Resalt() == false) {
		//DrawLine(wall_xC, wall_T, wall_xC, wall_B, Yellow);//中心線
		//DrawOvalAA(wall_L, wall_yC, 20, 90, 30, DarkRed, TRUE);//プレイヤーゴール線
		//DrawOvalAA(wall_R, wall_yC, 20, 90, 30, DarkBule, TRUE);//CPUゴール線
		//DrawCircleAA(wall_xC, wall_yC, 100, 30, Yellow, FALSE);//中心円

		DrawCircleAA(t_circle3.m_X, t_circle3.m_Y, t_circle3.m_R, 30, Purple, 1);	//パック
		DrawCircleAA(t_circle1.m_X, t_circle1.m_Y, t_circle1.m_R, 30, Red);			//プレイヤー
		DrawCircleAA(t_circle2.m_X, t_circle2.m_Y, t_circle2.m_R, 30, Blue);		//CPU

		//DrawBox(wall_L - 20, wall_yC - 100, wall_L + 1, wall_yC + 101, Black, TRUE);	//はみ出た左側ゴール線上書き
		//DrawBox(wall_R, wall_yC - 101, wall_R + 21, wall_yC + 101, Black, TRUE);    //はみ出た右側ゴール線上書き
		//DrawBox(wall_L, wall_T, wall_R, wall_B, White, FALSE);							//フィールド壁
		//DrawBox(wall_L - 10, wall_T - 10, wall_R + 11, wall_B + 11, White, FALSE);	//フィールド壁

		//Effect();
		DrawFormatString(wall_xC - 50, wall_T - 50, White, "%d - %d", score1, score2);
	}
	if (Resalt() == true) {
		if (score1 > score2) {
			for (int i = 0; i < 60; i++) {

				DrawFormatString(wall_xC - 80, wall_yC, Red, "Victory!!");
				//Parent->SetNext(new Scene_Select());    // セレクトシーンに移動
			}
		}

		if (score1 < score2) {
			for (int i = 0; i < 60; i++) {
				DrawFormatString(wall_xC -100, wall_yC, Blue, "Defeat･･･");
				//Parent->SetNext(new Scene_Select());    // セレクトシーンに移動
			}
		}
	}
}