#pragma once

class PageOne {
private:
	int *card[5][13];

	int Mouse_X; //�}�E�X��X���W
	int Mouse_Y; //�}�E�X��Y���W
	int Player_X; //�v���C���[��X���W
	int Player_Y; //�v���C���[��Y���W

public:
	void PageOne_Initialize();
	void PageOne_Finalize();
	void PageOne_Update();
	void PageOne_Draw();
};
