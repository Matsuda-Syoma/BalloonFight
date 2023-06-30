#include "GameMain.h"
#include "Map.h"
#include "UI.h"

GameMain::GameMain()				// ここで初期化
{
	player = new Player;
	bubble = new Bubble;
	int MapCount = 0;
	for (int i = 0; i < MAP_COUNT; i++) {
		float work[MAP_SIZE];
		for (int j = 0; j < MAP_SIZE; j++) {
			work[j] = LoadMap[MapCount][i][j];
		}

		// 読み込んだ座標が上下、左右足してどちらとも0より大きいなら足場に情報を渡す
		if (work[0] + work[2] > 0 && work[1] + work[3] > 0) {
			stage.emplace_back(work[0], work[1], work[2], work[3]);
		}
	}

	NowScore = 0;
	HighScore = 10000;

	PlayerLife = 0;

	Stage = 1;
	PhaseCount = 0;
}

GameMain::~GameMain()				// ここでdeleteなどをする
{
}

AbstractScene* GameMain::Update()	// ここでゲームメインの更新をする
{


	Game();
	return this;

	

}

void GameMain::Draw() const			// ここでゲームメインの描画
{
	//スコア
	DrawString(20,10,"I-",0xff0000);
	DrawFormatString(40, 10, 0xFFFFFF, "%06d", NowScore);

	DrawString(270, 10, "TOP-", 0xffa500);
	DrawFormatString(310, 10, 0xFFFFFF, "%06d", HighScore);

	

	if (PlayerLife == 3) {
		DrawBox(60, 30, 70, 40, 0xFF0000, TRUE);
		DrawBox(75, 30, 85, 40, 0xFF0000, TRUE);
	}

	if (PlayerLife == 2) {
		DrawBox(75, 30, 85, 40, 0xFF0000, TRUE);
	}

	if (!PhaseFlg) {
	DrawFormatString(290, 30, 0xffa500, "PHASE-%d", Stage);
	}

	if (PlayerLife == 0) {
		DrawString(280, 230, "GameOver", 0xffffff);
	}

	player->Draw();
	bubble->Draw();
	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}
}

void GameMain::Game()				// ここでゲームの判定などの処理をする
{

	player->Update();
	if (player->IsFlg()) {
		for (size_t i = 0; i < stage.size(); i++) {
			if (player->IsFly(stage.at(i))) {
				break;
			}
		}
	}
	else {
		player->Miss(0);
	}

	bubble->Update();

	if (PhaseCount < 240) {
		PhaseCount++;
		if (PhaseCount % 20 < 10) {
			PhaseFlg = true;
		}
		else {
			PhaseFlg = false;
		}
	}

	//ハイスコアを更新
	if (NowScore > HighScore) {
		HighScore = NowScore;
	}

}
