#include "Thunder.h"
//#include"ThunderBall.h"
#include <DxLib.h>
#include "common.h"

Thunder::Thunder(int _Stage)
{

	// memo Set関数でplayerのthunderhit情報取得　trueなら変数hitを作り、mainでhit==trueならnullにする

	Stage = _Stage;
	Spawn_Cnt = 0;

	current_flg = 0;
	FlashCount = 0;
	BallCount = 0;
	cu_Cnt= 0;
	CloudX = 400, CloudY = 100;
	FlFlg = false;
	current_flg = false;
	ThFlg = false;

	Spawn_Cnt = 0;
	cu_Cnt = 0;
	BallCount = 0;
	if (Stage <= 2) {
		WCloud_flg = true;
	}
	LoadImages();
	switch (Stage)
	{
	case 1:
		CloudX = 400, CloudY = 100;
		break;
	case 2:
		CloudX = 100, CloudY = 300;
		CloudX2 = 500, CloudY2 = 270;
		break;
	case 3:
		CloudX = 100, CloudY = 150;
		CloudX2 = 500, CloudY2 = 400;
		break;
	case 4:
		CloudX = 150, CloudY = 70;
		CloudX2 = 500, CloudY2 = 280;
		break;
	case 5:
		CloudX = 100, CloudY = 100;
		CloudX2 = 400, CloudY2 = 300;
		break;
	}
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

	// 再スポーン処理
	if (Spawn_Cnt > FRAMERATE * 10) {
		
		Respawn();
	}

}

void Thunder::Draw() const
{
	DrawGraph(CloudX + 20, CloudY, ThunderImg[3], TRUE);
	
		if (FlashCount % 4) {
			DrawGraph(CloudX, CloudY, CloudImg[1], TRUE);
			if (WCloud_flg == true) { DrawGraph(CloudX2, CloudY2, CloudImg[1], TRUE); }

		}
		else if (FlashCount % 2) {
			(DrawGraph(CloudX, CloudY, CloudImg[2], TRUE));
			if (WCloud_flg == true) { (DrawGraph(CloudX2, CloudY2, CloudImg[2], TRUE)); }

		}
		else {
			(DrawGraph(CloudX, CloudY, CloudImg[0], TRUE));
			if (WCloud_flg == true) { (DrawGraph(CloudX2, CloudY2, CloudImg[0], TRUE)); }

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

void Thunder::Respawn()
{
	Spawn_Cnt = 0;
	cu_Cnt = 0;
	BallCount = 0;
	FlashCount = 0;
	ThFlg = false;
	FlFlg = false;
	current_flg = false;
}



void Thunder::RandSpawn()
{
	switch (Th_rund)
	{
		// 右上
	case 0:
		CloudX_Set = CloudX + 110;
		CloudY_Set = CloudY - 25;

		CloudX_Set2 = CloudX2 + 110;
		CloudY_Set2 = CloudY2 - 25;

		break;
		// 右下
	case 1:
		CloudX_Set = CloudX + 110;
		CloudY_Set = CloudY + 65;

		CloudX_Set2 = CloudX2 + 110;
		CloudY_Set2 = CloudY2 + 65;
		break;
		// 左下
	case 2:
		CloudX_Set = CloudX-10;
		CloudY_Set = CloudY + 65;

		CloudX_Set2 = CloudX2 - 10;
		CloudY_Set2 = CloudY2 + 65;
		break;
		// 左上
	case 3:
		CloudX_Set = CloudX-20;
		CloudY_Set = CloudY-20;

		CloudX_Set2 = CloudX2 - 20;
		CloudY_Set2 = CloudY2 - 20;
		break;
	}

}


