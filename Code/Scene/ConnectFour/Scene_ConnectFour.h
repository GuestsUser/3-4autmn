#pragma once
#include "./../Scene.h"
class CF_Player;

class Scene_ConnectFour : public Scene {
private:
	CF_Player* player;
public:
	Scene_ConnectFour();
	~Scene_ConnectFour();
	void Update();
	void Draw();

};
