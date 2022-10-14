#pragma once
#include "./../Scene.h"
#include "Othello_Player.h"

class Othello_Player;

class Scene_Othello : public Scene {
private:
	Othello_Player* player_o;
public:
	Scene_Othello();
	~Scene_Othello();
	void Update();
	void Draw();
};