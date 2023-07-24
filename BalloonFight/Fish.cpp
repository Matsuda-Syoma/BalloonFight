#include "Fish.h"
#include"DxLib.h"
#include"common.h"
#include"LoadSounds.h"

// コンストラクタ
Fish::Fish(float _x, int _flg)
{
	imagecnt = -1;
	WeitTime = 0;
	flg = false;
	Animflg = _flg;
	x = _x;
	y = 400;
	w = WIDTH;
	h = HEIGHT;
	EatChanceTime = FRAMERATE;
	LoadDivGraph("Resources/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, image);

	
}

Fish::~Fish()
{

}

void Fish::Update()
{
	//if (player->GetY() > SCREEN_HEIGHT - 93 && player->GetX() > 170 && player->GetX() < 460 && player->GetFlg() == true) {
	//	player->Miss(1);
	//	Animflg= true; // アニメーション

	//	PlaySoundMem(Sounds::SE_Eatable, DX_PLAYTYPE_BACK, true);
	//	StopSoundMem(Sounds::SE_Falling);
	//}
	//else if (player->GetY() < SCREEN_HEIGHT - 94) {
	//	Animflg = false;
	//}

	if (++WeitTime % 11 == 0 && Animflg == true) {
		if (imagecnt < 5) {
			imagecnt++;
		}
		else {
			imagecnt = -1;
			Animflg = false;
		}
	}
	/*if (imagecnt >= 5) {
		imagecnt = 0;
	}*/

	imageX = x + (w / 2);
	imageY = y + (h / 2);


	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	if (--EatChanceTime < 0) {
		EatChanceTime = FRAMERATE ;
		EatChance = GetRand(9);
	}

}

void Fish::Draw() const
{
	//DrawBox(box.left, box.top, box.right, box.bottom, 0xffffff, false);
	DrawRotaGraph(imageX, imageY, 1.0f, 0, image[imagecnt], true);
}

bool Fish::GetFlg() {
	return flg;
}

void Fish::LoadImage()
{

	LoadDivGraph("Resources/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, image);
}

bool Fish::EatFlg(BoxCollider box) {
	if ((SCREEN_HEIGHT - 93) - box.GetSide(2) < 0 && box.GetSide(3) > 170 && box.GetSide(4) < 460) {
		return true;
	}
	else {
		return false;
	}
}

bool Fish::Eat(BoxCollider box) {
	if (EatChance >= 7) {
		Animflg = true; // アニメーション
		return true;
	}
	else {
		return false;
	}
}

void Fish::GetPlayerVector(float _x, float _y) {
	x = _x;
	//y = _y;
}