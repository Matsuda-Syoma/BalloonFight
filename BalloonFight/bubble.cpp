#include "bubble.h"
#include "Player.h"
#include"DxLib.h"

// �R���X�g���N�^
Bubble::Bubble()
{
	x = 40;
	y = 96;
	w = WIDTH;
	h = HEIGHT;
}

// �f�X�g���N�^
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
	DrawBox(box.left, box.top, box.right, box.bottom, 0xffff00, true);
}
