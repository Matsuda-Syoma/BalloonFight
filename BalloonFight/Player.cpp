#include "common.h"
#include "Player.h"
#include "LoadSounds.h"

Player::Player()			// コンストラクタ
{
	
	name = 'p';
	w = WIDTH;
	h = HEIGHT;
	GroundspeedMax = 3.0f;
	Init(3);
	LoadImages();
}

Player::~Player()			// デストラクタ
{
}

// 数値の初期化
void Player::Init(int _life) {
	life = _life;
	balloon = 2;
	x = 40;
	y = 400 - WIDTH;
	inertiaX = 0;
	inertiaY = 0;
	speedX = 0;
	startX = 0.15f;
	jumpdelay = 0;
	AnimFlg = 0;
	state = STATE::STAY;
	AnimUpdateTime = 0;
	AnimImg = 0;
	AnimWork = 0;
	imageReverse = true;
	flg = true;
	landingflg = false;
	groundflg = false;
	missflg = false;
	misssoundflg = false;
	spawnflg = false;
	thunderflg = false;
}

void Player::Update()		// プレイヤーの更新処理
{
	// プレイヤーの画像の中心座標
	imageX = x + (w / 2);
	imageY = y + (w / 2);

	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	FlyspeedMax = (balloon + 1);

		// 落下処理
	if (inertiaY < 150 && !landingflg || missflg) {
		if (flg && groundflg) {	
			AnimFlg = 0;
			state = STATE::FLY;
		}
		if (state != STATE::THUNDER) {
			inertiaY += 2.0 * (3 - balloon);
		}
	}

	/////////デバッグ処理
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_Y)) {
		BallonBreak(1);
	}

	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_X)) {
		Miss(2);
	}

	if (flg == true) {

		groundflg = landingflg;		// 滑らないようにする

		// ジャンプのクールタイム
		if (jumpdelay > 0) {
			--jumpdelay;
		}
		// Aボタンを押したときに上に加速、Bで1回のみ
		if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && jumpdelay <= 0 || PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_B) && jumpdelay <= 0) {
			AnimFlg = 0;
			state = STATE::FLY;
			PlaySoundMem(Sounds::SE_PlayerJump, DX_PLAYTYPE_BACK, true);
			jumpdelay = DELAY;
			if (groundflg) {
				groundflg = false;
				inertiaY -= 15.0f;
			}
			if (inertiaY > 0) {
				inertiaY -= 20.0f * (4 - balloon) + (inertiaY / 6);
			}
			else {
				inertiaY -= 20.0f * (4 - balloon);				// 速度調整、いま上がるのが遅い
			}
			if (inertiaY < -150) {
				inertiaY = -150;
			}
			// 右方向に入力したままAボタンを押したなら右に加速
			if (inputX() >= 0.3) {
				inertiaX += 1.0f;
				// 加速したときに速度上限なら速度を上限で固定
				if (inertiaX > FlyspeedMax) {
					inertiaX = FlyspeedMax;
				}
			}
			// 左方向に入力したままAボタンを押したなら左に加速
			if (inputX() <= -0.3) {
				inertiaX -= 1.0f;
				// 加速したときに速度上限なら速度を上限で固定
				if (inertiaX < -FlyspeedMax) {
					inertiaX = -FlyspeedMax;
				}
			}
		}

		// 右入力
		if (inputX() >= 0.3) {
			imageReverse = true;
			if (inertiaX < FlyspeedMax && !landingflg) {
				inertiaX += 0.001f;
			}
			else if (inertiaX < GroundspeedMax && landingflg) {
				state = STATE::WALK;
				inertiaX += startX - 0.05f;
			}
		}
		else if (inputX() == 0 && inertiaX > 0 && landingflg) {
			AnimFlg = 0;
			state = STATE::STAY;
			inertiaX += -startX;
		}

		// 左入力
		if (inputX() <= -0.3) {
			imageReverse = false;
			if (inertiaX > -FlyspeedMax && !landingflg) {
				inertiaX -= 0.001f;
			}
			else if (inertiaX > -GroundspeedMax && landingflg) {
				state = STATE::WALK;
				inertiaX += -startX + 0.05f;
			}
		}
		else if (fabsf(inputX()) < 0.1 && inertiaX < 0 && landingflg) {
			AnimFlg = 0;
			state = STATE::STAY;
			inertiaX += startX;
		}

		if (fabsf(inputX()) < 0.1 && inertiaX < 0.15f && inertiaX > -0.15f && landingflg) {
			AnimFlg = 0;
			state = STATE::STAY;
			inertiaX = 0;
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

		// 画面上の跳ね返り
		if (y < 0 - (WIDTH / 2)) {
			y = 0 - (WIDTH / 2);
			inertiaY *= -0.8f;
		}
	}


	if (state == STATE::MISS && !misssoundflg) {
			PlaySoundMem(Sounds::SE_Falling, DX_PLAYTYPE_BACK, true);
			misssoundflg = true;
	}

	// プレイヤーの座標更新
	y += inertiaY / FRAMERATE;		// 仮の重力(フレーム数 * 風船の数)
	x += inertiaX;

	// アニメーションの更新
	AnimUpdate();

}
// プレイヤーの描画
void Player::Draw() const
{
	DrawRotaGraph(imageX, imageY, 1.0f, 0, images[AnimImg],true, imageReverse);
	//DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xff0000, false);
}

