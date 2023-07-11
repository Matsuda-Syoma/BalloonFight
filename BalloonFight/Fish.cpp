#include "Fish.h"
#include "Player.h"
#include"DxLib.h"

// コンストラクタ
Fish::Fish()
{

	flg = true;

	x = 300;
	y = 400;
	w = WIDTH;
	h = HEIGHT;

}

Fish::~Fish()
{

}

void Fish::Update()
{
	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;
}

void Fish::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom, 0xffffff, false);
}

bool Fish::GetFlg() {
	return flg;
}
