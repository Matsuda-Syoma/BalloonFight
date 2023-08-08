#pragma once
#include "BoxCollider.h"
#include "DxLib.h" 
#include "Player.h"
class Fish: public BoxCollider
{
private:

	Player* player;

	bool flg;
	float x, y;					// プレイヤーの座標
	float w, h;					// プレイヤーの大きさ
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

	//コンストラクタ
	Fish();
	Fish(float _x, int _flg ,int _pflg);
	//デストラクタ
	~Fish();

	void Update();

	void Draw() const;					// 描画に関することを実装

	bool GetFlg();

	void LoadImage();
	bool Eat(BoxCollider box);
	bool GetTarget(BoxCollider box);
	BoxCollider GetEatTarget();
	void GetPlayerVector(float _x, float _y);
};

