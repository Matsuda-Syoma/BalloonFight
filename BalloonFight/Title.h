#pragma once
#include "AbstractScene.h"
class Title : public AbstractScene {
private:
	int TitleImg_Logo;					// タイトルロゴ画像
	int TitleImg_Select;				// タイトルセレクト画像
	int TitleImg_Credit;				// タイトルクレジット画像
	int TitleImg_Cursor[4];				// タイトルカーソル画像
	int CursorNum;
	int CursorY = 330;

	int WaitTime;
public:
	Title();							// コンストラクタ
	~Title();							// デストラクタ
	AbstractScene* Update() override;	// 描画以外の更新を実行
	void Draw() const override;			// 描画に関することを実装
	void LoadImage();
	bool CAnim_Play();
};
