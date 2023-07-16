#pragma once
#include "BoxCollider.h"
class Stage : public BoxCollider
{
private:
	int ImageX, ImageY, Image;
public:
	Stage();										// コンストラクタ
	Stage(float _x,float _y,float _w,float _h, int _image);		// 座標とサイズ指定
	~Stage();										// デストラクタ
	void Draw()const;								// 描画処理
	int GetImage();								// 画像読み込み
};