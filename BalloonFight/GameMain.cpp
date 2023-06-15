#include "GameMain.h"

GameMain::GameMain()				// ここで初期化
{
	player = new Player;
	stage = new Stage(200, 250, 210, 220);
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
	stage->Draw();
}

void GameMain::Game()				// ここでゲームの判定などの処理をする
{
	player->Update();
}
