#include "GameMain.h"
#include "Map.h"
GameMain::GameMain(int _score, int _stage)				// �����ŏ�����
{
	Sounds::LoadSounds();
	StageImages::LoadImages();
	SetSoundCurrentTime(0.0f, Sounds::BGM_Trip);
	PlaySoundMem(Sounds::BGM_Trip, DX_PLAYTYPE_BACK, true);
	player = new Player;
	ui = new UI;
	enemy.emplace_back(0,150);
	enemy.emplace_back(100,150);
	enemy.emplace_back(200,150);
	StageNum = _stage;
	if (StageNum > 4) {
		StageNum = 0;
	}
	Score = _score;
	for (int i = 0; i < MAP_COUNT; i++) {
		int imagework;
		imagework = StageImages::Image[LoadMapImage[StageNum][i]];
		float work[MAP_SIZE];
		for (int j = 0; j < MAP_SIZE; j++) {
			work[j] = LoadMap[StageNum][i][j];
		}
		// �ǂݍ��񂾍��W���㉺�A���E�����Ăǂ���Ƃ�0���傫���Ȃ瑫��ɏ���n��
		if (work[0] + work[2] > 0 && work[1] + work[3] > 0) {
			stage.emplace_back(work[0], work[1], work[2], work[3],imagework);
		}
	}

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
		return new GameMain(Score,++StageNum);
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

			DrawGraph(150 - (15 * i), 30, LifeImg, TRUE);
		}
	}

	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}

	player->Draw();

	for (size_t i = 0; i < enemy.size(); i++) {
		enemy.at(i).Draw();
	}


	for (size_t i = 0; i < bubble.size(); i++) {
		bubble.at(i).Draw();
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
		if (enemy.at(i).GetY() > SCREEN_HEIGHT - 24) {
			splash.emplace_back(enemy.at(i).GetX());
			bubble.emplace_back(enemy.at(i).GetX());
			enemy.at(i).SetFlg(false);
		}
		if (!enemy.at(i).GetFlg()) {
			enemy.erase(enemy.begin() + i);
			continue;
		}
	}

	for (size_t i = 0; i < bubble.size(); i++) {
		if (player->HitBox(bubble.at(i)) && !bubble.at(i).GetHitFlg()) {
			Score += 500;
			scoreUP.emplace_back(500, player->GetX(), player->GetY());
			PlaySoundMem(Sounds::SE_Bubble, DX_PLAYTYPE_BACK, true);
			bubble.at(i).SetHitFlg(true);
		}
		if (bubble.at(i).GetHitFlg()) {
			if (bubble.at(i).PlayAnim()) {
				bubble.erase(bubble.begin() + i);
				continue;
			}
		}
	}

	for (size_t i = 0; i < bubble.size(); i++) {
		bubble.at(i).Update();
		if (!bubble.at(i).GetFlg()) {
			bubble.erase(bubble.begin() + i);
			continue;
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

	ui->Update(Score,StageNum + 1);

}
