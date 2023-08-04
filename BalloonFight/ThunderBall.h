#pragma once
#include "BoxCollider.h"

class ThunderBall : public BoxCollider {
public:
	
	ThunderBall();							// コンストラクタ
	~ThunderBall();							// デストラクタ
	void Update();				//描画以外の更新を実行
	void Draw() const;			// 描画に関することを実装
	void ChangeAngle();
	void LoadImages();

private:
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;

	int BallX, BallY;
	int MoveX, MoveY;

	int Speed;				//ボール速度
	float BallAngle;		//ボールの角度

};

