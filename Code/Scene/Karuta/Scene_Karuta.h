#pragma once
#include "./../Scene.h"
class Karu_Game;

class Scene_Karuta : public Scene {
private:
	Karu_Game* game;
public:
	Scene_Karuta();
	~Scene_Karuta();
	void Update();
	void Draw();

};
