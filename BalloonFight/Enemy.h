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

	enum class STATE {
		stay = 0,
		walk,
		fly,
		miss,
	};
	STATE state;

	bool flg;

	bool landingflg;					// 適が地面に立っているか
	bool groundflg;					// 適が着地したか

	bool missflg;				// ミスしたときのフラグ
	bool animflg;				// ミスしたときのフラグ
	int life;					// 適の残機
	int ballon;					// 適の風船の数
	int HitStage;				// 適がどこに当たったか
	float x, y;					// 適の座標
	float w, h;					// 適の大きさ
	int speedX;					// 適の速度
	float startX;				// 適の初速
	float FlyspeedMax;			// 適の空中最大速度
	float GroundspeedMax;		// 適の地上最大速度
	float inertiaX, inertiaY;	// 慣性
	float imageX, imageY;		// 適の画像の座標
	bool imageReverse;						// 向いてる方向
	int images[40];
	int AnimImg;

	int jumpdelay;

	static const int WIDTH = 32;
	static const int HEIGHT = 48;
	static const int DELAY = 9;

public:
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
	void ChangeInertia(BoxCollider _player, int i);
	int HitEnemy(BoxCollider _enemy);
	void AnimUpdate();					// アニメーションの更新
};

