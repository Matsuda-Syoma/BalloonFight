#include "GameMain.h"

GameMain::GameMain()				// ‚±‚±‚Å‰Šú‰»
{
	player = new Player;
	bubble = new Bubble;
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
	bubble->Draw();
}

void GameMain::Game()				// ‚±‚±‚ÅƒQ[ƒ€‚Ì”»’è‚È‚Ç‚Ìˆ—‚ð‚·‚é
{
	player->Update();
	bubble->Update();
}
