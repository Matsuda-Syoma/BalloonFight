#include "GameMain.h"
#include "Map.h"

GameMain::GameMain()				// ここで初期化
{
	Sounds::LoadSounds();
	player = new Player;
	bubble = new Bubble;
	ui = new UI;
	enemy = new Enemy;

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

	LifeImg = LoadGraph("Resources/images/UI/UI_Stock.png");

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
		for (int i = 0; i < PlayerLife - 1; i++) {
			/*DrawBox(60 + (15 * i), 30, 70 + (15 * i)
				, 40, 0xFF0000, TRUE);*/

			DrawGraph(75 - (15 * i), 30, LifeImg, true);
		}
	}


	player->Draw();
	enemy->Draw();

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
	enemy->Update();
	player->Update();
	if (player->IsFlg()) {
		for (size_t i = 0; i < stage.size(); i++) {
			if (player->IsFly(stage.at(i))) {
				break;
			}
		}
	}
	if (player->GetLife() <= 0) {
		ui->GameOver();
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

	ui->Update();

}
