#pragma once
#include "BoxCollider.h"
#include "DxLib.h" 
#include "Player.h"
class Fish: public BoxCollider
{
private:

	Player* player;

	bool flg;
	float x, y;					// �v���C���[�̍��W
	float w, h;					// �v���C���[�̑傫��
	static const int WIDTH = 20;
	static const int HEIGHT = 20;
	int image[10];
	int imagecnt;
	float imageX, imageY;
	int WeitTime;
	int Animflg;
	int EatChanceTime;
	int EatChance = 0;
	int EatTime;
	int EatY;
	bool EatFlg;
	bool PlayerEat;
	int ImageReverse;
	BoxCollider EatTarget;


public:

	bool flg1;
	bool flg2;

	//�R���X�g���N�^
	Fish();
	Fish(float _x, int _flg ,int _pflg);
	//�f�X�g���N�^
	~Fish();

	void Update();

	void Draw() const;					// �`��Ɋւ��邱�Ƃ�����

	bool GetFlg();

	void LoadImage();
	bool Eat(BoxCollider box);
	bool GetTarget(BoxCollider box);
	BoxCollider GetEatTarget();
	void GetPlayerVector(float _x, float _y);
};

