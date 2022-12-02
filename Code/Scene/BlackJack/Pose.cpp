#include"BJ_Head.h"

int Pause_Button, Pause_Back, Pause_Continue, Pause_Select, nowKey, Mouse_X, Mouse_Y, OldKey;
bool PauseFlg;
int CF_GameBGM, pause_continue[2];
int pause_select[2];
extern bool pose = false;
extern bool end = false;

void Pose_Initialize() {
  pose = false;
  end = false;
  PauseFlg = false;
  Pause_Button = LoadGraph("Resource/image/PauseButton.png");
  Pause_Back = LoadGraph("Resource/image/PauseBack.png");
  Pause_Continue = LoadDivGraph("Resource/image/ContinueButton.png", 2, 2, 1, 400, 120, pause_continue);
  Pause_Select = LoadDivGraph("Resource/image/MenuButton.png", 2, 2, 1, 400, 120, pause_select);
}
void Pose_Update() {

  GetMousePoint(&Mouse_X, &Mouse_Y);
  nowKey = key->GetKeyState(REQUEST_MOUSE_LEFT); /*現在のマウス左ボタンの入力状態の取得*/
    /*ポーズボタンを押したらポーズ画面を開くフラグをtrueにする*/
  if ((20 <= Mouse_X && Mouse_X <= 200 && 25 <= Mouse_Y && Mouse_Y <= 105) || ((450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) && PauseFlg)) {

    if (OldKey != KEY_FREE && nowKey == KEY_PULL) {

      PauseFlg = !PauseFlg;

      pose = PauseFlg;
    }
  }
  if (PauseFlg) {

    if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
      if (OldKey != KEY_FREE && nowKey == KEY_PULL) {  /*前の入力で左キーを話していなくて、今マウスの左キーを離した時*/
        StopSoundMem(CF_GameBGM);
        end = true;
      }
    }
  }
  OldKey = nowKey; /*前に入力していたキーを今入力していたキーに上書きする*/
}
void Pose_Draw() {
  /*ポーズボタン*/
  DrawRotaGraph(110, 65, 0.9, 0, Pause_Button, TRUE);
  if (PauseFlg == true) {
    DrawRotaGraph(650, 380, 1.15, 0, Pause_Back, TRUE);
    if (450 <= Mouse_X && Mouse_X <= 850 && 320 <= Mouse_Y && Mouse_Y <= 440) {
      if (nowKey == KEY_HOLD) {
        DrawRotaGraph(650, 380, 0.9, 0, pause_continue[1], TRUE);
      }
      else {
        DrawRotaGraph(650, 380, 1.0, 0, pause_continue[1], TRUE);
      }
    }
    else {
      DrawRotaGraph(650, 380, 1.0, 0, pause_continue[0], TRUE);
    }
    if (450 <= Mouse_X && Mouse_X <= 850 && 470 <= Mouse_Y && Mouse_Y <= 590) {
      if (nowKey == KEY_HOLD) {
        DrawRotaGraph(650, 530, 0.9, 0, pause_select[1], TRUE);
      }
      else {
        DrawRotaGraph(650, 530, 1.0, 0, pause_select[1], TRUE);
      }
    }
    else {
      DrawRotaGraph(650, 530, 1.0, 0, pause_select[0], TRUE);
    }
  }
}
