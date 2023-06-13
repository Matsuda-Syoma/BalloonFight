#include "GameMain.h"

GameMain::GameMain()				// ここで初期化
{
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
}

void GameMain::Game()				// ここでゲームの判定などの処理をする
{
}
