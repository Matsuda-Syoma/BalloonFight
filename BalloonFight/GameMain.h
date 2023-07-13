#pragma once
#include "AbstractScene.h"
#include "LoadSounds.h"
#include "LoadImages.h"
#include "Player.h"
#include"Enemy.h"
#include "Stage.h"
#include"bubble.h"
#include"UI.h"
#include "ScoreUP.h"
#include <vector>
class GameMain : public AbstractScene
{
public:
	int StageImage = 0;
private:
	std::vector<Stage> stage;
	std::vector<ScoreUP>scoreUP;
	int Score;
	bool Pause;
public:
	GameMain();									// コンストラクタ
	~GameMain();								// デストラクタ

	// クラスのオブジェクト
	Player* player;		// プレイヤーのクラス
	Bubble* bubble;
	UI* ui;
	Enemy* enemy;		// 敵のクラス

	//Stage* stage;		// ステージのクラス
	virtual AbstractScene* Update() override;	// 描画以外の更新を実行
	void Draw() const override;					// 描画に関することを実装
	void Game();								// ゲームの処理

private:
	int NowScore;
	int HighScore;

	int LifeImg;
};

