#include "bubble.h"
#include "Player.h"
#include"DxLib.h"

// コンストラクタ
Bubble::Bubble()
{
	x = 40;
	y = 96;
	w = WIDTH;
	h = HEIGHT;
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
}

void Bubble::Draw() const
{
	DrawBox(10,10,100,100,0xffffff,1);
}
