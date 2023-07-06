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

	void GameOver();

private:
	int NowScore;					//現在のスコア
	int HighScore;					//ハイスコア

	int PlayerLife;					//残機

	int Stage;
	int PhaseCount;

	bool PhaseFlg;
	bool GameOverFlg;

	int NumImg[10];
	int ScoreImg;
	int HighScoreImg;
	int GameOImg;
	int PhaseImg;
};

