#include "common.h"
#include "bubble.h"
#include "Player.h"
#include"DxLib.h"

// コンストラクタ
Bubble::Bubble(float _x)
{
	flg = true;

	x = _x;
	y = SCREEN_HEIGHT;
	w = WIDTH;
	h = HEIGHT;

	SpeedX = 0.0f; 
	SpeedY = -1.0f;
	moveX = 3.0f;
	moveSwitch = false;

	LoadImage();
	WaitTime = 0;
	AnimImg = 0;
	Hitflg = false;
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

	imageX = x + (w / 2);
	imageY = y + (w / 2);
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

	if (!Hitflg) {
		if (++MoveWaitTime > 40) {
			x += SpeedX;
		}
	y += SpeedY;
	}

	
}


void Bubble::Draw() const
{
	//DrawBox(box.left, box.top, box.right, box.bottom,0xffffff,false);
	DrawRotaGraph(imageX, imageY, 1.0f, 0, images[AnimImg], true, 0);
}

bool Bubble::GetFlg() {
	return flg;
}

bool Bubble::GetHitFlg() {
	return Hitflg;
}


void Bubble::SetHitFlg(bool b) {
	Hitflg = b;
}

void Bubble::LoadImage()
{
	//LoadGraph("Resources/images/Stage/Stage_BubbleAnimation.png");
	LoadDivGraph("Resources/images/Stage/Stage_BubbleAnimation.png",4,4,1,64,64,images);
}

bool Bubble::PlayAnim()
{
	if (++WaitTime % 3 == 0) {
		AnimImg++;
	}
	if (AnimImg > 3) {
		return true;
	}
	return false;
}
