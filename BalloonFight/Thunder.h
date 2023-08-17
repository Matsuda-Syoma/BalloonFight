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
	void Respawn2();


	

	//bool Re_Thunder();// 再スポーン関数

	float CloudX_Set, CloudY_Set;		// 値受け渡し用
	float CloudX_Set2, CloudY_Set2;		// 値受け渡し用
	bool WCloud_flg;
	int Th_rund;			// 1~4で方向を決める
	int Th_rund2;			// 1~4で方向を決める
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

	int FlashCount2;
	int BallCount2;
	int cu_Cnt2;
	
	

	int SetTh_rund;			// 1~4で方向を決める
	int SetTh_rund2;			// 1~4で方向を決める
	
	int WaitTime;
	int WaitTime2;
	int ThAnimImg;
	
	int Spawn_Cnt;
	int Spawn_Cnt2;
	int Spawn_End;
	float thunderRota;
	float thunderRota2;


	
	bool ThFlg;
	bool ThFlg2;
	bool FlFlg;
	bool FlFlg2;
	bool current_flg;
	bool current_flg2;
	

};
