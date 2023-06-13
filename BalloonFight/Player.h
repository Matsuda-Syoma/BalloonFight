#pragma once

#include "BoxCollider.h"
class Player : public BoxCollider
{
private:
	bool flg;					// プレイヤーが動かせるか
	int life;					// プレイヤーの残機
	float x, y;					// プレイヤーの座標
	float w, h;					// プレイヤーの大きさ
	float speedX, speedY;		// プレイヤーの速度
	float speedMax;				// プレイヤーの最大速度
	float imageX, imageY;		// プレイヤーの画像の座標
	int images[3];

	static const int WIDTH = 40;
	static const int HEIGHT = 40;

public:
	Player();					// コンストラクタ
	~Player();					// デストラクタ
	void Update();				// 更新処理
	void Draw()const;			// 描画処理
	void LoadImages();			// 画像読み込み
	void DeleteImages();		// 画像削除
};

