#include "bubble.h"
#include "Player.h"
#include"DxLib.h"

// コンストラクタ
Bubble::Bubble()
{
	flg = true;

	x = 40;
	y = 400;
	w = WIDTH;
	h = HEIGHT;

	SpeedX = 0.0f; 
	SpeedY = -1.0f;
	moveX = 3.0f;
	moveSwitch = false;
}

// デストラクタ
Bubble::~Bubble()
{

}


void Bubble::Update()
{
	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;
	// 移動

	if (box.bottom < 0) {
		flg = false;
	}

	if (SpeedX > 2.0f || SpeedX < -2.0f) {
		moveSwitch = !moveSwitch;
	}
	if (moveSwitch) {
		SpeedX += -0.05f;
	}
	else {
		SpeedX += 0.05f;
	}
	x += SpeedX;
	y += SpeedY;

	// プレイヤーと泡の当たり判定
	
}


void Bubble::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom,0xffffff,false);
}

bool Bubble::GetFlg() {
	return flg;
}
