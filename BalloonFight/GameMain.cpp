#include "GameMain.h"
#include "Map.h"

GameMain::GameMain()				// �����ŏ�����
{
	Sounds::LoadSounds();
	StageImages::LoadImages();
	SetSoundCurrentTime(0.0f, Sounds::BGM_Trip);
	PlaySoundMem(Sounds::BGM_Trip, DX_PLAYTYPE_BACK, true);
	player = new Player;
	bubble = new Bubble;
	ui = new UI;
	enemy.emplace_back(0,150);
	enemy.emplace_back(100,150);
	enemy.emplace_back(200,150);
	int MapCount = 0;
	Score = 0;
	for (int i = 0; i < MAP_COUNT; i++) {
		int imagework;
		imagework = StageImages::Image[LoadMapImage[MapCount][i]];
		float work[MAP_SIZE];
		for (int j = 0; j < MAP_SIZE; j++) {
			work[j] = LoadMap[MapCount][i][j];
		}
		// �ǂݍ��񂾍��W���㉺�A���E�����Ăǂ���Ƃ�0���傫���Ȃ瑫��ɏ���n��
		if (work[0] + work[2] > 0 && work[1] + work[3] > 0) {
			stage.emplace_back(work[0], work[1], work[2], work[3],imagework);
		}
	}

	NowScore = 0;
	HighScore = 10000;

	Pause = false;
	LifeImg = LoadGraph("Resources/images/UI/UI_Stock.png");

}

GameMain::~GameMain()				// ������delete�Ȃǂ�����
{
	StopSoundMem(Sounds::BGM_Trip);
}

AbstractScene* GameMain::Update()	// �����ŃQ�[�����C���̍X�V������
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

void GameMain::Draw() const			// �����ŃQ�[�����C���̕`��
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

	for (size_t i = 0; i < enemy.size(); i++) {
		enemy.at(i).Draw();
	}

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

void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
{
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

	// ��ʉ��ɍs�����ꍇ�~�X
	if (player->GetY() > SCREEN_HEIGHT && !player->GetSpawnFlg()) {
		player->SetSpawnFlg(true);
		StopSoundMem(Sounds::SE_Falling);
		splash.emplace_back(player->GetX());
	}
	if (player->GetLife() <= 0) {
		ui->GameOver();
	}
	clsDx();/////////////////////////////////////////////////////////////
	for (size_t i = 0; i < enemy.size(); i++) {
		enemy.at(i).Update();
		for (size_t j = 0; j < stage.size(); j++) {
			if (enemy.at(i).IsFly(stage.at(j))) {
				break;
			}
		}
		if (player->GetFlg()) {
			enemy.at(i).ChangeInertia(*player, player->HitEnemy(enemy.at(i)));
		}
		for (size_t j = 0; j < enemy.size(); j++) {
			enemy.at(i).ChangeInertia(enemy.at(j), enemy.at(j).HitEnemy(enemy.at(i)));
		}
		if (enemy.at(i).GetY() > SCREEN_HEIGHT) {
			splash.emplace_back(enemy.at(i).GetX());
			enemy.at(i).SetFlg(false);
		}
		if (!enemy.at(i).GetFlg()) {
			enemy.erase(enemy.begin() + i);
			continue;
		}
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
		if (!bubble->GetFlg()) {		// ��ʊO�ɍs�����Ȃ�delete����nullptr
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
