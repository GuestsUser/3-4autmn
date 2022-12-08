#include "./../Code/Scene/Othello/Scene_Othello.h"
#include "Othello_Board.h"

Scene_Othello::Scene_Othello() {
	C_Board = new Othello_Board();

	C_Board->Othello_Board_Initialize(this);
}

Scene_Othello::~Scene_Othello() {
	delete C_Board;
}

void Scene_Othello::Update() {
	C_Board->Othello_Board_Update();
}

void Scene_Othello::Draw() {
	C_Board->Othello_Board_Draw();
}
