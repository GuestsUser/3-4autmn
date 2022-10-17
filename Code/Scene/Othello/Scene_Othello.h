#pragma once
#include "./../Scene.h"
#include "Othello_Player.h"

class Othello_Player;
class Othello_Board;

class Scene_Othello : public Scene {
private:
	Othello_Board* C_Board;
	Othello_Player* C_Player;
public:
	Scene_Othello();
	~Scene_Othello();
	void Update();
	void Draw();
};