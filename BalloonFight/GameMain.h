#pragma once
#include "AbstractScene.h"
#include "LoadSounds.h"
#include "LoadImages.h"
#include "Player.h"
#include"Enemy.h"
#include "Stage.h"
#include"bubble.h"
#include"Fish.h"
#include"UI.h"
#include "ScoreUP.h"
#include "Splash.h"
#include <vector>
class GameMain : public AbstractScene
{
public:
	int StageImage = 0;
private:
	std::vector<Stage> stage;
	std::vector<ScoreUP>scoreUP;
	std::vector<Splash>splash;
	std::vector<Enemy>enemy;
	std::vector<Bubble>bubble;

	int Score;
	bool Pause;
	int StageNum;
	bool StageSwitch;
	int StageSwitchTime;
	bool parachuteflg;
	int SpawnDelay;
public:
	GameMain(int _score, int _stage, int _life);// コンストラクタ

	~GameMain();								// デストラクタ

	// クラスのオブジェクト
	Player* player;		// プレイヤーのクラス
	UI* ui;
	Fish* fish;
	//Stage* stage;		// ステージのクラス
	virtual AbstractScene* Update() override;	// 描画以外の更新を実行
	void Draw() const override;					// 描画に関することを実装
	void Game();								// ゲームの処理

private:
	int HighScore;

	int LifeImg;

	int fishflg;		// 魚のupdate処理用フラグ
};

