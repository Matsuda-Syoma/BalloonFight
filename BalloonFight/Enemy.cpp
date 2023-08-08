#include "enemy.h"
#include "common.h"
#include "DxLib.h"
#include "LoadSounds.h"
// 画像モード分け

// コンストラクタ
Enemy::Enemy(float _x,float _y)
{
	name = 'e';

	w = WIDTH;
	h = HEIGHT;

	flg = true;
	imageReverse = true;
	deathflg = false;
	startflg = false;
	x = _x;
	y = _y - WIDTH;

	balloon = 0;
	color = GetRand(2);

	FlyspeedMax = 2;
	inertiaX = 0;
	inertiaY = 0;
	MoveX = 1;
	MoveY = GetRand(1);
	RandomMoveX = 0;
	RandomMoveY = 0;

	MaxRandomMoveX = GetRand(5) + 1 * FRAMERATE;
	MaxRandomMoveY = GetRand(2) + 2 * FRAMERATE;
	jumpdelay = 0;

	state = STATE::STAY;

	AnimFlg = 0;
	AnimUpdateTime = 0;
	AnimImg = 0;
	AnimWork = 0;

	LoadImages();
}

// デストラクタ
Enemy::~Enemy()
{

}

void Enemy::E_Init(int _life)
{
	
}

