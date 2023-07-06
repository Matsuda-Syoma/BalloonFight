#include "common.h"
#include "Player.h"
#include "PAD_INPUT.h"
#include <math.h>

Player::Player()			// コンストラクタ
{
	w = WIDTH;
	h = HEIGHT;
	GroundspeedMax = 2.0f;
	FlyspeedMax = 3.0f;
	Init(3);
	LoadImages();
}

Player::~Player()			// デストラクタ
{
}

// 数値の初期化
void Player::Init(int _life) {
	flg = true;
	landingflg = false;
	groundflg = false;
	missflg = false;
	life = _life;
	ballon = 2;
	x = 40;
	y = 440 - WIDTH;
	inertiaX = 0;
	inertiaY = 0;
	speedX = 0;
	speedY = 0;
	jumpdelay = 0;
}

void Player::Update()		// プレイヤーの更新処理
{
	// プレイヤーの画像の中心座標
	imageX = x + (w / 2);
	imageY = y + (h / 2);

	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

		// 落下処理
	if (inertiaY < 325 && !landingflg || missflg) {
		inertiaY += 1.5 * (3 - ballon);
	}

	/////////デバッグ処理
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_Y)) {
		BallonBreak(1);
	}

	if (flg == true) {

		groundflg = landingflg;		// 滑らないようにする

		// ジャンプのクールタイム
		if (jumpdelay > 0) {
			--jumpdelay;
		}

		// Aボタンを押したときに上に加速
		//if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A) && jumpdelay <= 0) {
		if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && jumpdelay <= 0) {	//////////自動連打
			jumpdelay = DELAY;
			if (groundflg) {
				groundflg = false;
				inertiaY -= 5.0f;
			}
			if (inertiaY > 0) {
				inertiaY -= 25.0f + (inertiaY / 4);
			}
			else {
				inertiaY -= 50.0f;				// 速度調整、いま上がるのが遅い
			}
			// 右方向に入力したままAボタンを押したなら右に加速
			if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1) {
				inertiaX += 1.0f;
				// 加速したときに速度上限なら速度を上限で固定
				if (inertiaX > FlyspeedMax) {
					inertiaX = FlyspeedMax;
				}
			}
			// 左方向に入力したままAボタンを押したなら左に加速
			if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1) {
				inertiaX -= 1.0f;
				// 加速したときに速度上限なら速度を上限で固定
				if (inertiaX < -FlyspeedMax) {
					inertiaX = -FlyspeedMax;
				}
			}
		}

		// 右入力
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1 && inertiaX < FlyspeedMax && !landingflg) {
			inertiaX += 0.001f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1 && inertiaX < GroundspeedMax && landingflg) {
			inertiaX += 0.25f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 == 0 && inertiaX > 0 && landingflg) {
			inertiaX += -0.25f;
		}

		// 左入力
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -FlyspeedMax && !landingflg) {
			inertiaX -= 0.001f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -GroundspeedMax && landingflg) {
			inertiaX += -0.25f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 == 0 && inertiaX < 0 && landingflg) {
			inertiaX += 0.25f;
		}

		// 画面外に出たら反対側から出てくる
		if (x + WIDTH < 0) {
			x = SCREEN_WIDTH;
		}
		if (x > SCREEN_WIDTH) {
			x = 0 - WIDTH;
		}

		if (y < 0) {		// 画面上の跳ね返り
			y = 0 - (y - 0);
			inertiaY *= -0.8f;
		}
	}

	//画面下に行った場合ミス
	if (y > SCREEN_HEIGHT) {
		Init(--life);
	}

	y += inertiaY / FRAMERATE;		// 仮の重力(フレーム数 * 風船の数)
	x += inertiaX;


}
// プレイヤーの描画
void Player::Draw() const
{
	DrawGraph(x, y, images[0], true);
	DrawFormatString(x +(w / 3), y - 20, 0xffffff, "%d", ballon);
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xff0000, false);
	DrawCircle(x, y, 2, 0xffffff);
	
	
}

void Player::LoadImages() {
	LoadDivGraph("Resources/images/Player/Player_animation_d.png",32,8,4,64,64,images);
}

bool Player::IsFly(Stage box){
	HitStage = Player::HitBox(box);
	if (HitStage == 1) {
		landingflg = true;
		if (!groundflg && jumpdelay <= 0) {
			inertiaY = 0;
			inertiaX = 0;
			groundflg = true;
		}
		if (jumpdelay <= DELAY - 1) {
			y = GetBoxSide(box,1) - h;
		}
		return true;
		}

	// 下側にあたった時の判定
	if (HitStage == 2) {
		//y = GetBoxSide(box, 2) - (y - GetBoxSide(box, 2));
		y = GetBoxSide(box, 2) + 1;
		inertiaY *= -0.8f;
	}
	// 左にあたった時の判定
	if (HitStage == 3) {
		x = GetBoxSide(box, 3) - (w + 1);
		inertiaX *= -0.8f;
	}
	// 右にあたった時の判定
	if (HitStage == 4) {
		//x = GetBoxSide(box, 4) - (x - GetBoxSide(box, 4));
		x = GetBoxSide(box, 4) + 1;
		inertiaX *= -0.8f;
	}
	landingflg = false;
	return false;
}

bool Player::IsFlg() {
	return flg;
}

// 引数で数値を返す(1:上、2:下、3:左、4:右)
float Player::GetBoxSide(Stage box ,int i) {
	return box.GetSide(i);
}

// 0以下ならtrueが返る
void Player::BallonBreak(int i) {
	ballon -= i;
	if (ballon <= 0) {
		flg = false;
		Miss(0);
	}
}

// 0が落下、1がさかな
void Player::Miss(int i) {
	switch (i) {
		case 0:
			if (!missflg) {
				inertiaX = 0.0f;
				inertiaY = -150.0f;
				missflg = true;
			}
			break;
	}
}

int Player::GetLife() {
	return life;
}