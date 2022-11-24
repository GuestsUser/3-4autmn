#pragma once
#include "./../Scene.h"
class CF_Player;
class Pause;

class Scene_ConnectFour : public Scene {
private:
	CF_Player* player;
	Pause* pause;
public:
	Scene_ConnectFour();
	~Scene_ConnectFour();
	void Update();
	void Draw();

};
