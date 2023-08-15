#include "Thunder.h"
//#include"ThunderBall.h"
#include <DxLib.h>
#include "common.h"

Thunder::Thunder()
{
	Spawn_Cnt = 0;

	current_flg = 0;
	FlashCount = 0;
	BallCount = 0;
	cu_Cnt= 0;
	CloudX = 200, CloudY = 100;
	CloudX2 = 200;
	CloudY2 = 100;
	FlFlg = false;
	current_flg = false;
	ThFlg = false;
	LoadImages();
}

Thunder::~Thunder()
{

}

void Thunder::Update()
{
	

	/*printfDx("  %d  ", Th_rund);*/
	// 10秒
	if (BallCount < FRAMERATE * 3) {
		Th_rund = GetRand(3);
		++BallCount;
	}
	else {
		++Spawn_Cnt;
	}

	if (BallCount / 60 == 3) {
		FlFlg = true;
	}

	if (FlFlg == true) {
		//点滅
		if (FlashCount < 100) {
			++FlashCount;
		}
		else
		{
			current_flg = true;
		}
	}
	//printfDx("%d", Th_rund);
	switch (Th_rund)
	{
		// 右上
	case 0:
		thunderRota = 4.0f;
		thunder_x = 90;
		thunder_y;
		break;
		// 右下
	case 1:
		thunderRota = 5.0f;
		thunder_x = 100;
		thunder_y = 50;
		break;
		// 左下
	case 2:
		thunderRota = 1.0f;
		thunder_x = 40;
		thunder_y = 60;
		break;
		// 左上
	case 3:
		thunderRota = 2.0f;
		thunder_x = 20;
		thunder_y = 10;
		break;
	}

	// 落雷処理
	if (current_flg == true) {
		if (++WaitTime % 5 == 0) {
			cu_Cnt = cu_Cnt + 1;
		}
	}
	// 20秒たったら再スポーン処理
	if (Spawn_Cnt > FRAMERATE * 10) {
		Spawn_Cnt = 0;
		cu_Cnt = 0;
		ThFlg = false;
		FlFlg = false;
		current_flg = false;
		printfDx("Spawn");
	}

}

void Thunder::Draw() const
{
	DrawGraph(CloudX + 20, CloudY, ThunderImg[3], TRUE);
	
		if (FlashCount % 4) {
			DrawGraph(CloudX, CloudY, CloudImg[1], TRUE);
		}
		else if (FlashCount % 2) {
			(DrawGraph(CloudX, CloudY, CloudImg[2], TRUE));
		}
		else {
			(DrawGraph(CloudX, CloudY, CloudImg[0], TRUE));
		}

		// 落雷処理
		// thunderRotaがTh_rundの１から４で値が変わる
		if (current_flg) {
			DrawRotaGraph(CloudX + thunder_x, CloudY + thunder_y, 1.0f, thunderRota, ThunderImg[cu_Cnt], true);
		}

		/*thunderball->Draw();*/

}

//画像読込
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
	if (cu_Cnt >= 7 && !ThFlg) {
		//thunderball->BallX = CloudX + 50;
		//thunderball->BallY = CloudY;
		ThFlg = true; 
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
		// 右上
	case 0:
		CloudX2 = CloudX + 110;
		CloudY2 = CloudY - 25;
		break;
		// 右下
	case 1:
		CloudX2 = CloudX + 110;
		CloudY2 = CloudY + 65;
		break;
		// 左下
	case 2:
		CloudX2 = CloudX-10;
		CloudY2 = CloudY + 65;
		break;
		// 左上
	case 3:
		CloudX2 = CloudX-20;
		CloudY2 = CloudY-20;
		break;
	}
}


