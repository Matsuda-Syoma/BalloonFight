#include "GameMain.h"

GameMain::GameMain()				// ‚±‚±‚Å‰Šú‰»
{
	player = new Player;
	stage.emplace_back(200,210,350,220);
}

GameMain::~GameMain()				// ‚±‚±‚Ådelete‚È‚Ç‚ð‚·‚é
{
}

AbstractScene* GameMain::Update()	// ‚±‚±‚ÅƒQ[ƒ€ƒƒCƒ“‚ÌXV‚ð‚·‚é
{
	Game();
	return this;
}

void GameMain::Draw() const			// ‚±‚±‚ÅƒQ[ƒ€ƒƒCƒ“‚Ì•`‰æ
{
	player->Draw();
	//stage->Draw();
	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}
}

void GameMain::Game()				// ‚±‚±‚ÅƒQ[ƒ€‚Ì”»’è‚È‚Ç‚Ìˆ—‚ð‚·‚é
{
	player->Update();
	for (size_t i = 0; i < stage.size(); i++) {
		if (player->IsFly(stage.at(i))) {

		}
	}
}
