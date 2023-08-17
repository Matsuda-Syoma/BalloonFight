#include "ThunderBall.h"
#include <DxLib.h>
#include"Stage.h"
#define _USE_MATH_DEFINES
#include <math.h>

ThunderBall::ThunderBall(int spown,bool p_flg, float _x, float _y)
{
	// ｘとｙが来ていないのが問題？
	
	Hitflg = p_flg;
	spownAngle = spown;


	BallX = _x;
	BallY = _y;

	/*MoveX = 1;
	MoveY = -2;*/

	Speed = 3;

	switch (spownAngle)
	{
	case 0:// 右上
		BallAngle = 0.875f;
		MoveX = 1;
		MoveY = -2;
		break;
	case 1:// 右下
		BallAngle = 0.125f;
		MoveX = 1;
		MoveY = +2;
		break;
	case 2:// 左下
		BallAngle = 0.375f;
		MoveX = -1;
		MoveY = +2;
		break;
	case 3:// 左上
		BallAngle = 0.625f;
		MoveX = -1;
		MoveY = -2;
		break;
	}

	FlashCount = 0;
	BallCount = -1;//問題はここ
	
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
		if (playerhit == true) {
			BallX = 1000;
			BallY = 1000;
		}
		printfDx("%d", playerhit);
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

void ThunderBall::SetplayerHit(bool _hit)
{
	playerhit = _hit;
}

void ThunderBall::SetY()
{
	BallY = -1000;
}

//int ThunderBall::SetXY(float _x, float _y)
//{
//	float Cloud_X = _x;
//	float Cloud_Y = _y;
//
//	BallX = Cloud_X;
//	BallY = Cloud_Y;
//
//	return TRUE;
//}

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

int ThunderBall::HitPlayer(BoxCollider _player)
{
	// 入ってきた値を代入
	int HitEnemy = HitBox(_player);

	switch (HitEnemy)
	{
	case 1:
		BallY = GetBoxSide(_player, 1) - (HEIGHT + 1);
		return 1;
		break;
	case 2:
		BallY = GetBoxSide(_player, 2) + 1;
		return 2;
		break;
	case 3:
		BallX = GetBoxSide(_player, 3) - (WIDTH + 1);
		return 3;
		break;
	case 4:
		BallX = GetBoxSide(_player, 4) + 1;
		return 4;
		break;
	default:
		return 0;
		break;
	}
	return 0;
}



