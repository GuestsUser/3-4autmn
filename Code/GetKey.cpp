#include "DxLib.h"
#include "GetKey.h"

#include <cmath>

int A_KEY = XINPUT_BUTTON_A;
int B_KEY = XINPUT_BUTTON_B;
int X_KEY = XINPUT_BUTTON_X;
int Y_KEY = XINPUT_BUTTON_Y;
int L_KEY = XINPUT_BUTTON_LEFT_SHOULDER;
int R_KEY = XINPUT_BUTTON_RIGHT_SHOULDER;
int POUSE_KEY = XINPUT_BUTTON_START;
int SELECT_KEY = XINPUT_BUTTON_BACK;
KeySystem* key;

KeySystem::KeySystem() :input{0} {
	for (int i = 0; i < key_vol+8; i++) { key_state[i] = KEY_FREE; hold_time[i] = 0; }
	SetJoypadDeadZone(DX_INPUT_PAD1, 0);//KeyInputで入力無効化を行っているのでこちらの処理は切る、KeyInputとこちらの違いとしてはKeyInputはx軸、y軸個別に無効範囲を決められる事にある……
}

void KeySystem::KeyInput() {
	int c_key=0;
	if (GetJoypadXInputState(DX_INPUT_PAD1, &input) == -1) { return; }//エラー対策

	for (int i = 0; i < key_vol; i++) {
		switch (i) {
		case 0:c_key = XINPUT_BUTTON_DPAD_UP; break;
		case 1:c_key = XINPUT_BUTTON_DPAD_DOWN; break;
		case 2:c_key = XINPUT_BUTTON_DPAD_LEFT; break;
		case 3:c_key = XINPUT_BUTTON_DPAD_RIGHT; break;
		case 4:c_key = A_KEY; break;
		case 5:c_key = B_KEY; break;
		case 6:c_key = X_KEY; break;
		case 7:c_key = Y_KEY; break;
		case 8:c_key = L_KEY; break;
		case 9:c_key = R_KEY; break;
		case 10:c_key = POUSE_KEY; break;
		case 11:c_key = SELECT_KEY; break;
		}
		if (input.Buttons[c_key]) {
			if (hold_time[i] > 0) { key_state[i] = KEY_HOLD; }
			else { key_state[i] = KEY_PUSH; }
			hold_time[i]++;
		}
		else {
			if (hold_time[i] > 0) { key_state[i] = KEY_PULL; }
			else { key_state[i] = KEY_FREE; }
			hold_time[i] = 0;
		}
	}

	//スティック入力状態入力
	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:c_key = input.ThumbLY; break;
		case 1:c_key = input.ThumbLX; break;
		case 2:c_key = input.ThumbRY; break;
		case 3:c_key = input.ThumbRX; break;
		}

		tilt[(int)((floor(i / 2) + 1) * 2 - ((i % 2) + 1.0))] = c_key / SHORT_SIZE;//傾きの具合を-1～1で格納する、tiltは格納順がlx、ly～という形なのでそれに合わせた添え字仕様
		short use_tilt_min = X_TILT_MIN * (i % 2) + Y_TILT_MIN * ((i + 1) % 2);//スティック傾き検知最低値、偶数回ならy軸使用、奇数はx

		for (int j = 0; j < 2; j++) {
			bool use = j == 0 ? c_key <= use_tilt_min * -1 : c_key >= use_tilt_min;//jが0なら-方向チェック、1なら+方向
			int sub = key_vol + j + (i % 2) * 2 + floor(i / 2) * 4;//今回使用する添え字、key_volでスティック入力状態の配列位置に持っていき、i%2でxy切替、i/2でLR切替、jで+-方向切替
			if (use) {
				if (hold_time[sub] > 0) { key_state[sub] = KEY_HOLD; }
				else { key_state[sub] = KEY_PUSH; }
				hold_time[sub]++;
				break;//一方向に入力があった場合以降は実行しない
			}
			//入力のなかった方向はリセットする
			if (hold_time[sub] > 0) { key_state[sub] = KEY_PULL; }
			else { key_state[sub] = KEY_FREE; }
			hold_time[sub] = 0;
		}
	}
}

int KeySystem::GetKeyState(int request) {
	switch (request) {
	case XINPUT_BUTTON_DPAD_UP:return key_state[0]; break;
	case XINPUT_BUTTON_DPAD_DOWN:return key_state[1]; break;
	case XINPUT_BUTTON_DPAD_LEFT:return key_state[2]; break;
	case XINPUT_BUTTON_DPAD_RIGHT:return key_state[3]; break;

	case L_STICK_DOWN:return key_state[12]; break;
	case L_STICK_UP:return key_state[13]; break;
	case L_STICK_LEFT:return key_state[14]; break;
	case L_STICK_RIGHT:return key_state[15]; break;
	case R_STICK_DOWN:return key_state[16]; break;
	case R_STICK_UP:return key_state[17]; break;
	case R_STICK_LEFT:return key_state[18]; break;
	case R_STICK_RIGHT:return key_state[19]; break;
	}
	//各種ボタンはコンフィグ対応を考え定数で宣言してないのでswitchが利用できなかった為、ifで行う
	if (request == A_KEY) { return key_state[4]; }
	if (request == B_KEY) { return key_state[5]; }
	if (request == X_KEY) { return key_state[6]; }
	if (request == Y_KEY) { return key_state[7]; }
	if (request == L_KEY) { return key_state[8]; }
	if (request == R_KEY) { return key_state[9]; }
	if (request == POUSE_KEY) { return key_state[10]; }
	if (request == SELECT_KEY) { return key_state[11]; }
	return -1;//引数エラー
}
int KeySystem::GetKeyHoldTime(int request) {
	switch (request) {
	case XINPUT_BUTTON_DPAD_UP:return hold_time[0]; break;
	case XINPUT_BUTTON_DPAD_DOWN:return hold_time[1]; break;
	case XINPUT_BUTTON_DPAD_LEFT:return hold_time[2]; break;
	case XINPUT_BUTTON_DPAD_RIGHT:return hold_time[3]; break;

	case L_STICK_DOWN:return key_state[12]; break;
	case L_STICK_UP:return key_state[13]; break;
	case L_STICK_LEFT:return key_state[14]; break;
	case L_STICK_RIGHT:return key_state[15]; break;
	case R_STICK_DOWN:return key_state[16]; break;
	case R_STICK_UP:return key_state[17]; break;
	case R_STICK_LEFT:return key_state[18]; break;
	case R_STICK_RIGHT:return key_state[19]; break;
	}
	//各種ボタンはコンフィグ対応を考え定数で宣言してないのでswitchが利用できなかった為、ifで行う
	if (request == A_KEY) { return hold_time[4]; }
	if (request == B_KEY) { return hold_time[5]; }
	if (request == X_KEY) { return hold_time[6]; }
	if (request == Y_KEY) { return hold_time[7]; }
	if (request == L_KEY) { return hold_time[8]; }
	if (request == R_KEY) { return hold_time[9]; }
	if (request == POUSE_KEY) { return hold_time[10]; }
	if (request == SELECT_KEY) { return key_state[11]; }
	return -1;//引数エラー
}
