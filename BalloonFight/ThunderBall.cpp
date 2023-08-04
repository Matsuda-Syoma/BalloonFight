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
	//�_�̓_��
	if (FlashCount < 100) {
		FlashCount++;
	}

	//�_�ł��I����
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


	// �ǁE�V��ł̔���
	if (BallX < 4 || BallX > 640 - 4) { // ���̕�
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
	if (BallY < 4) { // ��̕�
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

//�摜�Ǎ�
void ThunderBall::LoadImages()
{
	LoadDivGraph("Resources/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, ThunBallImg);
}

void ThunderBall::ChangeAngle()
{
	//�{�[���̔��ˊp�x
	float rad = BallAngle * (float)M_PI * 0.5;
	MoveX = (int)(Speed * cosf(rad));
	MoveY = (int)(Speed * sinf(rad));
}