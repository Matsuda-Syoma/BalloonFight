#include "GameMain.h"
#include "Map.h"

GameMain::GameMain()				// �����ŏ�����
{
	Sounds::LoadSounds();
	player = new Player;
	bubble = new Bubble;
	ui = new UI;
	int MapCount = 0;
	Score = 0;
	for (int i = 0; i < MAP_COUNT; i++) {
		float work[MAP_SIZE];
		for (int j = 0; j < MAP_SIZE; j++) {
			work[j] = LoadMap[MapCount][i][j];
		}

		// �ǂݍ��񂾍��W���㉺�A���E�����Ăǂ���Ƃ�0���傫���Ȃ瑫��ɏ���n��
		if (work[0] + work[2] > 0 && work[1] + work[3] > 0) {
			stage.emplace_back(work[0], work[1], work[2], work[3]);
		}
	}
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
		for (int i = 0; i < PlayerLife; i++) {
			DrawBox(60 + (15 * i), 30, 70 + (15 * i)
				, 40, 0xFF0000, TRUE);
		}
	}


	player->Draw();

	if (bubble != nullptr) {
		bubble->Draw();
	}

	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}

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

	if (bubble != nullptr) {
		if (player->HitBox(*bubble)) {
			delete bubble;
			bubble = nullptr;
			Score += 500;
		}
	}

	if (bubble != nullptr) {
		bubble->Update();
		if (!bubble->GetFlg()) {		// ��ʊO�ɍs�����Ȃ�delete����nullptr
			delete bubble;
			bubble = nullptr;
		}
	}

	ui->Update(Score);

}
