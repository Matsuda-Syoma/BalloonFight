#include "GameMain.h"

GameMain::GameMain()				// ‚±‚±‚Å‰Šú‰»
{
	player = new Player;
	stage.emplace_back(0,440,160,480);
	stage.emplace_back(480,340,640,480);

	stage.emplace_back(200,320,440,330);
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
	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}
}

void GameMain::Game()				// ‚±‚±‚ÅƒQ[ƒ€‚Ì”»’è‚È‚Ç‚Ìˆ—‚ð‚·‚é
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


}
