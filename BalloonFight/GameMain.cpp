#include "GameMain.h"
#include "Map.h"
#include "UI.h"

GameMain::GameMain()				// ここで初期化
{
	Sounds::LoadSounds();
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

	int PlayerLife = player->GetLife();

	if (PlayerLife > 0) {
		for (int i = 0; i < PlayerLife; i++) {
			DrawBox(60 + (15 * i), 30, 70 + (15 * i)
				, 40, 0xFF0000, TRUE);
		}
	}

	if (PlayerLife == 0) {
		DrawString(280, 230, "GameOver", 0xffffff);
	}


	if (!PhaseFlg) {
		DrawFormatString(290, 30, 0xffa500, "PHASE-%d", Stage);
	}


	player->Draw();

	if (bubble != nullptr) {
		bubble->Draw();
	}

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

	if (bubble != nullptr) {
		bubble->Update();
		if (!bubble->GetFlg()) {		// 画面外に行ったならdeleteしてnullptr
			delete bubble;
			bubble = nullptr;
		}
	}

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
