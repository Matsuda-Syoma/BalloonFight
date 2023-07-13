#include "GameMain.h"
#include "Map.h"

GameMain::GameMain()				// ここで初期化
{
	Sounds::LoadSounds();
	StageImages::LoadImages();
	SetSoundCurrentTime(0.0f, Sounds::BGM_Trip);
	PlaySoundMem(Sounds::BGM_Trip, DX_PLAYTYPE_BACK, true);
	player = new Player;
	bubble = new Bubble;
	ui = new UI;
	enemy = new Enemy;

	int MapCount = 0;
	Score = 0;
	for (int i = 0; i < MAP_COUNT; i++) {
		int imagework;
		imagework = StageImages::Image[LoadMapImage[MapCount][i]];
		float work[MAP_SIZE];
		for (int j = 0; j < MAP_SIZE; j++) {
			work[j] = LoadMap[MapCount][i][j];
		}
		// 読み込んだ座標が上下、左右足してどちらとも0より大きいなら足場に情報を渡す
		if (work[0] + work[2] > 0 && work[1] + work[3] > 0) {
			stage.emplace_back(work[0], work[1], work[2], work[3],imagework);
		}
	}

	NowScore = 0;
	HighScore = 10000;

	Pause = false;
	LifeImg = LoadGraph("Resources/images/UI/UI_Stock.png");

}

GameMain::~GameMain()				// ここでdeleteなどをする
{
	StopSoundMem(Sounds::BGM_Trip);
}

AbstractScene* GameMain::Update()	// ここでゲームメインの更新をする
{
	if(PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_START)) {
		//Pause = !Pause;
		return new GameMain();
	}
	if (!Pause) {
		Game();
	}
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

	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}

	player->Draw();
	enemy->Draw();

	if (bubble != nullptr) {
		bubble->Draw();
	}


	for (size_t i = 0; i < scoreUP.size(); i++) {
		scoreUP.at(i).Draw();
	}

	DrawGraph(-80, 455, StageImages::Image[4], true);
	DrawGraph(400, 455, StageImages::Image[4], true);

	DrawGraph(160,450,StageImages::Image[4],true);

	for (size_t i = 0; i < splash.size(); i++) {
		splash.at(i).Draw();
	}

	ui->Draw();
}

void GameMain::Game()				// ここでゲームの判定などの処理をする
{
	enemy->Update();
	player->Update();
	if (player->GetFlg()) {
		for (size_t i = 0; i < stage.size(); i++) {
			if (player->IsFly(stage.at(i))) {
				break;
			}
		}
	}
	else {
		player->Miss(0);
	}

	// 画面下に行った場合ミス
	if (player->GetY() > SCREEN_HEIGHT && !player->GetSpawnFlg()) {
		player->SetSpawnFlg(true);
		StopSoundMem(Sounds::SE_Falling);
		splash.emplace_back(player->GetX());
	}

	if (player->GetLife() <= 0) {
		ui->GameOver();
	}

	if (bubble != nullptr) {
		if (player->HitBox(*bubble) && !bubble->GetHitFlg()) {
			Score += 500;
			scoreUP.emplace_back(500, player->GetX(), player->GetY());
			PlaySoundMem(Sounds::SE_Bubble, DX_PLAYTYPE_BACK, true);
			bubble->SetHitFlg(true);
		}
		if (bubble->GetHitFlg()) {
			if (bubble->PlayAnim()) {
				delete bubble;
				bubble = nullptr;
			}
		}
	}

	if (bubble != nullptr) {
		bubble->Update();
		if (!bubble->GetFlg()) {		// 画面外に行ったならdeleteしてnullptr
			delete bubble;
			bubble = nullptr;
		}
	}

	for (size_t i = 0; i < scoreUP.size(); i++) {
		if (scoreUP.at(i).Update()) {
			scoreUP.erase(scoreUP.begin() + i);
			continue;
		}
	}

	for (size_t i = 0; i < splash.size(); i++) {
		if (splash.at(i).Update()) {
			if (player->GetSpawnFlg()) {
				player->Init(player->GetLife() - 1);
				PlaySoundMem(Sounds::SE_Restart, DX_PLAYTYPE_BACK, true);
			}
			splash.erase(splash.begin() + i);
			continue;
		}
	}

	ui->Update(Score);

}
