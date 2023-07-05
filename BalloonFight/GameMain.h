#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"
#include"bubble.h"
#include <vector>
class GameMain : public AbstractScene
{
public:
	int StageImage = 0;
private:
	std::vector<Stage> stage;
public:
	GameMain();									// コンストラクタ
	~GameMain();								// デストラクタ

	// クラスのオブジェクト
	Player* player;		// プレイヤーのクラス
	Bubble* bubble;
	//Stage* stage;		// ステージのクラス
	virtual AbstractScene* Update() override;	// 描画以外の更新を実行
	void Draw() const override;					// 描画に関することを実装
	void Game();								// ゲームの処理

private:
	int NowScore;					//現在のスコア
	int HighScore;					//ハイスコア

	int PlayerLife;					//残機

	int Stage;
	int PhaseCount;

	bool PhaseFlg;
};

