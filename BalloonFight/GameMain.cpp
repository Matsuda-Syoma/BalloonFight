#include "GameMain.h"
#include "Map.h"

GameMain::GameMain()				// ここで初期化
{
	Sounds::LoadSounds();
	player = new Player;
	bubble = new Bubble;
	ui = new UI;
	int MapCount = 0;
	Score = 0;
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
	int PlayerLife = player->GetLife();

	if (PlayerLife > 0) {
		for (int i = 0; i < PlayerLife; i++) {
			DrawBox(60 + (15 * i), 30, 70 + (15 * i)
				, 40, 0xFF0000, TRUE);
		}
	}


	player->Draw();

	if (bubble != nullptr) {
		bubble->Draw();
	}

	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}

	ui->Draw();
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
		if (player->HitBox(*bubble)) {
			delete bubble;
			bubble = nullptr;
			Score += 500;
		}
	}

	if (bubble != nullptr) {
		bubble->Update();
		if (!bubble->GetFlg()) {		// 画面外に行ったならdeleteしてnullptr
			delete bubble;
			bubble = nullptr;
		}
	}

	ui->Update(Score);

}
