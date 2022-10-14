#include "./../Code/Scene/Othello/Scene_Othello.h"
#include "Othello_Player.h"

Scene_Othello::Scene_Othello() {
	player_o = new Othello_Player();
	player_o->Othello_Plyaer_Initialize();
}

Scene_Othello::~Scene_Othello() {
	delete player_o;
}

void Scene_Othello::Update() {
	player_o->Othello_Player_Update();
}

void Scene_Othello::Draw() {
	player_o->Othello_Player_Draw();
}
