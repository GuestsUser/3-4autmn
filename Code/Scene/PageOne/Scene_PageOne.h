#pragma once
#include "./../Scene.h"
class PageOne;

class Scene_PageOne : public Scene {
private:
	PageOne* po_player;
public:
	Scene_PageOne();
	~Scene_PageOne();
	void Update();
	void Draw();

};
