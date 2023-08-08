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
	PlayerEat = false;
	EatFlg = false;
	EatTime = 0;
	EatY = 0;
	x = _x;
	w = WIDTH;
	h = HEIGHT;
	EatChanceTime = FRAMERATE;
	LoadDivGraph("Resources/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, image);
	flg1 = false;
	
}

Fish::~Fish()
{

}

void Fish::Update()
{
	x = EatTargetWork.GetSide(3);

	if (x < 170) {
		x = 170;
	}
	if (x > 460) {
		x = 460;
	}
	
	if (PlayerEat && imagecnt == 2) {
		imagecnt = 6;
	}
	if (++WeitTime % 15 == 0 && imagecnt == 5) {
		imagecnt = -1;
	}
	if (++WeitTime % 15 == 0 && imagecnt != 5 && Animflg) {
		if (imagecnt >= 6) {
			imagecnt = 3;
		}
		if (imagecnt < 5) {
			imagecnt++;
		}
		else {
			imagecnt = -1;
		}
	}

	if (imagecnt <= -1) {
		PlayerEat = false;
		Animflg = false;
		flg1 = false;
		EatTarget.name = 'n';
	}


	y = SCREEN_HEIGHT - 40 + EatY;

	if (imagecnt == -1) {
		EatY = 0;
	}

	if (EatFlg) {
		if (EatY > -30 && imagecnt < 3) {
			EatY+= -2;
		}
	}
	else if (EatY < 0 && !EatFlg) {
		EatY+=1;
	}

	imageX = x + (w / 2);
	imageY = y + (h / 2);

	// 1秒経ったら入る
	if (--EatChanceTime < 0) {
		EatChanceTime = FRAMERATE ;// カウントを戻す
		EatChance = GetRand(9);// 0~9のどれかを代入
	}

}

void Fish::Draw() const
{
	//DrawBox(imageX - 12, ((SCREEN_HEIGHT - 60) + EatY), imageX + 12, 480, 0xffffff, false);
	DrawRotaGraph(imageX, imageY, 1.0f, 0, image[imagecnt], true,ImageReverse);
}

bool Fish::GetFlg() {
	return flg;
}

void Fish::LoadImage()
{
	LoadDivGraph("Resources/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, image);
}

bool Fish::Eat(BoxCollider box) {
	EatTarget = box;
	if (PlayerEat) {
		return false;
	}
	if ((SCREEN_HEIGHT - 90) - box.GetSide(2) < 0 && SCREEN_HEIGHT > box.GetSide(1) && box.GetSide(3) > 170 && box.GetSide(4) < 460) {
		if (box.name == EatTarget.name) {
			EatTargetWork = EatTarget;
			EatFlg = true;
		}
		if(EatChance < 9){
			Animflg = true;
			flg1 = true;
		}
		if (imagecnt == 2 && WeitTime % 15 == 0) {
			if (((SCREEN_HEIGHT - 60) + EatY) - EatTargetWork.GetSide(2) < 0) {
				PlayerEat = true;
				return true;
			}
		}
	}
	return false;
}

void Fish::GetTarget(BoxCollider box) {
	if ((SCREEN_HEIGHT - 90) - box.GetSide(2) < 0 && SCREEN_HEIGHT > box.GetSide(1) && box.GetSide(3) > 170 && box.GetSide(4) < 460) {
		EatTarget = box;
	}
}

