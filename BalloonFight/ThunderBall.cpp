#include "ThunderBall.h"
#include <DxLib.h>
#include"Stage.h"
#define _USE_MATH_DEFINES
#include <math.h>

ThunderBall::ThunderBall()
{
	BallX = 50;
	BallY = 200;

	MoveX = 1;
	MoveY = -2;

	Speed = 3;
	BallAngle = 0.625f;

	FlashCount = 0;
	BallCount = 1;
	LoadImages();
}

ThunderBall::~ThunderBall()
{
}

void ThunderBall::Update()
{
	//雲の点滅
	if (FlashCount < 100) {
		FlashCount++;
	}

	//点滅が終わると
	if (FlashCount == 100) {
		BallX += MoveX;
		BallY += MoveY;
	}

	if (BallCount < 3 && FlashCount >= 100) {
		BallCount++;
		

		if (BallCount >= 3) {
			BallCount = 0;
		}
	}


	// 壁・天井での反射
	if (BallX < 4 || BallX > 640 - 4) { // 横の壁
		if (BallX < 4) {
			BallX = 4;
			
		}
		else {
			BallX = 640 - 4;
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
	if(BallCount == 0){
			DrawGraph(BallX, BallY, ThunBallImg[1], TRUE);
	}
}

//画像読込
void ThunderBall::LoadImages()
{
	LoadDivGraph("Resources/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, ThunBallImg);
}

void ThunderBall::ChangeAngle()
{
	//ボールの反射角度
	float rad = BallAngle * (float)M_PI * 0.5;
	MoveX = (int)(Speed * cosf(rad));
	MoveY = (int)(Speed * sinf(rad));
}