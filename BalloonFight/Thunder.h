#pragma once
#include "BoxCollider.h"
//#include"ThunderBall.h"


class Thunder : public BoxCollider{
public:
	Thunder(int _Stage);							// コンストラクタ
	~Thunder();							// デストラクタ
	void Update();				//描画以外の更新を実行
	void Draw() const;			// 描画に関することを実装

	void LoadImages();

	int BallAngle(int _i);

	bool ThunderSpawn();
	void RandSpawn();
	int GetRandSpawn();
	int GetRandSpawn2();

	void Respawn();

	

	//bool Re_Thunder();// 再スポーン関数

	float CloudX_Set, CloudY_Set;		// 値受け渡し用
	float CloudX_Set2, CloudY_Set2;		// 値受け渡し用
	bool WCloud_flg;
private:
	int Stage;
	float CloudX, CloudY;
	float CloudX2, CloudY2;

	float thunder_x, thunder_y;		// 落雷画像回転時に起こるずれを修正するための変数

	int CloudImg[3];
	int ThunderImg[6];
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;
	int cu_Cnt;
	
	int Th_rund;			// 1~4で方向を決める
	int Th_rund2;			// 1~4で方向を決める

	int WaitTime;
	int ThAnimImg;
	
	int Spawn_Cnt;
	int Spawn_End;
	float thunderRota;

	
	bool ThFlg;
	bool FlFlg;
	bool current_flg;
	

};
