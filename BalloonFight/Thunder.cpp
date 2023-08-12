#include "Thunder.h"
#include"ThunderBall.h"
#include <DxLib.h>
#include "common.h"

Thunder::Thunder()
{
	thunderball = new ThunderBall(0,0,0,0);
	FlashCount = 0;
	BallCount = 0;
	cu_Cnt= 0;
	CloudX = 200, CloudY = 100;
	CloudX2 = 200;
	CloudY2 = 100;
	FlFlg = false;
	current_flg = false;
	LoadImages();
}

Thunder::~Thunder()
{

}

void Thunder::Update()
{
	
	/*printfDx("  %d  ", Th_rund);*/
	// 10ïb
	if (BallCount < FRAMERATE * 3) {
		Th_rund = GetRand(3);
		++BallCount;
	}

	if (BallCount / 60 == 3) {
		FlFlg = true;
	}

	if (FlFlg == true) {
		//ì_ñ≈
		if (FlashCount < 100) {
			++FlashCount;
		}
	}
	// óéóãèàóù
	if (current_flg == true) {
		if (++WaitTime % 5 == 0) {
			cu_Cnt = cu_Cnt + 1;
		}
	}
}

void Thunder::Draw() const
{
	DrawGraph(CloudX + 20, CloudY, ThunderImg[3], TRUE);
		
		switch (cu_Cnt)
		{
		case 1:
			DrawGraph(CloudX+20, CloudY, ThunderImg[0], TRUE);
			break;
		case 2:
			DrawGraph(CloudX+20, CloudY, ThunderImg[1], TRUE);
			break;
		case 3:
			DrawGraph(CloudX+20, CloudY, ThunderImg[2], TRUE);
			break;
		case 4:
			DrawGraph(CloudX+20, CloudY, ThunderImg[3], TRUE);
			break;
		case 5:
			DrawGraph(CloudX+20, CloudY, ThunderImg[4], TRUE);
			break;
		}


	
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
	LoadDivGraph("Resources/images/Stage/Stage_ThunderAnimation.png", 6, 6, 1, 64, 64, ThunderImg);
	LoadDivGraph("Resources/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, ThunBallImg);
}

int Thunder::BallAngle(int _i) {
	return _i;
}

bool Thunder::ThunderSpawn() {
	if (FlashCount >= 100 && !ThFlg) {
		//thunderball->BallX = CloudX + 50;
		//thunderball->BallY = CloudY;
		ThFlg = true; 
		current_flg = true;
		return true;
	}
	return false;
}
int Thunder::GetRandSpawn()
{
	return Th_rund;
}

void Thunder::RandSpawn()
{
	switch (Th_rund)
	{
		// âEè„
	case 0:
		CloudX2 = CloudX + 100;
		break;
		// âEâ∫
	case 1:
		CloudX2 = CloudX + 100;
		CloudY2 = CloudY + 80;
		break;
		// ç∂â∫
	case 2:
		CloudX2 = CloudX-100;
		CloudY2 = CloudY + 80;
		break;
		// ç∂è„
	case 3:
		CloudX2 = CloudX;
		CloudY2 = CloudY;
		break;
	}
}


