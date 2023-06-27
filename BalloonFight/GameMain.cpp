#include "GameMain.h"

GameMain::GameMain()				// ここで初期化
{
	player = new Player;
	stage.emplace_back(0,440,160,480);
	stage.emplace_back(480,440,640,480);
	stage.emplace_back(200,320,440,330);
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


	for (size_t i = 0; i < stage.size(); i++) {
		if (player->IsFly(stage.at(i))) {
			break;
		}
	}
	player->Update();
}
