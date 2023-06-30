#include "bubble.h"
#include "Player.h"
#include"DxLib.h"

// コンストラクタ
Bubble::Bubble()
{
	x = 400;
	y = 306;
	w = WIDTH;
	h = HEIGHT;

	SpeedX = 0.0f; 
	SpeedY = -1.0f;
	moveX = 3.0f;
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
	x += SpeedX;
	y += SpeedY;

}

void Bubble::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom,0xffffff,1);
}
