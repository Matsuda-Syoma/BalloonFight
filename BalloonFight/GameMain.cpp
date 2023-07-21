#include "GameMain.h"
#include "Map.h"
GameMain::GameMain(int _score, int _stage, int _life)				// �����ŏ�����
{
	StageSwitch = false;
	StageSwitchTime = 0;
	Sounds::LoadSounds();
	StageImages::LoadImages();
	SetSoundCurrentTime(0.0f, Sounds::BGM_Trip);
	player = new Player;
	player->SetLife(_life);
	ui = new UI;
	fish = new Fish(0,0);
	thunder = new Thunder;
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
		Sounds::AllStop();
		return new GameMain(Score,++StageNum,player->GetLife());
	}
	if (!Pause) {
		Game();
	}
	if (StageSwitch) {
		Pause = true;
		Sounds::AllStop();
		PlaySoundMem(Sounds::SE_StageClear, DX_PLAYTYPE_BACK, false);
		if (++StageSwitchTime > 120) {
			return new GameMain(Score, ++StageNum,player->GetLife());
		}
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

	thunder->Draw();

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
	if (CheckSoundMem(Sounds::BGM_Trip) == 0) {
		PlaySoundMem(Sounds::BGM_Trip, DX_PLAYTYPE_BACK, true);
	}
	
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

	// �G�̏���
	for (size_t i = 0; i < enemy.size(); i++) {
		enemy.at(i).Update();
		if (!enemy.at(i).GetDeathFlg()) {
			// �G�ƃX�e�[�W�̓����蔻��
			for (size_t j = 0; j < stage.size(); j++) {
				if (enemy.at(i).IsFly(stage.at(j))) {
					break;
				}
			}
			// �G���m���˕Ԃ�悤�ɂ���
			for (size_t j = 0; j < enemy.size(); j++) {
				if (!enemy.at(j).GetDeathFlg()) {
					enemy.at(i).ChangeInertia(enemy.at(j), enemy.at(j).HitEnemy(enemy.at(i)));
				}

			}
			// �v���C���[�̃t���O�������Ă���Ȃ瓖���蔻�肪����
			if (player->GetFlg()) {
				int Hit = player->HitEnemy(enemy.at(i),enemy.at(i).GetState());
				if (Hit != 0) {
					if (Hit != 5) {
						if (enemy.at(i).GetBalloon() != 0) {
							enemy.at(i).ChangeInertia(*player, Hit);
						}
						
						if (player->DamageCheck(enemy.at(i), enemy.at(i).GetBalloon(), enemy.at(i).GetState())) {
							if (enemy.at(i).GetBalloon() != 0) {
								Score += 500;
								scoreUP.emplace_back(500, player->GetX(), player->GetY());
							}
							else {
								Score += 1000;
								scoreUP.emplace_back(1000, player->GetX(), player->GetY());
							}
							enemy.at(i).BallonBreak(1);
						}
					}
					// �n�ʂɗ����Ă���Ƃ��͒��˕Ԃ炸�ɓ|���
					else {
						Score += 750;
						scoreUP.emplace_back(750, player->GetX(), player->GetY());
						enemy.at(i).BallonBreak(1);
					}
				}
			}
		}

		if (enemy.at(i).GetBalloon() != 0) {
			parachuteflg = false;
		}
		else {
			parachuteflg = true;
			continue;
		}
		// ��ʊO�ɍs�����炵�Ԃ��ƖA���ł�
		if (enemy.at(i).GetY() > SCREEN_HEIGHT - 24) {
			splash.emplace_back(enemy.at(i).GetX());
			bubble.emplace_back(enemy.at(i).GetX());
			enemy.at(i).SetFlg(false);
		}
		// �t���O�������ĂȂ��Ȃ�폜
		if (!enemy.at(i).GetFlg()) {
			enemy.erase(enemy.begin() + i);
			continue;
		}
	}
	if (parachuteflg) {
		if (CheckSoundMem(Sounds::SE_parachute) == 0) {
			PlaySoundMem(Sounds::SE_parachute, DX_PLAYTYPE_BACK, true);
		}
	}
	else {
		StopSoundMem(Sounds::SE_parachute);
	}

	StageSwitch = true;
	for (size_t i = 0; i < enemy.size(); i++) {
		if (!enemy.at(i).GetDeathFlg() && enemy.size() != 0) {
			StageSwitch = false;
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
	thunder->Update();

}
