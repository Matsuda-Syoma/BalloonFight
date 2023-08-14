#include "Thunder.h"
#include"ThunderBall.h"
#include <DxLib.h>
Thunder::Thunder()
{
	thunderball = new ThunderBall;
	FlashCount = 0;
	BallCount = 0;
	ThAnimImg = 0;
	WaitTime = 0;
	FlWait = 0;
	
	CloudX = 200, CloudY = 100;
	ThX = CloudX + 10, ThY = CloudY + 50;

	thunderball->BallX = CloudX + 50;
	thunderball->BallY = CloudY;

	
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

	//ˆîÈ
	if (FlashCount >= 100 && ThAnimImg < 6) {
		ThAnimImg++;
		FlashCount = 97;
		
	}
	
	//ˆîÈ‚ªÁ‚¦‚é
	if (ThAnimImg == 6 && WaitTime < 10) {
		WaitTime++;
		if (WaitTime == 10) {
			FlFlg = true;
		}
		else {
			FlFlg = false;
		}
	}

	//thunderball->Update();
}

void Thunder::Draw() const
{
	//ˆîÈ
	if (ThAnimImg > 0 && !FlFlg) {
		DrawGraph(ThX, ThY, ThunderImg[ThAnimImg - 1], TRUE);
	}

	//‰_‚Ì“_–Å
	if (FlashCount % 4 || FlashCount / 100) {
		DrawGraph(CloudX, CloudY, CloudImg[0], TRUE);
	}
	else if (FlashCount % 2) {
		(DrawGraph(CloudX, CloudY, CloudImg[2], TRUE));
	}
	else {
		(DrawGraph(CloudX, CloudY, CloudImg[1], TRUE));
	}
		
	

	//thunderball->Draw();

}

//‰æ‘œ“Çž
void Thunder::LoadImages()
{
	LoadDivGraph("Resources/images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, CloudImg);
	LoadDivGraph("Resources/images/Stage/Stage_ThunderAnimation.png", 6, 6, 1, 64, 64, ThunderImg);
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