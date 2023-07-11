#pragma once
#include "BoxCollider.h"
#include "DxLib.h" 
class Fish: public BoxCollider
{
private:
	bool flg;
	float x, y;					// プレイヤーの座標
	float w, h;					// プレイヤーの大きさ
	static const int WIDTH = 20;
	static const int HEIGHT = 20;

public:
	//コンストラクタ
	Fish();
	//デストラクタ
	~Fish();

	void Update();

	void Draw() const;					// 描画に関することを実装

	bool GetFlg();
};

