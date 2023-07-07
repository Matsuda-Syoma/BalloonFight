#pragma once
#include "BoxCollider.h"
class Stage : public BoxCollider
{
public:
	Stage();										// コンストラクタ
	Stage(int _stage, int _i);//データの指定
	Stage(float _x,float _y,float _w,float _h);		// 座標とサイズ指定
	~Stage();										// デストラクタ
	void Draw()const;								// 描画処理
	void LoadImage();								// 画像読み込み
	float GetSide(int i);							// 引数で数値を返す(1:上、2:下、3:左、4:右)
};