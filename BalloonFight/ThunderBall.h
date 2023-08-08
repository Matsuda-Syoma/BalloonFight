#pragma once
#include "BoxCollider.h"

class ThunderBall : public BoxCollider {
public:
	
	ThunderBall();							// コンストラクタ
	~ThunderBall();							// デストラクタ
	void Update();				//描画以外の更新を実行
	void Draw() const;			// 描画に関することを実装
	void ChangeAngle();
	float GetBoxSide(BoxCollider box, int i);
	int Hit(BoxCollider _stage);
	void LoadImages();

	int BallX, BallY;

private:
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;

	
	int MoveX, MoveY;

	int Speed;				//ボール速度
	float BallAngle;		//ボールの角度

	static const int WIDTH = 32;
	static const int HEIGHT = 32;
};

