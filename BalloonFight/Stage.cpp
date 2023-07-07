#include "DxLib.h"
#include "common.h"
#include "Stage.h"
Stage::Stage()
{
}

Stage::Stage(int _stage, int _i)
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
	DrawBox(box.left, box.top, box.right, box.bottom, 0xffffff, false);
	DrawRotaGraph()
}

void Stage::LoadImage()
{

}

// �����Ő��l��Ԃ�(1:��A2:���A3:���A4:�E)
float Stage::GetSide(int i)
{
	switch (i)
	{
	case 1:
		return box.top;
		break;

	case 2:
		return box.bottom;
		break;

	case 3:
		return box.left;
		break;

	case 4:
		return box.right;
		break;

	default:
	return 0;
	}

}

