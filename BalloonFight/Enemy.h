#pragma once
#include "BoxCollider.h"
#include "Stage.h"
#include <math.h>
#include "BoxCollider.h"
// 今やること
// 敵の表示

class Enemy : public BoxCollider
{
private:

	bool flg;

	bool landingflg;				// 地面に立っているか
	bool groundflg;					// 着地したか
	bool deathflg;					// ミスしたときのフラグ
	bool startflg;
	int balloon;					// 風船の数
	int balloondelay;				// 
	int color;						// 色
	int HitStage;					// どこに当たったか
	float x, y;						// 座標
	float w, h;						// 大きさ
	int speedX;						// 速度
	float startX;					// 初速
	float FlyspeedMax;				// 空中最大速度
	float GroundspeedMax;			// 地上最大速度
	float inertiaX, inertiaY;		// 慣性
	float imageX, imageY;			// 画像の座標
	bool imageReverse;				// 向いてる方向
	int imagesG[18];
	int imagesR[18];
	int imagesP[18];
	int AnimImg;
	int AnimFlg;
	int AnimWork;
	int AnimSelect;
	int AnimUpdateTime;
	int MoveX;
	int MoveY;
	int RandomMoveX;
	int RandomMoveY;
	int MaxRandomMoveX;
	int MaxRandomMoveY;

	int jumpdelay;

	static const int WIDTH = 32;
	static const int HEIGHT = 48;
	static const int DELAY = 9;

public:

	enum class STATE : int {
		STAY = 0,
		FLY,
		FISH,
		MISS,
	};
	STATE state;

	// コンストラクタ

	Enemy(float _x, float _y);

	// デストラクタ
	~Enemy();
		
	void E_Init(int _life);				// 数値の初期化
	void Update();						// 更新処理
	void Draw()const;					// 描画処理
	void LoadImages();				// 画像読み込み
	bool IsFly(Stage box);
	float GetBoxSide(BoxCollider box, int i);
	float GetX();
	float GetY();
	bool GetFlg();
	void SetFlg(bool _flg);
	bool GetDeathFlg();
	int GetBalloon();
	int GetState();
	void ChangeInertia(BoxCollider _player, int i);
	int HitEnemy(BoxCollider _enemy);
	void BallonBreak(int i);
	void Death(int i);
	void AnimUpdate();					// アニメーションの更新
};

