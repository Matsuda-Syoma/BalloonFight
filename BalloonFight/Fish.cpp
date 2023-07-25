#include "Fish.h"
#include"DxLib.h"
#include"common.h"
#include"LoadSounds.h"

// コンストラクタ
Fish::Fish(float _x, int _flg,int _pflg)
{
	imagecnt = -1;
	WeitTime = 0;
	flg = false;
	Animflg = _flg;
	PlayerEat = TRUE;
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
	clsDx();
	printfDx("%d", imagecnt);
	if (++WeitTime % 11 == 0 && imagecnt != 5 && Animflg) {
		if (imagecnt >= 6) {
			imagecnt = 3;
		}
		if (imagecnt < 5) {
			imagecnt++;
		}
		else {
			imagecnt = -1;
			Animflg = false;
		}
		// プレイヤーが食べられた判定になったら
		if (PlayerEat == TRUE && imagecnt == 2) {
			imagecnt = 6;
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

	// 1秒経ったら入る
	if (--EatChanceTime < 0) {
		EatChanceTime = FRAMERATE ;// カウントを戻す
		EatChance = GetRand(9);// 0~9のどれかを代入
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
	if (EatChance >= 0) {
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