void Enemy::Update()
{
	// 敵の画像の中心座標
	imageX = x + (w / 2);
	imageY = y + (w / 2);

	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	if (inertiaY < 150 / (2 - balloon) && !landingflg || deathflg) {
		if (!deathflg && !groundflg) {
			//AnimFlg = 0;
			state = STATE::FLY;
		}
		inertiaY += 1.0;
		if (deathflg) {
			inertiaY += 4.0;
		}
	}

	groundflg = landingflg;

	if (jumpdelay > 0) {
		--jumpdelay;
	}
	// 横移動するかどうかを決める
	if (++RandomMoveX > MaxRandomMoveX || MoveX == 0) {
		MoveX = GetRand(2) - 1;
		RandomMoveX = 0;
		MaxRandomMoveX = GetRand(2) + 3 * FRAMERATE;
	}
	// 横移動する
	if (state == STATE::FLY) {
		inertiaX += MoveX * 0.01;
	}
	// 速度上限を超えたら速度を固定する
	if (inertiaX > FlyspeedMax) {
		inertiaX = FlyspeedMax;
	}
	if (inertiaX < -FlyspeedMax) {
		inertiaX = -FlyspeedMax;
	}
	// 上昇するかどうかを決める
	if (++RandomMoveY > MaxRandomMoveY) {
		MoveY = GetRand(1);
		RandomMoveY = 0;
		MaxRandomMoveY = GetRand(3) + 2 * FRAMERATE;
	}
	// 上昇する
	if (MoveY == 1 && jumpdelay <= 0 && balloon == 1) {
		AnimFlg = 0;
		state = STATE::FLY;
		if (!CheckSoundMem(Sounds::SE_EnemyMove)) {
			PlaySoundMem(Sounds::SE_EnemyMove, DX_PLAYTYPE_BACK, true);
		}
		jumpdelay = DELAY;
		if (groundflg) {
			groundflg = false;
			inertiaY -= 15.0f;
		}
		if (inertiaY > 0) {
			inertiaY -= 10.0f + (inertiaY / 6);
		}
		else {
			inertiaY -= 10.0f;				// 速度調整、いま上がるのが遅い
		}
		// 上昇速度上限を超えたら速度を固定する
		if (inertiaY < -75) {
			inertiaY = -75;
		}
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

	if (state == STATE::FLY) {
		imageReverse = MoveX + 1;
	}


	y += inertiaY / FRAMERATE;		// 仮の重力(フレーム数 * 風船の数)
	x += inertiaX;

	AnimUpdate();

	if (balloon != 1 && AnimUpdateTime > 210 && state == STATE::STAY) {
		// 風船の数を増やす
		balloon = 1;
		MoveY = 1;
		RandomMoveY = 0;
		MaxRandomMoveY = 3 * FRAMERATE;
		state = STATE::FLY;
	}
}

void Enemy::Draw() const
{
	switch (color)
	{
	case 0:
		DrawRotaGraph(imageX, imageY, 1.0f, 0, imagesP[AnimImg], true, imageReverse);
		break;
	case 1:
		DrawRotaGraph(imageX, imageY, 1.0f, 0, imagesG[AnimImg], true, imageReverse);
		break;
	case 2:
		DrawRotaGraph(imageX, imageY, 1.0f, 0, imagesR[AnimImg], true, imageReverse);
		break;
	default:
		break;
	}
	//DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xffffff, false);
}

void Enemy::LoadImages()
{
	LoadDivGraph("Resources/images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, imagesG);
	LoadDivGraph("Resources/images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, imagesR);
	LoadDivGraph("Resources/images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, imagesP);
}

bool Enemy::IsFly(Stage box) {
	HitStage = Enemy::HitBox(box);
	// 上側に当たったときの判定
	if (HitStage == 1) {
		landingflg = true;
		if (!groundflg && jumpdelay <= 0) {
			inertiaY = 0;
			MoveY = 1;
			RandomMoveY = 0;
			MaxRandomMoveY = GetRand(3) + 2 * FRAMERATE;
			groundflg = true;
			if (balloon != 1) {
				AnimFlg = 0;
				state = STATE::STAY;
				inertiaX = 0;
			}
		}
		if (jumpdelay <= DELAY - 1) {
			y = GetBoxSide(box, 1) - h;
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
		imageReverse = !imageReverse;
		inertiaX *= -0.8f;
	}
	// 右にあたった時の判定
	if (HitStage == 4) {
		//x = GetBoxSide(box, 4) - (x - GetBoxSide(box, 4));
		x = GetBoxSide(box, 4) + 1;
		imageReverse = !imageReverse;
		inertiaX *= -0.8f;
	}
	landingflg = false;
	return false;
}

float Enemy::GetBoxSide(BoxCollider box, int i) {
	return box.GetSide(i);
}

float Enemy::GetX() {
	return x;
}

float Enemy::GetY() {
	return y;
}

bool Enemy::GetFlg() {
	return flg;
}

void Enemy::SetFlg(bool _flg) {
	flg = _flg;
}

bool Enemy::GetDeathFlg() {
	return deathflg;
}

int Enemy::GetBalloon() {
	return balloon;
}

int Enemy::GetState() {
	return (int)state;
}

void Enemy::ChangeInertia(BoxCollider _player, int i) {
	switch (i)
	{
	case 1:
		y = GetBoxSide(_player, 2) + 1;
		inertiaY *= -RESTITUTION_COEFFICIENT;
		break;
	case 2:
		y = GetBoxSide(_player, 1) - (h + 1);
		inertiaY *= -RESTITUTION_COEFFICIENT;
		break;
	case 3:
		x = GetBoxSide(_player, 4) + 1;
		inertiaX *= -RESTITUTION_COEFFICIENT;
		break;
	case 4:
		x = GetBoxSide(_player, 3) - (w + 1);
		inertiaX *= -RESTITUTION_COEFFICIENT;
		break;
	default:
		break;
	/*case 1:
		y = GetBoxSide(_player, 1) - (h + 1);
		break;
	case 2:
		y = GetBoxSide(_player, 2) + 1;
		inertiaY *= -0.8f;
		break;
	case 3:
		x = GetBoxSide(_player, 3) - (w + 1);
		inertiaX *= -0.8f;
		break;
	case 4:
		x = GetBoxSide(_player, 4) + 1;
		inertiaX *= -0.8f;
		break;*/
	}
}

int Enemy::HitEnemy(BoxCollider _enemy) {

	int HitEnemy = HitBox(_enemy);

	switch (HitEnemy)
	{
	case 1:
		y = GetBoxSide(_enemy, 1) - (h + 1);
		inertiaY *= -0.8f;
		return 1;
		break;
	case 2:
		y = GetBoxSide(_enemy, 2) + 1;
		inertiaY *= -0.8f;
		return 2;
		break;
	case 3:
		x = GetBoxSide(_enemy, 3) - (w + 1);
		inertiaX *= -0.8f;
		return 3;
		break;
	case 4:
		x = GetBoxSide(_enemy, 4) + 1;
		inertiaX *= -0.8f;
		return 4;
		break;
	default:
		return 0;
		break;
	}

}

void Enemy::BallonBreak(int i) {
	PlaySoundMem(Sounds::SE_Splash, DX_PLAYTYPE_BACK, true);
	AnimFlg = 0;
	AnimUpdateTime = 0;
	balloon -= i;
	inertiaX = 0;
	inertiaY = 0;
	if (balloon < 0) {
		AnimImg = 14;
		Death(0);
	}
}


// 0が落下、1がさかな
void Enemy::Death(int i) {
	switch (i) {
	case 0:
		if (!deathflg) {
			AnimUpdateTime = 0;
			AnimFlg = 0;
			state = STATE::MISS;
			inertiaX = 0.0f;
			inertiaY = -100.0f;
			deathflg = true;
		}
		break;
	case 1:
		if (!deathflg) {
			AnimUpdateTime = 0;
			AnimFlg = 0;
			state = STATE::FISH;
			inertiaX = 0.0f;
			inertiaY = 0.0f;
			y = 480;
			deathflg = true;
		}
		break;
	}
}



void Enemy::AnimUpdate()
{
	AnimUpdateTime++;
	switch (state)
	{
	case STATE::STAY:
		if (AnimFlg == 0b0000) {
			AnimImg = 0;
			AnimUpdateTime = 0;
			balloondelay = 0;
			AnimFlg = 0b0001;
			if (!startflg) {
				AnimUpdateTime = 60;
				startflg = true;
			}
		}
		if (AnimUpdateTime % 10 == 0) {
			AnimWork++;
			if (AnimUpdateTime > 60 && AnimUpdateTime < 210) {
				if (AnimWork % 2 == 0) {
					if (balloondelay < 3) {
						if (GetRand(10) < 4 || AnimWork % 6 == 0) {
							balloondelay++;
						}
					}
					AnimImg = balloondelay * 2;
				}
				else {
					AnimImg++;
				}
			}
		}
		break;
	case STATE::FLY:
		if (AnimFlg == 0b0000) {
			if (balloon == 1) {
				AnimImg = 11;
			}
			if (balloon == 0) {
				AnimImg = 14;
			}
			AnimUpdateTime = 0;
			AnimFlg = 0b0100;
			if (!groundflg && jumpdelay <= 0) {
				if (balloon == 1) {
					AnimImg = 10;
				}
			}
		}
		if (AnimUpdateTime < 6) {
			if (AnimUpdateTime % 2 == 0) {
				if (balloon == 1) {
					AnimImg--;
				}
				if (balloon == 0) {
					AnimImg++;
				}
			}
		}
		else if (AnimUpdateTime < 12) {
			if (AnimUpdateTime % 2 == 0) {
				if (balloon == 1) {
					AnimImg++;
				}
			}
		}

		else if (AnimUpdateTime % 17 == 0) {
			if (AnimWork % 2 == 0) {
				if (balloon == 1) {
					AnimImg = 11;
				}
			}
			else if (AnimWork % 4 == 1) {
				if (balloon == 1) {
					AnimImg = 12;
				}
			}
			else {
				if (balloon == 1) {
					AnimImg = 10;
				}
			}
			AnimWork++;
		}
		break;
	case STATE::FISH:
		AnimImg = -1;
		break;
	case STATE::MISS:
		if (AnimUpdateTime > 2) {
			if (AnimWork % 2 == 0) {
				AnimImg = 14;
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
