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

public:

	//コンストラクタ
	Fish(float _x);
	//デストラクタ
	~Fish();

	void Update();

	void Draw() const;					// 描画に関することを実装

	bool GetFlg();

	void LoadImage();
};

