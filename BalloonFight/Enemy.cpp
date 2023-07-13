#include "enemy.h"
#include "common.h"

// 画像モード分け

enum class Enemy_STATE {
	stay = 0,
	walk,
	fly,
	miss,
};
Enemy_STATE E_state;

// コンストラクタ
Enemy::Enemy()
{
	Ew = E_WIDTH;
	Eh = E_HEIGHT;
	E_AnimImg = 0;

	Enemy_animflg = false;
	Eimg_Reverse = true;

	Ex = 450;
	Ey = 300 - E_WIDTH;

	Enemy_LoadImg();
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
	Enemy_imageX = Ex + (Ew / 2);
	Enemy_imageY = Ey + (Eh / 2);

	box.left = Ex;
	box.right = Ex + Ew;
	box.top = Ey;
	box.bottom = Ey + Eh;
}

void Enemy::Draw() const
{
	// 画像設定　画像表示番号　画像種別フラグ
	DrawRotaGraph(Enemy_imageX, Enemy_imageY, 1.0f, 0, E_images[E_AnimImg], true, Eimg_Reverse);
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xffffff, false);
	printfDx("%d %d",(int)box.left,(int)box.top);
}

void Enemy::Enemy_LoadImg()
{
	LoadDivGraph("Resources/images/Player/Player_animation_d.png", 32, 8, 4, 64, 64, E_images);	//	分割画像のE_images値の画像を表示
	// 敵の画像実装されたらEnemy_P_Animation.png
}

void Enemy::AnimUpdate()
{
	switch (E_state)
	{
	case Enemy_STATE::stay:
		break;
	case Enemy_STATE::walk:
		break;
	case Enemy_STATE::fly:
		break;
	case Enemy_STATE::miss:
		break;
	default:
		break;
	}
}
