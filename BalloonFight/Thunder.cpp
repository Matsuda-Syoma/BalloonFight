#include "Thunder.h"
#include"ThunderBall.h"
#include <DxLib.h>
Thunder::Thunder()
{
	thunderball = new ThunderBall;
	FlashCount = 0;
	BallCount = 0;
	ThAnimImg;
	CloudX = 200, CloudY = 100;
	LoadImages();
}

Thunder::~Thunder()
{
}

void Thunder::Update()
{

	if (FlashCount < 100) {
		++FlashCount;
	}

	if (FlashCount >= 100) {
		ThAnimImg++;
			//printfDx("1");
			
			//BallAngle(0);
	}
	thunderball->Update();

	/*switch (Stage) {
	case 1:
		CloudX = 200, CloudY = 100;
		break;
	}*/

}

void Thunder::Draw() const
{
	
		if (FlashCount % 4) {
			DrawGraph(CloudX, CloudY, CloudImg[1], TRUE);
		}
		else if (FlashCount % 2) {
			(DrawGraph(CloudX, CloudY, CloudImg[2], TRUE));
		}
		else {
			(DrawGraph(CloudX, CloudY, CloudImg[0], TRUE));
		}
		
		
		thunderball->Draw();
}

//âÊëúì«çû
void Thunder::LoadImages()
{
	LoadDivGraph("Resources/images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, CloudImg);
	LoadDivGraph("Resources/images/Stage/Stage_ThunderAnimation.png", 6, 3, 1, 64, 64, ThunderImg);
	LoadDivGraph("Resources/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, ThunBallImg);
}

int Thunder::BallAngle(int _i) {
	return _i;
}