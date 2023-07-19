#pragma once
#include "AbstractScene.h"
#include"DxLib.h"
#include"PAD_INPUT.h"
#include"GameMain.h"


class Title : public AbstractScene {
private:
	int TitleImg_Logo;					// タイトルロゴ画像
	int TitleImg_Select;				// タイトルセレクト画像
	int TitleImg_Credit;				// タイトルクレジット画像
	int TitleImg_Cursor[4];				// タイトルカーソル画像
	int CursorNum;
	float CursorY = 295;
	int testimg;
	int WaitTime;
	int Imgflg = 1;						// 1 通常 -1 反転

public:
	Title();							// コンストラクタ
	~Title();							// デストラクタ

	AbstractScene* Update() override;	// 描画以外の更新を実行
	void Draw() const override;			// 描画に関することを実装
	bool CAnim_Play();
};
