#pragma once
#include "./../Scene.h"
#include "Othello_Board.h"

class Othello_Player;
class Othello_Board;

class Scene_Othello : public Scene {
private:
	Othello_Board* C_Board;
public:
	Scene_Othello();
	~Scene_Othello();
	void Update();
	void Draw();
};