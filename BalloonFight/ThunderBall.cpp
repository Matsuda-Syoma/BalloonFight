#include "ThunderBall.h"
#include <DxLib.h>
#include"Stage.h"
#define _USE_MATH_DEFINES
#include <math.h>

ThunderBall::ThunderBall()
{
	BallX = 550;
	BallY = 300;

	MoveX = 1;
	MoveY = -2;

	Speed = 3;
	BallAngle = 0.65f;

	FlashCount = 0;
	BallCount = -1;
	
	LoadImages();
}

ThunderBall::~ThunderBall()
{
}

void ThunderBall::Update()
{
		BallX += MoveX;
		BallY += MoveY;
		box.top = BallY;
		box.bottom = BallY + HEIGHT;
		box.left = BallX;
		box.right = BallX + WIDTH;

	if (BallCount < 3) {
		BallCount++;
		
		

		if (BallCount >= 3) {
			BallCount = 0;
		}
	}

	// 壁・天井での反射
	if (BallX < 0 || BallX > 640 - 25) { // 横の壁
		if (BallX < 0) {
			BallX = 0;
			
		}
		else {
			BallX = 640 - 25;
		}
		BallAngle = (1 - BallAngle) + 0.5f;
		if (BallAngle > 1) BallAngle -= 1.0f;
		ChangeAngle();
	}
	if (BallY < 4) { // 上の壁
		BallAngle = (1 - BallAngle);
		
		ChangeAngle();
	}

}

void ThunderBall::Draw() const
{
	DrawGraph(BallX, BallY, ThunBallImg[BallCount], TRUE);
	
}

//画像読込
void ThunderBall::LoadImages()
{
	LoadDivGraph("Resources/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, ThunBallImg);
}

void ThunderBall::ChangeAngle()
{
	//ボールの反射角度
	float rad = BallAngle * (float)M_PI * 2;
	MoveX = (int)(Speed * cosf(rad));
	MoveY = (int)(Speed * sinf(rad));
}



float ThunderBall::GetBoxSide(BoxCollider box, int i) {
	return box.GetSide(i);
}


int ThunderBall::Hit(BoxCollider _stage) {
	clsDx();
	printfDx("%f", BallAngle);
	int HitEnemy = HitBox(_stage);
	switch (HitEnemy)
	{
	case 1://上
		BallY = GetBoxSide(_stage, 1) - (HEIGHT + 1);
		BallAngle = (1 - BallAngle);
		ChangeAngle();
		return 1;
		break;
	case 2://下
		BallY = GetBoxSide(_stage, 2) + 1;
		BallAngle = (1 - BallAngle);
		ChangeAngle();
		return 2;
		break;
	case 3://左
		BallX = GetBoxSide(_stage, 3) - (WIDTH + 1);
		BallAngle = (1 - BallAngle) + 0.5f;
		ChangeAngle();
		return 3;
		break;
	case 4://右
		BallX = GetBoxSide(_stage, 4) + 1;
		BallAngle = (1 - BallAngle) + 0.5f;
		ChangeAngle();
		return 4;
		break;
	default:
		return 0;
		break;
	}

}