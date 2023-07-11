#include "GameMain.h"
#include "Map.h"

GameMain::GameMain()				// �����ŏ�����
{
	Sounds::LoadSounds();
	StageImages::LoadImages();
	//printfDx("%d %d", StageImages::Image[0], LoadMapImage[0][0]);
	PlaySoundMem(Sounds::BGM_Trip, DX_PLAYTYPE_BACK, true);
	player = new Player;
	bubble = new Bubble;
	ui = new UI;
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

	LifeImg = LoadGraph("Resources/images/UI/UI_Stock.png");

}

GameMain::~GameMain()				// ������delete�Ȃǂ�����
{
}

AbstractScene* GameMain::Update()	// �����ŃQ�[�����C���̍X�V������
{

	
	Game();
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


	player->Draw();

	if (bubble != nullptr) {
		bubble->Draw();
	}

	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}

	for (size_t i = 0; i < scoreUP.size(); i++) {
		scoreUP.at(i).Draw();
	}

	DrawGraph(160,444,StageImages::Image[4],true);

	ui->Draw();
}

void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
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

	if (player->GetLife() <= 0) {
		ui->GameOver();
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

	ui->Update(Score);

}
