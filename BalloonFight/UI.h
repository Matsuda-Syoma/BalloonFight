#pragma once
#include"common.h"
#include"AbstractScene.h"
#include"Player.h"
#include<DxLib.h>

class UI{
public:
	UI();							// コンストラクタ
	~UI();							// デストラクタ
	void Update();				// 描画以外の更新を実行
	void Draw() const;			// 描画に関することを実装
	void LoadImages();

	void DeleteImages();

private:
	int NowScore;					//現在のスコア
	int HighScore;					//ハイスコア

	int PlayerLife;					//残機

	int Stage;
	int PhaseCount;

	bool PhaseFlg;

	/*int LifeImg;
	int NumImg[10];
	int IImg;
	int TopImg;
	int GameOImg;
	int PhaseImg;*/
};

