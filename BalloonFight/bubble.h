#pragma once
#include "BoxCollider.h"
#include "DxLib.h"
class Bubble : public BoxCollider
{
private:
	bool flg;
	float x, y;					// プレイヤーの座標
	float w, h;					// プレイヤーの大きさ
	static const int WIDTH = 40;
	static const int HEIGHT = 40;
	float SpeedX;
	float SpeedY;
	float moveX;
	bool moveSwitch;
	int images[4];
	float imageX, imageY;
	int WaitTime;
	int AnimImg;
	bool Hitflg;
public:

	//コンストラクタ
	Bubble();
	//デストラクタ
	~Bubble();

	void Update();

	void Draw() const;					// 描画に関することを実装

	bool GetFlg();

	bool GetHitFlg();

	void SetHitFlg(bool b);

	void LoadImage();

	bool PlayAnim();
};

