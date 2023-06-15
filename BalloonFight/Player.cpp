#include "common.h"
#include "Player.h"
#include "PAD_INPUT.h"
#include <math.h>

Player::Player()			// コンストラクタ
{
	flg = true;
	life = 3;
	x = 40;
	y = 96;
	w = WIDTH;
	h = HEIGHT;
	inertiaX = 0;
	inertiaY = 0;
	speedX = 0;
	speedY = 0;
	speedMax = 3.0f;
	LoadImages();
}

Player::~Player()			// デストラクタ
{
}

void Player::Update()		// プレイヤーの更新処理
{
	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	// プレイヤーの画像の中心座標
	imageX = x + (w / 2);
	imageY = y + (h / 2);

	// スティック操作時に0から1の間が出るようにする------------後で整数にする
	//speedX = round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
	//speedY = round(((float)PAD_INPUT::GetPadThumbLY() / 32767) * 100) / 100;

	// 落下処理
	if (inertiaY < 350) {
		inertiaY += 1.5;
	}

	// Aボタンを押したときに上に加速
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A)) {
		if (inertiaY > 0) {
			inertiaY -= 25 + (inertiaY / 4);
		}
		else {
			inertiaY -= 50;
		}

		//右方向に入力したままAボタンを押したなら右に加速
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1) {
			inertiaX += 1.0f;
			// 加速したときに速度上限なら速度を上限で固定
			if (inertiaX > speedMax) {
				inertiaX = speedMax;
			}
		}
		//左方向に入力したままAボタンを押したなら左に加速
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1) {
			inertiaX -= 1.0f;
			// 加速したときに速度上限なら速度を上限で固定
			if (inertiaX < -speedMax) {
				inertiaX = -speedMax;
			}
		}
	}

	y += inertiaY / (FRAMERATE * 1.0f);		// 仮の重力(フレーム数 * 風船の数)
	x += inertiaX;

	//右入力
	if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1 && inertiaX < speedMax) {
		inertiaX += 0.001f;
	}

	//左入力
	if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -speedMax) {
		inertiaX -= 0.001f;
	}

	// 画面外に出たら反対側から出てくる
	if (x + WIDTH < 0) {
		x = SCREEN_WIDTH;
	}

	if (x > SCREEN_WIDTH) {
		x = 0 - WIDTH;
	}

	if (y > SCREEN_HEIGHT) {
		y = 90;
	}
	if (y < 0) {
		inertiaY *= -0.8f;
	}

}

void Player::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom, 0xff0000, true);
}

void Player::LoadImages() {
	for (int i = 0; i < 3; i++) {
		images[i] = 0;
	}
}

bool Player::IsFly(BoxCollider box) const{
	if (Player::HitBox(box)) {
		return true;
	}
	return false;
}