// コントローラの入力を返す
float Player::inputX() {
	return round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
}

// 画像の読み込み
void Player::LoadImages() {
	LoadDivGraph("Resources/images/Player/Player_animation.png",32,8,4,64,64,images);
}

// プレイヤーが飛んでるか返す(1:上、2:下、3:左、4:右)
bool Player::IsFly(Stage box){
	HitStage = Player::HitBox(box);
	// 上側に当たったときの判定
	if (HitStage == 1) {
		landingflg = true;
		if (!groundflg && jumpdelay <= 0) {
			inertiaY = 0;
			//inertiaX = 0;
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
		inertiaY *= -RESTITUTION_COEFFICIENT;
	}
	// 左にあたった時の判定
	if (HitStage == 3) {
		x = GetBoxSide(box, 3) - (w + 1);
		imageReverse = !imageReverse;
		inertiaX *= -RESTITUTION_COEFFICIENT;
	}
	// 右にあたった時の判定
	if (HitStage == 4) {
		//x = GetBoxSide(box, 4) - (x - GetBoxSide(box, 4));
		x = GetBoxSide(box, 4) + 1;
		imageReverse = !imageReverse;
		inertiaX *= -RESTITUTION_COEFFICIENT;
	}
	landingflg = false;
	return false;
}

// プレイヤーのフラグを返す
bool Player::GetFlg() {
	return flg;
}

bool Player::GetSpawnFlg() {
	return spawnflg;
}

void Player::SetSpawnFlg(bool _flg) {
	spawnflg = _flg;
}

float Player::GetX() {
	return x;
}

float Player::GetY() {
	return y;
}

// 引数で数値を返す(1:上、2:下、3:左、4:右)
float Player::GetBoxSide(BoxCollider box ,int i) {
	return box.GetSide(i);
}

// ダメージ時に引数分風船を減らす
void Player::BallonBreak(int i) {
	PlaySoundMem(Sounds::SE_Splash, DX_PLAYTYPE_BACK, true);
	AnimUpdateTime = 31;
	if (state == STATE::STAY) {
		AnimImg += 3;
	}
	if (state == STATE::FLY) {
		AnimImg += 5;
	}
	balloon -= i;
	if (balloon <= 0) {
		Miss(0);
	}
}

// 0が落下、1がさかな、2が雷
void Player::Miss(int i) {
	flg = false;
	switch (i) {
		case 0:
			if (!missflg) {
				AnimUpdateTime = 0;
				AnimFlg = 0;
				state = STATE::MISS;
				inertiaX = 0.0f;
				inertiaY = -150.0f;
				missflg = true;
			}
			break;
		case 1:
			if (!missflg) {
				AnimFlg = 0;
				state = STATE::FISH;
				inertiaX = 0.0f;
				inertiaY = 0.0f;
				y = 480;
				missflg = true;
				thunderflg = true;
			}
			break;
		case 2:
			if (!missflg) {
				AnimUpdateTime = 0;
				AnimFlg = 0;
				state = STATE::THUNDER;
				inertiaX = 0.0f;
				inertiaY = 0.0f;
				missflg = true;
			}
			break;
	}
}

// プレイヤーのライフを返す
int Player::GetLife() {
	return life;
}

void Player::SetLife(int _life) {
	life = _life;
}

int Player::GetthunderHit()
{
	return thunderflg;
}

// アニメーションの更新
void Player::AnimUpdate() {
	AnimUpdateTime++;
	switch (state)
	{
	case STATE::STAY:
		AnimFlg = 0;
		if (AnimUpdateTime % 17 == 0) {
			if (AnimWork % 2 == 0) {
				if (balloon == 2) {
					AnimImg = 1;
				}
				if (balloon == 1) {
					AnimImg = 1 + 4;
				}
			}
			else if (AnimWork % 4 == 1) {
				if (balloon == 2) {
					AnimImg = 2;
				}
				if (balloon == 1) {
					AnimImg = 2 + 4;
				}
			}
			else {
				if (balloon == 2) {
					AnimImg = 0;
				}
				if (balloon == 1) {
					AnimImg = 0 + 4;
				}
			}
			AnimWork++;
			AnimUpdateTime = 0;
		}
		break;
	case STATE::WALK:
		if (AnimFlg == 0b0000) {
			if (balloon == 2) {
				AnimImg = 11;
			}
			if (balloon == 1) {
				AnimImg = 11 + 5;
			}
			AnimUpdateTime = 0;
			AnimFlg = 0b0010;
		}
		if (AnimUpdateTime < 3 * 3) {
			if (AnimUpdateTime % 3 == 0) {
				if (balloon == 2) {
					AnimImg--;
				}
				if (balloon == 1) {
					AnimImg--;
				}
			}
		}
		else {
			AnimImg = 10;
			if (balloon == 1) {//風船１個の時歩くと２個になるのを直すif
				AnimImg = 15;
			}
			AnimUpdateTime = 15;
			AnimFlg = 0b0000;
		}
		break;
	case STATE::FLY:
		if (AnimFlg == 0b0000) {
			if (balloon == 2) {
				AnimImg = 20;
			}
			if (balloon == 1) {
				AnimImg = 20 + 5;
			}
			AnimUpdateTime = 0;
			AnimFlg = 0b0100;
			if (!groundflg && jumpdelay <= 0) {
				if (balloon == 2) {
					AnimImg = 19;
				}
				if (balloon == 1) {
					AnimImg = 19 + 5;
				}
				AnimUpdateTime = 50;
			}
		}
		if (AnimFlg == 0b0100 && groundflg) {
			state = STATE::WALK;
		}
		if (AnimUpdateTime < 6) {
			if (AnimUpdateTime % 2 == 0) {
				if (balloon == 2) {
					AnimImg--;
				}
				if (balloon == 1) {
					AnimImg--;
				}
			}
		}
		else if (AnimUpdateTime < 12) {
			if (AnimUpdateTime % 2 == 0) {
				if (balloon == 2) {
					AnimImg++;
				}
				if (balloon == 1) {
					AnimImg++;
				}
			}
		}

		else if (AnimUpdateTime % 17 == 0) {
			if (AnimWork % 2 == 0) {
				if (balloon == 2) {
					AnimImg = 20;
				}
				if (balloon == 1) {
					AnimImg = 20 + 5;
				}
			}
			else if (AnimWork % 4 == 1) {
				if (balloon == 2) {
					AnimImg = 21;
				}
				if (balloon == 1) {
					AnimImg = 21 + 5;
				}
			}
			else {
				if (balloon == 2) {
					AnimImg = 19;
				}
				if (balloon == 1) {
					AnimImg = 19 + 5;
				}
			}
			AnimWork++;
		}
		break;
	case STATE::THUNDER:

		if (AnimFlg == 0b0000) {
			AnimImg = 30;
			AnimUpdateTime = 0;
			AnimFlg = 0b01000;
		}
		if (AnimFlg == 0b01000) {
			if (AnimUpdateTime % 2 == 0) {
				if (AnimWork % 2 == 0) {
					AnimImg = 29;
				}
				else {
					AnimImg = 30;
				}
				AnimWork++;
			}
			if (AnimUpdateTime > 60) {
				state = STATE::MISS;
			}
		}
		break;
	case STATE::FISH:
		AnimImg = -1;
		break;
	case STATE::MISS:
		if (AnimUpdateTime > 2) {
			if (AnimWork % 3 == 0) {
				AnimImg = 29;
			}
			else {
				AnimImg--;
			}
			AnimWork++;
			AnimUpdateTime = 0;
		}
		break;
	default:
		break;
	}
}

int Player::HitEnemy(BoxCollider _enemy,int _state) {

	int HitEnemy = HitBox(_enemy);
	if (HitEnemy != 0 && _state == 0) {
		return 5;
	}
	switch (HitEnemy)
	{
	case 1:
		y = GetBoxSide(_enemy, 1) - (h + 1);
		inertiaY *= -RESTITUTION_COEFFICIENT;
		return 1;
		break;
	case 2:
		y = GetBoxSide(_enemy, 2) + 1;
		inertiaY *= -RESTITUTION_COEFFICIENT;
		return 2;
		break;
	case 3:
		x = GetBoxSide(_enemy, 3) - (w + 1);
		inertiaX *= -RESTITUTION_COEFFICIENT;
		return 3;
		break;
	case 4:
		x = GetBoxSide(_enemy, 4) + 1;
		inertiaX *= -RESTITUTION_COEFFICIENT;
		return 4;
		break;
	default:
		return 0;
		break;
	}

}

bool Player::DamageCheck(BoxCollider _enemy, int _balloon, int _state) {
	float thisY = y - h / 2;
	float otherY = _enemy.GetCenterY();
	if (thisY - otherY > 20 && _balloon == 1) {
		BallonBreak(1);
		return false;
	}
	else if (thisY - otherY < -20) {
		return true;
	}
	else if (_state == 0 && _balloon != 1) {
		return true;
	}
	return false;
}