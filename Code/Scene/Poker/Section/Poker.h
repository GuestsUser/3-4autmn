#pragma once
#include "Scene.h"
#include <deque>

class Btn;
class Cmp_Image;
class PK_Chara;
class PK_CardDealer;
class PK_Dealer;
class PK_Player;
class PK_Pot;

class Poker :public Scene { //�|�[�J�[�̃Q�[���V�[��
	PK_Pot* pot;
	PK_Dealer* dealer;
	PK_CardDealer* cardDealer;
	std::deque<PK_Chara*> chara;
	Cmp_Image* back; //�w�i

	std::deque<Scene*> list; //�|�[�J�[���s���ׂ̏������s���V�[���̎��̕ێ��p�z��
	Scene* run; //����ɓ����Ă�V�[�������s����
public:
	enum class Character { leftCom, topLeftCom, topRightCom, rightCom, player, length }; //chara����_�����L���������o���ׂ̗v�f�w��p�񋓌^�Alength���Q�Ƃ���΃L���������擾�ł��郉�C�t�n�b�N
	enum class Section { ini, pre, main, change, showdown, nocontest, gameover, gameclear }; //list�z�񂩂�]�񂾃V�[�������o���ׂ̗v�f�w��p�񋓌^

	Poker();
	~Poker();
	void Update();
	void Draw();

private: //�|�[�J�[���s���ׂ̃f�[�^�𑀍삷�鏈�����`����Poker�Ǘ��V�[���O���錾
	class Ini;
	class Pre;
	class Main;
	class Change;
	class ShowDown;
	class NoContest;
	class GameOver;
	class GameClear;
};