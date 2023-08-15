#pragma once
#include "BoxCollider.h"
//#include"ThunderBall.h"


class Thunder : public BoxCollider{
public:
	Thunder();							// コンストラクタ
	~Thunder();							// デストラクタ
	void Update();				//描画以外の更新を実行
	void Draw() const;			// 描画に関することを実装

	void LoadImages();

	int BallAngle(int _i);

	bool ThunderSpawn();
	void RandSpawn();
	int GetRandSpawn();

	//bool Re_Thunder();// 再スポーン関数

	float CloudX2, CloudY2;
private:
	float CloudX, CloudY;
	float thunder_x, thunder_y;		// 落雷画像回転時に起こるずれを修正するための変数

	int CloudImg[3];
	int ThunderImg[6];
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;
	int cu_Cnt;
	int Th_rund;			// 1~4で方向を決める

	int WaitTime;
	int ThAnimImg;
	
	int Spawn_Cnt;
	float thunderRota;
	bool ThFlg;
	bool FlFlg;
	bool current_flg;

};
