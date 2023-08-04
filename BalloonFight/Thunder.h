#pragma once
#include "BoxCollider.h"
#include"ThunderBall.h"


class Thunder : public BoxCollider{
public:
	ThunderBall* thunderball;
	Thunder();							// コンストラクタ
	~Thunder();							// デストラクタ
	void Update();				//描画以外の更新を実行
	void Draw() const;			// 描画に関することを実装

	void LoadImages();

	int BallAngle(int _i);

private:
	int CloudImg[3];
	int ThunderImg[6];
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;

	int WaitTime;
	int ThAnimImg;
	int kw;

	int CloudX, CloudY;

	bool ThFlg;
	bool FlFlg;

};
