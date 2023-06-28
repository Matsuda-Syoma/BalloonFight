#include "GameMain.h"
#include"UI.h"

GameMain::GameMain()				// ここで初期化
{
	player = new Player;

	PlayerLife = 2;
	NowScore = 0;
	HighScore = 10000;
	
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

	DrawFormatString(50, 10, 0xFFFFFF, "I-%06d ", NowScore);		//現在のスコア描画
	DrawFormatString(270, 10, 0xFFFFFF, "TOP-%06d ", HighScore);	//ハイスコア描画

	//ライフ3
	if (PlayerLife == 3) {
		DrawBox(100, 40, 110, 50, 0xff0000, FALSE);
		DrawBox(85, 40, 95, 50, 0xff0000, FALSE);
	}
	//ライフ2
	if (PlayerLife == 2) {
		DrawBox(100, 40, 110, 50, 0xff0000, FALSE);
	}

}


void GameMain::Game()				// ここでゲームの判定などの処理をする
{
	player->Update();
}
