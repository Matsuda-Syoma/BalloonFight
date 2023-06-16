#include "DxLib.h"
#include "common.h"
#include "Stage.h"
Stage::Stage()
{
}

Stage::Stage(float _x, float _y, float _w, float _h)
{
	box.left = _x;
	box.right = _w;
	box.top = _y;
	box.bottom = _h;
}

Stage::~Stage()
{
}

void Stage::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom, 0xffffff, true);
}

