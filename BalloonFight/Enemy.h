#pragma once
#include "BoxCollider.h"
#include "Stage.h"
#include"Player.h"
#include <math.h>

// 今やること
// 敵の表示

class Enemy : public Player
{
private:

	bool Enemy_landingflg;					// 適が地面に立っているか
	bool Enemy_groundflg;					// 適が着地したか

	bool Enemy_missflg;						// ミスしたときのフラグ
	bool Enemy_animflg;						// ミスしたときのフラグ
	int Enemy_life;							// 適の残機
	int Enemy_ballon;						// 適の風船の数
	int Enemy_HitStage;						// 適がどこに当たったか
	float Ex, Ey;					// 適の座標
	float Ew, Eh;					// 適の大きさ
	int Enemy_speedX;						// 適の速度
	float Enemy_startX;						// 適の初速
	float Enemy_FlyspeedMax;				// 適の空中最大速度
	float Enemy_GroundspeedMax;				// 適の地上最大速度
	float Enemy_inertiaX, Enemy_inertiaY;	// 適の慣性
	float Enemy_imageX, Enemy_imageY;		// 適の画像の座標
	bool Eimg_Reverse;						// 向いてる方向
	int E_images[40];
	int E_AnimImg;

	static const int E_WIDTH = 64;
	static const int E_HEIGHT = 64;

public:
	// コンストラクタ
	Enemy();

	// デストラクタ
	~Enemy();
		
	void E_Init(int _life);				// 数値の初期化
	void Update();						// 更新処理
	void Draw()const;					// 描画処理
	void Enemy_LoadImg();				// 画像読み込み
	void AnimUpdate();					// アニメーションの更新
};

