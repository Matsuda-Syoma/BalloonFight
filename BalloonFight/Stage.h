#pragma once
#include "BoxCollider.h"
class Stage : public BoxCollider
{
public:
	Stage();										// コンストラクタ
	Stage(float _x,float _y,float _w,float _h);		// 座標とサイズ指定
	~Stage();										// デストラクタ
	void Draw()const;								// 描画処理
	float GetTop();
};

