#pragma once
#include "AbstractScene.h"
#include "Player.h"
class GameMain : public AbstractScene
{

public:
	GameMain();									// コンストラクタ
	~GameMain();								// デストラクタ

	// クラスのオブジェクト
	Player* player;		// プレイヤーのクラス

	virtual AbstractScene* Update() override;	// 描画以外の更新を実行
	void Draw() const override;					// 描画に関することを実装
	void Game();								// ゲームの処理

private:
	int NowScore;					//現在のスコア
	int HighScore;					//ハイスコア

	int PlayerLife;					//残機
	int WaitTime;
};

