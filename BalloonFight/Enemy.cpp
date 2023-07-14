#include "enemy.h"
#include "common.h"
#include "DxLib.h"
// 画像モード分け

// コンストラクタ
Enemy::Enemy(float _x,float _y)
{
	w = WIDTH;
	h = HEIGHT;
	AnimImg = 0;

	flg = true;
	animflg = false;
	imageReverse = true;

	x = _x;
	y = _y - WIDTH;

	inertiaX = 1;
	inertiaY = -100;

	jumpdelay = 0;

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

	if (inertiaY < 150 && !landingflg || missflg) {
		if (flg && groundflg) {
			//AnimFlg = 0;
			state = STATE::fly;
		}
			inertiaY += 1.0;
	}

	groundflg = landingflg;

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


	y += inertiaY / FRAMERATE;		// 仮の重力(フレーム数 * 風船の数)
	x += inertiaX;
	printfDx("%d ", (int)inertiaY);
}

void Enemy::Draw() const
{
	// 画像設定　画像表示番号　画像種別フラグ
	DrawRotaGraph(imageX, imageY, 1.0f, 0, images[AnimImg], true, imageReverse);
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xffffff, false);
}

void Enemy::LoadImages()
{
	switch (GetRand(2))
	{
	case 0:
		LoadDivGraph("Resources/images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, images);
		break;
	case 1:
		LoadDivGraph("Resources/images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, images);
		break;
	case 2:
		LoadDivGraph("Resources/images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, images);
		break;
	default:
		break;
	}
	//	分割画像のimages値の画像を表示
	// 敵の画像実装されたらEnemy_P_Animation.png
}

bool Enemy::IsFly(Stage box) {
	HitStage = Enemy::HitBox(box);
	// 上側に当たったときの判定
	if (HitStage == 1) {
		landingflg = true;
		if (!groundflg && jumpdelay <= 0) {
			inertiaY = 0;
			//inertiaX = 0;
			groundflg = true;
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

void Enemy::ChangeInertia(BoxCollider _player, int i) {
	switch (i)
	{
	case 1:
		y = GetBoxSide(_player, 2) + 1;
		break;
	case 2:
		y = GetBoxSide(_player, 1) - (h + 1);
		inertiaY *= -0.8f;
		break;
	case 3:
		x = GetBoxSide(_player, 4) + 1;
		inertiaX *= -0.8f;
		break;
	case 4:
		x = GetBoxSide(_player, 3) - (w + 1);
		inertiaX *= -0.8f;
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

void Enemy::AnimUpdate()
{
	switch (state)
	{
	case STATE::stay:
		break;
	case STATE::walk:
		break;
	case STATE::fly:
		break;
	case STATE::miss:
		break;
	default:
		break;
	}
}
