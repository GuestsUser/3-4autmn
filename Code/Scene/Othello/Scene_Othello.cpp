#include "./../Code/Scene/Othello/Scene_Othello.h"
#include "Othello_Player.h"
#include "Othello_Board.h"

Scene_Othello::Scene_Othello() {
	C_Board = new Othello_Board();
	C_Player = new Othello_Player();

	C_Board->Othello_Board_Initialize(this);
	C_Player->Othello_Plyaer_Initialize();
}

Scene_Othello::~Scene_Othello() {
	delete C_Board;
	delete C_Player;
}

void Scene_Othello::Update() {
	C_Board->Othello_Board_Update();
	C_Player->Othello_Player_Update();
}

void Scene_Othello::Draw() {
	C_Board->Othello_Board_Draw();
	C_Player->Othello_Player_Draw();

}
