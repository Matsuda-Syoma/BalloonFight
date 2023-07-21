#include "Thunder.h"
#include <DxLib.h>
Thunder::Thunder()
{
	FlashCount = 0;
	BallCount = 0;
	LoadImages();
}

Thunder::~Thunder()
{
}

void Thunder::Update()
{
	
	if (FlashCount < 100) {
		FlashCount++;
	}
	if (BallCount < 3){
		BallCount++;
	
		if (BallCount == 3) {
		BallCount = 0;
		}
	}
}

void Thunder::Draw() const
{
	if (FlashCount % 4) {
		DrawGraph(200, 100, CloudImg[1], TRUE);
	}
	else if (FlashCount % 2) {
		(DrawGraph(200, 100, CloudImg[2], TRUE));
	}
	else {
		(DrawGraph(200, 100, CloudImg[0], TRUE));
	}

	if (FlashCount == 100) {
		if (BallCount == 3) {
			DrawGraph(400, 100, ThunBallImg[1], TRUE);
		}
		else if (BallCount == 2) {
			(DrawGraph(400, 100, ThunBallImg[2], TRUE));
		}
		else {
			(DrawGraph(400, 100, ThunBallImg[0], TRUE));
		}
	} 
}

//‰æ‘œ“Çž
void Thunder::LoadImages()
{
	LoadDivGraph("Resources/images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, CloudImg);
	LoadDivGraph("Resources/images/Stage/Stage_ThunderAnimation.png", 6, 3, 1, 64, 64, ThunderImg);
	LoadDivGraph("Resources/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, ThunBallImg);
}