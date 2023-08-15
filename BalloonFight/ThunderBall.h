#pragma once
#include "BoxCollider.h"

class ThunderBall : public BoxCollider {
public:
	
	ThunderBall(bool p_flg);							// コンストラクタ
	~ThunderBall();							// デストラクタ
	void Update();				//描画以外の更新を実行
	void Draw() const;			// 描画に関することを実装
	void ChangeAngle();
	float GetBoxSide(BoxCollider box, int i);
	int Hit(BoxCollider _stage);
	//int HitPlayer(BoxCollider _player);
	int GetX();
	int GetY();
	void LoadImages();

	void SetXY(float _x,float _y);

	float BallX, BallY;
	bool Hitflg;				// プレイヤーのフラグ取得用変数
	bool thunder_flg;
private:

	
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;

	//float x, y;						// 座標
	//float w, h;						// 大きさ
	//
	int MoveX, MoveY;

	int Speed;				//ボール速度
	float BallAngle;		//ボールの角度

	static const int WIDTH = 32;
	static const int HEIGHT = 32;
};

