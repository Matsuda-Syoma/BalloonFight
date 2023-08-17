#include "Thunder.h"
//#include"ThunderBall.h"
#include <DxLib.h>
#include "common.h"

Thunder::Thunder(int _Stage)
{

	// memo Set関数でplayerのthunderhit情報取得　trueなら変数hitを作り、mainでhit==trueならnullにする

	Stage = _Stage;
	Spawn_Cnt = 0;

	
	FlashCount = 0;
	BallCount = 0;
	cu_Cnt= 0;
	CloudX = 400, CloudY = 100;
	FlFlg = false;
	current_flg = false;
	ThFlg = false;
	
	WCloud_flg = true;
	
	Spawn_Cnt = 0;
	cu_Cnt = 0;
	BallCount = 0;
	LoadImages();
	switch (Stage)
	{
	case 0:
		CloudX = 295, CloudY = 86;	//ステージ１
		break;
	case 1:
		CloudX = 55, CloudY = 222;	//ステージ２
		CloudX2 = 455, CloudY2 = 185;
		break;
	case 2:
		CloudX = 55, CloudY = 120;	//ステージ３
		CloudX2 = 415, CloudY2 = 255;
		break;
	case 3:
		CloudX = 135,CloudY = 85;	//ステージ４
		CloudX2 = 455, CloudY2 = 155;
		break;
	case 4:
		CloudX = 55, CloudY = 85;		//ステージ５
		CloudX2 = 335, CloudY2 = 120;
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
	if (BallCount < FRAMERATE * 10) {
		Th_rund = GetRand(3);
		if (BallCount < FRAMERATE * 2) {
			Th_rund2 = GetRand(3);
		}
		
		
		++BallCount;
	}
	else {
		++Spawn_Cnt;
	}

	if (BallCount / 60 == 10) {
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

	switch (Th_rund2)
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
			if (cu_Cnt > 10) {
				cu_Cnt = 11;
			}
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
		if (current_flg && WCloud_flg==true) {
			DrawRotaGraph(CloudX2 + thunder_x, CloudY2 + thunder_y, 1.0f, thunderRota, ThunderImg[cu_Cnt], true);
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
		ThFlg = true; 
		return true;
	}
	
	return false;
}
int Thunder::GetRandSpawn()
{
	return Th_rund;
}

int Thunder::GetRandSpawn2()
{
	return Th_rund2;
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

		break;
		// 右下
	case 1:
		CloudX_Set = CloudX + 110;
		CloudY_Set = CloudY + 65;
		break;
		// 左下
	case 2:
		CloudX_Set = CloudX-10;
		CloudY_Set = CloudY + 65;
		break;
		// 左上
	case 3:
		CloudX_Set = CloudX-20;
		CloudY_Set = CloudY-20;
		break;
	}

	switch (Th_rund2)
	{
		// 右上
	case 0:
	
		CloudX_Set2 = CloudX2 + 110;
		CloudY_Set2 = CloudY2 - 25;

		break;
		// 右下
	case 1:
		
		CloudX_Set2 = CloudX2 + 110;
		CloudY_Set2 = CloudY2 + 65;
		break;
		// 左下
	case 2:
		
		CloudX_Set2 = CloudX2 - 10;
		CloudY_Set2 = CloudY2 + 65;
		break;
		// 左上
	case 3:
		
		CloudX_Set2 = CloudX2 - 20;
		CloudY_Set2 = CloudY2 - 20;
		break;
	}

}


