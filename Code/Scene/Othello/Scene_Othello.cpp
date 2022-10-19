#include "./../Code/Scene/Othello/Scene_Othello.h"
#include "Othello_Player.h"
#include "Othello_Board.h"

Scene_Othello::Scene_Othello() {
	C_Player = new Othello_Player();
	C_Board = new Othello_Board();
	C_Player->Othello_Plyaer_Initialize();
	C_Board->Othello_Board_Initialize();

}

Scene_Othello::~Scene_Othello() {
	delete C_Player;
	delete C_Board;
}

void Scene_Othello::Update() {
	C_Player->Othello_Player_Update();
	C_Board->Othello_Board_Update();
}

void Scene_Othello::Draw() {
	C_Board->Othello_Board_Draw();
	C_Player->Othello_Player_Draw();

}
