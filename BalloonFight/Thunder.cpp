#include "Thunder.h"
#include"ThunderBall.h"
#include <DxLib.h>
Thunder::Thunder()
{
	thunderball = new ThunderBall;
	FlashCount = 0;
	BallCount = 0;
	
	CloudX = 200, CloudY = 100;
	thunderball->BallX = CloudX + 50;
	thunderball->BallY = CloudY;

	
	LoadImages();
}

Thunder::~Thunder()
{
}

void Thunder::Update()
{
	//“_–Å
	if (FlashCount < 100) {
		++FlashCount;
	}

	//thunderball->Update();
}

void Thunder::Draw() const
{
	
		DrawGraph(100, 200, ThunderImg[0], TRUE);

	
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

//‰æ‘œ“Çž
void Thunder::LoadImages()
{
	LoadDivGraph("Resources/images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, CloudImg);
	LoadDivGraph("Resources/images/Stage/Stage_ThunderAnimation.png", 6, 3, 1, 64, 64, ThunderImg);
	LoadDivGraph("Resources/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, ThunBallImg);
}

int Thunder::BallAngle(int _i) {
	return _i;
}

bool Thunder::ThunderSpawn() {
	if (FlashCount >= 100 && !ThFlg) {
		ThFlg = true; 
		return true;
	}
	return false;
}