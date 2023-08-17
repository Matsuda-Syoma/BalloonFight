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

	bool ThunderSpawn();

	int CloudX, CloudY, CloudX2, CloudY2;		//雲の座標
	int ThX, ThY;			//稲妻の座標

	int FlashCount;			//点滅のかうんと
	int CloudImg[3];		//雲の画像
private:
	
	int ThunderImg[6];		//稲妻の画像
	int ThunBallImg[3];		//雷の球の画像

	
	int BallCount;			//球のカウント

	int WaitTime;			//待つ
	int FlWait;				//点滅を待つ
	int ThAnimImg;			//稲妻を出す
	
	

	bool ThFlg;				//
	bool FlFlg;

};
