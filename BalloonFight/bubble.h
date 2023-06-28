#pragma once
#include "BoxCollider.h"
class Bubble : public BoxCollider
{
private:
	float x, y;					// プレイヤーの座標
	float w, h;					// プレイヤーの大きさ
	static const int WIDTH = 20;
	static const int HEIGHT = 20;
public:

	//コンストラクタ
	Bubble();
	//デストラクタ
	~Bubble();

	void Update();

	void Draw() const;					// 描画に関することを実装
};

