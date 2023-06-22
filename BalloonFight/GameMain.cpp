#include "GameMain.h"

GameMain::GameMain()				// ここで初期化
{
	player = new Player;
	stage.emplace_back(200,210,350,220);
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
	player->Draw();
	//stage->Draw();
	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}
}

void GameMain::Game()				// ここでゲームの判定などの処理をする
{
	player->Update();
	for (size_t i = 0; i < stage.size(); i++) {
		player->IsFly(stage.at(i));
	}
}
