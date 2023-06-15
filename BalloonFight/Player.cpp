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
	speedMax = 3;
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

	// スティック操作時に0から1の間が出るようにする------------後で整数にする
	//speedX = round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
	//speedY = round(((float)PAD_INPUT::GetPadThumbLY() / 32767) * 100) / 100;

	// 落下処理
	if (inertiaY < 350) {
		inertiaY += 0.8;
	}

	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A)) {
		inertiaY -= 25+(inertiaY / 4);
	}

	y += inertiaY / (FRAMERATE * 1.0f);		// 仮の重力(フレーム数 * 風船の数)

	// プレイヤーの移動処理  -----(仮)
	x += speedX;

	//右
	//if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 < 1 && speedX < 5.6f) {

	//	speed += 0.1f;

	//}
	//else if (gPlayer.speed > 0.0f) {
	//	gPlayer.speed -= 0.2f;
	//}

	////左
	//if (gNowKey & PAD_INPUT_LEFT && gPlayer.speed > -5.6f) {
	//	gPlayer.speed -= 0.1f;
	//}
	//else if (gPlayer.speed < 0.0f) {
	//	gPlayer.speed += 0.2f;
	//}
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