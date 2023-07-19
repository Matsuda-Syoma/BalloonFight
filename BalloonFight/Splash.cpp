#include "Splash.h"
#include "DxLib.h"

Splash::Splash(float _x)
{
	WaitTime = 0;
	x = _x;
	WorkImg = 0;
	AnimImg = 0;
	LoadImages();
}

Splash::~Splash()
{
}

void Splash::LoadImages()
{
	LoadDivGraph("Resources/images/Stage/Stage_SplashAnimation.png", 3, 3, 1, 64, 32, images);
}

void Splash::Draw() const
{
	//DrawGraph(x, 410, images[WorkImg], true);
	DrawRotaGraph(x, 430, 1.0f, 0, images[WorkImg], true);
}

bool Splash::Update()
{
	if (++AnimImg > 2) {
		WorkImg++;
		AnimImg = 0;
	}
	if (WorkImg > 12) {
		return true;
	}
	return false;
}
