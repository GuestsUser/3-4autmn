#pragma once
#include "Component.h"
#include "PK_Player.h"

#include <deque>

class Button;
class Vector3;

class PK_Player::Change :public Component {
	PK_Player* parent; //自身を保持する親
	std::deque<Button*> cardButton; //カードクリックを検知する為のボタン
	std::deque<Vector3*> cardPos; //カードの位置へのアクセスショートカット

	int count;
	int originalY; //カードをクリックした際、位置を前に出すので元に戻せるよう平常時のy記録用
	int moveY; //カードをクリックした時、カードが動くy量
public:
	Change(PK_Player& parent);

	void Update();
};