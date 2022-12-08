#pragma once
#include "../Scene.h"
#include <deque>

class Btn;
class CardDealer;
class Cmp_Image;
class Chara;
class PK_Dealer;
class PK_Player;
class Pot;

class Poker :public Scene { //�|�[�J�[�̃Q�[���V�[��
	Pot* pot;
	PK_Dealer* dealer;
	CardDealer* cardDealer;
	std::deque<Chara*> chara;
	Cmp_Image* back; //�w�i

	std::deque<Scene*> list; //�|�[�J�[���s���ׂ̏������s���V�[���̎��̕ێ��p�z��
	Scene* run; //����ɓ����Ă�V�[�������s����
public:
	enum class Character { leftCom, topCom, rightCom, player, length }; //chara����_�����L���������o���ׂ̗v�f�w��p�񋓌^�Alength���Q�Ƃ���΃L���������擾�ł��郉�C�t�n�b�N

	Poker();
	~Poker();
	void Update();
	void Draw();

private: //�|�[�J�[���s���ׂ̃f�[�^�𑀍삷�鏈�����`����Poker�Ǘ��V�[���O���錾
	enum class Section { ini, pre, main, change, showdown, nocontest, gameover, gameclear }; //list�z�񂩂�]�񂾃V�[�������o���ׂ̗v�f�w��p�񋓌^
	class Ini;
	class Pre;
	class Main;
	class Change;
	class ShowDown;
	class NoContest;
	class GameOver;
	class GameClear;
};