#include "GameMain.h"
#include "Map.h"
#include "UI.h"

GameMain::GameMain()				// �����ŏ�����
{
	player = new Player;
	bubble = new Bubble;
	int MapCount = 0;
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

	NowScore = 0;
	HighScore = 10000;

	PlayerLife = 0;

	Stage = 1;
	PhaseCount = 0;
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
	//�X�R�A
	DrawString(20,10,"I-",0xff0000);
	DrawFormatString(40, 10, 0xFFFFFF, "%06d", NowScore);

	DrawString(270, 10, "TOP-", 0xffa500);
	DrawFormatString(310, 10, 0xFFFFFF, "%06d", HighScore);

	

	if (PlayerLife == 3) {
		DrawBox(60, 30, 70, 40, 0xFF0000, TRUE);
		DrawBox(75, 30, 85, 40, 0xFF0000, TRUE);
	}

	if (PlayerLife == 2) {
		DrawBox(75, 30, 85, 40, 0xFF0000, TRUE);
	}

	if (!PhaseFlg) {
	DrawFormatString(290, 30, 0xffa500, "PHASE-%d", Stage);
	}

	if (PlayerLife == 0) {
		DrawString(280, 230, "GameOver", 0xffffff);
	}

	player->Draw();
	bubble->Draw();
	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}
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

	bubble->Update();

	if (PhaseCount < 240) {
		PhaseCount++;
		if (PhaseCount % 20 < 10) {
			PhaseFlg = true;
		}
		else {
			PhaseFlg = false;
		}
	}

	//�n�C�X�R�A���X�V
	if (NowScore > HighScore) {
		HighScore = NowScore;
	}

}
