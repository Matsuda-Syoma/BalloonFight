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

	if (y > SCREEN_HEIGHT) {
		y = 90;
	}

	// スティック操作時に0から1の間が出るようにする
	speedX = round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
	speedY = round(((float)PAD_INPUT::GetPadThumbLY() / 32767) * 100) / 100;

	// 落下処理
	if (inertiaY < 75) {
		inertiaY += 0.2;
	}
	y += inertiaY / (60 * 2.0f);		// 仮の重力(フレーム数 * 風船の数)

	// プレイヤーの移動処理  -----(仮)
	x += speedX * speedMax;
}

void Player::Draw() const
{
	DrawCircle(imageX, imageY, 4, 0xffffff);
}

void Player::LoadImages() {
	for (int i = 0; i < 3; i++) {
		images[i] = 0;
	}
}

bool IsFly(BoxCollider boxcollider) {
	if (Player::HitBox()) {
		return true;
	}
	
}