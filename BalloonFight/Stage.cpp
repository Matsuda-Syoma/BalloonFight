#include "DxLib.h"
#include "common.h"
#include "Stage.h"
Stage::Stage()
{
}


Stage::Stage(float _x, float _y, float _w, float _h, int _image)
{
	box.left = _x;
	box.right = _w;
	box.top = _y;
	box.bottom = _h;
	ImageX = box.left + (_w - _x) / 2;
	ImageY = box.top + (_h - _y) / 2;
	Image = _image;
}

Stage::~Stage()
{
}

void Stage::Draw() const
{
	//DrawRotaGraph(ImageX, ImageY, 1.0f, 0, Image, true);
	DrawGraph(box.left, box.top, Image, true);
	//DrawBox(box.left, box.top, box.right, box.bottom, 0xffffff, false);
	
}

int Stage::GetImage()
{
	return Image;
}

// 引数で数値を返す(1:上、2:下、3:左、4:右)
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

