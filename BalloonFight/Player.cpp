#include "common.h"
#include "Player.h"
#include "LoadSounds.h"
#include "PAD_INPUT.h"
#include <math.h>

enum class STATE {
	stay = 0,
	walk_right,
	walk_left,
	fly_right,
	fly_left,
	miss,
};
STATE state;

Player::Player()			// コンストラクタ
{
	w = WIDTH;
	h = HEIGHT;
	GroundspeedMax = 3.0f;
	FlyspeedMax = 3.0f;
	Init(2);
	LoadImages();
	AnimImg = 0;
	AnimWork = 0;
	state = STATE::stay;
	imageReverse = true;
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
	startX = 0.15f;
	jumpdelay = 0;
	AnimUpdateTime = 31;
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
	if (inertiaY < 150 && !landingflg || missflg) {
		inertiaY += 2.0 * (3 - ballon);
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
			PlaySoundMem(Sounds::SE_PlayerJump, DX_PLAYTYPE_BACK, true);
			jumpdelay = DELAY;
			if (groundflg) {
				groundflg = false;
				inertiaY -= 15.0f;
			}
			if (inertiaY > 0) {
				inertiaY -= 40.0f + (inertiaY / 6);
			}
			else {
				inertiaY -= 40.0f;				// 速度調整、いま上がるのが遅い
			}
			if (inertiaY < -150) {
				inertiaY = -150;
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
			inertiaX += startX;
			imageReverse = true;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 == 0 && inertiaX > 0 && landingflg) {
			inertiaX += -startX;
		}

		// 左入力
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -FlyspeedMax && !landingflg) {
			inertiaX -= 0.001f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -GroundspeedMax && landingflg) {
			inertiaX += -startX;
			imageReverse = false;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 == 0 && inertiaX < 0 && landingflg) {
			inertiaX += startX;
		}

		// 効果音の再生(足音)
		if (++speedX > 35 && inertiaX != 0 && landingflg) {
			PlaySoundMem(Sounds::SE_PlayerWalk, DX_PLAYTYPE_BACK, true);
			speedX = 0;
		}

		// 画面外に出たら反対側から出てくる
		if (x + WIDTH < 0) {
			x = SCREEN_WIDTH;
		}
		if (x > SCREEN_WIDTH) {
			x = 0 - WIDTH;
		}

		if (y < 0 - (WIDTH / 2)) {		// 画面上の跳ね返り
			y = 0 - ((WIDTH / 2));
			inertiaY *= -0.8f;
		}
	}

	//画面下に行った場合ミス
	if (y > SCREEN_HEIGHT) {
		Init(--life);
	}

	y += inertiaY / FRAMERATE;		// 仮の重力(フレーム数 * 風船の数)
	x += inertiaX;

	AnimUpdate();

}
// プレイヤーの描画
void Player::Draw() const
{
	DrawRotaGraph(imageX, imageY, 1.0f, 0, images[AnimImg],true, imageReverse);
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xff0000, false);
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
	AnimUpdateTime = 31;
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
void Player::AnimUpdate() {
	AnimUpdateTime++;
	switch (state)
	{
	case STATE::stay:
		if (AnimUpdateTime > 17) {
			if (AnimWork % 2 == 0) {
				if (ballon == 2) {
					AnimImg = 1;
				}
				if (ballon == 1) {
					AnimImg = 1 + 3;
				}
			}
			else if (AnimWork % 4 == 1) {
				if (ballon == 2) {
					AnimImg = 2;
				}
				if (ballon == 1) {
					AnimImg = 2 + 3;
				}
			}
			else {
				if (ballon == 2) {
					AnimImg = 0;
				}
				if (ballon == 1) {
					AnimImg = 0 + 3;
				}
			}
			AnimWork++;
			AnimUpdateTime = 0;
		}
		break;
	case STATE::walk_right:
		break;
	case STATE::walk_left:
		break;
	case STATE::fly_right:
		break;
	case STATE::fly_left:
		break;
	case STATE::miss:
		break;
	default:
		break;
	}
}